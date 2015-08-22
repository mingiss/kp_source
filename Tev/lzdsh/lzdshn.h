// -----------------------------------------
// lzdshn.h
// zodyno perziuros programa ir XMLT redaktorius
// aplinkos nuostatos
//

#ifndef lzdshn_included
#define lzdshn_included


// -----------------------------
#ifndef iBshn_included
#error iBshn.h not included
#endif

#ifndef IBSH_SKIN
#error IBSH_SKIN undefined
#endif


// -----------------------------
#define LZDSH_VERSION_TXT ((const unsigned char *)"WinLED v5.06f.32")

// -----------------------------
// XMLT redaktoriaus rezimas (jei uzkomentuota - zodyno browseris (LED'as).  
// #define LZDSH_EDITOR_BUILD

// -------------------------------------
// kaimynu liste m_MainList viso indexo turinys, ne tik tu,
// kurie matosi - tada slankiklis automatinis
#define LZDSHT_FULL_LIST

// -------------------------------------
// reikia m_lpszaListKeywords[][] - paieskos zodziai indexe
// be diakritu ar normalizuoti - skiriasi nuo isvedamo
// teksto liste m_MainList
// #define LZDSHT_DIFF_KWDS

// -------------------------------------
// #define KP_USE_WXWIDGETS

// -------------------------------------
// #define KP_USE_TextGRAB // neveikia be ATL, kuris neveikia MingW kompiliatoriuj
// #define KP_USE_classFactory

// -------------------------------------
// bandom du REZ laukus - vienas RTF, kitas BMP, kad nenugrabintu
// #define LZDSH_TEST_REZ_BMP


// --------------------------
#define LZDSH_MENU   // kol kas galioja tik IBSH_SKIN_STANDART skinui

// -------------------------- DeLt zodynas - standarinis skinas, be skino parinkimo
// #define LZDSH_DELT

#ifdef LZDSH_DELT
#  ifdef IBSH_SKIN
#     undef IBSH_SKIN
#  endif
#  define IBSH_SKIN IBSH_SKIN_STANDART
#endif


// ------------------------
// paieska m_SearchList dialogo threade LzdShDlg_tag neatnaujina, perduoda i LzdShSearch_tag,
// kad du threadai nekonkuruotu del kphp11 RC
#define LZDSHT_SEARCH_SINGLE_THREAD

#ifndef IBSH_RES_MODE_RTF
#define LZDSHT_DISPLAY_SINGLE_THREAD // XGecko neveikia kitam threade, tik tam, ið kurio paleistas 
#  ifdef LZDSHT_DISPLAY_SINGLE_THREAD
#     define LZDSHT_DISPLAY_SEARCH_THREAD // XGecko rodymas vienam threade, bet dabar paieðkos threade LzdShSearch::m_lThreadId,  
#  endif                                  // permetam atgal tik ið kphp11 threado
#endif

#ifndef IBSH_RES_MODE_RTF
// #  define LZDSH_OUT_VERS XML_VERS_SGML_TAGE
// #  define LZDSH_OUT_VERS XML_VERS_XML10
#  define LZDSH_OUT_VERS XML_VERS_HTML_TAGE // XML_VERS_HTML401_TRANS
// #  define LZDSH_OUT_VERS XML_VERS_XHTML_TAGE // XML_VERS_XHTML
#else
#  define LZDSH_OUT_VERS XM_NO_VERS
#endif

#ifdef IBSH_RES_MODE_XGECKO
#define LZDSH_RES_CODING_UTF8      // XML/HTML output UTF-8 (jei neapibrëþta - UTF-16) // former RES_MODE_UTF8
#endif

// -----------------------------
// duomenys uzkoduoti - naudojam .xdb vietoj .xml
#ifndef LZDSH_EDITOR_BUILD
#define LZDSHT_ENCODED
#endif

// ------------------------
#ifdef IBSH_RES_MODE_RTF
#ifdef IBSH_RES_MODE_MSHTML
#error IBSH_RES_MODE_RTF and IBSH_RES_MODE_MSHTML conflict
#endif
#ifdef IBSH_RES_MODE_XGECKO
#error IBSH_RES_MODE_RTF and IBSH_RES_MODE_XGECKO conflict
#endif
#ifdef LZDSH_OUT_VERS // #if XM_IS_VERS_HTML(LZDSH_OUT_VERS)
#if (LZDSH_OUT_VERS != XM_NO_VERS)
#error IBSH_RES_MODE_RTF and LZDSH_OUT_VERS conflict // #error IBSH_RES_MODE_RTF and XM_IS_VERS_HTML(LZDSH_OUT_VERS) conflict
#endif
#endif
#endif
#ifdef IBSH_RES_MODE_MSHTML
#ifdef IBSH_RES_MODE_XGECKO
#error IBSH_RES_MODE_MSHTML and IBSH_RES_MODE_XGECKO conflict
#endif
#endif


#endif // #ifndef lzdshn_included
