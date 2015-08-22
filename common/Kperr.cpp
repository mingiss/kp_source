// ==================================================
// kperr.cpp
// error processing
//

// ======================================= definitions
#include "stdafx.h"

#include "envir.h"
#include "iBshn.h"
#include "lzdshn.h"

#if CompilerGr==Msvc
#include <afx.h>
#endif
#include <string.h>
#include <string>
// #include <iostream>
#include <fstream>
#include <time.h>
#if (CompilerGr==Msvc) || (__WATCOMC__ >= 1202) || ((Compiler == Mingw) && (MingwVer >= 471))
#include <WINSOCK2.H>
#endif
#include <windows.h>
#include <windowsx.h>

#if (CompilerGr != Watcom) && ((Compiler != Mingw) || (MingwVer < 471))
// #include <Winternl.h>
#include <ddk\ntapi.h>
#endif

#include <commctrl.h>
#include <richedit.h>
#include <Richole.h>
#if (Envir==MSWin32Con) || (Envir==MSWin32) || (Envir==MSWin32Mfc) || (Envir==MSWin32ConMfc)
#include <shellapi.h>
#endif
#if (Envir==MSWin32) || (Envir==MSWin32Mfc)
#include "res_com.h"
#endif
#include <stdio.h>

#ifdef IBSH_RES_MODE_XGECKO
#if CompilerGr==Mingw
#include "IInputStream.hh"
#include "IString.hh"
#include "XApplication.hh"
#include "XGecko.hh"
#include "XGeckoDOMEvent.hh"
#include "XGeckoInit.hh"
#endif
#endif

#if Compiler != Watcom
using namespace std;
#endif

#include "kpstdlib.h"
#include "kperrno.h"
#include "kptt.h"
#include "kptree.h"
#include "kpcolors.h"
#include "kpfonts.h"
#include "kpmsg.h"
#include "kpmsg_en.h"
#include "kpmsg_lt.h"
#include "kpmsg_pl_1250.h"
#include "kpmsg_pl_1257.h"
#include "kpmsg_ru.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpstdio.h"
#include "kpttucf.h"
#include "res_com.h"
#include "tvxml.h"
#include "kpwindow.h"
#include "kpsock.h"
#include "kperr.h"
#include "kphp11y.h"
#include "kphp11i.h"
#include "kphp11t.h"
#include "kphp11m.h"
#include "kpcapp.h"
#include "tvmain.h"
#include "tvrtf.h"
#include "tvrtfo.h"
#include "tvtex.h"
#include "tvxml.h"
#include "xmlp.h"
#include "xmlh.h"
#include "xmlf.h"
#include "xml8.h"
#include "xmlu.h"
#include "xmlo1.h"
#include "xmlt.h"
#include "xmlis.h"
#include "xmli.h"
#include "KpFileSys.h"
#include "KpPubDlg.h"
#include "xmln.h"
#include "kpstap.h"

// #define TEST_DIAG_MSG // SendDiagMsg() debuginimui, nieko nesiunèia ir netrina siuntimo failo KpDiagMsgPost.txt


// ------------------------------------ bendri kp programø praneðimai
const unsigned char *lpszaKpMessages[NumOfKpMessages_23][KpNumOfLangs_2] =
{
KP_MSG_TITLE_EN,                    KP_MSG_TITLE_LT,                    KP_MSG_TITLE_PL_1250,                     KP_MSG_TITLE_PL_1257,                     KP_MSG_TITLE_RU,                    KP_MSG_TITLE_EN,                    // "Praneðimas"
KP_INPUT_TITLE_EN,                  KP_INPUT_TITLE_LT,                  KP_INPUT_TITLE_PL_1250,                   KP_INPUT_TITLE_PL_1257,                   KP_INPUT_TITLE_RU,                  KP_INPUT_TITLE_EN,                  // "Ávedimas"

KP_MSG_TAIP_EN,                     KP_MSG_TAIP_LT,                     KP_MSG_TAIP_PL_1250,                      KP_MSG_TAIP_PL_1257,                      KP_MSG_TAIP_RU,                     KP_MSG_TAIP_EN,                     // "Taip"
KP_MSG_YES_EN,                      KP_MSG_YES_LT,                      KP_MSG_YES_PL_1250,                       KP_MSG_YES_PL_1257,                       KP_MSG_YES_RU,                      KP_MSG_YES_EN,                      // KP_MSG_TAIP
KP_MSG_NE_EN,                       KP_MSG_NE_LT,                       KP_MSG_NE_PL_1250,                        KP_MSG_NE_PL_1257,                        KP_MSG_NE_RU,                       KP_MSG_NE_EN,                       // "Ne"
KP_MSG_NO_EN,                       KP_MSG_NO_LT,                       KP_MSG_NO_PL_1250,                        KP_MSG_NO_PL_1257,                        KP_MSG_NO_RU,                       KP_MSG_NO_EN,                       // KP_MSG_NE
KP_MSG_GERAI_EN,                    KP_MSG_GERAI_LT,                    KP_MSG_GERAI_PL_1250,                     KP_MSG_GERAI_PL_1257,                     KP_MSG_GERAI_RU,                    KP_MSG_GERAI_EN,                    // "Gerai"
KP_MSG_OK_EN,                       KP_MSG_OK_LT,                       KP_MSG_OK_PL_1250,                        KP_MSG_OK_PL_1257,                        KP_MSG_OK_RU,                       KP_MSG_OK_EN,                       // KP_MSG_GERAI
KP_MSG_ATSAUKTI_EN,                 KP_MSG_ATSAUKTI_LT,                 KP_MSG_ATSAUKTI_PL_1250,                  KP_MSG_ATSAUKTI_PL_1257,                  KP_MSG_ATSAUKTI_RU,                 KP_MSG_ATSAUKTI_EN,                 // "Atðaukti"
KP_MSG_CANCEL_EN,                   KP_MSG_CANCEL_LT,                   KP_MSG_CANCEL_PL_1250,                    KP_MSG_CANCEL_PL_1257,                    KP_MSG_CANCEL_RU,                   KP_MSG_CANCEL_EN,                   // KP_MSG_ATSAUKTI
KP_MSG_TESTI_EN,                    KP_MSG_TESTI_LT,                    KP_MSG_TESTI_PL_1250,                     KP_MSG_TESTI_PL_1257,                     KP_MSG_TESTI_RU,                    KP_MSG_TESTI_EN,                    // "Toliau"
KP_MSG_BAIGTI_EN,                   KP_MSG_BAIGTI_LT,                   KP_MSG_BAIGTI_PL_1250,                    KP_MSG_BAIGTI_PL_1257,                    KP_MSG_BAIGTI_RU,                   KP_MSG_BAIGTI_EN,                   // "Baigti"
KP_MSG_PAMIRSAU_SLAPTAZODI_EN,      KP_MSG_PAMIRSAU_SLAPTAZODI_LT,      KP_MSG_PAMIRSAU_SLAPTAZODI_PL_1250,       KP_MSG_PAMIRSAU_SLAPTAZODI_PL_1257,       KP_MSG_PAMIRSAU_SLAPTAZODI_RU,      KP_MSG_PAMIRSAU_SLAPTAZODI_EN,      // "Pamirðau slaptaþodá"

KP_MSG_ERROR_EN,                    KP_MSG_ERROR_LT,                    KP_MSG_ERROR_PL_1250,                     KP_MSG_ERROR_PL_1257,                     KP_MSG_ERROR_RU,                    KP_MSG_ERROR_RU,                    // "Klaida"
KP_MSG_WARNING_EN,                  KP_MSG_WARNING_LT,                  KP_MSG_WARNING_PL_1250,                   KP_MSG_WARNING_PL_1257,                   KP_MSG_WARNING_RU,                  KP_MSG_WARNING_RU,                  // "Perspëjimas"
KP_MSG_FILE_LINE_EN,                KP_MSG_FILE_LINE_LT,                KP_MSG_FILE_LINE_PL_1250,                 KP_MSG_FILE_LINE_PL_1257,                 KP_MSG_FILE_LINE_RU,                KP_MSG_FILE_LINE_RU,                // ", failas:%s, eilutë:%d"
KP_MSG_ENTRY_ID_EN,                 KP_MSG_ENTRY_ID_LT,                 KP_MSG_ENTRY_ID_PL_1250,                  KP_MSG_ENTRY_ID_PL_1257,                  KP_MSG_ENTRY_ID_RU,                 KP_MSG_ENTRY_ID_RU,                 // ", Áraðo nr.:%ld"
KP_MSG_ENTRY_EN,                    KP_MSG_ENTRY_LT,                    KP_MSG_ENTRY_PL_1250,                     KP_MSG_ENTRY_PL_1257,                     KP_MSG_ENTRY_RU,                    KP_MSG_ENTRY_RU,                    // ", Áraðas: %s"

KP_MSG_NO_STANDARD_PROG_EN,         KP_MSG_NO_STANDARD_PROG_LT,         KP_MSG_NO_STANDARD_PROG_PL_1250,          KP_MSG_NO_STANDARD_PROG_PL_1257,          KP_MSG_NO_STANDARD_PROG_RU,         KP_MSG_NO_STANDARD_PROG_RU,         // "Nerasta programa skirta atverti ðio tipo failus"
KP_MSG_WND_NOT_FOUND_EN,            KP_MSG_WND_NOT_FOUND_LT,            KP_MSG_WND_NOT_FOUND_PL_1250,             KP_MSG_WND_NOT_FOUND_PL_1257,             KP_MSG_WND_NOT_FOUND_RU,            KP_MSG_WND_NOT_FOUND_RU,            // "Langas nerastas"
KP_MSG_PID_NOT_FOUND_EN,            KP_MSG_PID_NOT_FOUND_LT,            KP_MSG_PID_NOT_FOUND_PL_1250,             KP_MSG_PID_NOT_FOUND_PL_1257,             KP_MSG_PID_NOT_FOUND_RU,            KP_MSG_PID_NOT_FOUND_RU,            // "Nerastas proceso identifikatorius"
KP_MSG_NO_SOCKET_EN,                KP_MSG_NO_SOCKET_LT,                KP_MSG_NO_SOCKET_PL_1250,                 KP_MSG_NO_SOCKET_PL_1257,                 KP_MSG_NO_SOCKET_RU,                KP_MSG_NO_SOCKET_RU,                // "Jungtis dar nesukurta"
KP_MSG_SOCK_UNRESOLVED_EN,          KP_MSG_SOCK_UNRESOLVED_LT,          KP_MSG_SOCK_UNRESOLVED_PL_1250,           KP_MSG_SOCK_UNRESOLVED_PL_1257,           KP_MSG_SOCK_UNRESOLVED_RU,          KP_MSG_SOCK_UNRESOLVED_RU,          // "Tarnybines stoties adresas dar nesurastas"

KP_MSG_ERR_OK_EN,                   KP_MSG_ERR_OK_LT,                   KP_MSG_ERR_OK_PL_1250,                    KP_MSG_ERR_OK_PL_1257,                    KP_MSG_ERR_OK_RU,                   KP_MSG_ERR_OK_RU,                   // "Operacija atlikta sëkmingai" // !!!
KP_MSG_INVALIDARG_EN,               KP_MSG_INVALIDARG_LT,               KP_MSG_INVALIDARG_PL_1250,                KP_MSG_INVALIDARG_PL_1257,                KP_MSG_INVALIDARG_RU,               KP_MSG_INVALIDARG_RU,               // "Neteisingi parametrai"
KP_MSG_NOTIMPL_EN,                  KP_MSG_NOTIMPL_LT,                  KP_MSG_NOTIMPL_PL_1250,                   KP_MSG_NOTIMPL_PL_1257,                   KP_MSG_NOTIMPL_RU,                  KP_MSG_NOTIMPL_RU,                  // "Priedas neádiegtas"
KP_MSG_UNEXPECTED_EN,               KP_MSG_UNEXPECTED_LT,               KP_MSG_UNEXPECTED_PL_1250,                KP_MSG_UNEXPECTED_PL_1257,                KP_MSG_UNEXPECTED_RU,               KP_MSG_UNEXPECTED_RU,               // "Netikëtas kreipinys á sàsajà"
KP_MSG_FERROR_EN,                   KP_MSG_FERROR_LT,                   KP_MSG_FERROR_PL_1250,                    KP_MSG_FERROR_PL_1257,                    KP_MSG_FERROR_RU,                   KP_MSG_FERROR_RU,                   // "Failo skaitymo/raðymo klaida"
KP_MSG_SYSTEM_ERROR_EN,             KP_MSG_SYSTEM_ERROR_LT,             KP_MSG_SYSTEM_ERROR_PL_1250,              KP_MSG_SYSTEM_ERROR_PL_1257,              KP_MSG_SYSTEM_ERROR_RU,             KP_MSG_SYSTEM_ERROR_RU,             // "Klaida sistemoje"
KP_MSG_EOF_EN,                      KP_MSG_EOF_LT,                      KP_MSG_EOF_PL_1250,                       KP_MSG_EOF_PL_1257,                       KP_MSG_EOF_RU,                      KP_MSG_EOF_RU,                      // "Neteisinga failo pabaiga"
KP_MSG_FILE_FORMAT_EN,              KP_MSG_FILE_FORMAT_LT,              KP_MSG_FILE_FORMAT_PL_1250,               KP_MSG_FILE_FORMAT_PL_1257,               KP_MSG_FILE_FORMAT_RU,              KP_MSG_FILE_FORMAT_RU,              // "Neteisingas failo formatas"
KP_MSG_FILE_NOT_FOUND_EN,           KP_MSG_FILE_NOT_FOUND_LT,           KP_MSG_FILE_NOT_FOUND_PL_1250,            KP_MSG_FILE_NOT_FOUND_PL_1257,            KP_MSG_FILE_NOT_FOUND_RU,           KP_MSG_FILE_NOT_FOUND_RU,           // "Failas nerastas"
KP_MSG_DIR_ERROR_EN,                KP_MSG_DIR_ERROR_LT,                KP_MSG_DIR_ERROR_PL_1250,                 KP_MSG_DIR_ERROR_PL_1257,                 KP_MSG_DIR_ERROR_RU,                KP_MSG_DIR_ERROR_RU,                // "Nepavyko atverti/sukurti failo"
KP_MSG_OUTOFMEM_EN,                 KP_MSG_OUTOFMEM_LT,                 KP_MSG_OUTOFMEM_PL_1250,                  KP_MSG_OUTOFMEM_PL_1257,                  KP_MSG_OUTOFMEM_RU,                 KP_MSG_OUTOFMEM_RU,                 // "Trûksta atminties"
KP_MSG_NO_FILE_EN,                  KP_MSG_NO_FILE_LT,                  KP_MSG_NO_FILE_PL_1250,                   KP_MSG_NO_FILE_PL_1257,                   KP_MSG_NO_FILE_RU,                  KP_MSG_NO_FILE_RU,                  // "Failas neatvertas"
KP_MSG_DOUBLE_UNGET_EN,             KP_MSG_DOUBLE_UNGET_LT,             KP_MSG_DOUBLE_UNGET_PL_1250,              KP_MSG_DOUBLE_UNGET_PL_1257,              KP_MSG_DOUBLE_UNGET_RU,             KP_MSG_DOUBLE_UNGET_RU,             // "Dvigubas ávedimo gràþinimas"
KP_MSG_UNKN_CHR_EN,                 KP_MSG_UNKN_CHR_LT,                 KP_MSG_UNKN_CHR_PL_1250,                  KP_MSG_UNKN_CHR_PL_1257,                  KP_MSG_UNKN_CHR_RU,                 KP_MSG_UNKN_CHR_RU,                 // "Neatpaþintas simbolis"
KP_MSG_COMMAND_ERROR_EN,            KP_MSG_COMMAND_ERROR_LT,            KP_MSG_COMMAND_ERROR_PL_1250,             KP_MSG_COMMAND_ERROR_PL_1257,             KP_MSG_COMMAND_ERROR_RU,            KP_MSG_COMMAND_ERROR_RU,            // "Iðorinë klaida"
KP_MSG_BUFFER_OVERFLOW_EN,          KP_MSG_BUFFER_OVERFLOW_LT,          KP_MSG_BUFFER_OVERFLOW_PL_1250,           KP_MSG_BUFFER_OVERFLOW_PL_1257,           KP_MSG_BUFFER_OVERFLOW_RU,          KP_MSG_BUFFER_OVERFLOW_RU,          // "Persipildë buferis"
KP_MSG_FONT_UNDEF_EN,               KP_MSG_FONT_UNDEF_LT,               KP_MSG_FONT_UNDEF_PL_1250,                KP_MSG_FONT_UNDEF_PL_1257,                KP_MSG_FONT_UNDEF_RU,               KP_MSG_FONT_UNDEF_RU,               // "Neapibrëþtas ðriftas"
KP_MSG_KWD_NOT_FOUND_EN,            KP_MSG_KWD_NOT_FOUND_LT,            KP_MSG_KWD_NOT_FOUND_PL_1250,             KP_MSG_KWD_NOT_FOUND_PL_1257,             KP_MSG_KWD_NOT_FOUND_RU,            KP_MSG_KWD_NOT_FOUND_RU,            // "Raktinis þodis nerastas"
KP_MSG_UNKNOWN_SYSTEM_EN,           KP_MSG_UNKNOWN_SYSTEM_LT,           KP_MSG_UNKNOWN_SYSTEM_PL_1250,            KP_MSG_UNKNOWN_SYSTEM_PL_1257,            KP_MSG_UNKNOWN_SYSTEM_RU,           KP_MSG_UNKNOWN_SYSTEM_RU,           // "Operacinë sistema neatpaþinta"
KP_MSG_ILL_CODE_EN,                 KP_MSG_ILL_CODE_LT,                 KP_MSG_ILL_CODE_PL_1250,                  KP_MSG_ILL_CODE_PL_1257,                  KP_MSG_ILL_CODE_RU,                 KP_MSG_ILL_CODE_RU,                 // "Klaidingas registracijos kodas"
KP_MSG_CANCELLED_EN,                KP_MSG_CANCELLED_LT,                KP_MSG_CANCELLED_PL_1250,                 KP_MSG_CANCELLED_PL_1257,                 KP_MSG_CANCELLED_RU,                KP_MSG_CANCELLED_RU,                // "Operacija nutraukta"
KP_MSG_DOUBLE_CALL_EN,              KP_MSG_DOUBLE_CALL_LT,              KP_MSG_DOUBLE_CALL_PL_1250,               KP_MSG_DOUBLE_CALL_PL_1257,               KP_MSG_DOUBLE_CALL_RU,              KP_MSG_DOUBLE_CALL_RU,              // "Dvigubas iðkvietimas"
KP_MSG_TIMEOUT_EN,                  KP_MSG_TIMEOUT_LT,                  KP_MSG_TIMEOUT_PL_1250,                   KP_MSG_TIMEOUT_PL_1257,                   KP_MSG_TIMEOUT_RU,                  KP_MSG_TIMEOUT_RU,                  // "Virðytas laukimo laikas"
KP_MSG_OBJ_NOT_FOUND_EN,            KP_MSG_OBJ_NOT_FOUND_LT,            KP_MSG_OBJ_NOT_FOUND_PL_1250,             KP_MSG_OBJ_NOT_FOUND_PL_1257,             KP_MSG_OBJ_NOT_FOUND_RU,            KP_MSG_OBJ_NOT_FOUND_RU,            // "Objektas nerastas"
KP_MSG_NO_CONN_EN,                  KP_MSG_NO_CONN_LT,                  KP_MSG_NO_CONN_PL_1250,                   KP_MSG_NO_CONN_PL_1257,                   KP_MSG_NO_CONN_RU,                  KP_MSG_NO_CONN_RU,                  // "Nëra ryðio"

KP_MSG_TRANS_ERR_EN,                KP_MSG_TRANS_ERR_LT,                KP_MSG_TRANS_ERR_PL_1250,                 KP_MSG_TRANS_ERR_PL_1257,                 KP_MSG_TRANS_ERR_RU,                KP_MSG_TRANS_ERR_RU,                // "Perdavimo klaida"
KP_MSG_TRANS_ERR_1_EN,              KP_MSG_TRANS_ERR_1_LT,              KP_MSG_TRANS_ERR_1_PL_1250,               KP_MSG_TRANS_ERR_1_PL_1257,               KP_MSG_TRANS_ERR_1_RU,              KP_MSG_TRANS_ERR_1_RU,              // "Ryðio klaida, pakartokite siuntimo procedûrà"

KP_MSG_REFUSED_EN,                  KP_MSG_REFUSED_LT,                  KP_MSG_REFUSED_PL_1250,                   KP_MSG_REFUSED_PL_1257,                   KP_MSG_REFUSED_RU,                  KP_MSG_REFUSED_RU,                  // "Registracija atmesta"
KP_MSG_ACCESS_DENIED_EN,            KP_MSG_ACCESS_DENIED_LT,            KP_MSG_ACCESS_DENIED_PL_1250,             KP_MSG_ACCESS_DENIED_PL_1257,             KP_MSG_ACCESS_DENIED_RU,            KP_MSG_ACCESS_DENIED_RU,            // "Neleista prisijungti"
KP_MSG_ILLEGAL_CHARACTER_EN,        KP_MSG_ILLEGAL_CHARACTER_LT,        KP_MSG_ILLEGAL_CHARACTER_PL_1250,         KP_MSG_ILLEGAL_CHARACTER_PL_1257,         KP_MSG_ILLEGAL_CHARACTER_RU,        KP_MSG_ILLEGAL_CHARACTER_RU,        // "Neleistinas simbolis"
KP_MSG_DIV_ZERO_EN,                 KP_MSG_DIV_ZERO_LT,                 KP_MSG_DIV_ZERO_PL_1250,                  KP_MSG_DIV_ZERO_PL_1257,                  KP_MSG_DIV_ZERO_RU,                 KP_MSG_DIV_ZERO_RU,                 // "Dalyba ið nulio"
KP_MSG_ILLMATHARG_EN,               KP_MSG_ILLMATHARG_LT,               KP_MSG_ILLMATHARG_PL_1250,                KP_MSG_ILLMATHARG_PL_1257,                KP_MSG_ILLMATHARG_RU,               KP_MSG_ILLMATHARG_RU,               // "Neleistinas matematinës funkcijos argumentas" // "Ðaknis ið neigiamo skaièiaus"
KP_MSG_ILLFUNC_EN,                  KP_MSG_ILLFUNC_LT,                  KP_MSG_ILLFUNC_PL_1250,                   KP_MSG_ILLFUNC_PL_1257,                   KP_MSG_ILLFUNC_RU,                  KP_MSG_ILLFUNC_RU,                  // "Neleistina operacija" // illegal function call (at the moment)

KP_MSG_NOTINST_EN,                  KP_MSG_NOTINST_LT,                  KP_MSG_NOTINST_PL_1250,                   KP_MSG_NOTINST_PL_1257,                   KP_MSG_NOTINST_RU,                  KP_MSG_NOTINST_RU,                  // "Programa neádiegta arba diegimas sugedo, pakartokite diegimo procedûrà"
KP_MSG_NOTINST_S_EN,                KP_MSG_NOTINST_S_LT,                KP_MSG_NOTINST_S_PL_1250,                 KP_MSG_NOTINST_S_PL_1257,                 KP_MSG_NOTINST_S_RU,                KP_MSG_NOTINST_S_RU,                // "Produktas „%s“ neádiegtas arba jo diegimas sugedo, pakartokite diegimo procedûrà"
KP_MSG_NOTINST_DELETE_EN,           KP_MSG_NOTINST_DELETE_LT,           KP_MSG_NOTINST_DELETE_PL_1250,            KP_MSG_NOTINST_DELETE_PL_1257,            KP_MSG_NOTINST_DELETE_RU,           KP_MSG_NOTINST_DELETE_RU,           // "Produktas neádiegtas arba jo diegimas sugedo, produktà panaikinkite ir pakartokite diegimo procedûrà"

KP_MSG_MSG_FORMAT_EN,               KP_MSG_MSG_FORMAT_LT,               KP_MSG_MSG_FORMAT_PL_1250,                KP_MSG_MSG_FORMAT_PL_1257,                KP_MSG_MSG_FORMAT_RU,               KP_MSG_MSG_FORMAT_RU,               // "Neteisingas praneðimo formatas"
KP_MSG_OBSOLETE_EN,                 KP_MSG_OBSOLETE_LT,                 KP_MSG_OBSOLETE_PL_1250,                  KP_MSG_OBSOLETE_PL_1257,                  KP_MSG_OBSOLETE_RU,                 KP_MSG_OBSOLETE_RU,                 // "Pasenusi funkcija"
KP_MSG_ERROR_HELP_EN,               KP_MSG_ERROR_HELP_LT,               KP_MSG_ERROR_HELP_PL_1250,                KP_MSG_ERROR_HELP_PL_1257,                KP_MSG_ERROR_HELP_RU,               KP_MSG_ERROR_HELP_RU,               // ".  Dël techninës pagalbos kreipkitës elektroniniu paðtu, adresu tech@tev.lt, prie laiðko prikabinkite failà %s"
KP_MSG_ERROR_HELP_REST_EN,          KP_MSG_ERROR_HELP_REST_LT,          KP_MSG_ERROR_HELP_REST_PL_1250,           KP_MSG_ERROR_HELP_REST_PL_1257,           KP_MSG_ERROR_HELP_REST_RU,          KP_MSG_ERROR_HELP_REST_RU,          // ".  Dël techninës pagalbos kreipkitës elektroniniu paðtu, adresu tech@tev.lt, prie laiðko prikabinkite failà %s"
KP_MSG_WSAEACCES_EN,                KP_MSG_WSAEACCES_LT,                KP_MSG_WSAEACCES_PL_1250,                 KP_MSG_WSAEACCES_PL_1257,                 KP_MSG_WSAEACCES_RU,                KP_MSG_WSAEACCES_RU,                // "Teisës nesuteiktos"
KP_MSG_WSAEADDRINUSE_EN,            KP_MSG_WSAEADDRINUSE_LT,            KP_MSG_WSAEADDRINUSE_PL_1250,             KP_MSG_WSAEADDRINUSE_PL_1257,             KP_MSG_WSAEADDRINUSE_RU,            KP_MSG_WSAEADDRINUSE_RU,            // "Adresas jau naudojamas"
KP_MSG_WSAEADDRNOTAVAIL_EN,         KP_MSG_WSAEADDRNOTAVAIL_LT,         KP_MSG_WSAEADDRNOTAVAIL_PL_1250,          KP_MSG_WSAEADDRNOTAVAIL_PL_1257,          KP_MSG_WSAEADDRNOTAVAIL_RU,         KP_MSG_WSAEADDRNOTAVAIL_RU,         // "Praðomas adresas negali bûti priskirtas"
KP_MSG_WSAEAFNOSUPPORT_EN,          KP_MSG_WSAEAFNOSUPPORT_LT,          KP_MSG_WSAEAFNOSUPPORT_PL_1250,           KP_MSG_WSAEAFNOSUPPORT_PL_1257,           KP_MSG_WSAEAFNOSUPPORT_RU,          KP_MSG_WSAEAFNOSUPPORT_RU,          // "Adresø ðeimos grupë nepalaikoma protokolo"
KP_MSG_WSAEALREADY_EN,              KP_MSG_WSAEALREADY_LT,              KP_MSG_WSAEALREADY_PL_1250,               KP_MSG_WSAEALREADY_PL_1257,               KP_MSG_WSAEALREADY_RU,              KP_MSG_WSAEALREADY_RU,              // "Operacija jau vykdoma"
KP_MSG_WSAECONNABORTED_EN,          KP_MSG_WSAECONNABORTED_LT,          KP_MSG_WSAECONNABORTED_PL_1250,           KP_MSG_WSAECONNABORTED_PL_1257,           KP_MSG_WSAECONNABORTED_RU,          KP_MSG_WSAECONNABORTED_RU,          // "Programa iððaukë ryðio nutraukimà"
KP_MSG_WSAECONNREFUSED_EN,          KP_MSG_WSAECONNREFUSED_LT,          KP_MSG_WSAECONNREFUSED_PL_1250,           KP_MSG_WSAECONNREFUSED_PL_1257,           KP_MSG_WSAECONNREFUSED_RU,          KP_MSG_WSAECONNREFUSED_RU,          // "Susijungimas atmestas"
KP_MSG_WSAECONNRESET_EN,            KP_MSG_WSAECONNRESET_LT,            KP_MSG_WSAECONNRESET_PL_1250,             KP_MSG_WSAECONNRESET_PL_1257,             KP_MSG_WSAECONNRESET_RU,            KP_MSG_WSAECONNRESET_RU,            // "Sujungimas nutrauktas"
KP_MSG_WSAEDESTADDRREQ_EN,          KP_MSG_WSAEDESTADDRREQ_LT,          KP_MSG_WSAEDESTADDRREQ_PL_1250,           KP_MSG_WSAEDESTADDRREQ_PL_1257,           KP_MSG_WSAEDESTADDRREQ_RU,          KP_MSG_WSAEDESTADDRREQ_RU,          // "Bûtinas kreities adresas"
KP_MSG_WSAEFAULT_EN,                KP_MSG_WSAEFAULT_LT,                KP_MSG_WSAEFAULT_PL_1250,                 KP_MSG_WSAEFAULT_PL_1257,                 KP_MSG_WSAEFAULT_RU,                KP_MSG_WSAEFAULT_RU,                // "Neteisingas adresas"
KP_MSG_WSAEHOSTDOWN_EN,             KP_MSG_WSAEHOSTDOWN_LT,             KP_MSG_WSAEHOSTDOWN_PL_1250,              KP_MSG_WSAEHOSTDOWN_PL_1257,              KP_MSG_WSAEHOSTDOWN_RU,             KP_MSG_WSAEHOSTDOWN_RU,             // "Serveris laikinai neveikia"
KP_MSG_WSAEHOSTUNREACH_EN,          KP_MSG_WSAEHOSTUNREACH_LT,          KP_MSG_WSAEHOSTUNREACH_PL_1250,           KP_MSG_WSAEHOSTUNREACH_PL_1257,           KP_MSG_WSAEHOSTUNREACH_RU,          KP_MSG_WSAEHOSTUNREACH_RU,          // "Serveris nepasiekiamas"
KP_MSG_WSAEINPROGRESS_EN,           KP_MSG_WSAEINPROGRESS_LT,           KP_MSG_WSAEINPROGRESS_PL_1250,            KP_MSG_WSAEINPROGRESS_PL_1257,            KP_MSG_WSAEINPROGRESS_RU,           KP_MSG_WSAEINPROGRESS_RU,           // "Operacija vykdoma"
KP_MSG_WSAEINTR_EN,                 KP_MSG_WSAEINTR_LT,                 KP_MSG_WSAEINTR_PL_1250,                  KP_MSG_WSAEINTR_PL_1257,                  KP_MSG_WSAEINTR_RU,                 KP_MSG_WSAEINTR_RU,                 // "Funkcija nutraukta"
KP_MSG_WSAEINVAL_EN,                KP_MSG_WSAEINVAL_LT,                KP_MSG_WSAEINVAL_PL_1250,                 KP_MSG_WSAEINVAL_PL_1257,                 KP_MSG_WSAEINVAL_RU,                KP_MSG_WSAEINVAL_RU,                // "Neteisingi parametrai"
KP_MSG_WSAEISCONN_EN,               KP_MSG_WSAEISCONN_LT,               KP_MSG_WSAEISCONN_PL_1250,                KP_MSG_WSAEISCONN_PL_1257,                KP_MSG_WSAEISCONN_RU,               KP_MSG_WSAEISCONN_RU,               // "Susijungimas jau ávykæs"
KP_MSG_WSAEMFILE_EN,                KP_MSG_WSAEMFILE_LT,                KP_MSG_WSAEMFILE_PL_1250,                 KP_MSG_WSAEMFILE_PL_1257,                 KP_MSG_WSAEMFILE_RU,                KP_MSG_WSAEMFILE_RU,                // "Perdaug atvertø failø"
KP_MSG_WSAEMSGSIZE_EN,              KP_MSG_WSAEMSGSIZE_LT,              KP_MSG_WSAEMSGSIZE_PL_1250,               KP_MSG_WSAEMSGSIZE_PL_1257,               KP_MSG_WSAEMSGSIZE_RU,              KP_MSG_WSAEMSGSIZE_RU,              // "Perdaug ilgas praneðimas"
KP_MSG_WSAENETDOWN_EN,              KP_MSG_WSAENETDOWN_LT,              KP_MSG_WSAENETDOWN_PL_1250,               KP_MSG_WSAENETDOWN_PL_1257,               KP_MSG_WSAENETDOWN_RU,              KP_MSG_WSAENETDOWN_RU,              // "Tinklas neveikia"
KP_MSG_WSAENETRESET_EN,             KP_MSG_WSAENETRESET_LT,             KP_MSG_WSAENETRESET_PL_1250,              KP_MSG_WSAENETRESET_PL_1257,              KP_MSG_WSAENETRESET_RU,             KP_MSG_WSAENETRESET_RU,             // "Atsijungë nuo tinklo"
KP_MSG_WSAENETUNREACH_EN,           KP_MSG_WSAENETUNREACH_LT,           KP_MSG_WSAENETUNREACH_PL_1250,            KP_MSG_WSAENETUNREACH_PL_1257,            KP_MSG_WSAENETUNREACH_RU,           KP_MSG_WSAENETUNREACH_RU,           // "Tinklas nepasiekiamas"
KP_MSG_WSAENOBUFS_EN,               KP_MSG_WSAENOBUFS_LT,               KP_MSG_WSAENOBUFS_PL_1250,                KP_MSG_WSAENOBUFS_PL_1257,                KP_MSG_WSAENOBUFS_RU,               KP_MSG_WSAENOBUFS_RU,               // "Trûksta vietos buferyje"
KP_MSG_WSAENOPROTOOPT_EN,           KP_MSG_WSAENOPROTOOPT_LT,           KP_MSG_WSAENOPROTOOPT_PL_1250,            KP_MSG_WSAENOPROTOOPT_PL_1257,            KP_MSG_WSAENOPROTOOPT_RU,           KP_MSG_WSAENOPROTOOPT_RU,           // "Neteisinga protokolo parinktis"
KP_MSG_WSAENOTCONN_EN,              KP_MSG_WSAENOTCONN_LT,              KP_MSG_WSAENOTCONN_PL_1250,               KP_MSG_WSAENOTCONN_PL_1257,               KP_MSG_WSAENOTCONN_RU,              KP_MSG_WSAENOTCONN_RU,              // "Sujungimas nepavyko"
KP_MSG_WSAENOTSOCK_EN,              KP_MSG_WSAENOTSOCK_LT,              KP_MSG_WSAENOTSOCK_PL_1250,               KP_MSG_WSAENOTSOCK_PL_1257,               KP_MSG_WSAENOTSOCK_RU,              KP_MSG_WSAENOTSOCK_RU,              // "Socket operation on non-socket"
KP_MSG_WSAEOPNOTSUPP_EN,            KP_MSG_WSAEOPNOTSUPP_LT,            KP_MSG_WSAEOPNOTSUPP_PL_1250,             KP_MSG_WSAEOPNOTSUPP_PL_1257,             KP_MSG_WSAEOPNOTSUPP_RU,            KP_MSG_WSAEOPNOTSUPP_RU,            // "Operacija negali bûti atlikta"
KP_MSG_WSAEPFNOSUPPORT_EN,          KP_MSG_WSAEPFNOSUPPORT_LT,          KP_MSG_WSAEPFNOSUPPORT_PL_1250,           KP_MSG_WSAEPFNOSUPPORT_PL_1257,           KP_MSG_WSAEPFNOSUPPORT_RU,          KP_MSG_WSAEPFNOSUPPORT_RU,          // "Protokolo ðeima nepalaikoma"
KP_MSG_WSAEPROCLIM_EN,              KP_MSG_WSAEPROCLIM_LT,              KP_MSG_WSAEPROCLIM_PL_1250,               KP_MSG_WSAEPROCLIM_PL_1257,               KP_MSG_WSAEPROCLIM_RU,              KP_MSG_WSAEPROCLIM_RU,              // "Perdaug procesø"
KP_MSG_WSAEPROTONOSUPPORT_EN,       KP_MSG_WSAEPROTONOSUPPORT_LT,       KP_MSG_WSAEPROTONOSUPPORT_PL_1250,        KP_MSG_WSAEPROTONOSUPPORT_PL_1257,        KP_MSG_WSAEPROTONOSUPPORT_RU,       KP_MSG_WSAEPROTONOSUPPORT_RU,       // "Protokolas nepalaikomas"
KP_MSG_WSAEPROTOTYPE_EN,            KP_MSG_WSAEPROTOTYPE_LT,            KP_MSG_WSAEPROTOTYPE_PL_1250,             KP_MSG_WSAEPROTOTYPE_PL_1257,             KP_MSG_WSAEPROTOTYPE_RU,            KP_MSG_WSAEPROTOTYPE_RU,            // "Neteisingas protokolo sujungimo tipas"
KP_MSG_WSAESHUTDOWN_EN,             KP_MSG_WSAESHUTDOWN_LT,             KP_MSG_WSAESHUTDOWN_PL_1250,              KP_MSG_WSAESHUTDOWN_PL_1257,              KP_MSG_WSAESHUTDOWN_RU,             KP_MSG_WSAESHUTDOWN_RU,             // "Siuntimas nebegalimas, sujungimas nutrauktas"
KP_MSG_WSAESOCKTNOSUPPORT_EN,       KP_MSG_WSAESOCKTNOSUPPORT_LT,       KP_MSG_WSAESOCKTNOSUPPORT_PL_1250,        KP_MSG_WSAESOCKTNOSUPPORT_PL_1257,        KP_MSG_WSAESOCKTNOSUPPORT_RU,       KP_MSG_WSAESOCKTNOSUPPORT_RU,       // "Sujungimo tipas nepalaikomas"
KP_MSG_WSAETIMEDOUT_EN,             KP_MSG_WSAETIMEDOUT_LT,             KP_MSG_WSAETIMEDOUT_PL_1250,              KP_MSG_WSAETIMEDOUT_PL_1257,              KP_MSG_WSAETIMEDOUT_RU,             KP_MSG_WSAETIMEDOUT_RU,             // "Maksimalus sujungimo laukimo laikas virðytas"
KP_MSG_WSATYPE_NOT_FOUND_EN,        KP_MSG_WSATYPE_NOT_FOUND_LT,        KP_MSG_WSATYPE_NOT_FOUND_PL_1250,         KP_MSG_WSATYPE_NOT_FOUND_PL_1257,         KP_MSG_WSATYPE_NOT_FOUND_RU,        KP_MSG_WSATYPE_NOT_FOUND_RU,        // "Klasës tipas nerastas"
KP_MSG_WSAEWOULDBLOCK_EN,           KP_MSG_WSAEWOULDBLOCK_LT,           KP_MSG_WSAEWOULDBLOCK_PL_1250,            KP_MSG_WSAEWOULDBLOCK_PL_1257,            KP_MSG_WSAEWOULDBLOCK_RU,           KP_MSG_WSAEWOULDBLOCK_RU,           // "Ðaltinis laikinai nepasiekiamas"
KP_MSG_WSAHOST_NOT_FOUND_EN,        KP_MSG_WSAHOST_NOT_FOUND_LT,        KP_MSG_WSAHOST_NOT_FOUND_PL_1250,         KP_MSG_WSAHOST_NOT_FOUND_PL_1257,         KP_MSG_WSAHOST_NOT_FOUND_RU,        KP_MSG_WSAHOST_NOT_FOUND_RU,        // "Serveris nerastas"
KP_MSG_WSA_INVALID_HANDLE_EN,       KP_MSG_WSA_INVALID_HANDLE_LT,       KP_MSG_WSA_INVALID_HANDLE_PL_1250,        KP_MSG_WSA_INVALID_HANDLE_PL_1257,        KP_MSG_WSA_INVALID_HANDLE_RU,       KP_MSG_WSA_INVALID_HANDLE_RU,       // "Klaidingas objekto valdiklis" // "Klaidingas pasirinkto ávykio objekto valdiklis"
KP_MSG_WSA_INVALID_PARAMETER_EN,    KP_MSG_WSA_INVALID_PARAMETER_LT,    KP_MSG_WSA_INVALID_PARAMETER_PL_1250,     KP_MSG_WSA_INVALID_PARAMETER_PL_1257,     KP_MSG_WSA_INVALID_PARAMETER_RU,    KP_MSG_WSA_INVALID_PARAMETER_RU,    // "Neteisingi parametrai" // "Neteisingi vienas ar daugiau parametrø"
KP_MSG_WSAINVALIDPROCTABLE_EN,      KP_MSG_WSAINVALIDPROCTABLE_LT,      KP_MSG_WSAINVALIDPROCTABLE_PL_1250,       KP_MSG_WSAINVALIDPROCTABLE_PL_1257,       KP_MSG_WSAINVALIDPROCTABLE_RU,      KP_MSG_WSAINVALIDPROCTABLE_RU,      // "Klaidinga procedûrø lentelë"
KP_MSG_WSAINVALIDPROVIDER_EN,       KP_MSG_WSAINVALIDPROVIDER_LT,       KP_MSG_WSAINVALIDPROVIDER_PL_1250,        KP_MSG_WSAINVALIDPROVIDER_PL_1257,        KP_MSG_WSAINVALIDPROVIDER_RU,       KP_MSG_WSAINVALIDPROVIDER_RU,       // "Neteisingas tiekëjo kodas"
KP_MSG_WSA_IO_INCOMPLETE_EN,        KP_MSG_WSA_IO_INCOMPLETE_LT,        KP_MSG_WSA_IO_INCOMPLETE_PL_1250,         KP_MSG_WSA_IO_INCOMPLETE_PL_1257,         KP_MSG_WSA_IO_INCOMPLETE_RU,        KP_MSG_WSA_IO_INCOMPLETE_RU,        // "Persikloja ávesties/iðvesties ávykiai"
KP_MSG_WSA_IO_PENDING_EN,           KP_MSG_WSA_IO_PENDING_LT,           KP_MSG_WSA_IO_PENDING_PL_1250,            KP_MSG_WSA_IO_PENDING_PL_1257,            KP_MSG_WSA_IO_PENDING_RU,           KP_MSG_WSA_IO_PENDING_RU,           // "Persiklojanèios operacijos bus atliktos vëliau"

KP_MSG_WSA_NOT_ENOUGH_MEMORY_EN,    KP_MSG_WSA_NOT_ENOUGH_MEMORY_LT,    KP_MSG_WSA_NOT_ENOUGH_MEMORY_PL_1250,     KP_MSG_WSA_NOT_ENOUGH_MEMORY_PL_1257,     KP_MSG_WSA_NOT_ENOUGH_MEMORY_RU,    KP_MSG_WSA_NOT_ENOUGH_MEMORY_RU,    // "Nepakanka atminties"
KP_MSG_WSANOTINITIALISED_EN,        KP_MSG_WSANOTINITIALISED_LT,        KP_MSG_WSANOTINITIALISED_PL_1250,         KP_MSG_WSANOTINITIALISED_PL_1257,         KP_MSG_WSANOTINITIALISED_RU,        KP_MSG_WSANOTINITIALISED_RU,        // "Tinklo posistemis neaktyvuotas"
KP_MSG_WSANO_DATA_EN,               KP_MSG_WSANO_DATA_LT,               KP_MSG_WSANO_DATA_PL_1250,                KP_MSG_WSANO_DATA_PL_1257,                KP_MSG_WSANO_DATA_RU,               KP_MSG_WSANO_DATA_RU,               // "Vardas teisingas, taèiau nëra reikiamo tipo duomenø"
KP_MSG_WSANO_RECOVERY_EN,           KP_MSG_WSANO_RECOVERY_LT,           KP_MSG_WSANO_RECOVERY_PL_1250,            KP_MSG_WSANO_RECOVERY_PL_1257,            KP_MSG_WSANO_RECOVERY_RU,           KP_MSG_WSANO_RECOVERY_RU,           // "Nepataisoma klaida"
KP_MSG_WSAPROVIDERFAILEDINIT_EN,    KP_MSG_WSAPROVIDERFAILEDINIT_LT,    KP_MSG_WSAPROVIDERFAILEDINIT_PL_1250,     KP_MSG_WSAPROVIDERFAILEDINIT_PL_1257,     KP_MSG_WSAPROVIDERFAILEDINIT_RU,    KP_MSG_WSAPROVIDERFAILEDINIT_RU,    // "Negalima inicializuoti paslaugos tiekëjo"
KP_MSG_WSASYSCALLFAILURE_EN,        KP_MSG_WSASYSCALLFAILURE_LT,        KP_MSG_WSASYSCALLFAILURE_PL_1250,         KP_MSG_WSASYSCALLFAILURE_PL_1257,         KP_MSG_WSASYSCALLFAILURE_RU,        KP_MSG_WSASYSCALLFAILURE_RU,        // "Sistemos kreipinio klaida"
KP_MSG_WSASYSNOTREADY_EN,           KP_MSG_WSASYSNOTREADY_LT,           KP_MSG_WSASYSNOTREADY_PL_1250,            KP_MSG_WSASYSNOTREADY_PL_1257,            KP_MSG_WSASYSNOTREADY_RU,           KP_MSG_WSASYSNOTREADY_RU,           // "Tinklo posistemë nepasiekiama"
KP_MSG_WSATRY_AGAIN_EN,             KP_MSG_WSATRY_AGAIN_LT,             KP_MSG_WSATRY_AGAIN_PL_1250,              KP_MSG_WSATRY_AGAIN_PL_1257,              KP_MSG_WSATRY_AGAIN_RU,             KP_MSG_WSATRY_AGAIN_RU,             // "Neautorizuotas serveris nerastas"
KP_MSG_WSAVERNOTSUPPORTED_EN,       KP_MSG_WSAVERNOTSUPPORTED_LT,       KP_MSG_WSAVERNOTSUPPORTED_PL_1250,        KP_MSG_WSAVERNOTSUPPORTED_PL_1257,        KP_MSG_WSAVERNOTSUPPORTED_RU,       KP_MSG_WSAVERNOTSUPPORTED_RU,       // "Netinka WINSOCK.DLL versija"
KP_MSG_WSAEDISCON_EN,               KP_MSG_WSAEDISCON_LT,               KP_MSG_WSAEDISCON_PL_1250,                KP_MSG_WSAEDISCON_PL_1257,                KP_MSG_WSAEDISCON_RU,               KP_MSG_WSAEDISCON_RU,               // "Pradëtas tvarkingas iðjungimas" // "Pradëtas gracingas iðjungimas"
KP_MSG_WSA_OPERATION_ABORTED_EN,    KP_MSG_WSA_OPERATION_ABORTED_LT,    KP_MSG_WSA_OPERATION_ABORTED_PL_1250,     KP_MSG_WSA_OPERATION_ABORTED_PL_1257,     KP_MSG_WSA_OPERATION_ABORTED_RU,    KP_MSG_WSA_OPERATION_ABORTED_RU,    // "Persiklojanti operacija nutraukta"

KP_MSG_OUT_OF_MEM_RES_EN,           KP_MSG_OUT_OF_MEM_RES_LT,           KP_MSG_OUT_OF_MEM_RES_PL_1250,            KP_MSG_OUT_OF_MEM_RES_PL_1257,            KP_MSG_OUT_OF_MEM_RES_RU,           KP_MSG_OUT_OF_MEM_RES_RU,           // "Operacinei sistemai trûksta atminties"
KP_MSG_ERROR_FILE_NOT_FOUND_EN,     KP_MSG_ERROR_FILE_NOT_FOUND_LT,     KP_MSG_ERROR_FILE_NOT_FOUND_PL_1250,      KP_MSG_ERROR_FILE_NOT_FOUND_PL_1257,      KP_MSG_ERROR_FILE_NOT_FOUND_RU,     KP_MSG_ERROR_FILE_NOT_FOUND_RU,     // "Nurodytas failas nerastas"
KP_MSG_ERROR_PATH_NOT_FOUND_EN,     KP_MSG_ERROR_PATH_NOT_FOUND_LT,     KP_MSG_ERROR_PATH_NOT_FOUND_PL_1250,      KP_MSG_ERROR_PATH_NOT_FOUND_PL_1257,      KP_MSG_ERROR_PATH_NOT_FOUND_RU,     KP_MSG_ERROR_PATH_NOT_FOUND_RU,     // "Nurodytas kelias iki failø nerastas"
KP_MSG_ERROR_BAD_FORMAT_EN,         KP_MSG_ERROR_BAD_FORMAT_LT,         KP_MSG_ERROR_BAD_FORMAT_PL_1250,          KP_MSG_ERROR_BAD_FORMAT_PL_1257,          KP_MSG_ERROR_BAD_FORMAT_RU,         KP_MSG_ERROR_BAD_FORMAT_RU,         // "Pasirinktas .exe failas sugadintas"
KP_MSG_SE_ERR_ACCESSDENIED_EN,      KP_MSG_SE_ERR_ACCESSDENIED_LT,      KP_MSG_SE_ERR_ACCESSDENIED_PL_1250,       KP_MSG_SE_ERR_ACCESSDENIED_PL_1257,       KP_MSG_SE_ERR_ACCESSDENIED_RU,      KP_MSG_SE_ERR_ACCESSDENIED_RU,      // "Operacinë sistema uþdraudë prisijungimà prie reikiamø failø"
KP_MSG_SE_ERR_ASSOCINCOMPLETE_EN,   KP_MSG_SE_ERR_ASSOCINCOMPLETE_LT,   KP_MSG_SE_ERR_ASSOCINCOMPLETE_PL_1250,    KP_MSG_SE_ERR_ASSOCINCOMPLETE_PL_1257,    KP_MSG_SE_ERR_ASSOCINCOMPLETE_RU,   KP_MSG_SE_ERR_ASSOCINCOMPLETE_RU,   // "Failo sàryðis su programa nepilnas arba neteisingas"
KP_MSG_SE_ERR_DDEBUSY_EN,           KP_MSG_SE_ERR_DDEBUSY_LT,           KP_MSG_SE_ERR_DDEBUSY_PL_1250,            KP_MSG_SE_ERR_DDEBUSY_PL_1257,            KP_MSG_SE_ERR_DDEBUSY_RU,           KP_MSG_SE_ERR_DDEBUSY_RU,           // "DDE transakcija negali bûti baigta, nes kitos DDE transakcijos dar vykdomos"
KP_MSG_SE_ERR_DDEFAIL_EN,           KP_MSG_SE_ERR_DDEFAIL_LT,           KP_MSG_SE_ERR_DDEFAIL_PL_1250,            KP_MSG_SE_ERR_DDEFAIL_PL_1257,            KP_MSG_SE_ERR_DDEFAIL_RU,           KP_MSG_SE_ERR_DDEFAIL_RU,           // "DDE transakcija nutraukta"
KP_MSG_SE_ERR_DDETIMEOUT_EN,        KP_MSG_SE_ERR_DDETIMEOUT_LT,        KP_MSG_SE_ERR_DDETIMEOUT_PL_1250,         KP_MSG_SE_ERR_DDETIMEOUT_PL_1257,         KP_MSG_SE_ERR_DDETIMEOUT_RU,        KP_MSG_SE_ERR_DDETIMEOUT_RU,        // "DDE transakcija negali bûti baigta, nes neuþteko nurodyto laukimo laiko"
KP_MSG_SE_ERR_DLLNOTFOUND_EN,       KP_MSG_SE_ERR_DLLNOTFOUND_LT,       KP_MSG_SE_ERR_DLLNOTFOUND_PL_1250,        KP_MSG_SE_ERR_DLLNOTFOUND_PL_1257,        KP_MSG_SE_ERR_DLLNOTFOUND_RU,       KP_MSG_SE_ERR_DLLNOTFOUND_RU,       // "Nurodyta dinaminë biblioteka nerasta"
KP_MSG_SE_ERR_FNF_EN,               KP_MSG_SE_ERR_FNF_LT,               KP_MSG_SE_ERR_FNF_PL_1250,                KP_MSG_SE_ERR_FNF_PL_1257,                KP_MSG_SE_ERR_FNF_RU,               KP_MSG_SE_ERR_FNF_RU,               // "Nurodytas failas nerastas"
KP_MSG_SE_ERR_NOASSOC_EN,           KP_MSG_SE_ERR_NOASSOC_LT,           KP_MSG_SE_ERR_NOASSOC_PL_1250,            KP_MSG_SE_ERR_NOASSOC_PL_1257,            KP_MSG_SE_ERR_NOASSOC_RU,           KP_MSG_SE_ERR_NOASSOC_RU,           // "Nerasta programa skirta atverti ðio tipo failus"
KP_MSG_SE_ERR_OOM_EN,               KP_MSG_SE_ERR_OOM_LT,               KP_MSG_SE_ERR_OOM_PL_1250,                KP_MSG_SE_ERR_OOM_PL_1257,                KP_MSG_SE_ERR_OOM_RU,               KP_MSG_SE_ERR_OOM_RU,               // "Nepakanka atminties atlikti operacijai"
KP_MSG_SE_ERR_PNF_EN,               KP_MSG_SE_ERR_PNF_LT,               KP_MSG_SE_ERR_PNF_PL_1250,                KP_MSG_SE_ERR_PNF_PL_1257,                KP_MSG_SE_ERR_PNF_RU,               KP_MSG_SE_ERR_PNF_RU,               // "Nurodytas kelias nerastas"
KP_MSG_SE_ERR_SHARE_EN,             KP_MSG_SE_ERR_SHARE_LT,             KP_MSG_SE_ERR_SHARE_PL_1250,              KP_MSG_SE_ERR_SHARE_PL_1257,              KP_MSG_SE_ERR_SHARE_RU,             KP_MSG_SE_ERR_SHARE_RU,             // "Dalijimosi klaida"

KP_MSG_FIRST_TIME_ADMIN_EN,         KP_MSG_FIRST_TIME_ADMIN_LT,         KP_MSG_FIRST_TIME_ADMIN_PL_1250,          KP_MSG_FIRST_TIME_ADMIN_PL_1257,          KP_MSG_FIRST_TIME_ADMIN_RU,         KP_MSG_FIRST_TIME_ADMIN_RU,         // "Programà paleidþiant pirmà kartà, reikalingos\n administratoriaus teisës. Paleiskite programà ið naujo administratoriaus teisëmis."
KP_MSG_NOW_NOT_ADMIN_EN,            KP_MSG_NOW_NOT_ADMIN_LT,            KP_MSG_NOW_NOT_ADMIN_PL_1250,             KP_MSG_NOW_NOT_ADMIN_PL_1257,             KP_MSG_NOW_NOT_ADMIN_RU,            KP_MSG_NOW_NOT_ADMIN_RU,            // KP_MSG_NOT_ADMIN // "Dabar programà paleiskite dar kartà paprasto vartotojo teisëmis"
KP_MSG_NOT_ADMIN_EN,                KP_MSG_NOT_ADMIN_LT,                KP_MSG_NOT_ADMIN_PL_1250,                 KP_MSG_NOT_ADMIN_PL_1257,                 KP_MSG_NOT_ADMIN_RU,                KP_MSG_NOT_ADMIN_RU,                // "Programà paleiskite ið naujo paprasto vartotojo teisëmis"
KP_MSG_COPY_FILE_ACCESS_DENIED_EN,  KP_MSG_COPY_FILE_ACCESS_DENIED_LT,  KP_MSG_COPY_FILE_ACCESS_DENIED_PL_1250,   KP_MSG_COPY_FILE_ACCESS_DENIED_PL_1257,   KP_MSG_COPY_FILE_ACCESS_DENIED_RU,  KP_MSG_COPY_FILE_ACCESS_DENIED_RU,  // "Failo nukopijuoti nepavyko, programà paleiskite ið naujo administratoriaus teisëmis"

KP_PROGRESS_TITLE_EN,               KP_PROGRESS_TITLE_LT,               KP_PROGRESS_TITLE_PL_1250,                KP_PROGRESS_TITLE_PL_1257,                KP_PROGRESS_TITLE_RU,               KP_PROGRESS_TITLE_EN,               // "Palaukite..." // naudojamas kaip progress langelio antraðtë
KP_MSG_DELETING_FILE_EN,            KP_MSG_DELETING_FILE_LT,            KP_MSG_DELETING_FILE_PL_1250,             KP_MSG_DELETING_FILE_PL_1257,             KP_MSG_DELETING_FILE_RU,            KP_MSG_DELETING_FILE_RU,            // "Naikinamas failas %s.%s..."
KP_MSG_COPYING_EN,                  KP_MSG_COPYING_LT,                  KP_MSG_COPYING_PL_1250,                   KP_MSG_COPYING_PL_1257,                   KP_MSG_COPYING_RU,                  KP_MSG_COPYING_RU,                  // "Kopijuojamas failas..."
KP_MSG_COPYING_DIR_EN,              KP_MSG_COPYING_DIR_LT,              KP_MSG_COPYING_DIR_PL_1250,               KP_MSG_COPYING_DIR_PL_1257,               KP_MSG_COPYING_DIR_RU,              KP_MSG_COPYING_DIR_RU,              // "Kopijuojamas aplankas %s.%s..."
KP_MSG_COPYING_FILE_EN,             KP_MSG_COPYING_FILE_LT,             KP_MSG_COPYING_FILE_PL_1250,              KP_MSG_COPYING_FILE_PL_1257,              KP_MSG_COPYING_FILE_RU,             KP_MSG_COPYING_FILE_RU,             // "Kopijuojamas failas %s.%s..."

KP_MSG_NEG_ANSW_EN,                 KP_MSG_NEG_ANSW_LT,                 KP_MSG_NEG_ANSW_PL_1250,                  KP_MSG_NEG_ANSW_PL_1257,                  KP_MSG_NEG_ANSW_RU,                 KP_MSG_NEG_ANSW_RU,                 // "Neigiamas atsakymas"

KP_MSG_UNABLE_TO_EXECUTE_EN,        KP_MSG_UNABLE_TO_EXECUTE_LT,        KP_MSG_UNABLE_TO_EXECUTE_PL_1250,         KP_MSG_UNABLE_TO_EXECUTE_PL_1257,         KP_MSG_UNABLE_TO_EXECUTE_RU,        KP_MSG_UNABLE_TO_EXECUTE_RU,        // "Komandos %s ávykdyti negaliu - patikrinkite, ar teisingai ádiegëte visus sistemos komponentus"

KP_MSG_FLASH_PLAYER_INSTALL_EN,     KP_MSG_FLASH_PLAYER_INSTALL_LT,     KP_MSG_FLASH_PLAYER_INSTALL_PL_1250,      KP_MSG_FLASH_PLAYER_INSTALL_PL_1257,      KP_MSG_FLASH_PLAYER_INSTALL_RU,     KP_MSG_FLASH_PLAYER_INSTALL_RU,     // "Dabar bus ádiegtas Macromedia Flash grotuvas. Vykdykite tolesnius diegimo programos nurodymus."

KP_MSG_FILE_CHANGED_EN,             KP_MSG_FILE_CHANGED_LT,             KP_MSG_FILE_CHANGED_PL_1250,              KP_MSG_FILE_CHANGED_PL_1257,              KP_MSG_FILE_CHANGED_RU,             KP_MSG_FILE_CHANGED_RU,             // "Failas pasikeitë"

KP_MSG_ALL_FILES_EN,                KP_MSG_ALL_FILES_LT,                KP_MSG_ALL_FILES_PL_1250,                 KP_MSG_ALL_FILES_PL_1257,                 KP_MSG_ALL_FILES_RU,                KP_MSG_ALL_FILES_RU,                // "Visi failai (*.*)"
KP_MSG_SAVE_AS_EN,                  KP_MSG_SAVE_AS_LT,                  KP_MSG_SAVE_AS_PL_1250,                   KP_MSG_SAVE_AS_PL_1257,                   KP_MSG_SAVE_AS_RU,                  KP_MSG_SAVE_AS_RU,                  // "Áraðyti kaip"

KP_MSG_FILE_EXISTS_EN,              KP_MSG_FILE_EXISTS_LT,              KP_MSG_FILE_EXISTS_PL_1250,               KP_MSG_FILE_EXISTS_PL_1257,               KP_MSG_FILE_EXISTS_RU,              KP_MSG_FILE_EXISTS_RU,              // "Failas %s jau yra, perraðyti?"

KP_MSG_DIAG_MSG_EN,                 KP_MSG_DIAG_MSG_LT,                 KP_MSG_DIAG_MSG_PL_1250,                  KP_MSG_DIAG_MSG_PL_1257,                  KP_MSG_DIAG_MSG_RU,                 KP_MSG_DIAG_MSG_RU,                 // "Formuojamas diagnostinis praneðimas"
KP_MSG_DIAG_MSG_TITLE_EN,           KP_MSG_DIAG_MSG_TITLE_LT,           KP_MSG_DIAG_MSG_TITLE_PL_1250,            KP_MSG_DIAG_MSG_TITLE_PL_1257,            KP_MSG_DIAG_MSG_TITLE_RU,           KP_MSG_DIAG_MSG_TITLE_EN,           // "Diagnostinis praneðimas"
KP_MSG_DIAG_MSG_EXPL_EN,            KP_MSG_DIAG_MSG_EXPL_LT,            KP_MSG_DIAG_MSG_EXPL_PL_1250,             KP_MSG_DIAG_MSG_EXPL_PL_1257,             KP_MSG_DIAG_MSG_EXPL_RU,            KP_MSG_DIAG_MSG_EXPL_RU,            // "Jei norite nusiøsti diagnostiná praneðimà gamintojui, uþpildykite pateiktus laukus. Praneðimas apie kompiuterio konfigûracijà, produktà bei klaidos pobûdá bus iðsiøstas internetu á produkto gamintojo tarnybinæ stotá. Jei po kurio laiko su Jumis nebus susisiekta Jûsø nurodytu paðto adresu, kreipkitës adresu pagalba@tev.lt")
KP_MSG_DIAG_MSG_EMAIL_PROMPT_EN,    KP_MSG_DIAG_MSG_EMAIL_PROMPT_LT,    KP_MSG_DIAG_MSG_EMAIL_PROMPT_PL_1250,     KP_MSG_DIAG_MSG_EMAIL_PROMPT_PL_1257,     KP_MSG_DIAG_MSG_EMAIL_PROMPT_RU,    KP_MSG_DIAG_MSG_EMAIL_PROMPT_RU,    // "Jûsø e-paðto adresas:")
KP_MSG_DIAG_MSG_COMMENTS_PROMPT_EN, KP_MSG_DIAG_MSG_COMMENTS_PROMPT_LT, KP_MSG_DIAG_MSG_COMMENTS_PROMPT_PL_1250,  KP_MSG_DIAG_MSG_COMMENTS_PROMPT_PL_1257,  KP_MSG_DIAG_MSG_COMMENTS_PROMPT_RU, KP_MSG_DIAG_MSG_COMMENTS_PROMPT_RU, // "Komentarai apie klaidos atsiradimo aplinkybes:")
KP_MSG_DIAG_MSG_FILE_PROMPT_EN,     KP_MSG_DIAG_MSG_FILE_PROMPT_LT,     KP_MSG_DIAG_MSG_FILE_PROMPT_PL_1250,      KP_MSG_DIAG_MSG_FILE_PROMPT_PL_1257,      KP_MSG_DIAG_MSG_FILE_PROMPT_RU,     KP_MSG_DIAG_MSG_FILE_PROMPT_RU,     // "Papildomas failas, kurá norëtumëte nusiøsti (pvz., ekrano kopijos paveikslëlis):")

KP_MSG_BAD_EMAIL_ADDRESS_EN,        KP_MSG_BAD_EMAIL_ADDRESS_LT,        KP_MSG_BAD_EMAIL_ADDRESS_PL_1250,         KP_MSG_BAD_EMAIL_ADDRESS_PL_1257,         KP_MSG_BAD_EMAIL_ADDRESS_RU,        KP_MSG_BAD_EMAIL_ADDRESS_RU,        // "Neteisingas e-paðto adresas"

KP_MSG_DIAG_MSG_SEL_FILE_EN,        KP_MSG_DIAG_MSG_SEL_FILE_LT,        KP_MSG_DIAG_MSG_SEL_FILE_PL_1250,         KP_MSG_DIAG_MSG_SEL_FILE_PL_1257,         KP_MSG_DIAG_MSG_SEL_FILE_RU,        KP_MSG_DIAG_MSG_SEL_FILE_EN,        // "Pasirinkite siunèiamà failà"

KP_MSG_DIAG_MSG_SUCCEEDED_EN,       KP_MSG_DIAG_MSG_SUCCEEDED_LT,       KP_MSG_DIAG_MSG_SUCCEEDED_PL_1250,        KP_MSG_DIAG_MSG_SUCCEEDED_PL_1257,        KP_MSG_DIAG_MSG_SUCCEEDED_RU,       KP_MSG_DIAG_MSG_SUCCEEDED_RU,       // "Diagnostinis praneðimas nusiøstas sëkmingai"

KP_MSG_DIAG_MSG_EXPL1_EN,           KP_MSG_DIAG_MSG_EXPL1_LT,           KP_MSG_DIAG_MSG_EXPL1_PL_1250,            KP_MSG_DIAG_MSG_EXPL1_PL_1257,            KP_MSG_DIAG_MSG_EXPL1_RU,           KP_MSG_DIAG_MSG_EXPL1_RU,           // "Jei norite siøsti diagnostiná praneðimà, spragtelëkite „Siøsti“, jei ne – „Atðaukti“."
KP_MSG_SIUSTI_EN,                   KP_MSG_SIUSTI_LT,                   KP_MSG_SIUSTI_PL_1250,                    KP_MSG_SIUSTI_PL_1257,                    KP_MSG_SIUSTI_RU,                   KP_MSG_SIUSTI_EN,                   // "Siøsti"
KP_MSG_DIAG_MSG_EXPL2_EN,           KP_MSG_DIAG_MSG_EXPL2_LT,           KP_MSG_DIAG_MSG_EXPL2_PL_1250,            KP_MSG_DIAG_MSG_EXPL2_PL_1257,            KP_MSG_DIAG_MSG_EXPL2_RU,           KP_MSG_DIAG_MSG_EXPL2_RU,           // "Jei norite nusiøsti diagnostiná praneðimà gamintojui, uþpildykite Jûsø e-paðto adreso laukà ir spragtelëkite mygtukà „Siøsti“."

KP_MSG_DOWNLOADING_EN,              KP_MSG_DOWNLOADING_LT,              KP_MSG_DOWNLOADING_PL_1250,               KP_MSG_DOWNLOADING_PL_1257,               KP_MSG_DOWNLOADING_RU,              KP_MSG_DOWNLOADING_RU,              // "Siunèiamas failas..."
KP_MSG_DOWNLOADING_FILE_EN,         KP_MSG_DOWNLOADING_FILE_LT,         KP_MSG_DOWNLOADING_FILE_PL_1250,          KP_MSG_DOWNLOADING_FILE_PL_1257,          KP_MSG_DOWNLOADING_FILE_RU,         KP_MSG_DOWNLOADING_FILE_RU,         // "Siunèiamas failas %s.%s..."

KP_MSG_FIREWALL_EN,                 KP_MSG_FIREWALL_LT,                 KP_MSG_FIREWALL_PL_1250,                  KP_MSG_FIREWALL_PL_1257,                  KP_MSG_FIREWALL_RU,                 KP_MSG_FIREWALL_RU,                 // "Neleista prisijungti prie interneto. Patikrinkite Jûsø ugniasienës parinktis – pabandykite átraukti %s á sàraðà programø, kurioms leidþiama kreiptis á internetà."

KP_MSG_POINTER_EN,                  KP_MSG_POINTER_LT,                  KP_MSG_POINTER_PL_1250,                   KP_MSG_POINTER_PL_1257,                   KP_MSG_POINTER_RU,                  KP_MSG_POINTER_RU,                  // "Bloga rodyklë"

KP_MSG_LOG_STARTED_EN,              KP_MSG_LOG_STARTED_LT,              KP_MSG_LOG_STARTED_PL_1250,               KP_MSG_LOG_STARTED_PL_1257,               KP_MSG_LOG_STARTED_RU,              KP_MSG_LOG_STARTED_RU,              // "Þurnalas iðvedamas ir á failà %s"
KP_MSG_CONS_TITLE_EN,               KP_MSG_CONS_TITLE_LT,               KP_MSG_CONS_TITLE_PL_1250,                KP_MSG_CONS_TITLE_PL_1257,                KP_MSG_CONS_TITLE_RU,               KP_MSG_CONS_TITLE_RU,               // "%s: Praneðimø þurnalas"
};


// --------------------------
KpLang iMsgLangOff =
#if (MsgLang >= 0) && (MsgLang < KpNumOfLangs_p)
   (KpLang)MsgLang;
#else
   KpLangEn;
#endif


// ================================================== KpErrorProc_tag functions
// --------------------------------------------------
KpErrorProcClass::KpErrorProcClass(bool bInLine, int iKptCtbl)
{
   bInLineFlag=bInLine;

   lhLastRetc=S_OK;
   lpszLastMessageText[0]=Nul;
   bLastSevereError=(bool)(-1);
   lpszLastSourceFile[0]=Nul;
   iLastSourceLine=0;
   lLastMainKeyId=0L;
   iKptCodeTable=iKptCtbl;

#if (Envir==MSWin32) || (Envir==MSWin32Mfc)
   m_pClMessages=NULL;
#endif
   lMsgPar=0L;
   szaMsgText[0]=Nul;

#ifdef KP_ERR_SENDDIAGMSG
   m_hDiagMsgWindow = NULL;
   m_bShiftFl = False;
   m_hDiagEmailEdit = NULL;
   m_hDiagCommentsEdit = NULL;
   m_hDiagFileEdit = NULL;
   m_hDiagFileButton = NULL;
   m_hDiagOkButton = NULL;
   m_hDiagCancelButton = NULL;
   m_lpszDiagEmail[0] = Nul;
   m_lpszDiagComments[0] = Nul;
   m_lpszDiagFile[0] = Nul;
#endif
}


// --------------------------------------------------
#if (Envir==MSWin32) || (Envir==MSWin32Mfc)
// initialisation task - do not use m_pClMessages inside of SetMsgList()
HRESULT KpErrorProcClass::SetMsgList(KpConsole *pClMessages)
{
   m_pClMessages=pClMessages;
return(S_OK);
}
#endif


// --------------------------------------------------
HRESULT KpErrorProcClass::SetLPar(long lPar)
{
   lMsgPar=lPar;

return(S_OK);
}


HRESULT KpErrorProcClass::SetLTxt(const unsigned char *lpszTxt)
{
   strncpy(szaMsgText, lpszTxt, KP_MSG_LEN);
   szaMsgText[KP_MSG_LEN]=Nul;

return(S_OK);
}

// --------------------------------------------------
HRESULT KpErrorProcClass::Message(const unsigned char *lpszMsg)
{
        fputs((const char *)lpszMsg, stdout);
// fputs("; ", stdout);

        return(S_OK);
}


// --------------------------------------------------
HRESULT KpErrorProcClass::StrDecode(unsigned char *lpszOutStr, const KpChar *uiaMsg)
{
HRESULT retc = S_OK;

   retc = KptStrDecode(lpszOutStr, uiaMsg, iKptCodeTable);

   if(retc==KP_E_UNKN_CHR)
   {
//    retc=KpErrorProc.OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L);
      retc=S_OK;
   }

return(retc);
}


// --------------------------------------------------
HRESULT KpErrorProcClass::Message16(const KpChar *uiaMsg)
{
HRESULT retc=S_OK;
unsigned char str_buf[KP_MSG_LEN+1];

   if(TvKpStrLen(uiaMsg) > KP_MSG_LEN)
      retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=StrDecode(str_buf, uiaMsg);

   if(SUCCEEDED(retc)) retc=Message(str_buf);

return(retc);
}


// --------------------------------------------------
HRESULT KpErrorProcClass::FormatErrorMessageMain
(
const HRESULT lhRetc,
unsigned char *lpszMsg
)
{
HRESULT retc=S_OK;
// unsigned char out_buf[MAX_LONG_HEX_DIGITS + 20];
// sprintf((char *)out_buf, "%lx", lhRetc);
const unsigned char *msgptr = (unsigned char *)""; // out_buf; //

   KP_ASSERT(lpszMsg != null, E_INVALIDARG, null, True);

   switch(lhRetc)
   {
      case S_OK:                 msgptr = KP_MSG_ERR_OK; break;
      case E_INVALIDARG:         msgptr = KP_MSG_INVALIDARG; break;
      case E_NOTIMPL:            msgptr = KP_MSG_NOTIMPL; break;
      case E_UNEXPECTED:         msgptr = KP_MSG_UNEXPECTED; break;
//    case E_NOINTERFACE:
      case E_POINTER:            msgptr = KP_MSG_POINTER; break;
//    case E_HANDLE:
//    case E_FAIL:
      case KP_E_FERROR:          msgptr = KP_MSG_FERROR; break;
      case KP_E_SYSTEM_ERROR:    msgptr = KP_MSG_SYSTEM_ERROR; break;
      case KP_E_EOF:             msgptr = KP_MSG_EOF; break;
      case KP_E_FILE_FORMAT:     msgptr = KP_MSG_FILE_FORMAT; break;
      case KP_E_FILE_NOT_FOUND:  msgptr = KP_MSG_FILE_NOT_FOUND; break;
      case KP_E_DIR_ERROR:       msgptr = KP_MSG_DIR_ERROR; break;
      case KP_E_OUTOFMEM:        msgptr = KP_MSG_OUTOFMEM; break;
      case KP_E_NO_FILE:         msgptr = KP_MSG_NO_FILE; break;
      case KP_E_DOUBLE_UNGET:    msgptr = KP_MSG_DOUBLE_UNGET; break;
      case KP_E_UNKN_CHR:        msgptr = KP_MSG_UNKN_CHR; break;
      case KP_E_COMMAND_ERROR:   msgptr = KP_MSG_COMMAND_ERROR; break;
      case KP_E_BUFFER_OVERFLOW: msgptr = KP_MSG_BUFFER_OVERFLOW; break;
      case KP_E_FONT_UNDEF:      msgptr = KP_MSG_FONT_UNDEF; break;
      case KP_E_KWD_NOT_FOUND:   msgptr = KP_MSG_KWD_NOT_FOUND; break;
      case KP_E_UNKNOWN_SYSTEM:  msgptr = KP_MSG_UNKNOWN_SYSTEM; break;
      case KP_E_ILL_CODE:        msgptr = KP_MSG_ILL_CODE; break;
      case KP_E_CANCEL:          msgptr = KP_MSG_CANCELLED; break;
      case KP_E_DOUBLE_CALL:     msgptr = KP_MSG_DOUBLE_CALL; break;
      case KP_E_TIMEOUT:         msgptr = KP_MSG_TIMEOUT; break;
      case KP_E_OBJ_NOT_FOUND:   msgptr = KP_MSG_OBJ_NOT_FOUND; break;
      case KP_E_NO_CONN:         msgptr = KP_MSG_NO_CONN; break;
      case KP_E_TRANS_ERR:       msgptr = KP_MSG_TRANS_ERR; break;
      case KP_E_REFUSED:         msgptr = KP_MSG_REFUSED; break;
      case KP_E_ACCESS_DENIED:   msgptr = KP_MSG_ACCESS_DENIED; break;
      case KP_E_ILL_CHR:         msgptr = KP_MSG_ILLEGAL_CHARACTER; break;
      case KP_E_DIV_ZERO:        msgptr = KP_MSG_DIV_ZERO; break;
      case KP_E_ILLMATHARG:      msgptr = KP_MSG_ILLMATHARG; break;
      case KP_E_ILLFUNC:         msgptr = KP_MSG_ILLFUNC; break;
      case KP_E_NOTINST:         msgptr = KP_MSG_NOTINST; break;
      case KP_E_MSG_FORMAT:      msgptr = KP_MSG_MSG_FORMAT; break;
      case KP_E_OBSOLETE:        msgptr = KP_MSG_OBSOLETE; break;
      case KP_E_NEG_ANSW:        msgptr = KP_MSG_NEG_ANSW; break;
      case KP_E_FILE_CHANGED:    msgptr = KP_MSG_FILE_CHANGED; break;
      case KP_S_DIAG_MSG:        msgptr = KP_MSG_DIAG_MSG; break;
      case KP_E_BAD_EMAIL:       msgptr = KP_MSG_BAD_EMAIL_ADDRESS; break;
   }

   if(SUCCEEDED(retc))
      if(strlen(msgptr)>KP_MSG_LEN)
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L, NULL /* pListBox */);
   if(SUCCEEDED(retc))
      strcpy((char *)lpszMsg,(const char *)msgptr);

return(retc);
}


// --------------------------------------------------
#if (Envir==MSWin32) || (Envir==MSWin32Con) || (Envir==MSWin32Mfc) || (Envir==MSWin32ConMfc)
HRESULT KpErrorProcClass::FormatErrorMessageSystem
(
long lWindowsErrorCode,
unsigned char *lpszMsg,
bool bFullFormat
)
{
HRESULT retc = S_OK;
const unsigned char *pszMsg0 = null;
unsigned char *pszMsg1 = null;
const unsigned char *pszMsg = null;
unsigned char *pnts;
unsigned char str_buf[MAX_LONG_DIGITS + 20];
   str_buf[0] = Nul;
int ii;

   KP_ASSERT(lpszMsg != null, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc)) lpszMsg[0] = Nul;

   if(lWindowsErrorCode != 0)
   {
      switch(lWindowsErrorCode)
      {
      case WSAEACCES:               pszMsg0=KP_MSG_WSAEACCES; break;
      case WSAEADDRINUSE:           pszMsg0=KP_MSG_WSAEADDRINUSE; break;
      case WSAEADDRNOTAVAIL:        pszMsg0=KP_MSG_WSAEADDRNOTAVAIL; break;
      case WSAEAFNOSUPPORT:         pszMsg0=KP_MSG_WSAEAFNOSUPPORT; break;
      case WSAEALREADY:             pszMsg0=KP_MSG_WSAEALREADY; break;
      case WSAECONNABORTED:         pszMsg0=KP_MSG_WSAECONNABORTED; break;
      case WSAECONNREFUSED:         pszMsg0=KP_MSG_WSAECONNREFUSED; break;
      case WSAECONNRESET:           pszMsg0=KP_MSG_WSAECONNRESET; break;
      case WSAEDESTADDRREQ:         pszMsg0=KP_MSG_WSAEDESTADDRREQ; break;
      case WSAEFAULT:               pszMsg0=KP_MSG_WSAEFAULT; break;
      case WSAEHOSTDOWN:            pszMsg0=KP_MSG_WSAEHOSTDOWN; break;
      case WSAEHOSTUNREACH:         pszMsg0=KP_MSG_WSAEHOSTUNREACH; break;
      case WSAEINPROGRESS:          pszMsg0=KP_MSG_WSAEINPROGRESS; break;
      case WSAEINTR:                pszMsg0=KP_MSG_WSAEINTR; break;
      case WSAEINVAL:               pszMsg0=KP_MSG_WSAEINVAL; break;
      case WSAEISCONN:              pszMsg0=KP_MSG_WSAEISCONN; break;
      case WSAEMFILE:               pszMsg0=KP_MSG_WSAEMFILE; break;
      case WSAEMSGSIZE:             pszMsg0=KP_MSG_WSAEMSGSIZE; break;
      case WSAENETDOWN:             pszMsg0=KP_MSG_WSAENETDOWN; break;
      case WSAENETRESET:            pszMsg0=KP_MSG_WSAENETRESET; break;
      case WSAENETUNREACH:          pszMsg0=KP_MSG_WSAENETUNREACH; break;
      case WSAENOBUFS:              pszMsg0=KP_MSG_WSAENOBUFS; break;
      case WSAENOPROTOOPT:          pszMsg0=KP_MSG_WSAENOPROTOOPT; break;
      case WSAENOTCONN:             pszMsg0=KP_MSG_WSAENOTCONN; break;
      case WSAENOTSOCK:             pszMsg0=KP_MSG_WSAENOTSOCK; break;
      case WSAEOPNOTSUPP:           pszMsg0=KP_MSG_WSAEOPNOTSUPP; break;
      case WSAEPFNOSUPPORT:         pszMsg0=KP_MSG_WSAEPFNOSUPPORT; break;
      case WSAEPROCLIM:             pszMsg0=KP_MSG_WSAEPROCLIM; break;
      case WSAEPROTONOSUPPORT:      pszMsg0=KP_MSG_WSAEPROTONOSUPPORT; break;
      case WSAEPROTOTYPE:           pszMsg0=KP_MSG_WSAEPROTOTYPE; break;
      case WSAESHUTDOWN:            pszMsg0=KP_MSG_WSAESHUTDOWN; break;
      case WSAESOCKTNOSUPPORT:      pszMsg0=KP_MSG_WSAESOCKTNOSUPPORT; break;
      case WSAETIMEDOUT:            pszMsg0=KP_MSG_WSAETIMEDOUT; break;
      case WSATYPE_NOT_FOUND:       pszMsg0=KP_MSG_WSATYPE_NOT_FOUND; break;
      case WSAEWOULDBLOCK:          pszMsg0=KP_MSG_WSAEWOULDBLOCK; break;
      case WSAHOST_NOT_FOUND:       pszMsg0=KP_MSG_WSAHOST_NOT_FOUND; break;
      case WSA_INVALID_HANDLE:      pszMsg0=KP_MSG_WSA_INVALID_HANDLE; break;
      case WSA_INVALID_PARAMETER:   pszMsg0=KP_MSG_WSA_INVALID_PARAMETER; break;
//    case WSAINVALIDPROCTABLE:     pszMsg0=KP_MSG_WSAINVALIDPROCTABLE; break;
//    case WSAINVALIDPROVIDER:      pszMsg0=KP_MSG_WSAINVALIDPROVIDER; break;
      case WSA_IO_INCOMPLETE:       pszMsg0=KP_MSG_WSA_IO_INCOMPLETE; break;
      case WSA_IO_PENDING:          pszMsg0=KP_MSG_WSA_IO_PENDING; break;
// tas pat, kaip SE_ERR_OOM
//    case WSA_NOT_ENOUGH_MEMORY:   pszMsg0=KP_MSG_WSA_NOT_ENOUGH_MEMORY; break;
      case WSANOTINITIALISED:       pszMsg0=KP_MSG_WSANOTINITIALISED; break;
      case WSANO_DATA:              pszMsg0=KP_MSG_WSANO_DATA; break;
      case WSANO_RECOVERY:          pszMsg0=KP_MSG_WSANO_RECOVERY; break;
//    case WSAPROVIDERFAILEDINIT:   pszMsg0=KP_MSG_WSAPROVIDERFAILEDINIT; break;
      case WSASYSCALLFAILURE:       pszMsg0=KP_MSG_WSASYSCALLFAILURE; break;
      case WSASYSNOTREADY:          pszMsg0=KP_MSG_WSASYSNOTREADY; break;
      case WSATRY_AGAIN:            pszMsg0=KP_MSG_WSATRY_AGAIN; break;
      case WSAVERNOTSUPPORTED:      pszMsg0=KP_MSG_WSAVERNOTSUPPORTED; break;
      case WSAEDISCON:              pszMsg0=KP_MSG_WSAEDISCON; break;
      case WSA_OPERATION_ABORTED:   pszMsg0=KP_MSG_WSA_OPERATION_ABORTED; break;

//    switch((int)hErrorCode)
//    {
// !!! case 0:                      pszMsg0=KP_MSG_OUT_OF_MEM_RES; break;
      case ERROR_FILE_NOT_FOUND:    pszMsg0=KP_MSG_ERROR_FILE_NOT_FOUND; break;
      case ERROR_PATH_NOT_FOUND:    pszMsg0=KP_MSG_ERROR_PATH_NOT_FOUND; break;
      case ERROR_BAD_FORMAT:        pszMsg0=KP_MSG_ERROR_BAD_FORMAT; break;
      case SE_ERR_ACCESSDENIED:     pszMsg0=KP_MSG_SE_ERR_ACCESSDENIED; break;
      case SE_ERR_ASSOCINCOMPLETE:  pszMsg0=KP_MSG_SE_ERR_ASSOCINCOMPLETE; break;
      case SE_ERR_DDEBUSY:          pszMsg0=KP_MSG_SE_ERR_DDEBUSY; break;
      case SE_ERR_DDEFAIL:          pszMsg0=KP_MSG_SE_ERR_DDEFAIL; break;
      case SE_ERR_DDETIMEOUT:       pszMsg0=KP_MSG_SE_ERR_DDETIMEOUT; break;
      case SE_ERR_DLLNOTFOUND:      pszMsg0=KP_MSG_SE_ERR_DLLNOTFOUND; break;
//    case SE_ERR_FNF:              pszMsg1=KP_MSG_SE_ERR_FNF; break;
      case SE_ERR_NOASSOC:          pszMsg0=KP_MSG_SE_ERR_NOASSOC; break;
      case SE_ERR_OOM:              pszMsg0=KP_MSG_SE_ERR_OOM; break;
//    case SE_ERR_PNF:              pszMsg0=KP_MSG_SE_ERR_PNF; break;
      case SE_ERR_SHARE:            pszMsg0=KP_MSG_SE_ERR_SHARE; break;

// klaidos ið GetAdaptersAddresses(), naudojama KpSocket::Bind()
//    case ERROR_ADDRESS_NOT_ASSOCIATED:  "DHCP lease information was available."
//    case ERROR_BUFFER_OVERFLOW:         "The buffer size indicated by the SizePointer parameter is too small to hold the adapter information or the AdapterAddresses parameter is NULL. The SizePointer parameter returned points to the required size of the buffer to hold the adapter information."
//    case ERROR_INVALID_PARAMETER:       "One of the parameters is invalid. This error is returned for any of the following conditions: the SizePointer parameter is NULL, the Address parameter is not AF_INET, AF_INET6, or AF_UNSPEC, or the address information for the parameters requested is greater than ULONG_MAX."
//    case ERROR_NOT_ENOUGH_MEMORY:       "Insufficient memory resources are available to complete the operation."
//    case ERROR_NO_DATA:                 "No addresses were found for the requested parameters."

      default: pszMsg0 = null; break;
      }

      pszMsg = null;
      if((pszMsg0 == null) || bFullFormat) if(FormatMessage(
         FORMAT_MESSAGE_ALLOCATE_BUFFER |
         FORMAT_MESSAGE_IGNORE_INSERTS |
         FORMAT_MESSAGE_FROM_SYSTEM,
         NULL, lWindowsErrorCode, 0,
         (char *)&pszMsg, 0, NULL)==0)
      {
         pszMsg = null; // nesuformavo
      }

//    if((pszMsg0 == null) && (pszMsg == null))
      {
         sprintf((char *)str_buf, " %ld", lWindowsErrorCode);
//       pszMsg0 = str_buf;
      }

   } // if(lWindowsErrorCode!=0)

   if(((pszMsg0 != null) || (pszMsg != null) || (str_buf[0] != Nul)) && SUCCEEDED(retc))
   {
      ii = 20;
      if(pszMsg0 != null) ii += strlen(pszMsg0);
      if(pszMsg != null) ii += strlen(pszMsg);
      ii += strlen(str_buf);

//    KP_NEWA(pszMsg1, unsigned char, ii + 1); // isvieciamas ir is KP_NEWA(), gali uzsiciklint
      pszMsg1 = new unsigned char[ii + 1];

      if((pszMsg1 != null) && SUCCEEDED(retc))
      {
         pszMsg1[0] = Nul;
         if(pszMsg0 != null)
         {
            strcat(pszMsg1, pszMsg0);
            if(pszMsg != null) strcat(pszMsg1, "; ");
         }

         if(pszMsg != null) strcat(pszMsg1, pszMsg);

         pnts = pszMsg1 + strlen(pszMsg1);
         if(pnts > pszMsg1) if(*(--pnts)==Lf) *pnts=Nul;
         if(pnts > pszMsg1) if(*(--pnts)==Cr) *pnts=Nul;
         if(pnts > pszMsg1) if(*(--pnts)=='.') *pnts=Nul;

         if((pszMsg1[0] != Nul) && (str_buf[0] != Nul)) strcat(pszMsg1, "; ");
         strcat(pszMsg1, str_buf);
      }
   }

   if((pszMsg1 != NULL) && SUCCEEDED(retc))
   {
      if(strlen(pszMsg1) > KP_MSG_LEN)
      {
         pszMsg1[KP_MSG_LEN] = Nul;
         retc = KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, False, __FILE__, __LINE__, 0L, NULL /* pListBox */);
      }
      if(SUCCEEDED(retc))
         strcpy(lpszMsg, pszMsg1);
   }

// KP_DELETEA(pszMsg1); // siaip iskvieciamas ir is KP_DELETE(), gali ir uzsiciklint
   if(pszMsg1 != null) delete [] pszMsg1;
   pszMsg1 = null;

   if(pszMsg!=null) LocalFree((HLOCAL)pszMsg);

return(S_OK);
}
#endif


// ------------------------------------
unsigned char *KpErrorProcClass::FormatErrorMessageHTTP(int iHTTP_RetCode)
{
unsigned char out_buf[MAX_LONG_DIGITS + 100];
   sprintf((char *)out_buf, "HTTP status: %d", iHTTP_RetCode);
unsigned char *retv = out_buf;

   switch(iHTTP_RetCode)
   {
      case HTTP_ANSW_CONTINUE /* 100 */: retv=(unsigned char *)"Continue"; break;
      case 101: retv=(unsigned char *)"Switching Protocols"; break;
      case HTTP_ANSW_OK /* 200 */: retv=(unsigned char *)"OK"; break;
      case 201: retv=(unsigned char *)"Created"; break;
      case 202: retv=(unsigned char *)"Accepted"; break;
      case 203: retv=(unsigned char *)"Non-Authoritative Information"; break;
      case 204: retv=(unsigned char *)"No Content"; break;
      case 205: retv=(unsigned char *)"Reset Content"; break;
      case 206: retv=(unsigned char *)"Partial Content"; break;
      case 300: retv=(unsigned char *)"Multiple Choices"; break;
      case 301: retv=(unsigned char *)"Moved Permanently"; break;
      case HTTP_ANSW_FOUND /* 302 */: retv=(unsigned char *)"Found"; break;
      case 303: retv=(unsigned char *)"See Other"; break;
      case 304: retv=(unsigned char *)"Not Modified"; break;
      case 305: retv=(unsigned char *)"Use Proxy"; break;
      case 307: retv=(unsigned char *)"Temporary Redirect"; break;
      case 400: retv=(unsigned char *)"Bad Request"; break;
      case 401: retv=(unsigned char *)"Unauthorized"; break;
      case 402: retv=(unsigned char *)"Payment Required"; break;
      case 403: retv=(unsigned char *)"Forbidden"; break;
      case HTTP_ANSW_FILE_NOT_FOUND /* 404 */: retv=(unsigned char *)"Not Found"; break;
      case 405: retv=(unsigned char *)"Method Not Allowed"; break;
      case 406: retv=(unsigned char *)"Not Acceptable"; break; // serveris negali iðsiøsti failo uþkoduoto në vienu ið metodø, nurodytø HTTP uþklausos lauke Accept-Encoding:
      case 407: retv=(unsigned char *)"Proxy Authentication Required"; break;
      case 408: retv=(unsigned char *)"Request Timeout"; break;
      case 409: retv=(unsigned char *)"Conflict"; break;
      case 410: retv=(unsigned char *)"Gone"; break;
      case 411: retv=(unsigned char *)"Length Required"; break;
      case 412: retv=(unsigned char *)"Precondition Failed"; break;
      case 413: retv=(unsigned char *)"Request Entity Too Large"; break;
      case 414: retv=(unsigned char *)"Request-URI Too Long"; break;
      case 415: retv=(unsigned char *)"Unsupported Media Type"; break;
      case 416: retv=(unsigned char *)"Requested Range Not Satisfiable"; break;
      case 417: retv=(unsigned char *)"Expectation Failed"; break;
      case 500: retv=(unsigned char *)"Internal Server Error"; break;
      case 501: retv=(unsigned char *)"Not Implemented"; break;
      case 502: retv=(unsigned char *)"Bad Gateway"; break;
      case 503: retv=(unsigned char *)"Service Unavailable"; break;
      case 504: retv=(unsigned char *)"Gateway Timeout"; break;
      case 505: retv=(unsigned char *)"HTTP Version Not Supported"; break;
   }

return(retv);
}


// ------------------------------------
int KpErrorProcClass::TranslToHTTP_RetCode(HRESULT iRetc)
{
int retv = 500 /* Internal Server Error */;

   switch(iRetc)
   {
      case S_OK:                 retv = HTTP_ANSW_OK /* 200 OK */; break;  // 100 continue
                                                                           // 201 Created
                                                                           // 202 Accepted
                                                                           // 302 Found
                                                                           // 300 Multiple Choices

//    case E_INVALIDARG:         retv = ; break; // 411 Length Required
      case E_NOTIMPL:            retv = 501 /* Not Implemented */; break; // 505 HTTP Version Not Supported
//    case KP_E_FERROR:          retv = ; break;

      case KP_E_SYSTEM_ERROR:    retv = 500 /* Internal Server Error */; break;  // 409 Conflict
                                                                                 // 412 Precondition Failed

//    case KP_E_EOF:             retv = ; break;
      case KP_E_FILE_FORMAT:     retv = 415; break; // Unsupported Media Type // 417 Expectation Failed
                                                                              // 406 Not Acceptable

      case KP_E_FILE_NOT_FOUND:  retv = HTTP_ANSW_FILE_NOT_FOUND /* 404 Not Found */; break; // 410 Gone
                                                                                             // 301 Moved Permanently

//    case KP_E_DIR_ERROR:       retv = ; break;
//    case KP_E_OUTOFMEM:        retv = ; break;
      case KP_E_NO_FILE:         retv = 204 /* No Content */; break;
//    case KP_E_DOUBLE_UNGET:    retv = ; break;
//    case KP_E_UNKN_CHR:        retv = ; break;
//    case KP_E_COMMAND_ERROR:   retv = ; break;

      case KP_E_BUFFER_OVERFLOW: retv = 413 /* Request Entity Too Large */; break;  // 414 Request-URI Too long
                                                                                    // 416 Requested Range Not Satisfiable

//    case KP_E_FONT_UNDEF:      retv = ; break;
//    case KP_E_KWD_NOT_FOUND:   retv = ; break;
//    case KP_E_UNKNOWN_SYSTEM:  retv = ; break;
//    case KP_E_ILL_CODE:        retv = ; break;
//    case KP_E_CANCEL:          retv = ; break;
//    case KP_E_DOUBLE_CALL:     retv = ; break;

      case KP_E_TIMEOUT:         retv = 408 /* Request Timeout */; break; // 504 Gateway Timeout
//    case KP_E_OBJ_NOT_FOUND:   retv = ; break;
      case KP_E_NO_CONN:         retv = 408 /* Request Timeout */; break;

      case KP_E_TRANS_ERR:       retv = 408 /* Request Timeout */; break;  // 305 Use Proxy
                                                                           // 502 Bad Gateway

      case KP_E_REFUSED:         retv = 403 /* Forbidden */; break;
      case KP_E_ACCESS_DENIED:   retv = 401 /* Unauthorized */; break;  // 402 Payment Required
                                                                        // 407 Proxy Authentication Required
//    case KP_E_ILL_CHR:         retv = ; break;
//    case KP_E_DIV_ZERO:        retv = ; break;
//    case KP_E_ILLMATHARG:      retv = ; break;

      case KP_E_ILLFUNC:         retv = 400 /* Bad Request */; break;   // 405 Method Not Allowed

      case KP_E_NOTINST:         retv = 503 /* Service Unavailable */; break;
   }

// 101 Switching Protocols
// 203 Non-Authoritative Information
// 205 Reset Content
// 206 Partial Content
// 303 See Other
// 304 Not Modified
// 307 Temporary Redirect

return(retv);
}


// ------------------------------------
HRESULT KpErrorProcClass::TranslFromHTTP_RetCode(int iHTTP_RetCode)
{
HRESULT retc = (iHTTP_RetCode == HTTP_ANSW_OK)?S_OK:KP_E_NEG_ANSW;

   switch(iHTTP_RetCode)
   {
      case HTTP_ANSW_OK /* 200 OK */:
      case HTTP_ANSW_CONTINUE /* 100 */:
      case 201 /* Created */:
      case 202 /* Accepted */:
      case 300 /* Multiple Choices */:
                                                         retc = S_OK; break;

// ðitais atvejais reikëtø ðokti nuoroda, nurodyta headerio lauke Location:, kol kas nerealizuota (kliento gale)
      case 302 /* Found */ /* Moved Temporarily */:
      case 303 /* See Other */:
      case 307 /* Temporary Redirect */:
      case 301 /* Moved Permanently */:
      case 305 /* Use Proxy */:
                                                         retc = E_NOTIMPL; break;

      case 304 /* Not Modified */: // atsakymas á sàlyginæ GET uþklausà – tuðèias atsakymas apie nepasikeitusá failà (tikriausiai, pasitikrinimui, ar reikia perkrauti cache'intà failà)
                                   // að tokiø uþklausø kol kas nesiunèiu, tai ir atsakymo turëtø neateiti
                                                         retc = KP_E_FILE_FORMAT; break;

      case 411 /* Length Required */:                    retc = E_INVALIDARG; break;

      case 501 /* Not Implemented */:
      case 505 /* HTTP Version Not Supported */:         retc = E_NOTIMPL; break; // nerealizuota funkcija serverio gale

//    case :                                             retc = KP_E_FERROR; break;

      case 500 /* Internal Server Error */:
      case 409 /* Conflict */:
      case 412 /* Precondition Failed */:                retc = KP_E_SYSTEM_ERROR; break;

//    case :                                             retc = KP_E_EOF; break;

      case 415 /* Unsupported Media Type */:
      case 417 /* Expectation Failed */:
      case 406 /* Not Acceptable */:                     retc = KP_E_FILE_FORMAT; break;

      case HTTP_ANSW_FILE_NOT_FOUND /* 404 Not Found */:
      case 410 /* Gone */:
                                                         retc = KP_E_FILE_NOT_FOUND; break;

//    case :                                             retc = KP_E_DIR_ERROR; break;
//    case :                                             retc = KP_E_OUTOFMEM; break;
      case 204 /* No Content */:                         retc = KP_E_NO_FILE; break;
//    case :                                             retc = KP_E_DOUBLE_UNGET; break;
//    case :                                             retc = KP_E_UNKN_CHR; break;
//    case :                                             retc = KP_E_COMMAND_ERROR; break;

      case 413 /* Request Entity Too Large */:
      case 414 /* Request-URI Too long */:
      case 416 /* Requested Range Not Satisfiable */:    retc = KP_E_BUFFER_OVERFLOW; break;

//    case :                                             retc = KP_E_FONT_UNDEF; break;
//    case :                                             retc = KP_E_KWD_NOT_FOUND; break;
//    case :                                             retc = KP_E_UNKNOWN_SYSTEM; break;
//    case :                                             retc = KP_E_ILL_CODE; break;
//    case :                                             retc = KP_E_CANCEL; break;
//    case :                                             retc = KP_E_DOUBLE_CALL; break;

      case 502 /* Bad Gateway */:                        retc = KP_E_TRANS_ERR; break;

      case 408 /* Request Timeout */:                                                  // retc = KP_E_TRANS_ERR; break; // retc = KP_E_NO_CONN; break;
      case 504 /* Gateway Timeout */:                    retc = KP_E_TIMEOUT; break;

//    case :                                             retc = KP_E_OBJ_NOT_FOUND; break;

      case 401 /* Unauthorized */:                       retc = KP_E_ACCESS_DENIED; break;
      case 403 /* Forbidden */:
      case 402 /* Payment Required */:
      case 407 /* Proxy Authentication Required */:      retc = KP_E_REFUSED; break;

//    case :                                             retc = KP_E_ILL_CHR; break;
//    case :                                             retc = KP_E_DIV_ZERO; break;
//    case :                                             retc = KP_E_ILLMATHARG; break;

      case 400 /* Bad Request */:
      case 405 /* Method Not Allowed */:                 retc = KP_E_ILLFUNC; break;

      case 503 /* Service Unavailable */:                retc = KP_E_NOTINST; break;
   }

// 101 Switching Protocols
// 203 Non-Authoritative Information
// 205 Reset Content
// 206 Partial Content
// 303 See Other
// 304 Not Modified
// 307 Temporary Redirect

return(retc);
}


// ---------------------
void StackDump
(
const HRESULT *
#if CompilerGr != Watcom
   plRetcAddrs
#endif
   , bool
#if CompilerGr != Watcom
      bDumpStack
#endif
)
{
HRESULT retc = S_OK;

#if CompilerGr != Watcom
// KP_ASSERT(sizeof(int) == sizeof(unsigned int *), KP_E_SYSTEM_ERROR, null, True); // negalima – mes jau klaidoje
   if(sizeof(int) != sizeof(unsigned int *))
   {
      PutLogMessage_("Sistemos klaida %s %d", __FILE__, __LINE__);
      retc = KP_E_SYSTEM_ERROR;
   }

// ---------------------
   if(SUCCEEDED(retc))
   {
CONTEXT context;
      context.ContextFlags = CONTEXT_CONTROL;
      GetThreadContext(GetCurrentThread(), &context);

unsigned int ebp_buf = 0;
#if CompilerGr == Mingw
      asm("movl %%ebp, %0\n":"=r"(ebp_buf));
#else
      ebp_buf = context.Ebp;
#endif
#if ((Compiler != Mingw) || (MingwVer < 471))
PutLogMessage_("Thread context:  eip: %08x  esp: %08x  ebp: %08x  ebp_buf: %08x  &retc: %08x  StackTop: %08x", context.Eip, context.Esp, context.Ebp, ebp_buf, plRetcAddrs, StackTop);
#endif

// ----------------------
unsigned int *stack_top = NULL;

// Watcome kaþko treisinant *ebp turiná rodo 0x40-a maþesnio adreso
// ir stekas kaþkoks neaiðkus, nesimato, kaip per *bp galima bûtø atsekti call trace
#if (CompilerGr != Watcom) && ((Compiler != Mingw) || ((MingwVer > 441) && (MingwVer < 471)))
THREAD_BASIC_INFORMATION basicInfo;
// NT_TIB tib;
NT_TIB *tib_ptr;
// Get TEB address
      NtQueryInformationThread(GetCurrentThread(), ThreadBasicInformation, &basicInfo, sizeof(THREAD_BASIC_INFORMATION), NULL);
// Read TIB
//    NtReadVirtualMemory(GetCurrentProcess(), basicInfo.TebBaseAddress, &tib, sizeof(NT_TIB), NULL);
      tib_ptr = (NT_TIB *)basicInfo.TebBaseAddress;
// Check tib.StackBase and tib.StackLimit

      stack_top = (unsigned int *)((tib_ptr != NULL)?tib_ptr->StackBase:0x0);
      PutLogMessage_("Stack trace:  StackBase: %08x  StackLimit: %08x", stack_top, (tib_ptr != NULL)?tib_ptr->StackLimit:0x0);
      if(stack_top == 0L)
#endif
         stack_top = (unsigned int *)StackTop;

// ----------------------
unsigned char *out_buf = null;
//    KP_NEWA(out_buf, unsigned char, KP_MAX_FILE_LIN_LEN + 1); // siaip iskvieciamas ir is KP_NEWA(), gali ir uzsiciklint
      out_buf = new unsigned char[KP_MAX_FILE_LIN_LEN + 1];

      if(out_buf != null)
      {
         out_buf[0] = Nul;
const unsigned int *stack_ptr = (const unsigned int *)ebp_buf;
         while((stack_ptr < stack_top - ((stack_top != (unsigned int *)StackTop)?0x40:0x0)) && (strlen(out_buf) <= (KP_MAX_FILE_LIN_LEN - MAX_LONG_HEX_DIGITS - 1)))
         {
unsigned char hex_buf[MAX_LONG_HEX_DIGITS + 1 + 1];
            sprintf((char *)hex_buf, "%08x ", stack_ptr[1]);
            strcat(out_buf, hex_buf);
            stack_ptr = (const unsigned int *)(*stack_ptr);
         }
         PutLogMessage_(out_buf);
      }

//    KP_DELETEA(out_buf); // siaip iskvieciamas ir is KP_DELETE(), gali ir uzsiciklint
      if(out_buf != null) delete [] out_buf;
      out_buf = null;

// ---------------------
      if(bDumpStack)
      {
// const unsigned int *pnti = (const unsigned int *)(((unsigned int)plRetcAddrs & 0xFFFFFF00) - 0x400);
// const unsigned int *pnti = (const unsigned int *)((unsigned int)plRetcAddrs & 0xFFFFFF00);
const unsigned int *pnti = (const unsigned int *)(ebp_buf & 0xFFFFFF00);

const unsigned int *pntd = NULL;
         if(plRetcAddrs != NULL) pntd = (const unsigned int *)((((unsigned int)plRetcAddrs) + 0x20) & 0xFFFFFFE0);
         else pntd = (const unsigned int *)((ebp_buf & 0xFFFFFF00) + 0x400);
         if(pntd > stack_top) pntd = (const unsigned int *)(((unsigned int)stack_top & 0xFFFFFFE0) - 0x20);

int cnt = (pntd - pnti) / 8;
         PutLogMessage_("Stack dump: &retc: %x", plRetcAddrs);
//       for(int ii = 0; ii < 64; ii++)
//       for(int ii = 0; ii < 32; ii++)
         for(int ii = 0; ii < cnt; ii++)
            PutLogMessage_("%08x: %08x %08x %08x %08x %08x %08x %08x %08x",
               &pnti[ii * 8 + 0], // pnti + ii * 8,
               pnti[ii * 8 + 0], pnti[ii * 8 + 1], pnti[ii * 8 + 2], pnti[ii * 8 + 3],
               pnti[ii * 8 + 4], pnti[ii * 8 + 5], pnti[ii * 8 + 6], pnti[ii * 8 + 7]);
      }

   } // if(SUCCEEDED(retc))

#endif // #if CompilerGr != Watcom
}


// --------------------------------------------------
const HRESULT KpErrorProcClass::OutputErrorMessage
(
   HRESULT lhRetc,
   const unsigned char *lpszMessageText,
   bool bPutMessageAndSetError, // former bSevereError
   const char *lpszSourceFile,
   int iSourceLine,
   long lMainKeyId,
// #if (Envir==MSWin32) || (Envir==MSWin32Mfc)
   void /* KpConsole */ *pListBox
// #else
// void *pListBox
// #endif
//    = NULL
   ,
   bool
#if (Envir==MSWin32) || (Envir==MSWin32Mfc)
      bPutMessage // = True
#endif
   ,
   bool bSevereError, // = True
   bool
#if (Envir==MSWin32) || (Envir==MSWin32Mfc)
      bSendDiagMsg // = True
#endif
   ,
   const HRESULT *
// #if (Envir==MSWin32) || (Envir==MSWin32Mfc)
      plRetcAddrs
// #endif
)
{
HRESULT retc = lhRetc;
#if (Envir==MSWin32) || (Envir==MSWin32Mfc)
HRESULT retc0=S_OK;
#endif
unsigned char msg[KP_MSG_LEN+1];
unsigned char msg_text[KP_MSG_LEN+1];
unsigned char out_text[KP_MAX_FILE_LIN_LEN+1]; // [KP_MAX_FILE_LIN_WDT+1];
unsigned char tmp_text[KP_MSG_LEN + 1];
long main_key_id;
int ii, jj;
int msg_tail_pos=0;
#if (Envir==MSWin32) || (Envir==MSWin32Mfc)
unsigned char log_fname /* app_name */[KP_MAX_FNAME_LEN+1];
// unsigned char long_path[KP_MAX_FNAME_LEN+1];
#endif

   if(retc == KP_S_DIAG_MSG) retc = S_OK;

   if(lpszMessageText!=NULL)
   {
      strncpy(msg, lpszMessageText, KP_MSG_LEN-2); msg[KP_MSG_LEN-2+1]=Nul;
      sprintf((char *)msg_text, ": %s", msg);
   }
   else msg_text[0]=Nul;
   if(lMainKeyId!=0L) main_key_id=lMainKeyId;
   else main_key_id=lMsgPar;

   if
   (
      (lhLastRetc!=lhRetc) ||
      (strcmp((const char *)lpszLastMessageText, (const char *)msg_text)!=0) ||
      (bLastSevereError!=bSevereError) ||
      (strcmp((const char *)lpszLastSourceFile, lpszSourceFile)!=0) ||
      (iLastSourceLine!=iSourceLine) ||
      (lLastMainKeyId!=main_key_id) ||
      (pListBox!=NULL)
   )
   {
      lhLastRetc=lhRetc;
      strncpy((char *)lpszLastMessageText, (const char *)msg_text, KP_MSG_LEN);
      lpszLastMessageText[KP_MSG_LEN]=Nul;
      bLastSevereError=bSevereError;
      strncpy((char *)lpszLastSourceFile, lpszSourceFile, KP_MAX_FNAME_LEN);
      lpszLastSourceFile[KP_MAX_FNAME_LEN]=Nul;
      iLastSourceLine=iSourceLine;
      lLastMainKeyId=main_key_id;

      FormatErrorMessage(lhRetc, msg);

      out_text[0] = Nul;
      if(FAILED(retc))
      {
         strcpy(out_text, bSevereError?KP_MSG_ERROR:KP_MSG_WARNING);

//       sprintf((char *)tmp_text, " %lx: ", lhRetc);
//       strcat(out_text, tmp_text);
         strcat(out_text, ": ");
      }

      ii=strlen(out_text); jj=KP_MAX_FILE_LIN_WDT-ii; if(jj<0) jj=0;
      strncpy((char *)out_text+ii, (const char *)msg, jj);
      out_text[KP_MAX_FILE_LIN_WDT]=Nul;

      ii=strlen(out_text); jj=KP_MAX_FILE_LIN_WDT-ii; if(jj<0) jj=0;
      strncpy((char *)out_text+ii, (const char *)msg_text, jj);
      out_text[KP_MAX_FILE_LIN_WDT]=Nul;

      sprintf((char *)tmp_text, (const char *)KP_MSG_FILE_LINE, lhRetc, lpszSourceFile, iSourceLine);
      ii=strlen(out_text); jj=KP_MAX_FILE_LIN_WDT-ii; if(jj<0) jj=0;
      msg_tail_pos=ii;
      strncpy(out_text+ii, tmp_text, jj);
      out_text[KP_MAX_FILE_LIN_WDT]=Nul;

      sprintf((char *)tmp_text, lLastMainKeyId!=0L?(const char *)KP_MSG_ENTRY_ID:"", lLastMainKeyId);
      ii=strlen(out_text); jj=KP_MAX_FILE_LIN_WDT-ii; if(jj<0) jj=0;
      strncpy(out_text+ii, tmp_text, jj);
      out_text[KP_MAX_FILE_LIN_WDT]=Nul;

      sprintf((char *)tmp_text, strlen(szaMsgText)>0?(const char *)KP_MSG_ENTRY:"", szaMsgText);
      ii=strlen(out_text); jj=KP_MAX_FILE_LIN_WDT-ii; if(jj<0) jj=0;
      strncpy(out_text+ii, tmp_text, jj);
      out_text[KP_MAX_FILE_LIN_WDT]=Nul;

// ----------------------
#if (Envir==MSWin32) || (Envir==MSWin32Mfc)
#  ifdef Debug // #if FALSE //
//    SplitToLines(out_text, 20, KP_MAX_FILE_LIN_WDT);
      if((pListBox!=NULL) || (m_pClMessages!=NULL))
      {
         if(pListBox!=NULL) retc0=((KpConsole *)pListBox)->AddStringNoMessage(out_text);
         else retc0=m_pClMessages->AddStringNoMessage(out_text);
         if(FAILED(retc0) && bPutMessage) KpMsgOut(out_text, bSevereError?IDI_ERROR:IDI_WARNING, KP_MB_TESTI);
      }
      else if(bPutMessage) KpMsgOut(out_text, bSevereError?IDI_ERROR:IDI_WARNING, KP_MB_TESTI);

#  endif // #else // #ifdef Debug

      retc0 = PutLogMessage(out_text, log_fname); // app_name);

// ----------------------
      if(bSevereError /* && (plRetcAddrs != NULL) */) StackDump(plRetcAddrs);

// ----------------------
//    if(SUCCEEDED(retc0)) if(!GetLongPathName((const char *)log_fname /* app_name */, (char *)long_path, KP_MAX_FNAME_LEN))
//       retc0 = KP_E_SYSTEM_ERROR;

      if(bPutMessage)
      {
#  ifndef Debug
         out_text[msg_tail_pos] = Nul;
#  endif
         if(FAILED(retc0))
         {
#  ifndef Debug
            if(msg_tail_pos /* strlen(out_text) */ + strlen(KP_MSG_ERROR_HELP) <
               KP_MAX_FILE_LIN_LEN) strcat(out_text, KP_MSG_ERROR_HELP);
#  endif
            KpMsgOut(out_text, bSevereError?IDI_ERROR:IDI_WARNING, KP_MB_TESTI);
         }
         else
#  ifndef Debug
//          if(bSevereError)
            if(bPutMessageAndSetError)
#  endif
            {
#  ifdef KP_ERR_SENDDIAGMSG
               retc0 = S_OK;
               if(bSevereError && bSendDiagMsg)
                  retc0 = SendDiagMsg(out_text, (FAILED(retc) && bSevereError)?IDI_ERROR:(FAILED(retc)?IDI_WARNING:IDI_INFORMATION), lhRetc, out_text + msg_tail_pos + 1);
               if((!bSevereError) || (!bSendDiagMsg) || (FAILED(retc0) && (retc0 != KP_E_CANCEL)))
#  endif
               {
#  ifndef Debug
                  if(bSevereError && bSendDiagMsg)
                  {
                     if(msg_tail_pos /* strlen(out_text) */ + strlen(KP_MSG_ERROR_HELP) <
                        KP_MAX_FILE_LIN_LEN) strcat(out_text, KP_MSG_ERROR_HELP);
                     jj = strlen(out_text);
                     if(jj + strlen(KP_MSG_ERROR_HELP_REST) +
                        strlen(log_fname /* long_path */ /* app_name */) < KP_MAX_FILE_LIN_LEN)
                           sprintf((char *)out_text + jj, (const char *)KP_MSG_ERROR_HELP_REST,
                              log_fname /* long_path */ /* app_name */);
                     CopyLogToDesktop();
                  }
#  endif
                  KpMsgOut(out_text, (FAILED(retc) && bSevereError)?IDI_ERROR:(FAILED(retc)?IDI_WARNING:IDI_INFORMATION), KP_MB_TESTI);
               }
            }
      }
#else // #if (Envir==MSWin32) || (Envir==MSWin32Mfc)

      printf((char *)out_text);
      printf("\n");
      PutLogMessage(out_text);
      if(bSevereError /* && (plRetcAddrs != NULL) */) StackDump(plRetcAddrs);
#endif
   }

return(
#ifdef IGNORE_ERRORS
S_OK
#else
(bPutMessageAndSetError && bSevereError)?retc:S_OK
#endif
);
}


// --------------------------------------------------
const HRESULT KpErrorProcClass::OutputErrorMessage
(
   HRESULT lhRetc,
   const char *lpszMessageText,
   bool bPutMessageAndSetError, // former bSevereError
   const char *lpszSourceFile,
   int iSourceLine,
   long lMainKeyId,
// #if (Envir==MSWin32) || (Envir==MSWin32Mfc)
   void /* KpConsole */ *pListBox
// #else
// void *pListBox
// #endif
//    = NULL
   ,
   bool bPutMessage, // = True
   bool bSevereError, // = True
   bool bSendDiagMsg, // = TRUE
   const HRESULT *plRetcAddrs
)
{
return(OutputErrorMessage(lhRetc, (const unsigned char *)lpszMessageText, bPutMessageAndSetError, lpszSourceFile, iSourceLine, lMainKeyId, pListBox, bPutMessage, bSevereError, bSendDiagMsg, plRetcAddrs));
}


// --------------------------------------------------
const HRESULT KpErrorProcClass::OutputErrorMessage
(
   HRESULT lhRetc,
   const KpChar *iazMessageText,
   bool bPutMessageAndSetError, // former bSevereError
   const char *lpszSourceFile,
   int iSourceLine,
   long lMainKeyId,
// #if (Envir==MSWin32) || (Envir==MSWin32Mfc)
   void /* KpConsole */ *pListBox
// #else
// void *pListBox
// #endif
//    = NULL
   ,
   bool bPutMessage, // = True
   bool bSevereError, // = True
   bool bSendDiagMsg, // = TRUE
   const HRESULT *plRetcAddrs
)
{
HRESULT retc = S_OK;
unsigned char *str_buf = null;

   if(iazMessageText != NULL)
   {
//    KP_NEWA(str_buf, unsigned char, TvKpStrLen(iazMessageText) + 1); // siaip iskvieciamas ir is KP_NEWA(), gali ir uzsiciklint
      str_buf = new unsigned char[TvKpStrLen(iazMessageText) + 1];
      if(str_buf == null) retc = KP_E_OUTOFMEM;
      if(SUCCEEDED(retc)) KptStrDecode(str_buf, iazMessageText, TV_MAIN_CTBL);
   }

   if(SUCCEEDED(retc)) retc = OutputErrorMessage(lhRetc, str_buf, bPutMessageAndSetError, lpszSourceFile, iSourceLine, lMainKeyId, pListBox, bPutMessage, bSevereError, bSendDiagMsg, plRetcAddrs);

// KP_DELETEA(str_buf); // siaip iskvieciamas ir is KP_DELETE(), gali ir uzsiciklint
   if(str_buf != null) delete [] str_buf;
   str_buf = null;

return(retc);
}


// --------------------------------------------------
#if (Envir==MSWin32) || (Envir==MSWin32Mfc) || (Envir==MSWin32Con) || (Envir==MSWin32ConMfc)
#ifdef KPSTTRG_DLL
extern "C" __declspec(dllexport)
#endif
const HRESULT KpErrorProcClass::OutputErrorMessage
(
   HRESULT lhRetc,
   LONG lWindowsErrorCode,  // HINSTANCE hErrorCode,
   bool bPutMessageAndSetError, // former bSevereError
   const char *lpszSourceFile,
   int iSourceLine,
   long lMainKeyId,
// #if (Envir==MSWin32) || (Envir==MSWin32Mfc)
   void /* KpConsole */ *pListBox
// #else
// void *pListBox
// #endif
//    = NULL
   ,
   bool bPutMessage,    // = True
   bool bSevereError,   // = True
   bool bSendDiagMsg,   // = TRUE
   const HRESULT *plRetcAddrs
)
{
HRESULT retc = S_OK;
unsigned char *pszMsg1 = null;

// KP_NEWA(pszMsg1, unsigned char, KP_MAX_FILE_LIN_LEN + 1); // siaip iskvieciamas ir is KP_NEWA(), gali ir uzsiciklint
   pszMsg1 = new unsigned char[KP_MAX_FILE_LIN_LEN + 1];

   if((pszMsg1 != null) && SUCCEEDED(retc))
      retc = FormatErrorMessageSystem(lWindowsErrorCode, pszMsg1, True);

   if(SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(lhRetc, pszMsg1, bPutMessageAndSetError, lpszSourceFile, iSourceLine, lMainKeyId, pListBox, bPutMessage, bSevereError, bSendDiagMsg, plRetcAddrs);

// KP_DELETEA(pszMsg1); // siaip iskvieciamas ir is KP_DELETE(), gali ir uzsiciklint
   if(pszMsg1 != null) delete [] pszMsg1;
   pszMsg1 = null;

return(retc);
}
#endif // #if (Envir==MSWin32) || (Envir==MSWin32Mfc) || (Envir==MSWin32Con) || (Envir==MSWin32ConMfc)


// --------------------------------------------------
HRESULT KpOutputErrorMessage
(
   const HRESULT lhRetc,
   const unsigned char *lpszMessageText,
   bool bPutMessageAndSetError, // former bSevereError
   const char *lpszSourceFile,
   const int iSourceLine,
   const long lMainKeyId,
// #if (Envir==MSWin32) || (Envir==MSWin32Mfc)
   void /* KpConsole */ *pListBox
// #else
// void *pListBox
// #endif
//    = NULL
   ,
   bool bPutMessage,    // = True
   bool bSevereError,   // = True
   bool bSendDiagMsg,   // = TRUE
   const HRESULT *plRetcAddrs
)
{
return(KpErrorProc.OutputErrorMessage(lhRetc, lpszMessageText, bPutMessageAndSetError, lpszSourceFile, iSourceLine, lMainKeyId, pListBox, bPutMessage, bSevereError, bSendDiagMsg, plRetcAddrs));
}


HRESULT KpOutputErrorMessage
(
   const HRESULT lhRetc,
   const char *lpszMessageText,
   bool bPutMessageAndSetError,
   const char *lpszSourceFile,
   const int iSourceLine,
   const long lMainKeyId,
   void *pListBox,
   bool bPutMessage,
   bool bSevereError,
   bool bSendDiagMsg,
   const HRESULT *plRetcAddrs
)
{
return(KpErrorProc.OutputErrorMessage(lhRetc, lpszMessageText, bPutMessageAndSetError, lpszSourceFile, iSourceLine, lMainKeyId, pListBox, bPutMessage, bSevereError, bSendDiagMsg, plRetcAddrs));
}


HRESULT KpOutputErrorMessage
(
   const HRESULT lhRetc,
   const KpChar *iazMessageText,
   bool bPutMessageAndSetError,
   const char *lpszSourceFile,
   const int iSourceLine,
   const long lMainKeyId,
   void *pListBox,
   bool bPutMessage,
   bool bSevereError,
   bool bSendDiagMsg,
   const HRESULT *plRetcAddrs
)
{
return(KpErrorProc.OutputErrorMessage(lhRetc, iazMessageText, bPutMessageAndSetError, lpszSourceFile, iSourceLine, lMainKeyId, pListBox, bPutMessage, bSevereError, bSendDiagMsg, plRetcAddrs));
}


HRESULT KpOutputErrorMessage
(
   const HRESULT lhRetc,
   LONG lWindowsErrorCode,
   bool bPutMessageAndSetError,
   const char *lpszSourceFile,
   const int iSourceLine,
   const long lMainKeyId,
   void *pListBox,
   bool bPutMessage,
   bool bSevereError,
   bool bSendDiagMsg,
   const HRESULT *plRetcAddrs
)
{
return(KpErrorProc.OutputErrorMessage(lhRetc, lWindowsErrorCode, bPutMessageAndSetError, lpszSourceFile, iSourceLine, lMainKeyId, pListBox, bPutMessage, bSevereError, bSendDiagMsg, plRetcAddrs));
}


// --------------------------------------------------
#ifdef KPSTTRG_DLL
extern "C" __declspec(dllexport)
#endif
void KpProcessError(HRESULT lhRetc, const wchar_t *wszMessageText, LONG lWindowsErrorCode, const char *lpszSourceFile, int iSourceLine)
{
static unsigned char msg_buf[KP_MAX_FILE_LIN_LEN + 1];
static wchar_t msg_buf_w[KP_MAX_FILE_LIN_LEN + 1];

   if(wszMessageText != NULL)
   {
      wcsncpy(msg_buf_w, wszMessageText, KP_MAX_FILE_LIN_LEN);
      msg_buf_w[KP_MAX_FILE_LIN_LEN] = 0;

      KptUnicodeToStr(msg_buf, msg_buf_w, TV_MAIN_CTBL);

      KpErrorProc.OutputErrorMessage(lhRetc, msg_buf, True, lpszSourceFile, iSourceLine, 0L);
   }
   else KpErrorProc.OutputErrorMessage(lhRetc, lWindowsErrorCode, True, lpszSourceFile, iSourceLine, 0L);
}


// -------------------------------------- compatibility with kpx
void cferr(int
#ifdef Debug
err
#endif
, const char *
#ifdef Debug
lpszSourceFile
#endif
, int
#ifdef Debug
iSourceLine
#endif
)
{
HRESULT retc = S_OK;

#ifdef Debug
   switch(err)
   {
   case  1: retc = KP_E_FILE_NOT_FOUND; break; // "File not found"
   case  2: retc = KP_E_DIR_ERROR; break; // "Directory I/O error"
   case  3: retc = KP_E_FERROR; break; // "File input error"
   case  4: retc = KP_E_FERROR; break; // "File output error"
   case  5: retc = KP_E_FERROR; break; // "Device full"
// case  6: retc = E_INVALIDARG; break; // "User break"
   case  7: retc = KP_E_FILE_NOT_FOUND; break; // "Dictionary file not found"
   case  8: retc = KP_E_FERROR; break; // "Dictionary file input error"
   case  9: retc = KP_E_FERROR; break; // "TXT.CFG file input error"
   case 10: retc = KP_E_FILE_FORMAT; break; // "Illegal TXT.CFG file format"
   case 11: retc = KP_E_FERROR; break; // "TXT.CFG file output error"
   default: retc = E_INVALIDARG; break;
   }
   if(FAILED(retc)) KpErrorProc.OutputErrorMessage(retc, null, False, lpszSourceFile, iSourceLine, err, NULL);
#endif
}


// ----------------------------------
#ifdef KP_ERR_SENDDIAGMSG
const HRESULT KpErrorProcClass::OpenDiagMsgWindow(unsigned char *lpszMsg, LPCTSTR lpszIconID, HRESULT lhRetc)
{
HRESULT retc = S_OK;
WNDCLASSEX wcx;
HDC dc;
int wnd_x = 0;
int wnd_y = 0;
int wnd_dx = 100;
int wnd_dy = 100;
SendDiagMsgPars *msg_pars_ptr = NULL;

   m_bShiftFl = False;

// KP_NEW(msg_pars_ptr, SendDiagMsgPars); // siaip iskvieciamas ir is KP_NEW(), gali ir uzsiciklint
   msg_pars_ptr = new SendDiagMsgPars;

   if(SUCCEEDED(retc))
   {
      wcx.hInstance     = hKpInstance;
      wcx.lpszClassName = ((lhRetc == KP_S_DIAG_MSG)?"KPDIAGMSG":"KPERRMSG"),
      wcx.lpfnWndProc   = (WNDPROC)((lhRetc == KP_S_DIAG_MSG)?KpErrSendDiagMsgProc:KpErrSendErrMsgProc);
      wcx.style         = CS_DBLCLKS;
      wcx.cbSize        = sizeof(WNDCLASSEX);
      wcx.hIcon         = ::LoadIcon(NULL /* hKpInstance */, lpszIconID); // MAKEINTRESOURCE(lpszIconID));
      wcx.hIconSm       = ::LoadIcon(NULL /* hKpInstance */, lpszIconID); // MAKEINTRESOURCE(lpszIconID));
      wcx.hCursor       = ::LoadCursor(NULL, IDC_ARROW);
      wcx.lpszMenuName  = 0;
      wcx.cbClsExtra    = 0;
      wcx.cbWndExtra    = 0;
      wcx.hbrBackground = CreateSolidBrush(GetSysColor(iaColorMap[KpShadowNorm])); // (HBRUSH)COLOR_BACKGROUND;

      if(!RegisterClassEx(&wcx))
      {
//       retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      }
   }

   if(SUCCEEDED(retc))
   {
      dc = GetDC(HWND_DESKTOP);
      KP_ASSERT(dc, KP_E_SYSTEM_ERROR, GetLastError(), True);
   }

   if(SUCCEEDED(retc))
   {
      wnd_dx = ((lhRetc == KP_S_DIAG_MSG)?KPDIAGMSG_WND_DX:KPERRMSG_WND_DX);
      wnd_dy = ((lhRetc == KP_S_DIAG_MSG)?KPDIAGMSG_WND_DY:KPERRMSG_WND_DY);
      wnd_x = (GetDeviceCaps(dc, HORZRES) - wnd_dx) / 2;
      wnd_y = (GetDeviceCaps(dc, VERTRES) - wnd_dy) / 2;

      if(msg_pars_ptr != NULL) msg_pars_ptr->m_lpszMsg = lpszMsg;
      if(msg_pars_ptr != NULL) msg_pars_ptr->m_lpszIconID = lpszIconID;

      m_hDiagMsgWindow = CreateWindowEx
      (
         0,                      // DWORD dwExStyle,      // extended window style
         ((lhRetc == KP_S_DIAG_MSG)?"KPDIAGMSG":"KPERRMSG"),
         (char *)KP_MSG_DIAG_MSG_TITLE,  // LPCTSTR lpWindowName, // pointer to window name
         WS_POPUPWINDOW|WS_VISIBLE|WS_CAPTION|WS_THICKFRAME, // |WS_BORDER|WS_POPUP, // DWORD dwStyle,        // window style
         wnd_x,  // CW_USEDEFAULT, // int x,               // horizontal position of window
         wnd_y,  // CW_USEDEFAULT, // int y,               // vertical position of window
         wnd_dx,          // int nWidth,           // window width
         wnd_dy,          // int nHeight,          // window height
         HWND_DESKTOP,           // HWND hWndParent,      // handle to parent or owner window
         0,                      // HMENU hMenu,          // handle to menu, or child-window identifier
         hKpInstance,
         msg_pars_ptr // NULL    // LPVOID lpParam        // pointer to window-creation data
      );

      KP_ASSERTE(m_hDiagMsgWindow, KP_E_SYSTEM_ERROR, GetLastError(), False);
   }

return(retc);
}
#endif


// -----------------------------------------
#ifdef KP_ERR_SENDDIAGMSG
BOOL CALLBACK KpErrSendDiagMsgProc(
  HWND hwndDlg,  // handle to dialog box
  UINT uMsg,     // message
  WPARAM wParam, // first message parameter
  LPARAM lParam  // second message parameter
)
{
HRESULT retc = S_OK;
int retp;
BOOL retw = FALSE;
bool endfl = False;
LPCREATESTRUCT cst_ptr = NULL;
SendDiagMsgPars *msg_pars_ptr = NULL;
LPCTSTR icon_id = NULL;
const unsigned char *msg_ptr = NULL;
unsigned char *formatted_msg = null;
HDC hdc = NULL;
PAINTSTRUCT ps;
OPENFILENAME op_fn_str;
static unsigned char att_fname[KP_MAX_FNAME_LEN + 1];
static unsigned char att_fname_sav[KP_MAX_FNAME_LEN + 1];
static unsigned char ini_dir[KP_MAX_FNAME_LEN + 1];
unsigned char filters[KP_MAX_FNAME_LEN + 1];
unsigned char *pntd;
unsigned char *pnts;

   retp = LOWORD(wParam);

   if(SUCCEEDED(retc)) switch(uMsg)
   {
   case WM_CREATE:

      cst_ptr = (LPCREATESTRUCT)lParam;
      if(cst_ptr != NULL) msg_pars_ptr = (SendDiagMsgPars *)cst_ptr->lpCreateParams;
      if(msg_pars_ptr != NULL)
      {
         icon_id = msg_pars_ptr->m_lpszIconID;
         msg_ptr = msg_pars_ptr->m_lpszMsg;
      }

      if(SUCCEEDED(retc)) retc = KpCreateIcon(hKpInstance, hwndDlg, NULL,
         LoadIcon(NULL /* hKpInstance */, icon_id),
         KPDIAGMSG_ICON_X, KPDIAGMSG_ICON_Y, KPDIAGMSG_ICON_WDT, KPDIAGMSG_ICON_WDT, 0);

// lauþom klaidos praneðimà
      if(SUCCEEDED(retc)) retc = WrapMsg(msg_ptr, &formatted_msg, NULL, KPDIAGMSG_MSG_NUMPOS);

      if(SUCCEEDED(retc)) retc = KpCreateStatic(hKpInstance, hwndDlg, NULL, formatted_msg,
         KPDIAGMSG_MSG_X, KPDIAGMSG_MSG_Y, KPDIAGMSG_MSG_DX, KPDIAGMSG_MSG_NUMLINES,
         KPDIAGMSG_MSG_STYLE, 0, 0, NULL);

//    KP_DELETEA(formatted_msg); // siaip iskvieciamas ir is KP_DELETEA(), gali ir uzsiciklint
      if(formatted_msg != null) delete [] formatted_msg;
      formatted_msg = null;

// lauþom paaiðkinimà
      if(SUCCEEDED(retc)) retc = WrapMsg(KP_MSG_DIAG_MSG_EXPL, &formatted_msg, NULL, KPDIAGMSG_EXPL_NUMPOS);

      if(SUCCEEDED(retc)) retc = KpCreateStatic(hKpInstance, hwndDlg, NULL,
         formatted_msg, KPDIAGMSG_EXPL_X, KPDIAGMSG_EXPL_Y,
         KPDIAGMSG_EXPL_DX, KPDIAGMSG_EXPL_NUMLINES, KPDIAGMSG_EXPL_STYLE, 0, 0, NULL);

//    KP_DELETEA(formatted_msg); // siaip iskvieciamas ir is KP_DELETEA(), gali ir uzsiciklint
      if(formatted_msg != null) delete [] formatted_msg;
      formatted_msg = null;

      if(SUCCEEDED(retc)) retc = KpCreateStatic(hKpInstance, hwndDlg, NULL,
         KP_MSG_DIAG_MSG_EMAIL_PROMPT, KPDIAGMSG_EMAIL_PROMPT_X, KPDIAGMSG_EMAIL_PROMPT_Y,
         KPDIAGMSG_EMAIL_PROMPT_DX, KPDIAGMSG_EMAIL_PROMPT_NUMLINES, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);

      if(SUCCEEDED(retc)) retc = KpCreateEdit(hKpInstance, hwndDlg,
         &(KpErrorProc.m_hDiagEmailEdit), KpErrorProc.m_lpszDiagEmail,
         KPDIAGMSG_EMAIL_EDIT_DX, KPDIAGMSG_EMAIL_EDIT_X, KPDIAGMSG_EMAIL_EDIT_Y,
         KPW_CONTROL_STYLE_NORMAL, WS_EX_CLIENTEDGE, 0, KPDIAGMSG_EMAIL_EDIT_NUMLINES);
      KP_ASSERT(KpErrorProc.m_hDiagEmailEdit != NULL, KP_E_SYSTEM_ERROR, null, True);

      if(SUCCEEDED(retc)) retc = KpCreateStatic(hKpInstance, hwndDlg, NULL,
         KP_MSG_DIAG_MSG_COMMENTS_PROMPT,
         KPDIAGMSG_COMMENTS_PROMPT_X, KPDIAGMSG_COMMENTS_PROMPT_Y,
         KPDIAGMSG_COMMENTS_PROMPT_DX, KPDIAGMSG_COMMENTS_PROMPT_NUMLINES,
         KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);

      if(SUCCEEDED(retc)) retc = KpCreateEdit(hKpInstance, hwndDlg,
         &(KpErrorProc.m_hDiagCommentsEdit), KpErrorProc.m_lpszDiagComments,
         KPDIAGMSG_COMMENTS_EDIT_DX, KPDIAGMSG_COMMENTS_EDIT_X, KPDIAGMSG_COMMENTS_EDIT_Y,
         KPW_CONTROL_STYLE_NORMAL, WS_EX_CLIENTEDGE, 0, KPDIAGMSG_COMMENTS_EDIT_NUMLINES);
      KP_ASSERT(KpErrorProc.m_hDiagCommentsEdit != NULL, KP_E_SYSTEM_ERROR, null, True);

      if(SUCCEEDED(retc)) retc = KpCreateStatic(hKpInstance, hwndDlg, NULL,
         KP_MSG_DIAG_MSG_FILE_PROMPT,
         KPDIAGMSG_FILE_PROMPT_X, KPDIAGMSG_FILE_PROMPT_Y,
         KPDIAGMSG_FILE_PROMPT_DX, KPDIAGMSG_FILE_PROMPT_NUMLINES,
         KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);

      if(SUCCEEDED(retc)) retc = KpCreateEdit(hKpInstance, hwndDlg,
         &(KpErrorProc.m_hDiagFileEdit), KpErrorProc.m_lpszDiagFile,
         KPDIAGMSG_FILE_EDIT_DX, KPDIAGMSG_FILE_EDIT_X, KPDIAGMSG_FILE_EDIT_Y,
         KPW_CONTROL_STYLE_NORMAL, WS_EX_CLIENTEDGE, 0, KPDIAGMSG_FILE_EDIT_NUMLINES);
      KP_ASSERT(KpErrorProc.m_hDiagFileEdit != NULL, KP_E_SYSTEM_ERROR, null, True);

      if(SUCCEEDED(retc)) retc = KpCreateButton(hKpInstance, hwndDlg,
         &(KpErrorProc.m_hDiagFileButton), KP_ID_OPEN, KP_IDI_OPEN_ICON,
         KPDIAGMSG_FILE_BUT_X, KPDIAGMSG_FILE_BUT_Y, KPW_BUTTON_HGT, KPW_BUTTON_HGT, 0, 0);
      KP_ASSERT(KpErrorProc.m_hDiagFileEdit != NULL, KP_E_SYSTEM_ERROR, null, True);


// lauþom antrà paaiðkinimà
      if(SUCCEEDED(retc)) retc = WrapMsg(KP_MSG_DIAG_MSG_EXPL1, &formatted_msg, NULL, KPDIAGMSG_EXPL_NUMPOS);

      if(SUCCEEDED(retc)) retc = KpCreateStatic(hKpInstance, hwndDlg, NULL,
         formatted_msg, KPDIAGMSG_EXPL1_X, KPDIAGMSG_EXPL1_Y,
         KPDIAGMSG_EXPL1_DX, KPDIAGMSG_EXPL1_NUMLINES, KPDIAGMSG_EXPL1_STYLE, 0, 0, NULL);

//    KP_DELETEA(formatted_msg); // siaip iskvieciamas ir is KP_DELETEA(), gali ir uzsiciklint
      if(formatted_msg != null) delete [] formatted_msg;
      formatted_msg = null;

      if(SUCCEEDED(retc)) retc = KpCreateButton(hKpInstance, hwndDlg,
         &(KpErrorProc.m_hDiagOkButton), IDOK, KP_MSG_SIUSTI,
         KPDIAGMSG_OK_BUT_X, KPDIAGMSG_OK_BUT_Y, KPW_BUTTON_WDT, KPW_BUTTON_HGT, 0, 0);
      KP_ASSERT(KpErrorProc.m_hDiagOkButton != NULL, KP_E_SYSTEM_ERROR, null, True);

      if(SUCCEEDED(retc)) retc = KpCreateButton(hKpInstance, hwndDlg,
         &(KpErrorProc.m_hDiagCancelButton), IDCANCEL, KP_MSG_ATSAUKTI,
         KPDIAGMSG_CANCEL_BUT_X, KPDIAGMSG_CANCEL_BUT_Y, KPW_BUTTON_WDT, KPW_BUTTON_HGT, 0, 0);
      KP_ASSERT(KpErrorProc.m_hDiagCancelButton != NULL, KP_E_SYSTEM_ERROR, null, True);

//    KP_DELETE(msg_pars_ptr); // siaip iskvieciamas ir is KP_DELETEA(), gali ir uzsiciklint
      if(msg_pars_ptr != NULL) delete msg_pars_ptr;
      msg_pars_ptr = NULL;

      break;

   case WM_INITDIALOG:
      retw = TRUE;
      break;

   case WM_PAINT:

      hdc = NULL;
      if(SUCCEEDED(retc))
      {
         hdc = BeginPaint(hwndDlg, &ps);
         KP_ASSERT(hdc, KP_E_SYSTEM_ERROR, GetLastError(), True);
      }

      if(SUCCEEDED(retc)) retc = KpDrawLine(hdc, KPDIAGMSG_LINE_X1, KPDIAGMSG_LINE0_Y,
         KPDIAGMSG_LINE_X2, KPDIAGMSG_LINE0_Y, KP_WND_SUNKEN, NULL);

//    if(SUCCEEDED(retc)) retc = KpDrawLine(hdc, KPDIAGMSG_LINE_X1, KPDIAGMSG_LINE1_Y,
//       KPDIAGMSG_LINE_X2, KPDIAGMSG_LINE1_Y, KP_WND_SUNKEN, NULL);

      if(SUCCEEDED(retc)) retc = KpDrawLine(hdc, KPDIAGMSG_LINE_X1, KPDIAGMSG_LINE2_Y,
         KPDIAGMSG_LINE_X2, KPDIAGMSG_LINE2_Y, KP_WND_SUNKEN, NULL);

      if(SUCCEEDED(retc)) EndPaint(hwndDlg, &ps);

      retw = DefWindowProc(hwndDlg, uMsg, wParam, lParam);

      break;

   case WM_CLOSE:
      endfl = True;
      retw = DefWindowProc(hwndDlg, uMsg, wParam, lParam);
      break;

   case WM_QUIT:
      switch(retp)
      {
         case IDCANCEL: retc = KP_E_CANCEL; break;
         case IDABORT: retc = KP_E_SYSTEM_ERROR; break;
      }
      endfl = True;
      break;

   case WM_COMMAND:
      switch(LOWORD(wParam))
      {
      case IDCANCEL:
//       retc = KP_E_CANCEL;
      case IDOK:
         endfl = True;
         break;

      case KP_ID_OPEN:
         att_fname[0] = Nul;
         if(KpErrorProc.m_hDiagFileEdit != NULL)
         {
            SendMessage(KpErrorProc.m_hDiagFileEdit, WM_GETTEXT, KP_MAX_FNAME_LEN, (LPARAM)att_fname);
            att_fname[KP_MAX_FNAME_LEN] = Nul;

            op_fn_str.lStructSize = sizeof(op_fn_str);
            op_fn_str.hwndOwner = hwndDlg;
            op_fn_str.hInstance = hKpInstance;

            strcpy(filters, KP_MSG_ALL_FILES);
            pntd = filters + strlen(filters) + 1;
            strcpy(pntd, "*.*");
            pntd += strlen(pntd) + 1;
            *(pntd++) = Nul;
            *(pntd++) = Nul;
            op_fn_str.lpstrFilter = (const char *)filters;

            op_fn_str.lpstrCustomFilter = NULL;
            op_fn_str.nMaxCustFilter = 0;
            op_fn_str.nFilterIndex = 1;
            op_fn_str.lpstrFile = (char *)att_fname;
            op_fn_str.nMaxFile = KP_MAX_FNAME_LEN;
            op_fn_str.lpstrFileTitle = NULL;
            op_fn_str.nMaxFileTitle = 0;

            strcpy(ini_dir, att_fname);
            pntd = ini_dir;
            do
            {
               pnts = strchr(pntd, '\\');
               if(pnts) pntd = pnts + 1;
            } while(pnts);
            if(pntd == ini_dir)
            {
               strcpy(ini_dir, ".\\");
               op_fn_str.nFileOffset = (WORD)0;
            }
            else
            {
               *pntd = Nul;
               op_fn_str.nFileOffset = (WORD)strlen(ini_dir);
            }
            op_fn_str.lpstrInitialDir = (char *)ini_dir;

            op_fn_str.lpstrTitle = (const char *)KP_MSG_DIAG_MSG_SEL_FILE;
            op_fn_str.Flags = 0;

            pnts = strchr(att_fname, '.');
            if(pnts != NULL) op_fn_str.nFileExtension = pnts - att_fname + 1;
            else op_fn_str.nFileExtension = strlen(att_fname);

            op_fn_str.lpstrDefExt = "*";
            op_fn_str.lCustData = 0L;
            op_fn_str.lpfnHook = 0L;
            op_fn_str.lpTemplateName = NULL;

            strcpy(att_fname_sav, att_fname);

//          if(!GetOpenFileName(&op_fn_str))
            {
#if FALSE
// nesuveikia, jei neteisingas pradinio failo vardas - isvalom
               att_fname[0] = Nul;

               strcpy(ini_dir, ".\\");
               op_fn_str.nFileOffset = (WORD)0;
               op_fn_str.nFileExtension = 0;
#endif
               KP_ASSERTE(GetOpenFileName(&op_fn_str), KP_E_CANCEL, null, False);
            }
            if(FAILED(retc))
            {
               strcpy(att_fname, att_fname_sav);
               retc = S_OK;
            }

            SendMessage(KpErrorProc.m_hDiagFileEdit, WM_SETTEXT, 0, (LPARAM)att_fname);
         }
         break;



      }
      break;

   default:
      retw = DefWindowProc(hwndDlg, uMsg, wParam, lParam);
      break;
   }

   if(endfl && SUCCEEDED(retc))
   {
      PostMessage(NULL, uMsg, wParam, lParam);
      retw = TRUE;
   }

   if(FAILED(retc)) PostQuitMessage(IDABORT);

return(retw);
}


BOOL CALLBACK KpErrSendErrMsgProc(
  HWND hwndDlg,  // handle to dialog box
  UINT uMsg,     // message
  WPARAM wParam, // first message parameter
  LPARAM lParam  // second message parameter
)
{
HRESULT retc = S_OK;
int retp;
BOOL retw = FALSE;
bool endfl = False;
LPCREATESTRUCT cst_ptr = NULL;
SendDiagMsgPars *msg_pars_ptr = NULL;
LPCTSTR icon_id = NULL;
const unsigned char *msg_ptr = NULL;
unsigned char *formatted_msg = null;
HDC hdc = NULL;
PAINTSTRUCT ps;

   retp = LOWORD(wParam);

   if(SUCCEEDED(retc)) switch(uMsg)
   {
   case WM_CREATE:

      cst_ptr = (LPCREATESTRUCT)lParam;
      if(cst_ptr != NULL) msg_pars_ptr = (SendDiagMsgPars *)cst_ptr->lpCreateParams;
      if(msg_pars_ptr != NULL)
      {
         icon_id = msg_pars_ptr->m_lpszIconID;
         msg_ptr = msg_pars_ptr->m_lpszMsg;
      }

      if(SUCCEEDED(retc)) retc = KpCreateIcon(hKpInstance, hwndDlg, NULL,
         LoadIcon(NULL /* hKpInstance */, icon_id),
         KPERRMSG_ICON_X, KPERRMSG_ICON_Y, KPERRMSG_ICON_WDT, KPERRMSG_ICON_WDT, 0);

// lauþom klaidos praneðimà
      if(SUCCEEDED(retc)) retc = WrapMsg(msg_ptr, &formatted_msg, NULL, KPERRMSG_MSG_NUMPOS);

      if(SUCCEEDED(retc)) retc = KpCreateStatic(hKpInstance, hwndDlg, NULL, formatted_msg,
         KPERRMSG_MSG_X, KPERRMSG_MSG_Y, KPERRMSG_MSG_DX, KPERRMSG_MSG_NUMLINES,
         KPERRMSG_MSG_STYLE, 0, 0, NULL);

//    KP_DELETEA(formatted_msg); // siaip iskvieciamas ir is KP_DELETEA(), gali ir uzsiciklint
      if(formatted_msg != null) delete [] formatted_msg;
      formatted_msg = null;

      if(SUCCEEDED(retc)) retc = KpCreateStatic(hKpInstance, hwndDlg, NULL,
         KP_MSG_DIAG_MSG_EMAIL_PROMPT,
         KPERRMSG_EMAIL_PROMPT_X, KPERRMSG_EMAIL_PROMPT_Y, KPERRMSG_EMAIL_PROMPT_DX,
         KPERRMSG_EMAIL_PROMPT_NUMLINES, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);

      if(SUCCEEDED(retc)) retc = KpCreateEdit(hKpInstance, hwndDlg,
         &(KpErrorProc.m_hDiagEmailEdit), KpErrorProc.m_lpszDiagEmail,
         KPERRMSG_EMAIL_EDIT_DX, KPERRMSG_EMAIL_EDIT_X, KPERRMSG_EMAIL_EDIT_Y,
         KPW_CONTROL_STYLE_NORMAL, WS_EX_CLIENTEDGE, 0, KPERRMSG_EMAIL_EDIT_NUMLINES);
      KP_ASSERT(KpErrorProc.m_hDiagEmailEdit != NULL, KP_E_SYSTEM_ERROR, null, True);


// lauþom paaiðkinimà
      if(SUCCEEDED(retc)) retc = WrapMsg(KP_MSG_DIAG_MSG_EXPL2, &formatted_msg, NULL, KPERRMSG_EXPL1_NUMPOS);

      if(SUCCEEDED(retc)) retc = KpCreateStatic(hKpInstance, hwndDlg, NULL,
         formatted_msg, KPERRMSG_EXPL1_X, KPERRMSG_EXPL1_Y,
         KPERRMSG_EXPL1_DX, KPERRMSG_EXPL1_NUMLINES, KPERRMSG_EXPL1_STYLE, 0, 0, NULL);

//    KP_DELETEA(formatted_msg); // siaip iskvieciamas ir is KP_DELETEA(), gali ir uzsiciklint
      if(formatted_msg != null) delete [] formatted_msg;
      formatted_msg = null;

      if(SUCCEEDED(retc)) retc = KpCreateButton(hKpInstance, hwndDlg,
         &(KpErrorProc.m_hDiagOkButton), IDOK, KP_MSG_SIUSTI,
         KPERRMSG_OK_BUT_X, KPERRMSG_OK_BUT_Y, KPW_BUTTON_WDT, KPW_BUTTON_HGT, 0, 0);
      KP_ASSERT(KpErrorProc.m_hDiagOkButton != NULL, KP_E_SYSTEM_ERROR, null, True);

      if(SUCCEEDED(retc)) retc = KpCreateButton(hKpInstance, hwndDlg,
         &(KpErrorProc.m_hDiagCancelButton), IDCANCEL, KP_MSG_ATSAUKTI,
         KPERRMSG_CANCEL_BUT_X, KPERRMSG_CANCEL_BUT_Y, KPW_BUTTON_WDT, KPW_BUTTON_HGT, 0, 0);
      KP_ASSERT(KpErrorProc.m_hDiagCancelButton != NULL, KP_E_SYSTEM_ERROR, null, True);

//    KP_DELETE(msg_pars_ptr); // siaip iskvieciamas ir is KP_DELETEA(), gali ir uzsiciklint
      if(msg_pars_ptr != NULL) delete [] msg_pars_ptr;
      msg_pars_ptr = NULL;

      break;

   case WM_INITDIALOG:
      retw = TRUE;
      break;

   case WM_PAINT:

      hdc = NULL;
      if(SUCCEEDED(retc))
      {
         hdc = BeginPaint(hwndDlg, &ps);
         KP_ASSERT(hdc, KP_E_SYSTEM_ERROR, GetLastError(), True);
      }

      if(SUCCEEDED(retc)) retc = KpDrawLine(hdc, KPERRMSG_LINE_X1, KPERRMSG_LINE0_Y,
         KPERRMSG_LINE_X2, KPERRMSG_LINE0_Y, KP_WND_SUNKEN, NULL);

//    if(SUCCEEDED(retc)) retc = KpDrawLine(hdc, KPDIAGMSG_LINE_X1, KPDIAGMSG_LINE2_Y,
//       KPDIAGMSG_LINE_X2, KPDIAGMSG_LINE2_Y, KP_WND_SUNKEN, NULL);

      if(SUCCEEDED(retc)) EndPaint(hwndDlg, &ps);

      retw = DefWindowProc(hwndDlg, uMsg, wParam, lParam);

      break;

   case WM_CLOSE:
      endfl = True;
      retw = DefWindowProc(hwndDlg, uMsg, wParam, lParam);
      break;

   case WM_QUIT:
      switch(retp)
      {
         case IDCANCEL: retc = KP_E_CANCEL; break;
         case IDABORT: retc = KP_E_SYSTEM_ERROR; break;
      }
      endfl = True;
      break;

   case WM_COMMAND:
      switch(LOWORD(wParam))
      {
      case IDCANCEL:
//       retc = KP_E_CANCEL;
      case IDOK:
         endfl = True;
         break;
      }
      break;

   default:
      retw = DefWindowProc(hwndDlg, uMsg, wParam, lParam);
      break;
   }

   if(endfl && SUCCEEDED(retc))
   {
      PostMessage(NULL, uMsg, wParam, lParam);
      retw = TRUE;
   }

   if(FAILED(retc)) PostQuitMessage(IDABORT);

return(retw);
}
#endif


// --------------------------------------------------
#ifdef KP_ERR_SENDDIAGMSG
#define KP_POST_ANSWER_SIZE 2000000 // KP_MAX_FILE_LIN_LEN
const HRESULT KpErrorProcClass::SendDiagMsg(unsigned char *lpszMsg, LPCTSTR lpszIconID, HRESULT lhRetc, unsigned char *lpszMsgTail)
{
HRESULT retc = S_OK;
HRESULT retc0 = S_OK;
MSG msg;
int retp;
HWND cur_wnd;
bool endfl = False;
const unsigned char *pnts;
const unsigned char *pnts1;
// const unsigned char *pntd;
static unsigned char full_log_fname[KP_MAX_FNAME_LEN + 1];
static unsigned char fname[KP_MAX_FNAME_LEN + 1];
static unsigned char fname_tmp[KP_MAX_FNAME_LEN + 1];
static unsigned char post_fname[KP_MAX_FNAME_LEN + 1];
static unsigned char post_boundary[KP_MAX_FNAME_LEN + 100];
fstream in_file;
unsigned char *file_buf = null;
long file_len = 0L;
KpSocket *sock_ptr = NULL;
static unsigned char post_answer[KP_POST_ANSWER_SIZE + 1];
long ll;
fstream out_file;
static unsigned char kodas[TV_TAG_LEN + 1];
const unsigned char **list_ptr = NULL;
KpStApp *kpstapp_ptr = NULL;
KpStApp *kpstapp_ptr_alloc = NULL;
static unsigned char cmd_str[KP_MAX_FILE_LIN_WDT + 1];
static unsigned char vol_name[KP_MAX_FNAME_LEN + 1];
int prod_ver;
static unsigned char prod_name[KP_MAX_FNAME_LEN + 1];
static unsigned char publ[KP_MAX_FNAME_LEN + 1];
long flash_id;
static unsigned char user_data[KP_MAX_FILE_LIN_WDT + 1];
int upd_num;
int comp_id;

// if(SUCCEEDED(retc)) retc = KpMsgOut(lpszMsg, lpszIconID, KP_MB_TESTI);

   m_lpszDiagEmail[0] = Nul;
   m_lpszDiagComments[0] = Nul;
   m_lpszDiagFile[0] = Nul;

// -----------------------
unsigned char cur_dir[KP_MAX_FNAME_LEN + 1];
   cur_dir[0] = Nul;
   if(SUCCEEDED(retc)) retc = GetLocalPath(cur_dir, KP_LocalDir);

// ----------------------------- iðtraukiam iðsaugotà email
   if((theKpStAppPtr != NULL) && SUCCEEDED(retc))
   {
      strcpy(fname, theKpStAppPtr->m_lpszFlashDevName);
      strcat(fname, KPDIAGMSG_EMAIL_FILE);

      if(SUCCEEDED(retc0))
      {
         in_file.open((const char *)fname, ios_base::in);
         KP_ASSERT0E(!in_file.fail(), KP_E_DIR_ERROR, fname, False);
      }

      if(FAILED(retc0))
      {
         retc0 = S_OK;
         retc0 = GetLocalPath(fname, KP_LocalDir, False);
         if(SUCCEEDED(retc0)) strcat(fname, KPDIAGMSG_EMAIL_FILE);

         if(SUCCEEDED(retc0))
         {
            in_file.open((const char *)fname, ios_base::in);
            KP_ASSERT0E(!in_file.fail(), KP_E_DIR_ERROR, fname, False);
         }
      }

      if(SUCCEEDED(retc0))
      {
         in_file.getline((char *)m_lpszDiagEmail, KP_MAX_FNAME_LEN);
         KP_ASSERT0E(!in_file.fail(), KP_E_FERROR, fname, False);
         if(FAILED(retc0)) m_lpszDiagEmail[0] = Nul;

         m_lpszDiagEmail[KP_MAX_FNAME_LEN] = Nul;

         in_file.close();
      }
   }

// ið registro tik tada, jei faile neradom
   if((m_lpszDiagEmail[0] == Nul) && SUCCEEDED(retc)) retc = KpRegQueryValue(HKEY_CURRENT_USER, "Software\\TEV\\SendDiagMsg", "Email", m_lpszDiagEmail, KP_MAX_FNAME_LEN);

// ----------
   if(SUCCEEDED(retc)) retc = OpenDiagMsgWindow(lpszMsg, lpszIconID, lhRetc);

   if(SUCCEEDED(retc)) do
   {
      KP_ASSERT(GetMessage(&msg, NULL, 0, 0) >= 0, KP_E_SYSTEM_ERROR, GetLastError(), True);

      if(SUCCEEDED(retc))
      {
         TranslateMessage(&msg);
         DispatchMessage(&msg);
      }

      retp = LOWORD(msg.wParam);

      if(SUCCEEDED(retc)) switch(msg.message)
      {
      case WM_CHAR:
         switch(retp)
         {
         case KP_HP11_TOGGLE_CONSOLE:
            if(lKphp11ThreadId != 0L)
               KP_ASSERT(::PostThreadMessage(lKphp11ThreadId, msg.message, msg.wParam, msg.lParam),
                  KP_E_SYSTEM_ERROR, GetLastError(), True);
            break;

         case Tab:
            cur_wnd = GetFocus();

            if(cur_wnd == m_hDiagEmailEdit) SetFocus(m_bShiftFl?m_hDiagCancelButton:m_hDiagCommentsEdit);
            else if(cur_wnd == m_hDiagCommentsEdit) SetFocus(m_bShiftFl?m_hDiagEmailEdit:m_hDiagFileEdit);
            else if(cur_wnd == m_hDiagFileEdit) SetFocus(m_bShiftFl?m_hDiagCommentsEdit:m_hDiagFileButton);
            else if(cur_wnd == m_hDiagFileButton) SetFocus(m_bShiftFl?m_hDiagFileEdit:m_hDiagOkButton);
            else if(cur_wnd == m_hDiagOkButton) SetFocus(m_bShiftFl?m_hDiagFileButton:m_hDiagCancelButton);
            else if(cur_wnd == m_hDiagCancelButton) SetFocus(m_bShiftFl?m_hDiagOkButton:m_hDiagEmailEdit);
            else SetFocus(m_hDiagOkButton);
            break;

         case Enter:
//          PostMessage(NULL, WM_COMMAND, IDOK, 0L);
            break;

         case Esc:
            PostMessage(NULL, WM_COMMAND, IDCANCEL, 0L);
            break;
         }
         break;

      case WM_KEYDOWN:
         switch(retp)
         {
         case Shift:
            m_bShiftFl = True;
            break;

         case Dn:
            cur_wnd = GetFocus();
            if(cur_wnd == m_hDiagEmailEdit) SetFocus(m_hDiagCommentsEdit);
            else if(cur_wnd == m_hDiagCommentsEdit) SetFocus(m_hDiagFileEdit);
            else if(cur_wnd == m_hDiagFileEdit) SetFocus(m_hDiagOkButton);
            else if(cur_wnd == m_hDiagFileButton) SetFocus(m_hDiagCancelButton);
            else if(cur_wnd == m_hDiagCancelButton);
            else SetFocus(m_hDiagOkButton);
            break;

         case Up:
            cur_wnd = GetFocus();
            if(cur_wnd == m_hDiagEmailEdit);
            else if(cur_wnd == m_hDiagCommentsEdit) SetFocus(m_hDiagEmailEdit);
            else if(cur_wnd == m_hDiagFileEdit) SetFocus(m_hDiagCommentsEdit);
            else if(cur_wnd == m_hDiagFileButton) SetFocus(m_hDiagCommentsEdit);
            else if(cur_wnd == m_hDiagOkButton) SetFocus(m_hDiagFileEdit);
            else if(cur_wnd == m_hDiagCancelButton) SetFocus(m_hDiagFileButton);
            else SetFocus(m_hDiagOkButton);
            break;
         }
         break;

      case WM_KEYUP:
         if(retp == Shift) m_bShiftFl = False;
         break;

      case WM_COMMAND:
         switch(retp)
         {
         case IDOK:
            m_lpszDiagEmail[0] = Nul;
            m_lpszDiagComments[0] = Nul;

//          KP_ASSERT((m_hDiagEmailEdit != NULL) && (m_hDiagCommentsEdit != NULL) && (m_hDiagFileEdit != NULL), KP_E_SYSTEM_ERROR, null, True);
//          if(SUCCEEDED(retc))
            if(m_hDiagEmailEdit != NULL)
            {
               SendMessage(m_hDiagEmailEdit, WM_GETTEXT, KP_MAX_FNAME_LEN, (LPARAM)m_lpszDiagEmail);
               m_lpszDiagEmail[KP_MAX_FNAME_LEN] = Nul;
            }

            if(m_hDiagCommentsEdit != NULL)
            {
               SendMessage(m_hDiagCommentsEdit, WM_GETTEXT, KP_MAX_FILE_LIN_LEN, (LPARAM)m_lpszDiagComments);
               m_lpszDiagComments[KP_MAX_FILE_LIN_LEN] = Nul;
            }

            if(m_hDiagFileEdit != NULL)
            {
               SendMessage(m_hDiagFileEdit, WM_GETTEXT, KP_MAX_FNAME_LEN, (LPARAM)m_lpszDiagFile);
               m_lpszDiagFile[KP_MAX_FNAME_LEN] = Nul;
            }

// tikrinam paðto adreso sintaksæ
            retc0 = S_OK;
            if(strlen(m_lpszDiagEmail) > 0)
            {
               if(strchr(m_lpszDiagEmail, Spc) != null) retc0 = KP_E_BAD_EMAIL;
               else
               {
                  pnts = strchr(m_lpszDiagEmail, '@');
                  if(pnts == null) retc0 = KP_E_BAD_EMAIL;
                  else if(strchr(pnts + 1, '.') == null) retc0 = KP_E_BAD_EMAIL;
               }
            }

            if(FAILED(retc0)) KpMsgOut(KP_MSG_BAD_EMAIL_ADDRESS, IDI_ERROR, KP_MB_TESTI); // KP_ERROR0(retc0, null);
            else endfl = True;

            break;

         case IDCANCEL:
            endfl = True;
            retc = KP_E_CANCEL;
            break;

         }
         break;

      case WM_QUIT:
         switch(retp)
         {
         case IDCANCEL: retc = KP_E_CANCEL; break;
         case IDABORT: retc = KP_E_SYSTEM_ERROR; break;
         }
         endfl = True;
         break;

      case WM_CLOSE:
         endfl = True;
         retc = KP_E_CANCEL;
         break;

      }

   } while((!endfl) && SUCCEEDED(retc));

   if(m_hDiagMsgWindow != NULL)
   {
      if(!(::DestroyWindow(m_hDiagMsgWindow)))
      {
//       KP_ERROR(KP_E_SYSTEM_ERROR, GetLastError());
      }
   }
   m_hDiagMsgWindow = NULL;

// -----------------
   SetCurrentDirectory((const char *)cur_dir); // priekabos pasirinkimas numuða darbiná aplankà

// ----------------------------- iðsaugojam email
   if((theKpStAppPtr != NULL) && SUCCEEDED(retc))
   {
      strcpy(fname, theKpStAppPtr->m_lpszFlashDevName);
      strcat(fname, KPDIAGMSG_EMAIL_FILE);

      if(SUCCEEDED(retc0)) retc0 = CreatePath(fname, False);

      if(SUCCEEDED(retc0))
      {
         out_file.open((const char *)fname, ios_base::out);
         KP_ASSERT0(!out_file.fail(), KP_E_DIR_ERROR, fname, False);
      }

      if(SUCCEEDED(retc0))
      {
         out_file << m_lpszDiagEmail << endl;

         out_file.close();
      }
   }

   if(SUCCEEDED(retc)) retc = KpRegSetValue(HKEY_CURRENT_USER, "Software\\TEV\\SendDiagMsg", "Email", m_lpszDiagEmail);

// -----------------------------
   if(SUCCEEDED(retc))
   {
      retc0 = S_OK;
      if(SUCCEEDED(retc0)) retc0 = GetLogFileName(full_log_fname);

// ----------------------------- pridedam sts.bat rezultatus
unsigned char cmd_buf[KP_MAX_FNAME_LEN + 100];
FILE *check_file = NULL;
      check_file = fopen("sts.bat", "rb");
      if(check_file != NULL)
      {
         fclose(check_file);
         strcpy(cmd_buf, "sts.bat ");
         strcat(cmd_buf, full_log_fname);
         StartProcess(cmd_buf, KP_CUR_DIR, NULL, NULL, SW_SHOWMINNOACTIVE);
      }

// ------------------------------------------- POST praneðimo turinys
// POST /error_report.php HTTP/1.1
// Accept: image/gif, image/x-xbitmap, image/jpeg, image/pjpeg, application/x-shockwave-flash, */*
// Referer: http://www.tev.lt/error_report.php
// Accept-Language: lt
// Content-Type: multipart/form-data; boundary=----------------------tv689907.tmp
// UA-CPU: x86
// Accept-Encoding: gzip, deflate
// User-Agent: Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 5.1)
// Host: www.tev.lt
// Content-Length: 999
// Connection: Keep-Alive
// Cache-Control: no-cache
//
// ------------------------tv689907.tmp
// Content-Disposition: form-data; name="Emailas"
// Content-Type: text/plain; charset=ISO-8859-13
// Content-Transfer-Encoding: quoted-printable
//
// klientas@pastas.lt
// ------------------------tv689907.tmp
// Content-Disposition: form-data; name="ProdName"
// Content-Type: text/plain; charset=ISO-8859-13
// Content-Transfer-Encoding: quoted-printable
//
// MIKO knyga IX klasei (MT 9)
// ------------------------tv689907.tmp
// Content-Disposition: form-data; name="ProdVer"
// Content-Type: text/plain; charset=ISO-8859-13
// Content-Transfer-Encoding: quoted-printable
//
// 1037
// ------------------------tv689907.tmp
// Content-Disposition: form-data; name="LicKodas"
// Content-Type: text/plain; charset=ISO-8859-13
// Content-Transfer-Encoding: quoted-printable
//
// 9M7-64890-9929
// ------------------------tv689907.tmp
// Content-Disposition: form-data; name="DiegKodas"
// Content-Type: text/plain; charset=ISO-8859-13
// Content-Transfer-Encoding: quoted-printable
//
// 1142-G9E8-7468-9J83
// ------------------------tv689907.tmp
// Content-Disposition: form-data; name="Komentai"
// Content-Type: text/plain; charset=ISO-8859-13
// Content-Transfer-Encoding: quoted-printable
//
// Neveikia programa
// ------------------------tv689907.tmp
// Content-Disposition: form-data; name="Logas"
// Content-Type: text/plain; charset=ISO-8859-13
// Content-Transfer-Encoding: quoted-printable
//
// 2011.04.01 12:24:42 StartSel[01037:2011.04.01] 1301653482 IRRDH(): l_h: 0 r_d_i: 0 r_m: 2147483647
// 2011.04.01 12:24:42 StartSel[01037:2011.04.01] 1301653482 Perspïjimas: Failas pasikeitï: e:\papildomos funkcijos.exe, klaida: 80040323, failas: ..\kps\kpstap.cpp, eilutï: 13811
// 2011.04.01 12:24:45 StartSel[01037:2011.04.01] 1301653485 Formuojamas diagnostinis prane­imas, klaida: 80040324, failas: startsel.cpp, eilutï: 1772
// 2011.04.01 12:24:46 StartSel[01037:2011.04.01] 1301653486 ------------------ >>> dir
// autorun.inf	49
// Papildomos funkcijos.exe	1338880
// Pradzia.exe	1256960
// DAT0
// DAT0\bl_1.ico	326006
// DAT0\kpstedp.bin	979456
// DAT0\MIKO_papild.pdf	597730
// DAT0\papild-f-atsklanda.bmp	921656
// DAT0\AR6
// DAT0\AR6\Reader
// DAT9\cd\MT9.dat	33769213
// DAT9\cd\mygtukai.pdf	711289
// DAT9\cd\pagalba.pdf	543346
// DAT9\cd\matematika_tau_9.pdf	33769213
// Mano_MT9
// MT9.ini.sav	5360
// dir.bat	46
// dir.txt	32229
// data.dat	388
// 2011.04.01 17:11:30 StartSel[01037:2011.04.01] 1301670690 ------------------ <<< Dir
// 2011.04.01 17:11:30 StartSel[01037:2011.04.01] 1301670690 ------------------ >>> E:\data.dat
// %FDF-1.2
// 1 0 obj<</FDF<</Fields[<</T(PI)/V 3 0 R>><</T(AI)/V 4 0 R>>]>>>>
// endobj
// 3 0 obj
// <</Filter[/A85]>>
// stream
// ;E-Kf/P7fk8hE"Z2)?g^;F*&E8kM]J/P8W-8hEY-8kL[-8kM\^0F:ro6:i[f/1X%A2)%'S.5sC?6<Z$(.5<h:.P!gl0F9E>0aTWl2D[#n;GqLNDJ=)fCC)^Q0KM?G2a&Yt1G]=k#r2fF#quYl2D?g=#qu~>
// endstream
// endobj
// 4 0 obj
// <</Filter[/A85]>>
// stream
// 3DDFa2D[0K0eG.:0J`~>
// endstream
// endobj
// trailer
// <</Root 1 0 R>>
// %%EOF
//
// 2011.04.01 17:11:30 StartSel[01037:2011.04.01] 1301670690 ------------------ >>> E:\data.dat
// 2011.04.01 17:11:30 StartSel[01037:2011.04.01] 1301670690 ------------------ >>> Pars
// 2011.04.01 17:11:30 StartSel[01037:2011.04.01] 1301670690 LocalDir: E:
// 2011.04.01 17:11:30 StartSel[01037:2011.04.01] 1301670690 SystemRoot: C:\Windows
// 2011.04.01 17:11:30 StartSel[01037:2011.04.01] 1301670690 USERNAME: mindaugas
// 2011.04.01 17:11:30 StartSel[01037:2011.04.01] 1301670690 Temp: C:\Users\MINDAU~1\AppData\Local\Temp
// 2011.04.01 17:11:30 StartSel[01037:2011.04.01] 1301670690 TEMP: C:\Users\MINDAU~1\AppData\Local\Temp\
// 2011.04.01 17:11:30 StartSel[01037:2011.04.01] 1301670690 HOMEPATH: \Users\mindaugas
// 2011.04.01 17:11:30 StartSel[01037:2011.04.01] 1301670690 E-mail: mpiesina@netscape.net
// 2011.04.01 17:11:30 StartSel[01037:2011.04.01] 1301670690 Comments: Neveikia
// 2011.04.01 17:11:30 StartSel[01037:2011.04.01] 1301670690 Attachment: F:\kp\bin\Sheep_imitating_clouds.bmp
// 2011.04.01 17:11:30 StartSel[01037:2011.04.01] 1301670690 LogFile: Papildomos funkcijos.log
// 2011.04.01 17:11:30 StartSel[01037:2011.04.01] 1301670690 ------------------ <<< Pars
// 2011.04.01 17:11:30 StartSel[01037:2011.04.01] 1301670690 ------------------ >>> Priekaba.jpg
// QlKhsQckM2LB0SVy4fAVQ5Ki8RYmNFOCY+L/xAAZAQADAQEBAAAAAAAAAAAAAAACAwQBAAX/
// xAAzEQACAgIBAwMBBgYBBQAAAAAAAQIRAyESBDFBEyJRYTJxgaHB8AUUI0KRsTNSctHh8f/a
// AAwDAQACEQMRAD8ASLpcOarnpU2q3KROckUHk1RB4ikpjGXWOK4aQY60Eu9XVQe9VFNYDvjN
// Hp0X8qocUkq+mWSnEARWx5ljuaKftJcniuystvZ7aGKKNfJcD+9H3ZjW6B9pHyyW8OMrCgz/
// AJjRoq0hjjGwJ3xQ3T+9cTE9efH0pm0eFHvU5hneikyiT445NeXX4IL2sSwWqLuCBkDGKLya
// u+iaXYINnnDSsPjjFVdQhTCAZGAAMfGgP7RJHXXFiDEJFGqqPIYoLvQiWj//2Q==
// 2011.04.01 17:11:30 StartSel[01037:2011.04.01] 1301670690 ------------------ <<< Priekaba.jpg

// ------------------------tv689907.tmp--

// ----------------------------------- kpstapp_ptr
      if(SUCCEEDED(retc0))
      {
         kpstapp_ptr = theKpStAppPtr;
         if(kpstapp_ptr == NULL)
         {
//          KP_NEW(kpstapp_ptr, KpStApp); // siaip iskvieciamas ir is KP_NEWA(), gali ir uzsiciklint
            kpstapp_ptr = new KpStApp;
            kpstapp_ptr_alloc = kpstapp_ptr;
         }
      }

// ------------------
      if(SUCCEEDED(retc0)) retc0 = GetLocalPath(post_fname, KP_Temp_Dir, True);
      if(SUCCEEDED(retc0))
      {
         strcat(post_fname, KP_ERR_DIAG_MSG_POST_FILE);

         strcpy(post_boundary, "----------------------");
         retc0 = TvUniFname.Generate(post_boundary + strlen(post_boundary));
      }

      if(SUCCEEDED(retc0))
      {
         out_file.open((const char *)post_fname, ios_base::out | ios_base::binary);
         KP_ASSERT0E(!out_file.fail(), KP_E_DIR_ERROR, post_fname, False);

         if(SUCCEEDED(retc0))
         {

// -------------------- Emailas
            if(SUCCEEDED(retc0)) out_file << "--" << post_boundary << endl;
            if(SUCCEEDED(retc0)) out_file << "Content-Disposition: form-data; name=\"Emailas\"" << endl;
            if(SUCCEEDED(retc0)) out_file << "Content-Type: text/plain; charset=ISO-8859-13" << endl;
            if(SUCCEEDED(retc0)) out_file << "Content-Transfer-Encoding: quoted-printable" << endl;
            if(SUCCEEDED(retc0)) out_file << endl;
            if(SUCCEEDED(retc0)) out_file << m_lpszDiagEmail << endl;
            retc0 = S_OK;

// -------------------- ProdName
            if(SUCCEEDED(retc0)) out_file << "--" << post_boundary << endl;
            if(SUCCEEDED(retc0)) out_file << "Content-Disposition: form-data; name=\"ProdName\"" << endl;
            if(SUCCEEDED(retc0)) out_file << "Content-Type: text/plain; charset=ISO-8859-13" << endl;
            if(SUCCEEDED(retc0)) out_file << "Content-Transfer-Encoding: quoted-printable" << endl;
            if(SUCCEEDED(retc0)) out_file << endl;

// ------------- pradþiai darbinio katalogo uodegà
            if(SUCCEEDED(retc0)) retc0 = GetAppPath(fname, False);
            if(SUCCEEDED(retc0))
            {
               pnts = fname;
               do
               {
                  pnts1 = strchr(pnts, '\\');
                  if(pnts1 == null) pnts1 = strchr(pnts, '/');
                  if(pnts1 != null) pnts = pnts1 + 1;
               } while(pnts1 != null);

               strcpy(prod_name, pnts);

               if(kpstapp_ptr != NULL) retc0 = kpstapp_ptr->GetIniProdName(prod_name);
            }
            if(SUCCEEDED(retc0)) out_file << prod_name << endl;
            retc0 = S_OK;

// -------------------- ProdVer
            if(SUCCEEDED(retc0)) out_file << "--" << post_boundary << endl;
            if(SUCCEEDED(retc0)) out_file << "Content-Disposition: form-data; name=\"ProdVer\"" << endl;
            if(SUCCEEDED(retc0)) out_file << "Content-Type: text/plain; charset=ISO-8859-13" << endl;
            if(SUCCEEDED(retc0)) out_file << "Content-Transfer-Encoding: quoted-printable" << endl;
            if(SUCCEEDED(retc0)) out_file << endl;

// ------------- pradþiai globalø
            if(SUCCEEDED(retc0)) prod_ver = iProdVerGlob;
            if(SUCCEEDED(retc0)) if(kpstapp_ptr != NULL) retc0 = kpstapp_ptr->GetIniProdVer(&prod_ver);
            if(SUCCEEDED(retc0)) out_file << prod_ver << endl;
            retc0 = S_OK;

// -------------------- LicKodas // AtmKod
            if(SUCCEEDED(retc0)) out_file << "--" << post_boundary << endl;
//          if(SUCCEEDED(retc0)) out_file << "Content-Disposition: form-data; name=\"AtmKod\"" << endl;
            if(SUCCEEDED(retc0)) out_file << "Content-Disposition: form-data; name=\"LicKodas\"" << endl;
            if(SUCCEEDED(retc0)) out_file << "Content-Type: text/plain; charset=ISO-8859-13" << endl;
            if(SUCCEEDED(retc0)) out_file << "Content-Transfer-Encoding: quoted-printable" << endl;
            if(SUCCEEDED(retc0)) out_file << endl;

            kodas[0] = Nul;

// ---- pradþiai traukiam AI ið data.dat
#if FALSE
            if(SUCCEEDED(retc0)) retc0 = GetAppPath(fname, True);
            if(SUCCEEDED(retc0)) strcat(fname, KPST_FDF_DATA_FNAME);
KpString fname_s((const char *)fname);
KpString atm_kod_s;
            if((kpstapp_ptr != NULL) && SUCCEEDED(retc0))
            {
               retc0 = kpstapp_ptr->GetDataDatVariable(&fname_s, (const unsigned char *)"AI", &atm_kod_s, False);
               if(SUCCEEDED(retc0))
               {
                  strncpy(kodas, atm_kod_s.ExtractValueA(), TV_TAG_LEN);
                  kodas[TV_TAG_LEN] = Nul;
               }
            }
#endif
            if((kpstapp_ptr != NULL) && SUCCEEDED(retc0))
            {
               retc0 = kpstapp_ptr->GetAtmKodTxt(kodas);
//             if(retc0 == KP_E_KWD_NOT_FOUND)
                  retc0 = S_OK;
            }

// ---- jei neradom – ið KpStIniData::m_lpszAdminPwd
            if(SUCCEEDED(retc0))
            {
               CutInitTrailSpcs(kodas);
               if((kodas[0] == Nul) || (strcmp(kodas, KPST_ATM_KOD_NULL) == 0))
                  if(kpstapp_ptr != NULL) retc0 = kpstapp_ptr->GetIniAdminPwd(kodas);
            }

// ---- jei vis tiek nëra – tada èia diegiamas produktas, formuojam LicKodas
            if(SUCCEEDED(retc0))
            {
               CutInitTrailSpcs(kodas);
               if((kodas[0] == Nul) || (strcmp(kodas, KPST_ATM_KOD_NULL) == 0))
                  if(kpstapp_ptr != NULL) retc0 = kpstapp_ptr->FormatLicCodeFull(kodas);
            }

            if(SUCCEEDED(retc0)) out_file << kodas << endl;
            retc0 = S_OK;

// -------------------- DiegKodas
            kodas[0] = Nul;
            if(SUCCEEDED(retc0)) out_file << "--" << post_boundary << endl;
            if(SUCCEEDED(retc0)) out_file << "Content-Disposition: form-data; name=\"DiegKodas\"" << endl;
            if(SUCCEEDED(retc0)) out_file << "Content-Type: text/plain; charset=ISO-8859-13" << endl;
            if(SUCCEEDED(retc0)) out_file << "Content-Transfer-Encoding: quoted-printable" << endl;
            if(SUCCEEDED(retc0)) out_file << endl;

            if(SUCCEEDED(retc0))
               if(kpstapp_ptr != NULL) retc0 = kpstapp_ptr->FormatInstCodeFull(kodas);

            if(SUCCEEDED(retc0)) out_file << kodas << endl;
            retc0 = S_OK;

// -------------------- Komentai
            if(SUCCEEDED(retc0)) out_file << "--" << post_boundary << endl;
            if(SUCCEEDED(retc0)) out_file << "Content-Disposition: form-data; name=\"Komentai\"" << endl;
            if(SUCCEEDED(retc0)) out_file << "Content-Type: text/plain; charset=ISO-8859-13" << endl;
            if(SUCCEEDED(retc0)) out_file << "Content-Transfer-Encoding: quoted-printable" << endl;
            if(SUCCEEDED(retc0)) out_file << endl;
            if(SUCCEEDED(retc0))
            {
               CutInitTrailSpcs(m_lpszDiagComments);
               if(m_lpszDiagComments[0] != Nul) out_file << m_lpszDiagComments;
               else
               {
                  if(lpszMsg != null) out_file << lpszMsg;
                  out_file << ",";
                  if(lpszMsgTail != null) out_file << lpszMsgTail;
               }
               out_file << endl;
            }
            retc0 = S_OK;

#if FALSE
// -------------------- AttName
            if(SUCCEEDED(retc0)) out_file << "--" << post_boundary << endl;
            if(SUCCEEDED(retc0)) out_file << "Content-Disposition: form-data; name=\"AttName\"" << endl;
            if(SUCCEEDED(retc0)) out_file << "Content-Type: text/plain; charset=ISO-8859-13" << endl;
            if(SUCCEEDED(retc0)) out_file << "Content-Transfer-Encoding: quoted-printable" << endl;
            if(SUCCEEDED(retc0)) out_file << endl;
            if(SUCCEEDED(retc0)) out_file << m_lpszDiagFile << endl;
            retc0 = S_OK;
#endif

// ------------------------------------ logas ir visa kita
            if(SUCCEEDED(retc0)) out_file << "--" << post_boundary << endl;
            if(SUCCEEDED(retc0)) out_file << "Content-Disposition: form-data; name=\"Logas\"" << endl;
//          if(SUCCEEDED(retc0)) out_file << "Content-Type: text/plain; charset=ISO-8859-13" << endl;
            if(SUCCEEDED(retc0)) out_file << "Content-Type: application/octet-stream" << endl;
            if(SUCCEEDED(retc0)) out_file << "Content-Transfer-Encoding: quoted-printable" << endl;
            if(SUCCEEDED(retc0)) out_file << endl;
            retc0 = S_OK;

// ------------------------------------------ sistemos parametrai
            out_file << "------------------ >>> Pars" << endl;

            out_file << "ProdNameGlob: " << lpszProdName << endl;
            out_file << "ProdVerGlob: " << dec << iProdVerGlob << endl;
            out_file << "UpdNumGlob: " << dec << iUpdNumGlob << endl;
            if(SUCCEEDED(retc0)) if(kpstapp_ptr != NULL)
            {
               out_file << "ProdVar: " << kpstapp_ptr->m_ProdVar << endl;
               out_file << "ProdDate: " << kpstapp_ptr->m_ProdDate << endl;
               out_file << "ProdVersion: " << kpstapp_ptr->m_ProdVersion << endl;

               if(SUCCEEDED(retc0)) retc0 = kpstapp_ptr->GetIniPublisher(publ);
               if(SUCCEEDED(retc0)) out_file << "Publ: " << publ << endl;
               retc0 = S_OK;

               if(SUCCEEDED(retc0)) retc0 = kpstapp_ptr->GetIniProdName(prod_name);
               if(SUCCEEDED(retc0)) out_file << "ProdName: " << prod_name << endl;
               retc0 = S_OK;

               if(SUCCEEDED(retc0)) retc0 = kpstapp_ptr->GetIniVolName(vol_name);
               if(SUCCEEDED(retc0)) out_file << "ProjID: " << vol_name << endl;
               retc0 = S_OK;

               if(SUCCEEDED(retc0)) retc0 = kpstapp_ptr->GetIniProdVer(&prod_ver);
               if(SUCCEEDED(retc0)) out_file << "ProdVer: " << prod_ver << endl;
               retc0 = S_OK;

               if(SUCCEEDED(retc0)) retc0 = kpstapp_ptr->GetIniUpdNum(&upd_num);
               if(SUCCEEDED(retc0)) out_file << "UpdNum: " << upd_num << endl;
               retc0 = S_OK;

               if(SUCCEEDED(retc0)) retc0 = kpstapp_ptr->GetIniCmdStr(cmd_str);
               if(SUCCEEDED(retc0)) out_file << "CmdStr: " << cmd_str << endl;
               retc0 = S_OK;

               if(SUCCEEDED(retc0)) retc0 = kpstapp_ptr->GetIniFlashId(&flash_id);
               if(SUCCEEDED(retc0)) out_file << "FID: " << hex << flash_id << endl;
               retc0 = S_OK;

               if(SUCCEEDED(retc0)) retc0 = kpstapp_ptr->GetAtmKodTxt(kodas);
               if(SUCCEEDED(retc0)) out_file << "AI: " << kodas << endl;
               retc0 = S_OK;

               if(SUCCEEDED(retc0)) retc0 = kpstapp_ptr->GetIniAdminPwd(kodas);
               if(SUCCEEDED(retc0)) out_file << "AI.ini: " << kodas << endl;
               retc0 = S_OK;

               if(SUCCEEDED(retc0)) retc0 = kpstapp_ptr->GetIniUserData(user_data);
               if(SUCCEEDED(retc0)) out_file << "UserData: " << user_data << endl;
               retc0 = S_OK;

               if(SUCCEEDED(retc0)) retc0 = EmuTv.GetHp11Variable(&comp_id, KP11_COMPID);
               if(SUCCEEDED(retc0)) out_file << "CID: " << dec << comp_id << endl;
               retc0 = S_OK;

               if(SUCCEEDED(retc0)) retc0 = kpstapp_ptr->FormatLicCodeFull(kodas);
               if(SUCCEEDED(retc0)) out_file << "LicKodas: " << kodas << endl;
               retc0 = S_OK;

               if(SUCCEEDED(retc0)) retc0 = kpstapp_ptr->FormatInstCodeFull(kodas);
               if(SUCCEEDED(retc0)) out_file << "DiegKodas: " << kodas << endl;
               retc0 = S_OK;
            }

//          if(SUCCEEDED(retc0)) retc0 = GetLocalPath(fname, KP_LocalDir, True);
            if(SUCCEEDED(retc0)) retc0 = GetAppPath(fname, False);
            if(SUCCEEDED(retc0)) out_file << "LocalDir: " << fname << endl;
            retc0 = S_OK;

            out_file << "SystemRoot: " << getenv("SystemRoot") << endl;
            out_file << "USERNAME: " << getenv("USERNAME") << endl;

            out_file << "Temp: " << getenv("Temp") << endl;
            if(SUCCEEDED(retc0)) retc0 = GetLocalPath(fname, KP_Temp_Dir, True);
            if(SUCCEEDED(retc0)) out_file << "TEMP: " << fname << endl;
            retc0 = S_OK;

            out_file << "HOMEPATH: " << getenv("HOMEPATH") << endl;
            out_file << "E-mail: " << m_lpszDiagEmail << endl;
            out_file << "Comments: " << m_lpszDiagComments << endl;
            out_file << "Attachment: " << m_lpszDiagFile << endl;
            out_file << "LogFile: " << full_log_fname << endl;
            out_file << "------------------ <<< Pars" << endl;

// ---------------------------------------------------- logas
            {
static unsigned char *str_buf = null;
//          KP_NEWA(str_buf, unsigned char, /* KP_MAX_FNAME_LEN + 100 */ 10000); // siaip iskvieciamas ir is KP_NEWA(), gali ir uzsiciklint
            str_buf = new unsigned char[/* KP_MAX_FNAME_LEN + 100 */ 10000];
            if(str_buf == null) retc0 = KP_E_OUTOFMEM;

            if(SUCCEEDED(retc0)){ sprintf((char *)str_buf, "------------------ >>> %s\n", full_log_fname); PutEncodedLogMsg(str_buf, &out_file); }
            if(SUCCEEDED(retc0))
            {
#ifndef ENCODE_LOG
               if(strstr(full_log_fname, KP_XFS_LOG_FNAME) != null)
                  retc0 = DecodeXfsLog(full_log_fname, &out_file, False);
               else
#endif
               {
// KpMsgOutF("SendDiagMsg(): %lx %s %s", strstr(full_log_fname, KP_XFS_LOG_FNAME), full_log_fname, KP_XFS_LOG_FNAME);
                  if(SUCCEEDED(retc0)) retc0 = ReadFileContents(full_log_fname, &file_buf, &file_len, False, False);
#ifdef ENCODE_LOG
//                if(SUCCEEDED(retc0)) retc0 = EncodeLogBuf(file_buf, file_len); // jau uþkoduotas
#endif
                  if(SUCCEEDED(retc0)) out_file.write((const char *)file_buf, file_len);
//                if(SUCCEEDED(retc0)) out_file << endl;
                  KP_ASSERT0E(!out_file.fail(), KP_E_FERROR, post_fname, False);

//                KP_DELETEA(file_buf); // siaip iskvieciamas ir is KP_DELETEA(), gali ir uzsiciklint
                  if(file_buf != null) delete [] file_buf;
                  file_buf = null;
               }
            }
            if(SUCCEEDED(retc0)){ sprintf((char *)str_buf, "------------------ <<< %s\n", full_log_fname); PutEncodedLogMsg(str_buf, &out_file); }
            retc0 = S_OK;

// ------------------------------------------ failø katalogas
            if(SUCCEEDED(retc0)) retc0 = GetAppPath(fname, False);
            if(SUCCEEDED(retc0)){ sprintf((char *)str_buf, "------------------ >>> %s\n", fname); PutEncodedLogMsg(str_buf, &out_file); }
            if(SUCCEEDED(retc0)) retc0 = KpDir(fname /* (const unsigned char *)"." */, &out_file, False
#ifdef ENCODE_LOG
               , True
#endif
               );
            if(SUCCEEDED(retc0)){ sprintf((char *)str_buf, "------------------ <<< %s\n", fname); PutEncodedLogMsg(str_buf, &out_file); }
            retc0 = S_OK;

// ------------------------------------------ ádiegtø programø sàraðas ið registro
            if(SUCCEEDED(retc0)){ PutEncodedLogMsg((const unsigned char *)"------------------ >>> HKEY_LOCAL_MACHINE\\Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall\n", &out_file); }
//          retc0 = S_OK;
         /* retc0 = */ KpRegExportBranch(&out_file, HKEY_LOCAL_MACHINE, (const unsigned char *)"Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall"
#ifdef ENCODE_LOG
                           , True
#endif
                           );
            if(SUCCEEDED(retc0)){ PutEncodedLogMsg((const unsigned char *)"------------------ <<< HKEY_LOCAL_MACHINE\\Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall\n", &out_file); }
            retc0 = S_OK;

// ------------------------------------------ data.dat
//          if(SUCCEEDED(retc0)) retc0 = GetLocalPath(fname, KP_LocalDir, True);
            if(SUCCEEDED(retc0)) retc0 = GetAppPath(fname, True);
            if(SUCCEEDED(retc0)) strcat(fname, KPST_FDF_DATA_FNAME);
            if(SUCCEEDED(retc0)){ sprintf((char *)str_buf, "------------------ >>> %s\n", fname); PutEncodedLogMsg(str_buf, &out_file); }
            if(SUCCEEDED(retc0)) retc0 = EncodeLogBase64(fname, &out_file);
            if(SUCCEEDED(retc0)){ sprintf((char *)str_buf, "------------------ <<< %s\n", fname); PutEncodedLogMsg(str_buf, &out_file); }
            retc0 = S_OK;

// ------------------------------------------ prijungiam papildomus failus ið KpDiagMsgAddFiles[]
            list_ptr = KpDiagMsgAddFiles;
            while((*list_ptr != null) && SUCCEEDED(retc0))
            {
               strcpy(fname, *list_ptr);

// ----------------------------- {temp} --> %TEMP%
               if(SUCCEEDED(retc0)) retc0 = GetLocalPath(fname_tmp, KP_Temp_Dir, False);
               if(SUCCEEDED(retc0)) /* retc0 = */ KpExpandMacro(fname, KP_MAX_FNAME_LEN, KPST_FNAME_SHORTCUT_TEMP, fname_tmp);
               retc0 = S_OK;
#if FALSE
// ----------------------------- {user} --> kpstapp_ptr->m_lpszFlashDevName
               if((kpstapp_ptr != NULL) && SUCCEEDED(retc0))
               /* retc0 = */ KpExpandMacro(fname, KP_MAX_FNAME_LEN, KPST_FNAME_SHORTCUT_USER, kpstapp_ptr->m_lpszFlashDevName);
               retc0 = S_OK;
#endif

// ----------------------------- {progpath}
               if(SUCCEEDED(retc0)) retc0 = GetLocalPath(fname_tmp, KP_LocalDir, False);
               if(SUCCEEDED(retc0)) /* retc0 = */ KpExpandMacro(fname, KP_MAX_FNAME_LEN, KPST_FNAME_SHORTCUT_PROGPATH, fname_tmp);
               retc0 = S_OK;

// -------------------
               if(SUCCEEDED(retc0))
               {
                  if(SUCCEEDED(retc0)){ sprintf((char *)str_buf, "------------------ >>> %s\n", fname); PutEncodedLogMsg(str_buf, &out_file); }
                  if(SUCCEEDED(retc0))
                  {
#ifndef ENCODE_LOG
                     if(strstr(fname, KP_XFS_LOG_FNAME) != null) retc0 = DecodeXfsLog(fname, &out_file, False);
                     else
#endif
                     {
                        if(IsPlainTextFile(fname))
                        {
                           if(SUCCEEDED(retc0)) retc0 = ReadFileContents(fname, &file_buf, &file_len, False, False);
#ifdef ENCODE_LOG
                           if((strstr(fname, ".log") == null) && SUCCEEDED(retc0)) retc0 = EncodeLogBuf(file_buf, file_len);
#endif
                           if(SUCCEEDED(retc0)) out_file.write((const char *)file_buf, file_len);

//                         KP_DELETEA(file_buf); // siaip iskvieciamas ir is KP_DELETEA(), gali ir uzsiciklint
                           if(file_buf != null) delete [] file_buf;
                           file_buf = null;
                        }
                        else if(SUCCEEDED(retc0)) retc0 = EncodeLogBase64(fname, &out_file);
                     }
                     if(SUCCEEDED(retc0)){ sprintf((char *)str_buf, "------------------ <<< %s\n", fname); PutEncodedLogMsg(str_buf, &out_file); }
                  }
               }

               list_ptr++;
               retc0 = S_OK;
            }
            retc0 = S_OK;

// ------------------------------------------ priekaba
            if(m_lpszDiagFile[0] != Nul)
            {
               if(SUCCEEDED(retc0)){ sprintf((char *)str_buf, "------------------ >>> %s\n", m_lpszDiagFile); PutEncodedLogMsg(str_buf, &out_file); }
#if FALSE
               if(SUCCEEDED(retc0)) out_file << "--" << post_boundary << endl;
               if(SUCCEEDED(retc0))
               {
                  pntd = m_lpszDiagFile;
                  do
                  {
                     pnts = strchr(pntd, '\\');
                     if(pnts) pntd = pnts + 1;
                  } while(pnts);
               }
               if(SUCCEEDED(retc0)) out_file << "Content-Disposition: attachment; filename=\"" << pntd << "\"; name=\"Priekaba\"" << endl;
               if(SUCCEEDED(retc0)) out_file << "Content-Transfer-Encoding: base64" << endl;
               if(SUCCEEDED(retc0)) out_file << endl;
#endif
               if(SUCCEEDED(retc0)) retc0 = EncodeLogBase64(m_lpszDiagFile, &out_file);

               if(SUCCEEDED(retc0)){ sprintf((char *)str_buf, "------------------ <<< %s\n", m_lpszDiagFile); PutEncodedLogMsg(str_buf, &out_file); }
            }
            retc0 = S_OK;

//          KP_DELETEA(str_buf); // siaip iskvieciamas ir is KP_DELETEA(), gali ir uzsiciklint
            if(str_buf != null) delete [] str_buf;
            str_buf = null;
            }

// -------------------------
            KP_ASSERT0E(!out_file.fail(), KP_E_FERROR, post_fname, False);
            retc0 = S_OK;

// -------------------------
            if(SUCCEEDED(retc0)) out_file << "\n--" << post_boundary << "--" << endl;

            if(SUCCEEDED(retc0))
            {
               out_file.close();
               KP_ASSERT0E(!out_file.fail(), KP_E_FERROR, post_fname, False);
            }
//          retc0 = S_OK;

// ------------------------- siunèiam POST
            if(SUCCEEDED(retc0))
            {
//             if(SUCCEEDED(retc0)) KP_NEWO(sock_ptr, KpSocket); // siaip iskvieciamas ir is KP_NEWO(), gali ir uzsiciklint
               if(SUCCEEDED(retc0)){ sock_ptr = new KpSocket; if(sock_ptr == NULL) retc0 = KP_E_OUTOFMEM; }

               if(SUCCEEDED(retc0)) retc0 = sock_ptr->Resolve(KPDIAGMSG_URL_SERVER, False); // "http://www.tev.lt"
               if(SUCCEEDED(retc0)) retc0 = sock_ptr->Connect(False);

               if(SUCCEEDED(retc0)) retc0 = ReadFileContents(post_fname, &file_buf, &ll, False, True);
               if(SUCCEEDED(retc0))
                  retc0 = sock_ptr->SendHttpRequest(HTTP_POST_REQUEST_CMD,
                       KPDIAGMSG_URL_FILE, False, ll, False, post_boundary);

#ifndef TEST_DIAG_MSG
               if(SUCCEEDED(retc0)) retc0 = sock_ptr->SendMsg(file_buf, ll, False);
#endif

//             KP_DELETEA(file_buf); // siaip iskvieciamas ir is KP_DELETEA(), gali ir uzsiciklint
               if(file_buf != null) delete [] file_buf;
               file_buf = null;

// ------------------------- gaudom atsakymà á POST
#ifndef TEST_DIAG_MSG
               ll = KP_POST_ANSWER_SIZE;
               if(SUCCEEDED(retc0))
               {
                  retc0 = sock_ptr->RcvHttpMsg(post_answer, &ll, False);
                  if(retc0 == KP_E_NEG_ANSW) KP_ERROR0N(retc0, null);
                  if(((ll < 0) || (ll > KP_POST_ANSWER_SIZE)) && SUCCEEDED(retc0))
                     KP_ERROR0N(KP_E_BUFFER_OVERFLOW, null);
                  if(SUCCEEDED(retc0)) post_answer[ll] = Nul;
                  KP_ASSERT0EN(strcmp(post_answer, KPDIAGMSG_RESP_OK) == 0, KP_E_REFUSED, null, False);
               }
#endif

// ----------------------
#if FALSE
post_answer[200] = Nul;
KpMsgOutF(post_answer);
#endif
if(SUCCEEDED(retc0)) PutLogMessage_("=============================================");
if(SUCCEEDED(retc0)) PutLogMessage_(post_answer);

//             KP_DELETE(sock_ptr); // siaip iskvieciamas ir is KP_DELETEA(), gali ir uzsiciklint
               if(sock_ptr != NULL) delete sock_ptr;
               sock_ptr = NULL;

#ifndef TEST_DIAG_MSG
               DeleteFile((const char *)post_fname);
#endif
            } // if(SUCCEEDED(retc0)) // out_file.close()

         } // if(SUCCEEDED(retc0)) // out_file.open()

      } // if(SUCCEEDED(retc0))

      if(SUCCEEDED(retc0)) KpMsgOutF(KP_MSG_DIAG_MSG_SUCCEEDED)
      else KP_ERROR0N(retc0, null);

// ------------------------------------------ kpstapp_ptr_alloc
//    KP_DELETE(kpstapp_ptr_alloc); // siaip iskvieciamas ir is KP_DELETE(), gali ir uzsiciklint
      if(kpstapp_ptr_alloc != NULL) delete kpstapp_ptr_alloc;
      kpstapp_ptr_alloc = NULL;

   } // if(SUCCEEDED(retc))

// ------------------------------------------
   if(retc == KP_E_CANCEL) retc = S_OK;

return(retc);
}
#endif



// ------------------------------------------
#if CompilerGr == Mingw
int KpExceptionFilter(unsigned int code, unsigned int excToFilter)
{
/* if(code == excToFilter) */ return EXCEPTION_EXECUTE_HANDLER;
// else return EXCEPTION_CONTINUE_SEARCH;
}
#endif

