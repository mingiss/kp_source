#ifndef TUX_FS_XFS_HH
#define TUX_FS_XFS_HH

/*
Changelog:
  1.0.18:
    * Idetas *.tmp failu kodavimas

  1.0.19:
    * Idetas XFS_NULL_BINARY, leidziantis pakeisti null.exe pavadinima
    * Pakeisti projekto settingai, kad nemestu konsoles
    * Ideta galimybe keisti XFS.exe failo varda
    * Pridetas '/A "scrollbar=0&statusbar=0&navpanes=0"' prie acrobato argumentu
    * Pakeista lango XIPA lango antraste i XFS_WINDOW_TITLE
    * Ideta ikona (XipaResource.rc)

  1.0.20:
    * Logas perkeltas i %TEMP%\XFS.log ir uzkoduotas

  1.0.21:
    * I XPDF idetas setShowScrollbar; atjungtas navigacijos scrollbar'as PDFams, kurie turi
      daugiau negu 1 puslapi.
    * Idetas XFS_CLIPBOARD_GUARD, kuris jei #define'intas, tai trins periodiskai kas 0.5 s
      clipboarda.

  1.0.22:
    * Istaisytas txCreateFile, kad praleistu visus "\Device" failu atidarymus native rezimu.
      Tai istaiso update & submitField bugus
    * Integruoti TUX_SPLASH_FNAME ir TUX_SHOW_SCROLLBAR
    * Idetas XFS_ENCRYPT_LOG, kuris nustato, ar koduoti logus

  1.0.23:
    * BUGFIX: acrobatas nuluzta, antra karta iskvietus app.activeDocs
    * BUGFIX: acrobatas budavo uzkillinamas, todel negaledavo nieko issaugoti i GLOB.JS

  1.0.24:
    * BUGFIX: mapinami puslapiai roundinami iki 64K vietoj 4K; dabar veiks su win7 64 bit,
      atitinkamai pakeistas XFSTool, kad generuotu archyvus su 64K alignmentu

  1.0.25:
    * BUGFIX: nutimas puslapiu roundinimas i 4K txMapViewOfSection funkcijoje

  1.0.26:
    * Dumpinant stack trace, bus issvestas ir code dump.

  1.0.27:
    * Pakeistas unpatch mechanizmas (is memcpy i asm rep movsb)
    * Logas papildytas su base-patch informacija
    * Pataisytas code dump offsetas

  1.0.28:
    * Papildomas thread-safety

  1.0.29:
    * idetas visiems IcePatch globalus thread-lockas

  1.0.30:
    * integruoti Mindaugo pakeitimai
    * sutvarkytas temporary failu adresavimo mechanizmas

  1.0.31:
    * idetas automatinis logu perkelimas is TEMP\XFS.log ir USERPROFILE\Desktop\XFS.log
    * idetas XFS_CRASH_TEST env kintamasis: jei jo reiksme TRUE (set XFS_CRASH_TEST=TRUE), tuomet
      XFS pasileidimo metu nulus

  1.0.32:
    * AcLayers.DLL ir AppHelp.DLL blokavimas
    * sumerginti Mindaugo kalbiniai patchai

  1.0.33:
    * idetas tinkamas 0x000006ba exceptiono handlinimas

  1.0.34:
    * comodo firewall fix

  1.0.35:
    * extra loggingas del image allocation
    * praleidziami \??\IDE#, \??\MountPointManager ir \??\Storage# failai

  1.0.36:
    * blacklistintas Avast snxhk.dll

  1.0.37:
    * nauji DLL blacklistai
    * nauji pass-through

  1.0.38:
    * dumpinamas kodas ties EIP

  1.0.39:
    * apsauga nuo parazitinu procesu

  1.0.40:
    * pafixintas DLL unload kodas

  1.0.41:
    * failu whitelist

  1.0.42:
    * pakeistas funkciju hook mechanizmas
    * sumazintas handlu wrap skaicius

  1.0.43:
    * isimti AcLayers.dll ir apphelp.dll is blacklist

  1.0.44:
    * i reference counteri idetas mutexas

  1.0.45:
    * blacklistintas AhJsctNs.dll
    * pataisytas stringu lyginimas txSetWindowText hooke

  1.0.46:
    * langø iðkëlimas á virðø
*/

////////////////////////////////////////////////////////////////////////////////////////////////
#include <tux/XTux.hh>
////////////////////////////////////////////////////////////////////////////////////////////////
#define XFS_EXE_VERSION             L"1.0.46"
#define XFS_DLL_VERSION             L"1.0.46"
#define XFS_ENCRYPTION_KEY          0x054fc05af9c51d90LL
#define XFS_ENCRYPT_LOG
//#define XLangEng
////////////////////////////////////////////////////////////////////////////////////////////////
#define XFS_NULL_BINARY             L"XFS_null.exe"
////////////////////////////////////////////////////////////////////////////////////////////////
//#define XFS_WINDOW_TITLE            L"XFS " XFS_EXE_VERSION
//#define XFS_WINDOW_TITLE            L"Matematika Tau. 5 klas\x0117"
#define XFS_WINDOW_TITLE            L"Matematika Tau plius-5E"
#define XFS_CLIPBOARD_GUARD
////////////////////////////////////////////////////////////////////////////////////////////////
#define XFS_MAX_PATH                4096
/************************************************************* TX *************************************************************/
/*                                                            XFS                                                             */
/******************************************************************************************************************************/
/******************************************************************************************************************************/

#endif /* TUX_FS_XFS_HH */
