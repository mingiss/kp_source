// ==================================================
// tvxmlel.cpp (changed to tvxmlel1.cpp)
// endings and suffixes skipper for searching in flex. languages
// lithuanian endings


// ================================================== definitions
#include "envir.h"

#include <stdlib.h>
#if OsGr==MSWin
#include <windows.h>
#endif

#include "kpstdlib.h"
#include "kptt.h"
#include "tvmain.h"
#include "tvxmle.h"


// ===================================================
// Lietuvisku zodziu pagrindines formos suradimo duombaze
//
// Turinys:
//
//    plpszaToGrForm_l - pagrindines formos susiejimas su kalbos dalimi
//    lpszToMainForm_l - pagrindines gram. formos ir isvestiniu formu galuniu
//       susiejimas su pagrindines formos galune
//    lpszForms_l - isvestines gramatines formos
//    plpszaEndSkipTable_l - lietuvusku galuniu lentele
//    plpszaUnRegForms_l[] - pagrindines formos suradimas isimciu ir kamieno kaitos
//       atveju arba grizimas prie isvestines formos, kai zodis neturi reiksmes
//       pagrindineje formoje
//
// Algoritmas:
//    1. Lenteleje plpszaEndSkipTable_l radus reikiama galune, ja reikia pakeisti
//       reiksme is antros koloneles.  Gaunamas pagrindines formos kamienas.
//       Pagal trecioje koloneleje esanti simboli is lenteles plpszToMainForm_l
//       surasti atitinkamos pagrindines formos simboli.
//    2. Lenteleje plpszaUnRegForms_l ieskoti galimu isimciu ar kamieno raidziu
//       kaitos, taip gaunama nuoroda i, gal but, kita pagrindine forma.
//    3. Po to lenteleje plpszaEndSkipTable_l ieskoti visu galimu atitinkamu
//       pagrindines formos galuniu ir atlikti atvirkstini pakeitima; gaunamos
//       galimos zodzio pagrindines formos su galunemis.
//
// Pastabos:
//    '.' (taskas) segmento pradzioje ar gale reiskia, kad zodis turi prasideti
//       (pasibaigti) butent sia raidziu kombinacija.  Taskas zodzio pradzioje
//       reiskia, kad nurodytas pakeitimas negalioja, kai prie nagrinejamo kamieno
//       yra priesdeliai ar sudurtiniu zodziu atveju.  Kai taskas segmento gale,
//       po konvertavimo nereikia prideti pagrindines formos galunes, konvertuotas
//       zodis ivestas su visa pasikeitusia pagrindines formos galune, pvz. "dometis"
//    akcentuotos raides ivestos pagal XML (SGML) taisykles, numetus ribojancius '&'
//       ir ';', zr. lentele plpszaXmlSpecCharTags faile tvxmlc.cpp
//
// Problemos:
//    sangraziniu veiksmazodziu pagrindines formos radimas, kai "-si-" yra
//       tarp priesdelio ir kamieno: pasisukti, ...
//    neigiamojo priesdelio "ne-" numetimas
//    veiksmazodziu liepiamosios nuosakos treciojo asmens pagr. formos radimas -
//       sudaromas ne galunes, o priesdelio "te-" pagalba (dar gali buti ir
//       neigiamasis priesdelis "ne-", pvz., "teneatnesa"
//    plpszaUnRegForms_l dar nepilna - reikia visu veiksmazodziu formu ("Q)" ir "R)")
//       atitinkamybiu. Geriau butu pilnas pagr. veiksmazodziu formu zodynas.
//

// ===================================================
// Pagrindines formos susiejimas su kalbos dalimi
//       kaire kolonele - kalbos dalys, desine - sia kalbos dali atitinkanciu
//       pagr. formu sarasas (zr. plpszToMainForm_l).  Pagr. formos, kuriu nera
//       sioje lenteleje turi buti konvertuojamos, naudojant lentele
//       plpszaUnRegForms_l.
//
unsigned char *plpszaToGrForm_l[] =
{
   (unsigned char *)"m",     (unsigned char *)"ABPCEFHIJ",
                                    // vyr. g. daiktavardis, gal dar D? (-ia, -c-ia,
                                    //          -dz-ia, -i)
   (unsigned char *)"f",     (unsigned char *)"CDEGK",
                                    // mot. g. daiktavardis
   (unsigned char *)"h",     (unsigned char *)"CEF",
                                    // niek. g. daiktavardis (plevesa, meme, vagis) gal dar
                                    //          D? (-ia, -c-ia, -dz-ia, -i)
   (unsigned char *)"a",     (unsigned char *)"LMNO",     // budvardis
   (unsigned char *)"n",     (unsigned char *)"12340@[+", // skaitvardis, kelintiniai skaitvardziai ("]") - tik
                                    //       per lentele plpszaUnRegForms_l
   (unsigned char *)"p",     (unsigned char *)"^?,;>",    // ivardis
   (unsigned char *)"v",     (unsigned char *)")",        // veiksmazodis
   NULL,    NULL
};


// ===================================================
// isvestiniu formu galuniu susiejimas su pagrindines formos galune - kairysis
//       simbolis (mazoji raide) galuniu lenteleje plpszaEndSkipTable_l
//       nurodyta prie isvestiniu formu galuniu, desinysis - prie pagrindines formos
//       galunes.
//
unsigned char lpszToMainForm_l[] =
{
#if Compiler==Msvc60
   (unsigned char *)
#endif
   "aA"  // - 1-osios linksniuotes daiktavardis, kietas kamieno galas (-as)
   "bB"  // - 1-osios linksniuotes daiktavardis, minkstas kamieno galas (-ias)
   "pP"  // - 1-osios linksniuotes daiktavardis, minkstas kamieno galas (-is, -ys)
   "cC"  // - 2-osios linksniuotes daiktavardis, kietas kamieno galas (-a)
   "dD"  // - 2-osios linksniuotes daiktavardis, minkstas kamieno galas (-ia, -c-ia,
         //          -dz-ia, -i)
   "eE"  // - 2-osios linksniuotes daiktavardis, vard. galune -e (-e)
   "fF"  // - 3-osios linksniuotes daiktavardis, vyr. gimine (-is)
   "gG"  // - 3-osios linksniuotes daiktavardis, mot. gimine (-is)
   "hH"  // - 4-osios linksniuotes daiktavardis, kietas kamieno galas (-us)
   "iI"  // - 4-osios linksniuotes daiktavardis, minkstas kamieno galas (-ius, -c-ius,
         //          -dz-ius)
   "jJ"  // - 5-osios linksniuotes daiktavardis, vyr. gimine (-uo)
   "kK"  // - 5-osios linksniuotes daiktavardis, mot. gimine (-uo, -e)
   "lL"  // - 1-osios linksniuotes budvardis, kietas kamieno galas (-as)
   "mM"  // - 1-osios linksniuotes budvardis, minkstas kamieno galas (-ias, -c-ias,
         //          (-dz-ias), -is (didis, didelis, abipusis))
   "nN"  // - 2-osios linksniuotes budvardis, kietas kamieno galas (-us)
// "  "     - 2-osios linksniuotes budvardis, minkstas kamieno galas (-ius, -c-ius,
//                   -dz-ius))

   "oO"  // - 3-osios linksniuotes budvardis (-in-is)
   "61"  // - skaitvardziai: vienas, vieneri, (vienetas)
   "72"  // - skaitvardziai, asm. ivardziai: du, dveji, dvejetas, mudu, judu, jiedu, juodu
   "83"  // - skaitvardziai: trys, treji, trejetas
   "94"  // - kiekiniai skaitvardziai: keturi, penki, ...; dauginiai ir kuopiniai
         //           skaitvardziai: ketveri, penkeri..., ketvertas, penketas, ...
   "50"  // - kiekiniai skaitvardziai: vienuolika, dvylika, ...
   "`@"  // - kiekiniai skaitvardziai: dvidesimt, trisdesimt, ...
   "{["  // - kiekiniai skaitvardziai: simtas, milijonas, milijardas
   "-+"  // - kiekiniai skaitvardziai: nulis, tukstantis
   "}]"  // - kelintiniai skaitvardziai: pirmas, ketvirtas, ..., trecias
   "*/"  // - kelintiniai skaitvardziai: simtinis, tukstantinis, milijoninis
   "~^"  // - asmeniniai ivardziai: as, mes
   "!?"  // - asmeniniai ivardziai: tu, jus
   ".,"  // - asmeniniai, parodomieji, klausiamieji ivardziai, kietas kamieno galas:
         //             jis, tas, kas
   ":;"  // - parodomieji, klausiamieji ivardziai, minkstas kamieno galas: sis, toks,
         //             kuris, koks
   "<>"  // - pazymimasis ivardis: pats

   "()"  // - veiksmazodzio bendratis

   "qQ"  // - veiksmazodziu, dalyviu, padalyviu esamasis laikas
   "rR"  // - veiksmazodziu, dalyviu, padalyviu butasis kartinis laikas
   "sS"  // - veiksmazodziu, dalyviu, padalyviu busimasis laikas

   "zZ"  // - veiksmazodzio liepiamoji nuosaka


   "xX"  // - prieveiksmiai, prielinksniai, dalelytes ir kt.

// "uU"  // -
// "wW"  // -
// "vV"  // -
// "yY"  // -
//
// "=_"  // -
// "%#"  // -
// "&$"  // -
// "\'\""  // -
// "\\|"  // -
};


// ===================================================
// isvestines gramatines formos
unsigned char lpszForms_l[] =
{
#if Compiler==Msvc60
   (unsigned char *)
#endif
    "1"  // - budvardziu, kelintiniu skaitvardziu, prieveiksmiu aukstesnysis laipsnis
    "2"  // - budvardziu, kelintiniu skaitvardziu, prieveiksmiu auksciausiasis laipsnis

    "e"  // - ivardziuotinis budvardis, kelintinis skaitvardis, dalyvis

    "d"  // - dauginis skaitvardis
    "p"  // - kuopinis skaitvardis

    "m"  // - vyriska gimine
    "f"  // - moteriska gimine
    "o"  // - budvardziu ir kelintiniu skaitvardziu niekatroji gimine
    "k"  // - budvardinis prieveiksmis - keitimui i budvardi

    "vV" // - vardininkas (vienaskaita, daugiskaita)
    "kK" // - kilmininkas (vienaskaita, daugiskaita)
    "nN" // - naudininkas (vienaskaita, daugiskaita)
    "gG" // - galininkas (vienaskaita, daugiskaita)
    "iI" // - inagininkas (vienaskaita, daugiskaita)
    "wW" // - vietininkas (vienaskaita, daugiskaita)
    "s"  // - sauksmininkas

    "aA" // - veiksmazodziu pirmas asmuo (vienaskaita, daugiskaita)
    "tT" // - veiksmazodziu antras asmuo (vienaskaita, daugiskaita)
    "jJ" // - veiksmazodziu trecias asmuo (vienaskaita, daugiskaita)

    "r"  // - butasis laikas (neveikiamuju dalyviu, sudaromas is bendraties)
    "b"  // - veiksmazodziu, dalyviu, padalyviu butasis dazninis laikas

    "h"  // - veiksmazodziu tariamoji nuosaka
    "z"  // - veiksmazodziu liepiamoji nuosaka (ne visi asmenys padaryti is
         //       pagrindines liepiamosios nuosakos formos)

    "l"  // - veikiamasis dalyvis
    "c"  // - neveikiamasis dalyvis
    "y"  // - pusdalyvis
    "q"  // - padalyvis

    "x"  // - veiksmazodzio, dalyvio sangrazine forma
};


// -------------------------------------------------
char *plpszaPrefixes_l[] =
{
#if FALSE
   "ATSI",     "ATSI",     "AT",       "AT",       ")",   "",
   "BESI",     "BESI",     "BE",       "BE",       ")",   "",
// "DASI",     "DASI",     "DA",       "DA",       ")",   "",
   "ISI",      "ÁSI",      "I",        "Á",        ")",   "",   
   "ISSI",     "IÐSI",     "IS",       "IÐ",       ")",   "",   
   "NUSI",     "NUSI",     "NU",       "NU",       ")",   "",
   "NESI",     "NESI",     "NE",       "NE",       ")",   "",
   "PASI",     "PASI",     "PA",       "PA",       ")",   "",
   "PRISI",    "PRISI",    "PRI",      "PRI",      ")",   "",
   "SUSI",     "SUSI",     "SU",       "SU",       ")",   "",
   "UZSI",     "UÞSI",     "UZ",       "UÞ",       ")",   "",
#endif
   
   NULL,       NULL,       NULL,       NULL,       NULL, NULL
};


// ===================================================
// lietuvusku galuniu lentele
//
// trecioji/ketvirtoji koloneles - kuo keisti pirmosios/antrosios koloneles galune su pakitusiu kamieno galu
//    (t-c d-dz ir pan. kaitos atveju, isimciu atveju - norint gauti pagrindines
//    formos kamiena).
//
// pirma ir trecia koloneles - antros ir ketvirtos koloneles variantai be diakritu
//
// penktoji kolonele - informacija apie pagrindines formos galune, zr.
//    plpszToMainForm_l.
//
// sestoji kolonele - isvestines formos apibudinimas, zr. plpszForms_l.
//
//
char *plpszaEndSkipTable_l[] =
{


"AS",          "AS",          "",          "",          "A",      "mv",   
".NAMAS",      ".NAMAS",      "NAM",       "NAM",       "A",      "mv",   // suveikia neveikiamasis dalyvis -amas
"IAS",         "IAS",         "",          "",          "B",      "mv",   
"IS",          "IS",          "",          "",          "P",      "mv",   
"YS",          "YS",          "",          "",          "P",      "mv",   

"O",           "O",           "",          "",          "a",      "mk",   
".NAMO",       ".NAMO",       "NAM",       "NAM",       "A",      "mk",   // suveikia neveikiamasis dalyvis -amo
"IO",          "IO",          "",          "",          "bp",     "mk",   
"CIO",         "ÈIO",    "T",         "T",         "bp",     "mk",   
"DZIO",        "DÞIO",   "D",         "D",         "bp",     "mk",   

"UI",          "UI",          "",          "",          "a",      "mn",   
".NAMUI",      ".NAMUI",      "NAM",       "NAM",       "A",      "mn",   // suveikia neveikiamasis dalyvis -amui
"IUI",         "IUI",         "",          "",          "bp",     "mn",   
"CIUI",        "ÈIUI",   "T",         "T",         "bp",     "mn",   
"DZIUI",       "DÞIUI",  "D",         "D",         "bp",     "mn",   

"A",           "À",       "",          "",          "a",      "mg",   
".NAMA",       ".NAMÀ",   "NAM",       "NAM",       "A",      "mg",   // suveikia neveikiamasis dalyvis -ama
"IA",          "IÀ",      "",          "",          "b",      "mg",   
"I",           "Á",       "",          "",          "p",      "mg",   

"U",           "U",           "",          "",          "a",      "mi",   
".NAMU",       ".NAMU",   "NAM",       "NAM",       "A",      "mi",   // suveikia neveikiamasis dalyvis -amu
"IU",          "IU",          "",          "",          "bp",     "mi",   
"CIU",         "ÈIU",    "T",         "T",         "bp",     "mi",   
"DZIU",        "DÞIU",   "D",         "D",         "bp",     "mi",   

"E",           "E",           "",          "",          "a",      "mw",   
".NAME",       ".NAME",       "NAM",       "NAM",       "A",      "mw",   // suveikia neveikiamasis dalyvis -ame
"Y",           "Y",           "",          "",          "bp",     "mw",   
"YJ",          "YJ",          "",          "",          "bp",     "mw",   
"YJE",         "YJE",         "",          "",          "bp",     "mw",   

"E",           "E",           "",          "",          "a",      "ms",   
"I",           "I",           "",          "",          "bp",     "ms",   
"Y",           "Y",           "",          "",          "bp",     "ms",   

"AI",          "AI",          "",          "",          "a",      "mV",   
".NAMAI",      ".NAMAI",      "NAM",       "NAM",       "A",      "mV",   // suveikia neveikiamasis dalyvis -amai
"IAI",         "IAI",         "",          "",          "bp",     "mV",   
"CIAI",        "ÈIAI",   "T",         "T",         "bp",     "mV",   
"DZIAI",       "DÞIAI",  "D",         "D",         "bp",     "mV",   

"U",           "Ø",       "",          "",          "a",      "mK",   
".NAMU",       ".NAMØ",   "NAM",       "NAM",       "A",      "mK",   // suveikia neveikiamasis dalyvis -amu
"IU",          "IØ",      "",          "",          "bp",     "mK",   
"CIU",         "ÈIØ", "T",         "T",         "bp",     "mK",   
".ACIU",       ".AÈIØ",   "ACIU",         "AÈIØ",         "bp",     "mi",   
"DZIU",        "DÞIØ", "D",         "D",         "bp",     "mK",   

"AM",          "AM",          "",          "",          "a",      "mN",   
".NAMAM",      ".NAMAM",      "NAM",       "NAM",       "A",      "mN",   // suveikia neveikiamasis dalyvis -amam
"AMS",         "AMS",         "",          "",          "a",      "mN",   
".NAMAMS",     ".NAMAMS",     "NAM",       "NAM",       "A",      "mN",   // suveikia neveikiamasis dalyvis -amams
"IAM",         "IAM",         "",          "",          "bp",     "mN",   
"IAMS",        "IAMS",        "",          "",          "bp",     "mN",   
"CIAM",        "ÈIAM",   "T",         "T",         "bp",     "mN",   
"CIAMS",       "ÈIAMS",  "T",         "T",         "bp",     "mN",   
"DZIAM",       "DÞIAM",  "D",         "D",         "bp",     "mN",   
"DZIAMS",      "DÞIAMS", "D",         "D",         "bp",     "mN",   

"US",          "US",          "",          "",          "a",      "mG",   
".NAMUS",      ".NAMUS",      "NAM",       "NAM",       "A",      "mG",   // suveikia neveikiamasis dalyvis -amus
"IUS",         "IUS",         "",          "",          "bp",     "mG",   
"CIUS",        "ÈIUS",   "T",         "T",         "bp",     "mG",   
"DZIUS",       "DÞIUS",  "D",         "D",         "bp",     "mG",   

"AIS",         "AIS",         "",          "",          "a",      "mI",   
".NAMAIS",     ".NAMAIS",     "NAM",       "NAM",       "A",      "mI",   // suveikia neveikiamasis dalyvis -amais
"IAIS",        "IAIS",        "",          "",          "bp",     "mI",   
"CIAIS",       "ÈIAIS",  "T",         "T",         "bp",     "mI",   
"DZIAIS",      "DÞIAIS", "D",         "D",         "bp",     "mI",   

"UOS",         "UOS",         "",          "",          "a",      "mW",   
".NAMUOS",     ".NAMUOS",     "NAM",       "NAM",       "A",      "mW",   // suveikia neveikiamasis dalyvis -amuos
"UOSE",        "UOSE",        "",          "",          "a",      "mW",   
".NAMUOSE",    ".NAMUOSE",    "NAM",       "NAM",       "A",      "mW",   // suveikia neveikiamasis dalyvis -amuose
"IUOS",        "IUOS",        "",          "",          "bp",     "mW",   
"IUOSE",       "IUOSE",       "",          "",          "bp",     "mW",   
"CIUOS",       "ÈIUOS",  "T",         "T",         "bp",     "mW",   
"CIUOSE",      "ÈIUOSE", "T",         "T",         "bp",     "mW",   
"DZIUOS",      "DÞIUOS", "D",         "D",         "bp",     "mW",   
"DZIUOSE",      "DÞIUOSE", "D",         "D",         "bp",     "mW",   


// --------------------------------- daiktavardis, 2-oji linksniuote
// mama, zinia, varcia, valdzia, ???i, marti, ???di, zole, kate, kede, ???ce, ???dze

"A",           "A",           "",          "",          "C",      "fv",   
"IA",          "IA",          "",          "",          "D",      "fv",   
"CIA",         "ÈIA",    "T",         "T",         "D",      "fv",   
"DZIA",        "DÞIA",   "D",         "D",         "D",      "fv",   
"I",           "I",           "",          "",          "D",      "fv",   
"E",           "Ë",        "",          "",          "E",      "fv",   
// "CE",         "ÈË",  "T",         "T",         "E",      "fv",   // nera
// "DZE",         "DÞË", "D",         "D",         "E",      "fv",   // nera

"OS",          "OS",          "",          "",          "c",      "fk",   
"IOS",         "IOS",         "",          "",          "d",      "fk",   
"CIOS",        "ÈIOS",   "T",         "T",         "d",      "fk",   
"DZIOS",       "DÞIOS",  "D",         "D",         "d",      "fk",   
"ES",          "ËS",       "",          "",          "e",      "fk",   
// "CES",         "ÈËS", "T",         "T",         "e",      "fk",   // nera
// "DZES",         "DÞËS", "D",         "D",         "e",      "fk",   // nera

"AI",          "AI",          "",          "",          "c",      "fn",   
"IAI",         "IAI",         "",          "",          "d",      "fn",   
"CIAI",        "ÈIAI",   "T",         "T",         "d",      "fn",   
"DZIAI",       "DÞIAI",  "D",         "D",         "d",      "fn",   
"EI",          "EI",          "",          "",          "e",      "fn",   
// "CEI",      "ÈEI",    "T",         "T",         "e",      "fn",   // nera
// "DZEI",      "DÞEI",   "D",         "D",         "e",      "fn",   // nera

"A",           "À",       "",          "",          "c",      "fg",   
"IA",          "IÀ",      "",          "",          "d",      "fg",   
"CIA",         "ÈIÀ", "T",         "T",         "d",      "fg",   
"DZIA",        "DÞIÀ", "D",         "D",         "d",      "fg",   
"E",           "Æ",       "",          "",          "e",      "fg",   
// "CE",       "ÈÆ", "T",         "T",         "e",      "fg",   // nera
// "DZE",      "DÞÆ", "D",         "D",         "e",      "fg",   // nera

"A",           "A",           "",          "",          "c",      "fi",   
"IA",          "IA",          "",          "",          "d",      "fi",   
"CIA",         "ÈIA",    "T",         "T",         "d",      "fi",   
"DZIA",        "DÞIA",   "D",         "D",         "d",      "fi",   
"E",           "E",           "",          "",          "e",      "fi",   
// "CE",       "ÈE",     "T",         "T",         "e",      "fi",   // nera
// "DZE",      "DÞE",    "D",         "D",         "e",      "fi",   // nera

// "O",        "O",           "",          "",          "c",      "fw",   // tarm.
"OJ",          "OJ",          "",          "",          "c",      "fw",   
"OJE",         "OJE",         "",          "",          "c",      "fw",   
// "IO",       "IO",          "",          "",          "d",      "fw",   // tarm.
"IOJ",         "IOJ",         "",          "",          "d",      "fw",   
"IOJE",        "IOJE",        "",          "",          "d",      "fw",   
// "CIO",      "ÈIO",    "T",         "T",         "d",      "fw",   // tarm.
"CIOJ",        "ÈIOJ",   "T",         "T",         "d",      "fw",   
"CIOJE",       "ÈIOJE",  "T",         "T",         "d",      "fw",   
// "DZIO",      "DÞIO",   "D",         "D",         "d",      "fw",   // tarm.
"DZIOJ",       "DÞIOJ",  "D",         "D",         "d",      "fw",   
"DZIOJE",      "DÞIOJE", "D",         "D",         "d",      "fw",   
// "E",        "Ë",        "",          "",          "e",      "fw",   // tarm.
"EJ",          "ËJ",       "",          "",          "e",      "fw",   
"EJE",         "ËJE",      "",          "",          "e",      "fw",   
// "CE",         "ÈË",  "T",         "T",         "e",      "fw",   // nera, tarm.
// "CEJ",         "ÈËJ", "T",         "T",         "e",      "fw",   // nera
// "CEJE",         "ÈËJE", "T",         "T",         "e",      "fw",   // nera
// "DZE",         "DÞË", "D",         "D",         "e",      "fw",   // nera, tarm.
// "DZEJ",         "DÞËJ", "D",         "D",         "e",      "fw",   // nera
// "DZEJE",         "DÞËJE", "D",         "D",         "e",      "fw",   // nera

"A",           "A",           "",          "",          "c",      "fs",   
"IA",          "IA",          "",          "",          "d",      "fs",   
"CIA",         "ÈIA",    "T",         "T",         "d",      "fs",   
"DZIA",        "DÞIA",   "D",         "D",         "d",      "fs",   
"E",           "E",           "",          "",          "e",      "fs",   
// "CE",       "ÈE",     "T",         "T",         "e",      "fs",   // nera
// "DZE",      "DÞE",    "D",         "D",         "e",      "fs",   // nera

"OS",          "OS",          "",          "",          "c",      "fV",   
".PAJAMOS",    ".PAJAMOS",    "PAJAM",     "PAJAM",     "c",      "fV",   // suveikia neveikiamasis dalyvis -amos
"IOS",         "IOS",         "",          "",          "d",      "fV",   
"CIOS",        "ÈIOS",   "T",         "T",         "d",      "fV",   
"DZIOS",       "DÞIOS",  "D",         "D",         "d",      "fV",   
"ES",          "ËS",       "",          "",          "e",      "fV",   
// "CES",         "ÈËS", "T",         "T",         "e",      "fV",   // nera
// "DZES",         "DÞËS", "D",         "D",         "e",      "fV",   // nera

"U",           "Ø",       "",          "",          "c",      "fK",   
".PAJAMU",     ".PAJAMØ",    "PAJAM",     "PAJAM",     "c",      "fK",   // suveikia neveikiamasis dalyvis -amu
"IU",          "IØ",      "",          "",          "de",     "fK",   
"CIU",         "ÈIØ", "T",         "T",         "de",     "fK",   
"DZIU",        "DÞIØ", "D",         "D",         "de",     "fK",   

"OM",          "OM",          "",          "",          "c",      "fN",   
".PAJAMOM",    ".PAJAMOM",    "PAJAM",     "PAJAM",     "c",      "fN",   // suveikia neveikiamasis dalyvis -amom
"OMS",         "OMS",         "",          "",          "c",      "fN",   
".PAJAMOMS",   ".PAJAMOMS",   "PAJAM",     "PAJAM",     "c",      "fN",   // suveikia neveikiamasis dalyvis -amoms
"IOM",         "IOM",         "",          "",          "d",      "fN",   
"IOMS",        "IOMS",        "",          "",          "d",      "fN",   
"CIOM",        "ÈIOM",   "T",         "T",         "d",      "fN",   
"CIOMS",       "ÈIOMS",  "T",         "T",         "d",      "fN",   
"DZIOM",       "DÞIOM",  "D",         "D",         "d",      "fN",   
"DZIOMS",      "DÞIOMS", "D",         "D",         "d",      "fN",   
"EM",          "ËM",       "",          "",          "e",      "fN",   
"EMS",         "ËMS",      "",          "",          "e",      "fN",   
// "CEM",         "ÈËM", "T",         "T",         "e",      "fN",   // nera
// "CEMS",         "ÈËMS", "T",         "T",         "e",      "fN",   // nera
// "DZEM",         "DÞËM", "D",         "D",         "e",      "fN",   // nera
// "DZEMS",         "DÞËMS", "D",         "D",         "e",      "fN",   // nera

"AS",          "AS",          "",          "",          "c",      "fG",   
".PAJAMAS",    ".PAJAMAS",   "PAJAM",     "PAJAM",     "c",      "fG",   // suveikia neveikiamasis dalyvis -amas
"IAS",         "IAS",         "",          "",          "d",      "fG",   
"CIAS",        "ÈIAS",   "T",         "T",         "d",      "fG",   
"DZIAS",       "DÞIAS",  "D",         "D",         "d",      "fG",   
"ES",          "ES",          "",          "",          "e",      "fG",   
// "CES",      "ÈES",    "T",         "T",         "e",      "fG",   // nera
// "DZES",      "DÞES",   "D",         "D",         "e",      "fG",   // nera

"OM",          "OM",          "",          "",          "c",      "fI",   
".PAJAMOM",    ".PAJAMOM",    "PAJAM",     "PAJAM",     "c",      "fI",   // suveikia neveikiamasis dalyvis -amom
"OMIS",        "OMIS",        "",          "",          "c",      "fI",   
".PAJAMOMIS",  ".PAJAMOMIS",  "PAJAM",     "PAJAM",     "c",      "fI",   // suveikia neveikiamasis dalyvis -amomis
"IOM",         "IOM",         "",          "",          "d",      "fI",   
"IOMIS",       "IOMIS",       "",          "",          "d",      "fI",   
"CIOM",        "ÈIOM",   "T",         "T",         "d",      "fI",   
"CIOMIS",      "ÈIOMIS", "T",         "T",         "d",      "fI",   
"DZIOM",       "DÞIOM",  "D",         "D",         "d",      "fI",   
"DZIOMIS",      "DÞIOMIS", "D",         "D",         "d",      "fI",   
"EM",          "ËM",       "",          "",          "e",      "fI",   
"EMIS",        "ËMIS",     "",          "",          "e",      "fI",   
// "CEM",         "ÈËM", "T",         "T",         "e",      "fI",   // nera
// "CEMIS",         "ÈËMIS", "T",         "T",         "e",      "fI",   // nera
// "DZEM",         "DÞËM", "D",         "D",         "e",      "fI",   // nera
// "DZEMIS",         "DÞËMIS", "D",         "D",         "e",      "fI",   // nera

"OSE",         "OSE",         "",          "",          "c",      "fW",   
".PAJAMOSE",   ".PAJAMOSE",   "PAJAM",     "PAJAM",     "c",      "fW",   // suveikia neveikiamasis dalyvis -amose
"IOSE",        "IOSE",        "",          "",          "d",      "fW",   
"CIOSE",       "ÈIOSE",  "T",         "T",         "d",      "fW",   
"DZIOSE",      "DÞIOSE", "D",         "D",         "d",      "fW",   
"ESE",         "ËSE",      "",          "",          "e",      "fW",   
// "CESE",         "ÈËSE", "T",         "T",         "e",      "fW",   // nera
// "DZESE",         "DÞËSE", "D",         "D",         "e",      "fW",   // nera


// --------------------------------- daiktavardis, 3-oji linksniuote
// zveris, vagis, ???tis(vyr.), ???dis(vyr.), ausis, antis, ???dis(mot.), desimtis

"IS",          "IS",          "",          "",          "FG",     "mfv",   

"IES",         "IES",         "",          "",          "fg",     "mfk",   

"UI",          "UI",          "",          "",          "f",      "mn",   
"IUI",         "IUI",         "",          "",          "f",      "mn",   
"CIUI",        "ÈIUI",   "T",         "T",         "f",      "mn",   
"DZIUI",       "DÞIUI",  "D",         "D",         "f",      "mn",   
"AI",          "AI",          "",          "",          "g",      "fn",   
"IAI",         "IAI",         "",          "",          "g",      "fn",   
"CIAI",        "ÈIAI",   "T",         "T",         "g",      "fn",   
"DZIAI",       "DÞIAI",  "D",         "D",         "g",      "fn",   

"I",           "Á",       "",          "",          "fg",     "mfg",   

"IM",          "IM",          "",          "",          "fg",     "mfi",   
"IMI",         "IMI",         "",          "",          "fg",     "mfi",   
"CIA",         "ÈIA",    "T",         "T",         "g",      "fi",   // desimcia

"Y",           "Y",           "",          "",          "fg",     "mfw",   
"YJ",          "YJ",          "",          "",          "fg",     "mfw",   
"YJE",         "YJE",         "",          "",          "fg",     "mfw",   

"IE",          "IE",          "",          "",          "fg",     "mfs",   

"YS",          "YS",          "",          "",          "fg",     "mfV",   

"IU",          "IØ",      "",          "",          "fg",     "mfK",   
"CIU",         "ÈIØ", "T",         "T",         "fg",     "mfK",   
"DZIU",        "DÞIØ", "D",         "D",         "fg",     "mfK",   

"IM",          "IM",          "",          "",          "fg",     "mfN",   
"IMS",         "IMS",         "",          "",          "fg",     "mfN",   

"IS",          "IS",          "",          "",          "fg",     "mfG",   

"IM",          "IM",          "",          "",          "fg",     "mfI",   
"IMIS",        "IMIS",        "",          "",          "fg",     "mfI",   

"YSE",         "YSE",         "",          "",          "fg",     "mfW",   


// --------------------------------- daiktavardis, 4-oji linksniuote
// sunus, balius, morcius, puodzius

"US",          "US",          "",          "",          "H",      "mv",   
"IUS",         "IUS",         "",          "",          "I",      "mv",   // nekinta
"CIUS",        "ÈIUS",   "T",         "T",         "I",      "mv",   // nekinta
"DZIUS",       "DÞIUS",  "D",         "D",         "I",      "mv",   // nekinta

"AUS",         "AUS",         "",          "",          "h",      "mk",   
"IAUS",        "IAUS",        "",          "",          "i",      "mk",   // nekinta
"CIAUS",       "ÈIAUS",  "T",         "T",         "i",      "mk",   // nekinta
"DZIAUS",      "DÞIAUS", "D",         "D",         "i",      "mk",   // nekinta


"UI",          "UI",          "",          "",          "h",      "mn",   
"IUI",         "IUI",         "",          "",          "i",      "mn",   // nekinta
"CIUI",        "ÈIUI",   "T",         "T",         "i",      "mn",   // nekinta
"DZIUI",       "DÞIUI",  "D",         "D",         "i",      "mn",   // nekinta

"U",           "Ø",       "",          "",          "h",      "mg",   
"IU",          "IØ",      "",          "",          "i",      "mg",   // nekinta
"CIU",         "ÈIØ", "T",         "T",         "i",      "mg",   // nekinta
"DZIU",        "DÞIØ", "D",         "D",         "i",      "mg",   // nekinta

"UM",          "UM",          "",          "",          "h",      "mi",   
"UMI",         "UMI",         "",          "",          "h",      "mi",   
"IUM",         "IUM",         "",          "",          "i",      "mi",   // nekinta
"IUMI",        "IUMI",        "",          "",          "i",      "mi",   // nekinta
"CIUM",        "ÈIUM",   "T",         "T",         "i",      "mi",   // nekinta
"CIUMI",       "ÈIUMI",  "T",         "T",         "i",      "mi",   // nekinta
"DZIUM",       "DÞIUM",  "D",         "D",         "i",      "mi",   // nekinta
"DZIUMI",      "DÞIUMI", "D",         "D",         "i",      "mi",   // nekinta

"UJ",          "UJ",          "",          "",          "h",      "mw",   
"UJE",         "UJE",         "",          "",          "h",      "mw",   
"IUJ",         "IUJ",         "",          "",          "i",      "mw",   // nekinta
"IUJE",        "IUJE",        "",          "",          "i",      "mw",   // nekinta
"CIUJ",        "ÈIUJ",   "T",         "T",         "i",      "mw",   // nekinta
"CIUJE",       "ÈIUJE",  "T",         "T",         "i",      "mw",   // nekinta
"DZIUJ",       "DÞIUJ",  "D",         "D",         "i",      "mw",   // nekinta
"DZIUJE",      "DÞIUJE", "D",         "D",         "i",      "mw",   // nekinta

"AU",          "AU",          "",          "",          "h",      "ms",   
"IAU",         "IAU",         "",          "",          "i",      "ms",   // nekinta
"CIAU",        "ÈIAU",   "T",         "T",         "i",      "ms",   // nekinta
"DZIAU",       "DÞIAU",  "D",         "D",         "i",      "ms",   // nekinta

"US",          "ÛS",      "",          "",          "h",      "mV",   
"IUS",         "IÛS",     "",          "",          "i",      "mV",   // nekinta
"CIUS",          "ÈIÛS", "T",         "T",         "i",      "mV",   // nekinta
"DZIUS",          "DÞIÛS", "D",         "D",         "i",      "mV",   // nekinta

"U",           "Ø",       "",          "",          "h",      "mK",   
"IU",          "IØ",      "",          "",          "i",      "mK",   // nekinta
"CIU",         "ÈIØ", "T",         "T",         "i",      "mK",   // nekinta
"DZIU",        "DÞIØ", "D",         "D",         "i",      "mK",   // nekinta

"UM",          "UM",          "",          "",          "h",      "mN",   
"UMS",         "UMS",         "",          "",          "h",      "mN",   
"IUM",         "IUM",         "",          "",          "i",      "mN",   // nekinta
"IUMS",        "IUMS",        "",          "",          "i",      "mN",   // nekinta
"CIUM",        "ÈIUM",   "T",         "T",         "i",      "mN",   // nekinta
"CIUMS",       "ÈIUMS",  "T",         "T",         "i",      "mN",   // nekinta
"DZIUM",       "DÞIUM",  "D",         "D",         "i",      "mN",   // nekinta
"DZIUMS",      "DÞIUMS", "D",         "D",         "i",      "mN",   // nekinta

"US",          "US",          "",          "",          "h",      "mG",   
"IUS",         "IUS",         "",          "",          "i",      "mG",   // nekinta
"CIUS",        "ÈIUS",   "T",         "T",         "i",      "mG",   // nekinta
"DZIUS",       "DÞIUS",  "D",         "D",         "i",      "mG",   // nekinta

"UM",          "UM",          "",          "",          "h",      "mI",   
"UMIS",        "UMIS",        "",          "",          "h",      "mI",   
"IUM",         "IUM",         "",          "",          "i",      "mI",   // nekinta
"IUMIS",       "IUMIS",       "",          "",          "i",      "mI",   // nekinta
"CIUM",        "ÈIUM",   "T",         "T",         "i",      "mI",   // nekinta
"CIUMIS",      "ÈIUMIS", "T",         "T",         "i",      "mI",   // nekinta
"DZIUM",       "DÞIUM",  "D",         "D",         "i",      "mI",   // nekinta
"DZIUMIS",      "DÞIUMIS", "D",         "D",         "i",      "mI",   // nekinta

"UOS",         "UOS",         "",          "",          "h",      "mW",   
"UOSE",        "UOSE",        "",          "",          "h",      "mW",   
"IUOS",        "IUOS",        "",          "",          "i",      "mW",   // nekinta
"IUOSE",       "IUOSE",       "",          "",          "i",      "mW",   // nekinta
"CIUOS",       "ÈIUOS",  "T",         "T",         "i",      "mW",   // nekinta
"CIUOSE",      "ÈIUOSE", "T",         "T",         "i",      "mW",   // nekinta
"DZIUOS",      "DÞIUOS", "D",         "D",         "i",      "mW",   // nekinta
"DZIUOSE",      "DÞIUOSE", "D",         "D",         "i",      "mW",   // nekinta


// --------------------------------- daiktavardis, 5-oji linksniuote
// akmuo, sesuo, dukte; suo, suva

"UO",          "UO",          "",          "",          "JK",     "mfv",   
"E",           "Ë",        "",          "",          "K",      "fv",   
"SUO",         "ÐUO",    "SUN",       "ÐUN",  "J",      "mv",   
"SUVA",        "ÐUVA",   "SUN",       "ÐUN",  "J",      "mv",   

"ENS",         "ENS",         "",          "",          "j",      "mk",   
"ERS",         "ERS",         "",          "",          "k",      "fk",   
"SUNS",        "ÐUNS",   "SUN",       "ÐUN",  "j",      "mk",   
"SUNIO",       "ÐUNIO",  "SUN",       "ÐUN",  "j",      "mk",   

"ENIUI",       "ENIUI",       "",          "",          "j",      "mn",   
"ERIAI",       "ERIAI",       "",          "",          "k",      "fn",   
"SUNIUI",      "ÐUNIUI", "SUN",       "ÐUN",  "j",      "mn",   

"ENI",         "ENÁ",     "",          "",          "j",      "mg",   
"ERI",         "ERÁ",     "",          "",          "k",      "fg",   
"SUNI",        "ÐUNÁ", "SUN",       "ÐUN",  "j",      "mg",   

"ENIU",        "ENIU",        "",          "",          "j",      "mi",   
"ENIM",        "ENIM",        "",          "",          "j",      "mi",   
"ENIMI",       "ENIMI",       "",          "",          "j",      "mi",   
"ERIA",        "ERIA",        "",          "",          "k",      "fi",   
"ERIM",        "ERIM",        "",          "",          "k",      "fi",   
"ERIMI",       "ERIMI",       "",          "",          "k",      "fi",   
"SUNIU",       "ÐUNIU",  "SUN",       "ÐUN",  "j",      "mi",   
"SUNIM",       "ÐUNIM",  "SUN",       "ÐUN",  "j",      "mi",   
"SUNIMI",      "ÐUNIMI", "SUN",       "ÐUN",  "j",      "mi",   

"ENY",         "ENY",         "",          "",          "j",      "mw",   
"ENYJ",        "ENYJ",        "",          "",          "j",      "mw",   
"ENYJE",       "ENYJE",       "",          "",          "j",      "mw",   
"ERY",         "ERY",         "",          "",          "k",      "fw",   
"ERYJ",        "ERYJ",        "",          "",          "k",      "fw",   
"ERYJE",       "ERYJE",       "",          "",          "k",      "fw",   
"SUNY",        "ÐUNY",   "SUN",       "ÐUN",  "j",      "mw",   
"SUNYJ",       "ÐUNYJ",  "SUN",       "ÐUN",  "j",      "mw",   
"SUNYJE",      "ÐUNYJE", "SUN",       "ÐUN",  "j",      "mw",   

"ENIE",        "ENIE",        "",          "",          "j",      "ms",   
"ERIE",        "ERIE",        "",          "",          "k",      "fs",   
"SUNIE",       "ÐUNIE",  "SUN",       "ÐUN",  "j",      "ms",   

"ENS",         "ENS",         "",          "",          "j",      "mV",   
"ENYS",        "ENYS",        "",          "",          "j",      "mV",   
"ERS",         "ERS",         "",          "",          "k",      "fV",   
"ERYS",        "ERYS",        "",          "",          "k",      "fV",   
"SUNYS",       "ÐUNYS",  "SUN",       "ÐUN",  "j",      "mV",   

"ENU",         "ENØ",     "",          "",          "j",      "mK",   
"ERU",         "ERØ",     "",          "",          "k",      "fK",   
"SUNU",        "ÐUNØ", "SUN",       "ÐUN",  "j",      "mK",   

"ENIM",        "ENIM",        "",          "",          "j",      "mN",   
"ENIMS",       "ENIMS",       "",          "",          "j",      "mN",   
"ERIM",        "ERIM",        "",          "",          "k",      "fN",   
"ERIMS",       "ERIMS",       "",          "",          "k",      "fN",   
"SUNIM",       "ÐUNIM",  "SUN",       "ÐUN",  "j",      "mN",   
"SUNIMS",      "ÐUNIMS", "SUN",       "ÐUN",  "j",      "mN",   

"ENIS",        "ENIS",        "",          "",          "j",      "mG",   
"ERIS",        "ERIS",        "",          "",          "k",      "fG",   
"ADAPTERIS",   "ADAPTERIS",   "ADAPTER",   "ADAPTER",          "k",      "fG",   
"SUNIS",       "ÐUNIS",  "SUN",       "ÐUN",  "j",      "mG",   

"ENIM",        "ENIM",        "",          "",          "j",      "mI",   
"ENIMIS",      "ENIMIS",      "",          "",          "j",      "mI",   
"ERIM",        "ERIM",        "",          "",          "k",      "fI",   
"ERIMIS",      "ERIMIS",      "",          "",          "k",      "fI",   
"SUNIM",       "ÐUNIM",  "SUN",       "ÐUN",  "j",      "mI",   
"SUNIMIS",      "ÐUNIMIS", "SUN",       "ÐUN",  "j",      "mI",   

"ENYSE",       "ENYSE",       "",          "",          "j",      "mW",   
"ERYSE",       "ERYSE",       "",          "",          "k",      "fW",   
"SUNYSE",      "ÐUNYSE", "SUN",       "ÐUN",  "j",      "mW",   


// --------------------------------- budvardis, 1-oji linksniuote, vyr. gimine
// baltas, zalias, kurcias, ???dzias; abipusis, didelis (daugisk.)

"AS",          "AS",          "",          "",          "L",      "mv",   
"IAS",         "IAS",         "",          "",          "M",      "mv",   
"CIAS",        "ÈIAS",   "T",         "T",         "M",      "mv",   
// "DZIAS",      "DÞIAS",  "D",         "D",         "M",      "mv",   // nera

"O",           "O",           "",          "",          "l",      "mk",   
"IO",          "IO",          "",          "",          "m",      "mk",   
"CIO",         "ÈIO",    "T",         "T",         "m",      "mk",   
// "DZIO",      "DÞIO",   "D",         "D",         "m",      "mk",   // nera

"AM",          "AM",          "",          "",          "l",      "mn",   
"IAM",         "IAM",         "",          "",          "m",      "mn",   
"CIAM",        "ÈIAM",   "T",         "T",         "m",      "mn",   
// "DZIAM",      "DÞIAM",  "D",         "D",         "m",      "mn",   // nera

"A",           "À",       "",          "",          "l",      "mg",   
"IA",          "IÀ",      "",          "",          "m",      "mg",   
"CIA",         "ÈIÀ", "T",         "T",         "m",      "mg",   
// "DZIA",      "DÞIÀ", "D",         "D",         "m",      "mg",   // nera

"U",           "U",           "",          "",          "l",      "mi",   
"IU",          "IU",          "",          "",          "m",      "mi",   
"CIU",         "ÈIU",    "T",         "T",         "m",      "mi",   
// "DZIU",      "DÞIU",   "D",         "D",         "m",      "mi",   // nera

"AM",          "AM",          "",          "",          "l",      "mw",   
"AME",         "AME",         "",          "",          "l",      "mw",   
"IAM",         "IAM",         "",          "",          "m",      "mw",   
"IAME",        "IAME",        "",          "",          "m",      "mw",   
"CIAM",        "ÈIAM",   "T",         "T",         "m",      "mw",   
"CIAME",       "ÈIAME",  "T",         "T",         "m",      "mw",   
// "DZIAM",      "DÞIAM",  "D",         "D",         "m",      "mw",   // nera
// "DZIAME",      "DÞIAME", "D",         "D",         "m",      "mw",   // nera

"AS",          "AS",          "",          "",          "l",      "ms",   
"IAS",         "IAS",         "",          "",          "m",      "ms",   
"CIAS",        "ÈIAS",   "T",         "T",         "m",      "ms",   
// "DZIAS",      "DÞIAS",  "D",         "D",         "m",      "ms",   // nera

"I",           "I",           "",          "",          "lm",     "mV",   

"U",           "Ø",       "",          "",          "l",      "mK",   
"IU",          "IØ",      "",          "",          "m",      "mK",   
"CIU",         "ÈIØ", "T",         "T",         "m",      "mK",   
// "DZIU",      "DÞIØ", "D",         "D",         "m",      "mK",   // nera

"IEM",         "IEM",         "",          "",          "lm",     "mN",   
"IEMS",        "IEMS",        "",          "",          "lm",     "mN",   

"US",          "US",          "",          "",          "l",      "mG",   
"IUS",         "IUS",         "",          "",          "m",      "mG",   
"CIUS",        "ÈIUS",   "T",         "T",         "m",      "mG",   
// "DZIUS",      "DÞIUS",  "D",         "D",         "m",      "mG",   // nera

"AIS",         "AIS",         "",          "",          "l",      "mI",   
"IAIS",        "IAIS",        "",          "",          "m",      "mI",   
"CIAIS",       "ÈIAIS",  "T",         "T",         "m",      "mI",   
// "DZIAIS",      "DÞIAIS", "D",         "D",         "m",      "mI",   // nera

"UOS",         "UOS",         "",          "",          "l",      "mW",   
"UOSE",        "UOSE",        "",          "",          "l",      "mW",   
"IUOS",        "IUOS",        "",          "",          "m",      "mW",   
"IUOSE",       "IUOSE",       "",          "",          "m",      "mW",   
"CIUOS",       "ÈIUOS",  "T",         "T",         "m",      "mW",   
"CIUOSE",      "ÈIUOSE", "T",         "T",         "m",      "mW",   
// "DZIUOS",      "DÞIUOS", "D",         "D",         "m",      "mW",   // nera
// "DZIUOSE",      "DÞIUOSE", "D",         "D",         "m",      "mW",   // nera


// --------------------------------- budvardis, 1-oji linksniuote, mot. gimine
// minksta, slapia, kurcia, ???dzia

"A",           "A",           "",          "",          "l",      "fv",   
"IA",          "IA",          "",          "",          "m",      "fv",   // nekinta
"CIA",         "ÈIA",    "T",         "T",         "m",      "fv",   // nekinta
// "DZIA",      "DÞIA",   "D",         "D",         "m",      "fv",   // nekinta, nera

"OS",          "OS",          "",          "",          "l",      "fk",   
"IOS",         "IOS",         "",          "",          "m",      "fk",   // nekinta
"CIOS",        "ÈIOS",   "T",         "T",         "m",      "fk",   // nekinta
// "DZIOS",      "DÞIOS",  "D",         "D",         "m",      "fk",   // nekinta, nera

"AI",          "AI",          "",          "",          "l",      "fn",   
"IAI",         "IAI",         "",          "",          "m",      "fn",   // nekinta
"CIAI",        "ÈIAI",   "T",         "T",         "m",      "fn",   // nekinta
// "DZIAI",      "DÞIAI",  "D",         "D",         "m",      "fn",   // nekinta, nera

"A",           "À",       "",          "",          "l",      "fg",   
"IA",          "IÀ",      "",          "",          "m",      "fg",   // nekinta
"CIA",         "ÈIÀ", "T",         "T",         "m",      "fg",   // nekinta
// "DZIA",      "DÞIÀ", "D",         "D",         "m",      "fg",   // nekinta, nera

"A",           "A",           "",          "",          "l",      "fi",   
"IA",          "IA",          "",          "",          "m",      "fi",   // nekinta
"CIA",         "ÈIA",    "T",         "T",         "m",      "fi",   // nekinta
// "DZIA",      "DÞIA",   "D",         "D",         "m",      "fi",   // nekinta, nera

// "O",        "O",           "",          "",          "l",      "fw",   // tarm.
"OJ",          "OJ",          "",          "",          "l",      "fw",   
"OJE",         "OJE",         "",          "",          "l",      "fw",   
// "IO",       "IO",          "",          "",          "m",      "fw",   // nekinta, tarm.
"IOJ",         "IOJ",         "",          "",          "m",      "fw",   // nekinta
"IOJE",        "IOJE",        "",          "",          "m",      "fw",   // nekinta
// "CIO",      "ÈIO",    "T",         "T",         "m",      "fw",   // nekinta, tarm.
"CIOJ",        "ÈIOJ",   "T",         "T",         "m",      "fw",   // nekinta
"CIOJE",       "ÈIOJE",  "T",         "T",         "m",      "fw",   // nekinta
// "DZIO",      "DÞIO",   "D",         "D",         "m",      "fw",   // nekinta, nera, tarm.
// "DZIOJ",      "DÞIOJ",  "D",         "D",         "m",      "fw",   // nekinta, nera
// "DZIOJE",      "DÞIOJE", "D",         "D",         "m",      "fw",   // nekinta, nera

"A",           "A",           "",          "",          "l",      "fs",   
"IA",          "IA",          "",          "",          "m",      "fs",   // nekinta
"CIA",         "ÈIA",    "T",         "T",         "m",      "fs",   // nekinta
// "DZIA",      "DÞIA",   "D",         "D",         "m",      "fs",   // nekinta, nera

"OS",          "OS",          "",          "",          "l",      "fV",   
"IOS",         "IOS",         "",          "",          "m",      "fV",   // nekinta
"CIOS",        "ÈIOS",   "T",         "T",         "m",      "fV",   // nekinta
// "DZIOS",      "DÞIOS",  "D",         "D",         "m",      "fV",   // nekinta, nera

"U",           "Ø",       "",          "",          "l",      "fK",   
"IU",          "IØ",      "",          "",          "m",      "fK",   // nekinta
"CIU",         "ÈIØ", "T",         "T",         "m",      "fK",   // nekinta
// "DZIU",      "DÞIØ", "D",         "D",         "m",      "fK",   // nekinta, nera

"OM",          "OM",          "",          "",          "l",      "fN",   
"OMS",         "OMS",         "",          "",          "l",      "fN",   
"IOM",         "IOM",         "",          "",          "m",      "fN",   // nekinta
"IOMS",        "IOMS",        "",          "",          "m",      "fN",   // nekinta
"CIOM",        "ÈIOM",   "T",         "T",         "m",      "fN",   // nekinta
"CIOMS",       "ÈIOMS",  "T",         "T",         "m",      "fN",   // nekinta
// "DZIOM",      "DÞIOM",  "D",         "D",         "m",      "fN",   // nekinta, nera
// "DZIOMS",      "DÞIOMS", "D",         "D",         "m",      "fN",   // nekinta, nera

"AS",          "AS",          "",          "",          "l",      "fG",   
"IAS",         "IAS",         "",          "",          "m",      "fG",   // nekinta
"CIAS",        "ÈIAS",   "T",         "T",         "m",      "fG",   // nekinta
// "DZIAS",      "DÞIAS",  "D",         "D",         "m",      "fG",   // nekinta, nera

"OM",          "OM",          "",          "",          "l",      "fI",   
"OMIS",        "OMIS",        "",          "",          "l",      "fI",   
"IOM",         "IOM",         "",          "",          "m",      "fI",   // nekinta
"IOMIS",       "IOMIS",       "",          "",          "m",      "fI",   // nekinta
"CIOM",        "ÈIOM",   "T",         "T",         "m",      "fI",   // nekinta
"CIOMIS",      "ÈIOMIS", "T",         "T",         "m",      "fI",   // nekinta
// "DZIOM",      "DÞIOM",  "D",         "D",         "m",      "fI",   // nekinta, nera
// "DZIOMIS",      "DÞIOMIS", "D",         "D",         "m",      "fI",   // nekinta, nera

"OSE",         "OSE",         "",          "",          "l",      "fW",   
"IOSE",        "IOSE",        "",          "",          "m",      "fW",   // nekinta
"CIOSE",       "ÈIOSE",  "T",         "T",         "m",      "fW",   // nekinta
// "DZIOSE",      "DÞIOSE", "D",         "D",         "m",      "fW",   // nekinta, nera


// --------------------------------- budvardis, 1-oji linksniuote, niek. gimine
// minksta, slapia, ???cia, ???dzia

"A",           "A",           "",          "",          "l",      "o",   
"IA",          "IA",          "",          "",          "m",      "o",   
"CIA",         "ÈIA",    "T",         "T",         "m",      "o",   
// "DZIA",      "DÞIA",   "D",         "D",         "m",      "o",   // nera


// -------------------- budvardinis prieveiksmis, padarytas is 1-osios linksniuotes budvardzio
// minkstai, slapiai, kurciai, ???dziai

"AI",          "AI",          "",          "",          "l",      "k",   
"IAI",         "IAI",         "",          "",          "m",      "k",   
"CIAI",        "ÈIAI",   "T",         "T",         "m",      "k",   
// "DZIAI",      "DÞIAI",  "D",         "D",         "m",      "k",   // nera


// --------------------------------- budvardis, 2-oji linksniuote, vyr. gimine
// tamsus, ???ius, kartus, kandus

"US",          "US",          "",          "",          "N",      "mv",   
// "IUS",      "IUS",         "",          "",          "N",      "mv",   // nera

"AUS",         "AUS",         "",          "",          "n",      "mk",   
// "IAUS",     "IAUS",        "",          "",          "n",      "mk",   // nera

// "AM",       "AM",          "",          "",          "n",      "mn",   // nera
"IAM",         "IAM",         "",          "",          "n",      "mn",   
"CIAM",        "ÈIAM",   "T",         "T",         "n",      "mn",   
"DZIAM",       "DÞIAM",  "D",         "D",         "n",      "mn",   

"U",           "Ø",       "",          "",          "n",      "mg",   
// "IU",       "IØ",      "",          "",          "n",      "mg",   // nera

// "U",        "U",           "",          "",          "n",      "mi",   // nera
"IU",          "IU",          "",          "",          "n",      "mi",   
"CIU",         "ÈIU",    "T",         "T",         "n",      "mi",   
"DZIU",        "DÞIU",   "D",         "D",         "n",      "mi",   

// "AM",       "AM",          "",          "",          "n",      "mw",   // nera
"IAM",         "IAM",         "",          "",          "n",      "mw",   
// "AME",      "AME",         "",          "",          "n",      "mw",   // nera
"IAME",        "IAME",        "",          "",          "n",      "mw",   
"CIAM",        "ÈIAM",   "T",         "T",         "n",      "mw",   
"CIAME",       "ÈIAME",  "T",         "T",         "n",      "mw",   
"DZIAM",       "DÞIAM",  "D",         "D",         "n",      "mw",   
"DZIAME",      "DÞIAME", "D",         "D",         "n",      "mw",   

"US",          "US",          "",          "",          "n",      "ms",   
// "IUS",      "IUS",         "",          "",          "n",      "ms",   // nera

"US",          "ÛS",      "",          "",          "n",      "mV",   
// "IUS",      "IÛS",     "",          "",          "n",      "mV",   // nera

// "U",        "Ø",       "",          "",          "n",      "mK",   // nera
"IU",          "IØ",      "",          "",          "n",      "mK",   
"CIU",         "ÈIØ", "T",         "T",         "n",      "mK",   
"DZIU",        "DÞIØ", "D",         "D",         "n",      "mK",   

"IEM",         "IEM",         "",          "",          "n",      "mN",   
"IEMS",        "IEMS",        "",          "",          "n",      "mN",   

// "US",       "US",          "",          "",          "n",      "mG",   // nera
"IUS",         "IUS",         "",          "",          "n",      "mG",   
"CIUS",        "ÈIUS",   "T",         "T",         "n",      "mG",   
"DZIUS",       "DÞIUS",  "D",         "D",         "n",      "mG",   

// "AIS",      "AIS",         "",          "",          "n",      "mI",   // nera
"IAIS",        "IAIS",        "",          "",          "n",      "mI",   
"CIAIS",       "ÈIAIS",  "T",         "T",         "n",      "mI",   
"DZIAIS",      "DÞIAIS", "D",         "D",         "n",      "mI",   

// "UOS",      "UOS",         "",          "",          "n",      "mW",   // nera
"IUOS",        "IUOS",        "",          "",          "n",      "mW",   
// "UOSE",     "UOSE",        "",          "",          "n",      "mW",   // nera
"IUOSE",       "IUOSE",       "",          "",          "n",      "mW",   
"CIUOS",       "ÈIUOS",  "T",         "T",         "n",      "mW",   
"CIUOSE",      "ÈIUOSE", "T",         "T",         "n",      "mW",   
"DZIUOS",      "DÞIUOS", "D",         "D",         "n",      "mW",   
"DZIUOSE",      "DÞIUOSE", "D",         "D",         "n",      "mW",   


// --------------------------------- budvardis, 2-oji linksniuote, mot. gimine
// tamsi, karti, kandi

"I",           "I",           "",          "",          "n",      "fv",   // nekinta

"IOS",         "IOS",         "",          "",          "n",      "fk",   // nekinta
"CIOS",        "ÈIOS",   "T",         "T",         "n",      "fk",   
"DZIOS",       "DÞIOS",  "D",         "D",         "n",      "fk",   

"IAI",         "IAI",         "",          "",          "n",      "fn",   // nekinta
"CIAI",        "ÈIAI",   "T",         "T",         "n",      "fn",   
"DZIAI",       "DÞIAI",  "D",         "D",         "n",      "fn",   

"IA",          "IÀ",      "",          "",          "n",      "fg",   // nekinta
"CIA",         "ÈIÀ", "T",         "T",         "n",      "fg",   
"DZIA",        "DÞIÀ", "D",         "D",         "n",      "fg",   

"IA",          "IA",          "",          "",          "n",      "fi",   // nekinta
"CIA",         "ÈIA",    "T",         "T",         "n",      "fi",   
"DZIA",        "DÞIA",   "D",         "D",         "n",      "fi",   

// "IO",       "IO",          "",          "",          "n",      "fw",   // nekinta, tarm.
"IOJ",         "IOJ",         "",          "",          "n",      "fw",   // nekinta
"IOJE",        "IOJE",        "",          "",          "n",      "fw",   // nekinta
// "CIO",      "ÈIO",    "T",         "T",         "n",      "fw",   // tarm.
"CIOJ",        "ÈIOJ",   "T",         "T",         "n",      "fw",   
"CIOJE",       "ÈIOJE",  "T",         "T",         "n",      "fw",   
// "DZIO",      "DÞIO",   "D",         "D",         "n",      "fw",   // tarm.
"DZIOJ",       "DÞIOJ",  "D",         "D",         "n",      "fw",   
"DZIOJE",      "DÞIOJE", "D",         "D",         "n",      "fw",   

"I",           "I",           "",          "",          "n",      "fs",   // nekinta

"IOS",         "IOS",         "",          "",          "n",      "fV",   // nekinta
"CIOS",        "ÈIOS",   "T",         "T",         "n",      "fV",   
"DZIOS",       "DÞIOS",  "D",         "D",         "n",      "fV",   

"IU",          "IØ",      "",          "",          "n",      "fK",   // nekinta
"CIU",         "ÈIØ", "T",         "T",         "n",      "fK",   
"DZIU",        "DÞIØ", "D",         "D",         "n",      "fK",   

"IOM",         "IOM",         "",          "",          "n",      "fN",   // nekinta
"IOMS",        "IOMS",        "",          "",          "n",      "fN",   // nekinta
"CIOM",        "ÈIOM",   "T",         "T",         "n",      "fN",   
"CIOMS",       "ÈIOMS",  "T",         "T",         "n",      "fN",   
"DZIOM",       "DÞIOM",  "D",         "D",         "n",      "fN",   
"DZIOMS",      "DÞIOMS", "D",         "D",         "n",      "fN",   

"IAS",         "IAS",         "",          "",          "n",      "fG",   // nekinta
"CIAS",        "ÈIAS",   "T",         "T",         "n",      "fG",   
"DZIAS",       "DÞIAS",  "D",         "D",         "n",      "fG",   

"IOM",         "IOM",         "",          "",          "n",      "fI",   // nekinta
"IOMIS",       "IOMIS",       "",          "",          "n",      "fI",   // nekinta
"CIOM",        "ÈIOM",   "T",         "T",         "n",      "fI",   
"CIOMIS",      "ÈIOMIS", "T",         "T",         "n",      "fI",   
"DZIOM",       "DÞIOM",  "D",         "D",         "n",      "fI",   
"DZIOMIS",      "DÞIOMIS", "D",         "D",         "n",      "fI",   

"IOSE",        "IOSE",        "",          "",          "n",      "fW",   // nekinta
"CIOSE",       "ÈIOSE",  "T",         "T",         "n",      "fW",   
"DZIOSE",      "DÞIOSE", "D",         "D",         "n",      "fW",   


// --------------------------------- budvardis, 2-oji linksniuote, niek. gimine
// tamsu, ???iu, kartu, kandu

"U",           "U",           "",          "",          "n",      "o",   
// "IU",       "IU",          "",          "",          "",       "o",   // nera


// -------------------- budvardinis prieveiksmis, padarytas is 2-osios linksniuotes budvardzio
// tamsiai, karciai, saldziai

"IAI",         "IAI",         "",          "",          "n",      "k",   
"CIAI",        "ÈIAI",   "T",         "T",         "n",      "k",   
"DZIAI",       "DÞIAI",  "D",         "D",         "n",      "k",   


// --------------------------------- budvardis, 3oji linksniuote, vyr. gimine
// medinis; abipusis, didelis (vienask.)

"IS",          "IS",          "",          "",          "O",      "mv",   

"IO",          "IO",          "",          "",          "o",      "mk",   

"IAM",         "IAM",         "",          "",          "o",      "mn",   

"I",           "Á",       "",          "",          "o",      "mg",   

"IU",          "IU",          "",          "",          "o",      "mi",   

"IAM",         "IAM",         "",          "",          "o",      "mw",   
"IAME",        "IAME",        "",          "",          "o",      "mw",   

"IS",          "IS",          "",          "",          "o",      "ms",   

"IAI",         "IAI",         "",          "",          "o",      "mV",   

"IU",          "IØ",      "",          "",          "o",      "mK",   

"IAM",         "IAM",         "",          "",          "o",      "mN",   
"IAMS",        "IAMS",        "",          "",          "o",      "mN",   

"IUS",         "IUS",         "",          "",          "o",      "mG",   

"IAIS",        "IAIS",        "",          "",          "o",      "mI",   

"IUOS",        "IUOS",        "",          "",          "o",      "mW",   
"IUOSE",       "IUOSE",       "",          "",          "o",      "mW",   


// --------------------------------- budvardis, 3-oji linksniuote, mot. gimine
// medine, abipuse, didele

"E",           "Ë",        "",          "",          "o",      "fv",   

"ES",          "ËS",       "",          "",          "o",      "fk",   

"EI",          "EI",          "",          "",          "o",      "fn",   

"E",           "Æ",       "",          "",          "o",      "fg",   

"E",           "E",           "",          "",          "o",      "fi",   

// "E",        "Ë",        "",          "",          "o",      "fw",   // tarm.
"EJ",          "ËJ",       "",          "",          "o",      "fw",   
"EJE",         "ËJE",      "",          "",          "o",      "fw",   

"E",           "E",           "",          "",          "o",      "fs",   

"ES",          "ËS",       "",          "",          "o",      "fV",   

"IU",          "IØ",      "",          "",          "o",      "fK",   

"EM",          "ËM",       "",          "",          "o",      "fN",   
"EMS",         "ËMS",      "",          "",          "o",      "fN",   

"ES",          "ES",          "",          "",          "o",      "fG",   

"EM",          "ËM",       "",          "",          "o",      "fI",   
"EMIS",        "ËMIS",     "",          "",          "o",      "fI",   

"ESE",         "ËSE",      "",          "",          "o",      "fW",   


// -------------------- budvardinis prieveiksmis, padarytas is 3-osios linksniuotes budvardzio
// geleziniai ???

"IAI",         "IAI",         "",          "",          "o",      "k",   


// ------- budvardis, 1-oji ir 2-oji linksniuotes, aukstesnysis laipsnis, vyr. gimine
// baltesnis, kurtesnis, skurdesnis

"ESNIS",       "ESNIS",       "",          "",          "lmn",    "1mv",   

"ESNIO",       "ESNIO",       "",          "",          "lmn",    "1mk",   

"ESNIAM",      "ESNIAM",      "",          "",          "lmn",    "1mn",   

"ESNI",        "ESNÁ",    "",          "",          "lmn",    "1mg",   

"ESNIU",       "ESNIU",       "",          "",          "lmn",    "1mi",   

"ESNIAM",      "ESNIAM",      "",          "",          "lmn",    "1mw",   
"ESNIAME",     "ESNIAME",     "",          "",          "lmn",    "1mw",   

"ESNIS",       "ESNIS",       "",          "",          "lmn",    "1ms",   

"ESNI",        "ESNI",        "",          "",          "lmn",    "1mV",   

"ESNIU",       "ESNIØ",   "",          "",          "lmn",    "1mK",   

"ESNIEM",      "ESNIEM",      "",          "",          "lmn",    "1mN",   
"ESNIEMS",     "ESNIEMS",     "",          "",          "lmn",    "1mN",   

"ESNIUS",      "ESNIUS",      "",          "",          "lmn",    "1mG",   

"ESNIAIS",     "ESNIAIS",     "",          "",          "lmn",    "1mI",   

"ESNIUOS",     "ESNIUOS",     "",          "",          "lmn",    "1mW",   
"ESNIUOSE",    "ESNIUOSE",    "",          "",          "lmn",    "1mW",   


// ------ budvardis, 1-oji ir 2-oji linksniuotes, aukstesnysis laipsnis, mot. gimine
// baltesne, kurtesne, skurdesne

"ESNE",        "ESNË",     "",          "",          "lmn",    "1fv",   

"ESNES",       "ESNËS",    "",          "",          "lmn",    "1fk",   

"ESNEI",       "ESNEI",       "",          "",          "lmn",    "1fn",   

"ESNE",        "ESNÆ",    "",          "",          "lmn",    "1fg",   

"ESNE",        "ESNE",        "",          "",          "lmn",    "1fi",   

// "ESNE",     "ESNË",     "",          "",          "lmn",    "1fw",   // tarm.
"ESNEJ",       "ESNËJ",    "",          "",          "lmn",    "1fw",   
"ESNEJE",      "ESNËJE",   "",          "",          "lmn",    "1fw",   

"ESNE",        "ESNE",        "",          "",          "lmn",    "1fs",   

"ESNES",       "ESNËS",    "",          "",          "lmn",    "1fV",   

"ESNIU",       "ESNIØ",   "",          "",          "lmn",    "1fK",   

"ESNEM",       "ESNËM",    "",          "",          "lmn",    "1fN",   
"ESNEMS",      "ESNËMS",   "",          "",          "lmn",    "1fN",   

"ESNES",       "ESNES",       "",          "",          "lmn",    "1fG",   

"ESNEM",       "ESNËM",    "",          "",          "lmn",    "1fI",   
"ESNEMIS",     "ESNËMIS",  "",          "",          "lmn",    "1fI",   

"ESNESE",      "ESNËSE",   "",          "",          "lmn",    "1fW",   


// ------ budvardis, 1-oji ir 2-oji linksniuotes, aukstesnysis laipsnis, niek. gimine
// ramiau, balciau, kurciau, skurdziau

"IAU",         "IAU",         "",          "",          "lmn",    "1o",   
"CIAU",        "ÈIAU",   "T",         "T",         "lmn",    "1o",   
"DZIAU",       "DÞIAU",  "D",         "D",         "lmn",    "1o",   


// ------ budvardinis prieveiksmis, padarytas is 1-osios ir 2-osios linksniuotes budvardzio, aukstesnysis laipsnis
// ramiau, balciau, kurciau, skurdziau

"IAU",         "IAU",         "",          "",          "lmn",    "1k",   
"CIAU",        "ÈIAU",   "T",         "T",         "lmn",    "1k",   
"DZIAU",       "DÞIAU",  "D",         "D",         "lmn",    "1k",   


// ---- budvardis, 1-oji ir 2-oji linksniuotes, auksciausiasis laipsnis vyr. gimine
// maziausias, balciausias, skurdziausias

"IAUSIAS",     "IAUSIAS",     "",          "",          "lmn",    "2mv",   
"CIAUSIAS",      "ÈIAUSIAS", "T",         "T",         "lmn",    "2mv",   
"DZIAUSIAS",      "DÞIAUSIAS", "D",         "D",         "lmn",    "2mv",   


"IAUSIO",      "IAUSIO",      "",          "",          "lmn",    "2mk",   
"CIAUSIO",      "ÈIAUSIO", "T",         "T",         "lmn",    "2mk",   
"DZIAUSIO",      "DÞIAUSIO", "D",         "D",         "lmn",    "2mk",   

"IAUSIAM",     "IAUSIAM",     "",          "",          "lmn",    "2mn",   
"CIAUSIAM",      "ÈIAUSIAM", "T",         "T",         "lmn",    "2mn",   
"DZIAUSIAM",      "DÞIAUSIAM", "D",         "D",         "lmn",    "2mn",   

"IAUSIA",      "IAUSIÀ",  "",          "",          "lmn",    "2mg",   
"CIAUSIA",      "ÈIAUSIÀ", "T",         "T",         "lmn",    "2mg",   
"DZIAUSIA",      "DÞIAUSIÀ", "D",         "D",         "lmn",    "2mg",   

"IAUSIU",      "IAUSIU",      "",          "",          "lmn",    "2mi",   
"CIAUSIU",      "ÈIAUSIU", "T",         "T",         "lmn",    "2mi",   
"DZIAUSIU",      "DÞIAUSIU", "D",         "D",         "lmn",    "2mi",   

"IAUSIAM",     "IAUSIAM",     "",          "",          "lmn",    "2mw",   
"IAUSIAME",    "IAUSIAME",    "",          "",          "lmn",    "2mw",   
"CIAUSIAM",      "ÈIAUSIAM", "T",         "T",         "lmn",    "2mw",   
"CIAUSIAME",      "ÈIAUSIAME", "T",         "T",         "lmn",    "2mw",   
"DZIAUSIAM",      "DÞIAUSIAM", "D",         "D",         "lmn",    "2mw",   
"DZIAUSIAME",      "DÞIAUSIAME", "D",         "D",         "lmn",    "2mw",   

"IAUSIAS",     "IAUSIAS",     "",          "",          "lmn",    "2ms",   
"CIAUSIAS",      "ÈIAUSIAS", "T",         "T",         "lmn",    "2ms",   
"DZIAUSIAS",      "DÞIAUSIAS", "D",         "D",         "lmn",    "2ms",   

"IAUSI",       "IAUSI",       "",          "",          "lmn",    "2mV",   
"CIAUSI",      "ÈIAUSI", "T",         "T",         "lmn",    "2mV",   
"DZIAUSI",      "DÞIAUSI", "D",         "D",         "lmn",    "2mV",   

"IAUSIU",      "IAUSIØ",  "",          "",          "lmn",    "2mK",   
"CIAUSIU",      "ÈIAUSIØ", "T",         "T",         "lmn",    "2mK",   
"DZIAUSIU",      "DÞIAUSIØ", "D",         "D",         "lmn",    "2mK",   

"IAUSIEM",     "IAUSIEM",     "",          "",          "lmn",    "2mN",   
"IAUSIEMS",    "IAUSIEMS",    "",          "",          "lmn",    "2mN",   
"CIAUSIEM",      "ÈIAUSIEM", "T",         "T",         "lmn",    "2mN",   
"CIAUSIEMS",      "ÈIAUSIEMS", "T",         "T",         "lmn",    "2mN",   
"DZIAUSIEM",      "DÞIAUSIEM", "D",         "D",         "lmn",    "2mN",   
"DZIAUSIEMS",      "DÞIAUSIEMS", "D",         "D",         "lmn",    "2mN",   

"IAUSIUS",     "IAUSIUS",     "",          "",          "lmn",    "2mG",   
"CIAUSIUS",      "ÈIAUSIUS", "T",         "T",         "lmn",    "2mG",   
"DZIAUSIUS",      "DÞIAUSIUS", "D",         "D",         "lmn",    "2mG",   

"IAUSIAIS",    "IAUSIAIS",    "",          "",          "lmn",    "2mI",   
"CIAUSIAIS",      "ÈIAUSIAIS", "T",         "T",         "lmn",    "2mI",   
"DZIAUSIAIS",      "DÞIAUSIAIS", "D",         "D",         "lmn",    "2mI",   

"IAUSIUOS",    "IAUSIUOS",    "",          "",          "lmn",    "2mW",   
"IAUSIUOSE",   "IAUSIUOSE",   "",          "",          "lmn",    "2mW",   
"CIAUSIUOS",      "ÈIAUSIUOS", "T",         "T",         "lmn",    "2mW",   
"CIAUSIUOSE",      "ÈIAUSIUOSE", "T",         "T",         "lmn",    "2mW",   
"DZIAUSIUOS",      "DÞIAUSIUOS", "D",         "D",         "lmn",    "2mW",   
"DZIAUSIUOSE",      "DÞIAUSIUOSE", "D",         "D",         "lmn",    "2mW",   


// ------ budvardis, 1-oji ir 2-oji linksniuotes, auksciausiasis laipsnis mot. gimine
// maziausia, balciausia, skurdziausia

"IAUSIA",      "IAUSIA",      "",          "",          "lmn",    "2fv",   
"CIAUSIA",      "ÈIAUSIA", "T",         "T",         "lmn",    "2fv",   
"DZIAUSIA",      "DÞIAUSIA", "D",         "D",         "lmn",    "2fv",   

"IAUSIOS",     "IAUSIOS",     "",          "",          "lmn",    "2fk",   
"CIAUSIOS",      "ÈIAUSIOS", "T",         "T",         "lmn",    "2fk",   
"DZIAUSIOS",      "DÞIAUSIOS", "D",         "D",         "lmn",    "2fk",   

"IAUSIAI",     "IAUSIAI",     "",          "",          "lmn",    "2fn",   
"CIAUSIAI",      "ÈIAUSIAI", "T",         "T",         "lmn",    "2fn",   
"DZIAUSIAI",      "DÞIAUSIAI", "D",         "D",         "lmn",    "2fn",   

"IAUSIA",      "IAUSIÀ",  "",          "",          "lmn",    "2fg",   
"CIAUSIA",      "ÈIAUSIÀ", "T",         "T",         "lmn",    "2fg",   
"DZIAUSIA",      "DÞIAUSIÀ", "D",         "D",         "lmn",    "2fg",   

"IAUSIA",      "IAUSIA",      "",          "",          "lmn",    "2fi",   
"CIAUSIA",      "ÈIAUSIA", "T",         "T",         "lmn",    "2fi",   
"DZIAUSIA",      "DÞIAUSIA", "D",         "D",         "lmn",    "2fi",   

// "IAUSIO",   "IAUSIO",      "",          "",          "lmn",    "2fw",   // tarm.
"IAUSIOJ",     "IAUSIOJ",     "",          "",          "lmn",    "2fw",   
"IAUSIOJE",    "IAUSIOJE",    "",          "",          "lmn",    "2fw",   
// "CIAUSIO",      "ÈIAUSIO", "T",         "T",         "lmn",    "2fw",   // tarm.
"CIAUSIOJ",      "ÈIAUSIOJ", "T",         "T",         "lmn",    "2fw",   
"CIAUSIOJE",      "ÈIAUSIOJE", "T",         "T",         "lmn",    "2fw",   
// "DZIAUSIO",      "DÞIAUSIO", "D",         "D",         "lmn",    "2fw",   // tarm.
"DZIAUSIOJ",      "DÞIAUSIOJ", "D",         "D",         "lmn",    "2fw",   
"DZIAUSIOJE",      "DÞIAUSIOJE", "D",         "D",         "lmn",    "2fw",   

"IAUSIA",      "IAUSIA",      "",          "",          "lmn",    "2fs",   
"CIAUSIA",      "ÈIAUSIA", "T",         "T",         "lmn",    "2fs",   
"DZIAUSIA",      "DÞIAUSIA", "D",         "D",         "lmn",    "2fs",   

"IAUSIOS",     "IAUSIOS",     "",          "",          "lmn",    "2fV",   
"CIAUSIOS",      "ÈIAUSIOS", "T",         "T",         "lmn",    "2fV",   
"DZIAUSIOS",      "DÞIAUSIOS", "D",         "D",         "lmn",    "2fV",   

"IAUSIU",      "IAUSIØ",  "",          "",          "lmn",    "2fK",   
"CIAUSIU",      "ÈIAUSIØ", "T",         "T",         "lmn",    "2fK",   
"DZIAUSIU",      "DÞIAUSIØ", "D",         "D",         "lmn",    "2fK",   

"IAUSIOM",     "IAUSIOM",     "",          "",          "lmn",    "2fN",   
"IAUSIOMS",    "IAUSIOMS",    "",          "",          "lmn",    "2fN",   
"CIAUSIOM",      "ÈIAUSIOM", "T",         "T",         "lmn",    "2fN",   
"CIAUSIOMS",      "ÈIAUSIOMS", "T",         "T",         "lmn",    "2fN",   
"DZIAUSIOM",      "DÞIAUSIOM", "D",         "D",         "lmn",    "2fN",   
"DZIAUSIOMS",      "DÞIAUSIOMS", "D",         "D",         "lmn",    "2fN",   

"IAUSIAS",     "IAUSIAS",     "",          "",          "lmn",    "2fG",   
"CIAUSIAS",      "ÈIAUSIAS", "T",         "T",         "lmn",    "2fG",   
"DZIAUSIAS",      "DÞIAUSIAS", "D",         "D",         "lmn",    "2fG",   

"IAUSIOM",     "IAUSIOM",     "",          "",          "lmn",    "2fI",   
"IAUSIOMIS",   "IAUSIOMIS",   "",          "",          "lmn",    "2fI",   
"CIAUSIOM",      "ÈIAUSIOM", "T",         "T",         "lmn",    "2fI",   
"CIAUSIOMIS",      "ÈIAUSIOMIS", "T",         "T",         "lmn",    "2fI",   
"DZIAUSIOM",      "DÞIAUSIOM", "D",         "D",         "lmn",    "2fI",   
"DZIAUSIOMIS",      "DÞIAUSIOMIS", "D",         "D",         "lmn",    "2fI",   

"IAUSIOSE",    "IAUSIOSE",    "",          "",          "lmn",    "2fW",   
"CIAUSIOSE",      "ÈIAUSIOSE", "T",         "T",         "lmn",    "2fW",   
"DZIAUSIOSE",      "DÞIAUSIOSE", "D",         "D",         "lmn",    "2fW",   


// ------ budvardis, 1-oji ir 2-oji linksniuotes, auksciausiasis laipsnis niek. gimine
// ramiausia, balciausia, kurciausia, skurdziausia

"IAUSIA",      "IAUSIA",      "",          "",          "lmn",    "2o",   
"CIAUSIA",      "ÈIAUSIA", "T",         "T",         "lmn",    "2o",   
"DZIAUSIA",      "DÞIAUSIA", "D",         "D",         "lmn",    "2o",   



// ------ budvardinis prieveiksmis, padarytas is 1-osios ir 2-osios linksniuotes budvardzio, auksciausiasis laipsnis
// ramiausiai, balciausiai, kurciausiai, skurdziausiai

"IAUSIAI",     "IAUSIAI",     "",          "",          "lmn",    "2k",   
"CIAUSIAI",      "ÈIAUSIAI", "T",         "T",         "lmn",    "2k",   
"DZIAUSIAI",      "DÞIAUSIAI", "D",         "D",         "lmn",    "2k",   


// -------------------- ivardziuotinis budvardis, 1-oji linksniuote, vyr. gimine
// baltasis, zaliasis, kurciasis, kurtysis, ???dziasis, didysis

"ASIS",        "ASIS",        "",          "",          "l",      "emv",   
"IASIS",       "IASIS",       "",          "",          "m",      "emv",   // nekinta
"CIASIS",      "ÈIASIS", "T",         "T",         "m",      "emv",   
// "DZIASIS",      "DÞIASIS", "D",         "D",         "m",      "emv",   // nera
"YSIS",        "YSIS",        "",          "",          "m",      "emv",   

"OJO",         "OJO",         "",          "",          "l",      "emk",   
"IOJO",        "IOJO",        "",          "",          "m",      "emk",   // nekinta
"CIOJO",       "ÈIOJO",  "T",         "T",         "m",      "emk",   
"DZIOJO",      "DÞIOJO", "D",         "D",         "m",      "emk",   

"AJAM",        "AJAM",        "",          "",          "l",      "emn",   
"IAJAM",       "IAJAM",       "",          "",          "m",      "emn",   // nekinta
"CIAJAM",      "ÈIAJAM", "T",         "T",         "m",      "emn",   
"DZIAJAM",      "DÞIAJAM", "D",         "D",         "m",      "emn",   

"AJI",         "ÀJÁ", "",          "",          "l",      "emg",   
"IAJI",        "IÀJÁ", "",          "",          "m",      "emg",   // nekinta
"CIAJI",       "ÈIÀJÁ", "T",         "T",         "m",      "emg",   
// "DZIAJI",      "DÞIÀJÁ", "D",         "D",         "m",      "emg",   // nera
"IJI",         "ÁJÁ", "",          "",          "m",      "emg",   

"UOJU",        "UOJU",        "",          "",          "l",      "emi",   
"IUOJU",       "IUOJU",       "",          "",          "m",      "emi",   // nekinta
"CIUOJU",      "ÈIUOJU", "T",         "T",         "m",      "emi",   
"DZIUOJU",      "DÞIUOJU", "D",         "D",         "m",      "emi",   

"AJAM",        "AJAM",        "",          "",          "l",      "emw",   
"AJAME",       "AJAME",       "",          "",          "l",      "emw",   
"IAJAM",       "IAJAM",       "",          "",          "m",      "emw",   // nekinta
"IAJAME",      "IAJAME",      "",          "",          "m",      "emw",   // nekinta
"CIAJAM",      "ÈIAJAM", "T",         "T",         "m",      "emw",   
"CIAJAME",      "ÈIAJAME", "T",         "T",         "m",      "emw",   
"DZIAJAM",      "DÞIAJAM", "D",         "D",         "m",      "emw",   
"DZIAJAME",      "DÞIAJAME", "D",         "D",         "m",      "emw",   

"ASIS",        "ASIS",        "",          "",          "l",      "ems",   
"IASIS",       "IASIS",       "",          "",          "m",      "ems",   // nekinta
"CIASIS",      "ÈIASIS", "T",         "T",         "m",      "ems",   
// "DZIASIS",      "DÞIASIS", "D",         "D",         "m",      "ems",   // nera
"YSIS",        "YSIS",        "",          "",          "m",      "ems",   

"IEJI",        "IEJI",        "",          "",          "lm",     "emV",   
// "CIEJI",      "ÈIEJI",  "T",         "T",         "m",      "emV",   // nera
// "DZIEJI",      "DÞIEJI", "D",         "D",         "m",      "emV",   // nera
"DIEJI",       "DIEJI",       "D",         "D",         "m",      "emV",   // nera

"UJU",         "ØJØ", "",          "",          "l",      "emK",   
"IUJU",        "IØJØ", "",          "",          "m",      "emK",   // nekinta
"CIUJU",       "ÈIØJØ", "T",         "T",         "m",      "emK",   
"DZIUJU",      "DÞIØJØ", "D",         "D",         "m",      "emK",   

"IESIEM",      "IESIEM",      "",          "",          "lm",     "emN",   
"IESIEMS",     "IESIEMS",     "",          "",          "lm",     "emN",   

"UOSIUS",      "UOSIUS",      "",          "",          "l",      "emG",   
"IUOSIUS",     "IUOSIUS",     "",          "",          "m",      "emG",   // nekinta
"CIUOSIUS",      "ÈIUOSIUS", "T",         "T",         "m",      "emG",   
"DZIUOSIUS",      "DÞIUOSIUS", "D",         "D",         "m",      "emG",   

"AISIAIS",     "AISIAIS",     "",          "",          "l",      "emI",   
"IAISIAIS",    "IAISIAIS",    "",          "",          "m",      "emI",   // nekinta
"CIAISIAIS",      "ÈIAISIAIS", "T",         "T",         "m",      "emI",   
"DZIAISIAIS",      "DÞIAISIAIS", "D",         "D",         "m",      "emI",   

"UOSIUOS",     "UOSIUOS",     "",          "",          "l",      "emW",   
"UOSIUOSE",    "UOSIUOSE",    "",          "",          "l",      "emW",   
"IUOSIUOS",    "IUOSIUOS",    "",          "",          "m",      "emW",   // nekinta
"IUOSIUOSE",   "IUOSIUOSE",   "",          "",          "m",      "emW",   // nekinta
"CIUOSIUOS",      "ÈIUOSIUOS", "T",         "T",         "m",      "emW",   
"CIUOSIUOSE",      "ÈIUOSIUOSE", "T",         "T",         "m",      "emW",   
"DZIUOSIUOS",      "DÞIUOSIUOS", "D",         "D",         "m",      "emW",   
"DZIUOSIUOSE",      "DÞIUOSIUOSE", "D",         "D",         "m",      "emW",   


// ------------------- ivardziuotinis budvardis, 2-oji linksniuote, vyr. gimine
// tamsusis, ???iusis, kartusis, kandusis

"USIS",        "USIS",        "",          "",          "n",      "emv",   
// "IUSIS",    "IUSIS",       "",          "",          "",       "emv",   // nera

// "OJO",      "OJO",         "",          "",          "n",      "emk",   // nera
"IOJO",        "IOJO",        "",          "",          "n",      "emk",   
"CIOJO",       "ÈIOJO",  "T",         "T",         "n",      "emk",   
"DZIOJO",      "DÞIOJO", "D",         "D",         "n",      "emk",   

// "AJAM",     "AJAM",        "",          "",          "n",      "emn",   // nera
"IAJAM",       "IAJAM",       "",          "",          "n",      "emn",   
"CIAJAM",      "ÈIAJAM", "T",         "T",         "n",      "emn",   
"DZIAJAM",      "DÞIAJAM", "D",         "D",         "n",      "emn",   

"UJI",         "ØJÁ", "",          "",          "n",      "emg",   
// "IUJI",     "IØJÁ", "",          "",          "",       "emg",   // nera

// "UOUJU",    "UOUJU",       "",          "",          "n",      "emi",   // nera
"IUOUJU",      "IUOUJU",      "",          "",          "n",      "emi",   
"CIUOUJU",      "ÈIUOUJU", "T",         "T",         "n",      "emi",   
"DZIUOUJU",      "DÞIUOUJU", "D",         "D",         "n",      "emi",   

// "AJAM",     "AJAM",        "",          "",          "n",      "emw",   // nera
// "AJAME",    "AJAME",       "",          "",          "n",      "emw",   // nera
"IAJAM",       "IAJAM",       "",          "",          "n",      "emw",   
"IAJAME",      "IAJAME",      "",          "",          "n",      "emw",   
"CIAJAM",      "ÈIAJAM", "T",         "T",         "n",      "emw",   
"CIAJAME",      "ÈIAJAME", "T",         "T",         "n",      "emw",   
"DZIAJAM",      "DÞIAJAM", "D",         "D",         "n",      "emw",   
"DZIAJAME",      "DÞIAJAME", "D",         "D",         "n",      "emw",   

"USIS",        "USIS",        "",          "",          "n",      "ems",   
// "IUSIS",    "IUSIS",       "",          "",          "",       "ems",   // nera

"IEJI",        "IEJI",        "",          "",          "n",      "emV",   

// "UJU",      "ØJØ", "",          "",          "n",      "emK",   // nera
"IUJU",        "IØJØ", "",          "",          "n",      "emK",   
"CIUJU",       "ÈIØJØ", "T",         "T",         "n",      "emK",   
"DZIUJU",      "DÞIØJØ", "D",         "D",         "n",      "emK",   

"IESIEM",      "IESIEM",      "",          "",          "n",      "emN",   
"IESIEMS",     "IESIEMS",     "",          "",          "n",      "emN",   

// "UOSIUS",   "UOSIUS",      "",          "",          "n",      "emG",   // nera
"IUOSIUS",     "IUOSIUS",     "",          "",          "n",      "emG",   
"CIUOSIUS",      "ÈIUOSIUS", "T",         "T",         "n",      "emG",   
"DZIUOSIUS",      "DÞIUOSIUS", "D",         "D",         "n",      "emG",   

// "AISIAIS",  "AISIAIS",     "",          "",          "n",      "emI",   // nera
"IAISIAIS",    "IAISIAIS",    "",          "",          "n",      "emI",   
"CIAISIAIS",      "ÈIAISIAIS", "T",         "T",         "n",      "emI",   
"DZIAISIAIS",      "DÞIAISIAIS", "D",         "D",         "n",      "emI",   

// "UOSIUOS",  "UOSIUOS",     "",          "",          "n",      "emW",   // nera
// "UOSIUOSE", "UOSIUOSE",    "",          "",          "n",      "emW",   // nera
"IUOSIUOS",    "IUOSIUOS",    "",          "",          "n",      "emW",   
"IUOSIUOSE",   "IUOSIUOSE",   "",          "",          "n",      "emW",   
"CIUOSIUOS",      "ÈIUOSIUOS", "T",         "T",         "n",      "emW",   
"CIUOSIUOSE",      "ÈIUOSIUOSE", "T",         "T",         "n",      "emW",   
"DZIUOSIUOS",      "DÞIUOSIUOS", "D",         "D",         "n",      "emW",   
"DZIUOSIUOSE",      "DÞIUOSIUOSE", "D",         "D",         "n",      "emW",   


// -------------- ivardziuotinis budvardis, 1-oji ir 2-oji linksniuotes, mot. gimine
// minkstoji, slapioji, kurcioji,
// tamsioji, karcioji, kandzioji, didzioji

"OJI",         "OJI",         "",          "",          "l",      "efv",   
"IOJI",        "IOJI",        "",          "",          "mn",     "efv",   // nekinta
"CIOJI",       "ÈIOJI",  "T",         "T",         "mn",     "efv",   // nekinta
"DZIOJI",      "DÞIOJI", "D",         "D",         "mn",     "efv",   // nekinta

"OSIOS",       "OSIOS",       "",          "",          "l",      "efk",   
"IOSIOS",      "IOSIOS",      "",          "",          "mn",     "efk",   // nekinta
"CIOSIOS",      "ÈIOSIOS", "T",         "T",         "mn",     "efk",   // nekinta
"DZIOSIOS",      "DÞIOSIOS", "D",         "D",         "mn",     "efk",   // nekinta

"AJAI",        "AJAI",        "",          "",          "l",      "efn",   
"IAJAI",       "IAJAI",       "",          "",          "mn",     "efn",   // nekinta
"CIAJAI",      "ÈIAJAI", "T",         "T",         "mn",     "efn",   // nekinta
"DZIAJAI",      "DÞIAJAI", "D",         "D",         "mn",     "efn",   // nekinta

"AJA",         "ÀJÀ", "",          "",          "l",      "efg",   
"IAJA",        "IÀJÀ", "",          "",          "mn",     "efg",   // nekinta
"CIAJA",       "ÈIÀJÀ", "T",         "T",         "mn",     "efg",   // nekinta
"DZIAJA",      "DÞIÀJÀ", "D",         "D",         "mn",     "efg",   // nekinta

"AJA",         "ÀJA",     "",          "",          "l",      "efi",   
"IAJA",        "IÀJA",    "",          "",          "mn",     "efi",   // nekinta
"CIAJA",       "ÈIÀJA", "T",         "T",         "mn",     "efi",   // nekinta
"DZIAJA",      "DÞIÀJA", "D",         "D",         "mn",     "efi",   // nekinta

// "OJO",      "OJO",         "",          "",          "l",      "efw",   // tarm.
"OJOJ",        "OJOJ",        "",          "",          "l",      "efw",   
"OJOJE",       "OJOJE",       "",          "",          "mn",     "efw",   
// "IOJO",     "IOJO",        "",          "",          "mn",     "efw",   // nekinta, tarm.
"IOJOJ",       "IOJOJ",       "",          "",          "mn",     "efw",   // nekinta
"IOJOJE",      "IOJOJE",      "",          "",          "mn",     "efw",   // nekinta
// "CIOJO",      "ÈIOJO",  "T",         "T",         "mn",     "efw",   // nekinta, tarm.
"CIOJOJ",      "ÈIOJOJ", "T",         "T",         "mn",     "efw",   // nekinta
"CIOJOJE",      "ÈIOJOJE", "T",         "T",         "mn",     "efw",   // nekinta
// "DZIOJO",      "DÞIOJO", "D",         "D",         "mn",     "efw",   // nekinta, tarm.
"DZIOJOJ",      "DÞIOJOJ", "D",         "D",         "mn",     "efw",   // nekinta
"DZIOJOJE",      "DÞIOJOJE", "D",         "D",         "mn",     "efw",   // nekinta

"OJI",         "OJI",         "",          "",          "l",      "efs",   
"IOJI",        "IOJI",        "",          "",          "mn",     "efs",   // nekinta
"CIOJI",       "ÈIOJI",  "T",         "T",         "mn",     "efs",   // nekinta
"DZIOJI",      "DÞIOJI", "D",         "D",         "mn",     "efs",   // nekinta

"OSIOS",       "OSIOS",       "",          "",          "l",      "efV",   
"IOSIOS",      "IOSIOS",      "",          "",          "mn",     "efV",   // nekinta
"CIOSIOS",      "ÈIOSIOS", "T",         "T",         "mn",     "efV",   // nekinta
"DZIOSIOS",      "DÞIOSIOS", "D",         "D",         "mn",     "efV",   // nekinta

"UJU",         "ØJØ", "",          "",          "l",      "efK",   
"IUJU",        "IØJØ", "",          "",          "mn",     "efK",   // nekinta
"CIUJU",       "ÈIØJØ", "T",         "T",         "mn",     "efK",   // nekinta
"DZIUJU",      "DÞIØJØ", "D",         "D",         "mn",     "efK",   // nekinta

"OSIOM",       "OSIOM",       "",          "",          "l",      "efN",   
"OSIOMS",      "OSIOMS",      "",          "",          "l",      "efN",   
"IOSIOM",      "IOSIOM",      "",          "",          "mn",     "efN",   // nekinta
"IOSIOMS",     "IOSIOMS",     "",          "",          "mn",     "efN",   // nekinta
"CIOSIOM",      "ÈIOSIOM", "T",         "T",         "mn",     "efN",   // nekinta
"CIOSIOMS",      "ÈIOSIOMS", "T",         "T",         "mn",     "efN",   // nekinta
"DZIOSIOM",      "DÞIOSIOM", "D",         "D",         "mn",     "efN",   // nekinta
"DZIOSIOMS",      "DÞIOSIOMS", "D",         "D",         "mn",     "efN",   // nekinta

"ASIAS",       "ÀSIAS",   "",          "",          "l",      "efG",   
"IASIAS",      "IÀSIAS",  "",          "",          "mn",     "efG",   // nekinta
"CIASIAS",      "ÈIÀSIAS", "T",         "T",         "mn",     "efG",   // nekinta
"DZIASIAS",      "DÞIÀSIAS", "D",         "D",         "mn",     "efG",   // nekinta

"OSIOM",       "OSIOM",       "",          "",          "l",      "efI",   
"OSIOMIS",     "OSIOMIS",     "",          "",          "l",      "efI",   
"IOSIOM",      "IOSIOM",      "",          "",          "mn",     "efI",   // nekinta
"IOSIOMIS",    "IOSIOMIS",    "",          "",          "mn",     "efI",   // nekinta
"CIOSIOM",      "ÈIOSIOM", "T",         "T",         "mn",     "efI",   // nekinta
"CIOSIOMIS",      "ÈIOSIOMIS", "T",         "T",         "mn",     "efI",   // nekinta
"DZIOSIOM",      "DÞIOSIOM", "D",         "D",         "mn",     "efI",   // nekinta
"DZIOSIOMIS",      "DÞIOSIOMIS", "D",         "D",         "mn",     "efI",   // nekinta

"OSIOSE",      "OSIOSE",      "",          "",          "l",      "efW",   
"IOSIOSE",     "IOSIOSE",     "",          "",          "mn",     "efW",   // nekinta
"CIOSIOSE",      "ÈIOSIOSE", "T",         "T",         "mn",     "efW",   // nekinta
"DZIOSIOSE",      "DÞIOSIOSE", "D",         "D",         "mn",     "efW",   // nekinta


// -- ivardziuotinis budvardis, 1-oji ir 2-oji linksniuotes, aukstesnysis laipsnis, vyr. gimine
// baltesnysis
// tamsesnysis, kartesnysis,

"ESNYSIS",     "ESNYSIS",     "",          "",          "lmn",    "1emv",   

"ESNIOJO",     "ESNIOJO",     "",          "",          "lmn",    "1emk",   

"ESNIAJAM",    "ESNIAJAM",    "",          "",          "lmn",    "1emn",   

"ESNIJI",      "ESNÁJÁ", "",          "",          "lmn",    "1emg",   

"ESNIUOJU",    "ESNIUOJU",    "",          "",          "lmn",    "1emi",   

"ESNIAJAM",    "ESNIAJAM",    "",          "",          "lmn",    "1emw",   
"ESNIAJAME",   "ESNIAJAME",   "",          "",          "lmn",    "1emw",   

"ESNYSIS",     "ESNYSIS",     "",          "",          "lmn",    "1ems",   

"ESNIEJI",     "ESNIEJI",     "",          "",          "lmn",    "1emV",   

"ESNIUJU",     "ESNIØJØ", "",          "",          "lmn",    "1emK",   

"ESNIESIEM",   "ESNIESIEM",   "",          "",          "lmn",    "1emN",   
"ESNIESIEMS",  "ESNIESIEMS",  "",          "",          "lmn",    "1emN",   

"ESNIUOSIUS",  "ESNIUOSIUS",  "",          "",          "lmn",    "1emG",   

"ESNIAISIAIS", "ESNIAISIAIS", "",          "",          "lmn",    "1emI",   

"ESNIUOSIUOS", "ESNIUOSIUOS", "",          "",          "lmn",    "1emW",   
"ESNIUOSIUOSE", "ESNIUOSIUOSE", "",          "",          "lmn",    "1emW",   


// -- ivardziuotinis budvardis, 1-oji ir 2-oji linksniuotes, aukstesnysis laipsnis, mot. gimine
// baltesnioji
// tamsesnioji, kartesnioji,

"ESNIOJI",     "ESNIOJI",     "",          "",          "lmn",    "1efv",   

"ESNIOSIOS",   "ESNIOSIOS",   "",          "",          "lmn",    "1efk",   

"ESNIAJAI",    "ESNIAJAI",    "",          "",          "lmn",    "1efn",   

"ESNIAJA",     "ESNIÀJÀ", "",          "",          "lmn",    "1efg",   

"ESNIAJA",     "ESNIÀJA", "",          "",          "lmn",    "1efi",   

// "ESNIOJO",  "ESNIOJO",     "",          "",          "lmn",    "1efw",   // tarm.
"ESNIOJOJ",    "ESNIOJOJ",    "",          "",          "lmn",    "1efw",   
"ESNIOJOJE",   "ESNIOJOJE",   "",          "",          "lmn",    "1efw",   

"ESNIOJI",     "ESNIOJI",     "",          "",          "lmn",    "1efs",   

"ESNIOSIOS",   "ESNIOSIOS",   "",          "",          "lmn",    "1efV",   

"ESNIUJU",     "ESNIØJØ", "",          "",          "lmn",    "1efK",   

"ESNIOSIOM",   "ESNIOSIOM",   "",          "",          "lmn",    "1efN",   
"ESNIOSIOMS",  "ESNIOSIOMS",  "",          "",          "lmn",    "1efN",   

"ESNIASIAS",   "ESNIÀSIAS", "",          "",          "lmn",    "1efG",   

"ESNIOSIOM",   "ESNIOSIOM",   "",          "",          "lmn",    "1efI",   
"ESNIOSIOMIS", "ESNIOSIOMIS", "",          "",          "lmn",    "1efI",   

"ESNIOSIOSE",  "ESNIOSIOSE",  "",          "",          "lmn",    "1efW",   


// ----- ivardziuotinis budvardis, 1-oji ir 2-oji linksniuotes, auksciausiasis laipsnis, vyr. gimine
// balciausiasis, auksciausiasis
// tamsiausiasis, karciausiasis, saldziausiasis

"IAUSIASIS",   "IAUSIASIS",   "",          "",          "lmn",    "2emv",   
"CIAUSIASIS",      "ÈIAUSIASIS", "T",         "T",         "lmn",    "2emv",   
"DZIAUSIASIS",      "DÞIAUSIASIS", "D",         "D",         "lmn",    "2emv",   

"IAUSIOJO",    "IAUSIOJO",    "",          "",          "lmn",    "2emk",   
"CIAUSIOJO",      "ÈIAUSIOJO", "T",         "T",         "lmn",    "2emk",   
"DZIAUSIOJO",      "DÞIAUSIOJO", "D",         "D",         "lmn",    "2emk",   

"IAUSIAJAM",   "IAUSIAJAM",   "",          "",          "lmn",    "2emn",   
"CIAUSIAJAM",      "ÈIAUSIAJAM", "T",         "T",         "lmn",    "2emn",   
"DZIAUSIAJAM",      "DÞIAUSIAJAM", "D",         "D",         "lmn",    "2emn",   

"IAUSIAJI",    "IAUSIÀJÁ", "",          "",          "lmn",    "2emg",   
"CIAUSIAJI",      "ÈIAUSIÀJÁ", "T",         "T",         "lmn",    "2emg",   
"DZIAUSIAJI",      "DÞIAUSIÀJÁ", "D",         "D",         "lmn",    "2emg",   

"IAUSIUOJU",   "IAUSIUOJU",   "",          "",          "lmn",    "2emi",   
"CIAUSIUOJU",      "ÈIAUSIUOJU", "T",         "T",         "lmn",    "2emi",   
"DZIAUSIUOJU",      "DÞIAUSIUOJU", "D",         "D",         "lmn",    "2emi",   

"IAUSIAJAM",   "IAUSIAJAM",   "",          "",          "lmn",    "2emw",   
"IAUSIAJAME",  "IAUSIAJAME",  "",          "",          "lmn",    "2emw",   
"CIAUSIAJAM",      "ÈIAUSIAJAM", "T",         "T",         "lmn",    "2emw",   
"CIAUSIAJAME",      "ÈIAUSIAJAME", "T",         "T",         "lmn",    "2emw",   
"DZIAUSIAJAM",      "DÞIAUSIAJAM", "D",         "D",         "lmn",    "2emw",   
"DZIAUSIAJAME",      "DÞIAUSIAJAME", "D",         "D",         "lmn",    "2emw",   

"IAUSIASIS",   "IAUSIASIS",   "",          "",          "lmn",    "2ems",   
"CIAUSIASIS",      "ÈIAUSIASIS", "T",         "T",         "lmn",    "2ems",   
"DZIAUSIASIS",      "DÞIAUSIASIS", "D",         "D",         "lmn",    "2ems",   

"IAUSIEJI",    "IAUSIEJI",    "",          "",          "lmn",    "2emV",   
"CIAUSIEJI",      "ÈIAUSIEJI", "T",         "T",         "lmn",    "2emV",   
"DZIAUSIEJI",      "DÞIAUSIEJI", "D",         "D",         "lmn",    "2emV",   

"IAUSIUJU",    "IAUSIØJØ", "",          "",          "lmn",    "2emK",   
"CIAUSIUJU",      "ÈIAUSIØJØ", "T",         "T",         "lmn",    "2emK",   
"DZIAUSIUJU",      "DÞIAUSIØJØ", "D",         "D",         "lmn",    "2emK",   

"IAUSIESIEM",  "IAUSIESIEM",  "",          "",          "lmn",    "2emN",   
"IAUSIESIEMS", "IAUSIESIEMS", "",          "",          "lmn",    "2emN",   
"CIAUSIESIEM",      "ÈIAUSIESIEM", "T",         "T",         "lmn",    "2emN",   
"CIAUSIESIEMS",      "ÈIAUSIESIEMS", "T",         "T",         "lmn",    "2emN",   
"DZIAUSIESIEM",      "DÞIAUSIESIEM", "D",         "D",         "lmn",    "2emN",   
"DZIAUSIESIEMS",      "DÞIAUSIESIEMS", "D",         "D",         "lmn",    "2emN",   

"IAUSIUOSIUS", "IAUSIUOSIUS", "",          "",          "lmn",    "2emG",   
"CIAUSIUOSIUS",      "ÈIAUSIUOSIUS", "T",         "T",         "lmn",    "2emG",   
"DZIAUSIUOSIUS",      "DÞIAUSIUOSIUS", "D",         "D",         "lmn",    "2emG",   

"IAUSIASIAIS", "IAUSIASIAIS", "",          "",          "lmn",    "2emI",   
"CIAUSIASIAIS",      "ÈIAUSIASIAIS", "T",         "T",         "lmn",    "2emI",   
"DZIAUSIASIAIS",      "DÞIAUSIASIAIS", "D",         "D",         "lmn",    "2emI",   

"IAUSIUOSIUOS", "IAUSIUOSIUOS", "",          "",          "lmn",    "2emW",   
"IAUSIUOSIUOSE", "IAUSIUOSIUOSE", "",          "",          "lmn",    "2emW",   
"CIAUSIUOSIUOS",      "ÈIAUSIUOSIUOS", "T",         "T",         "lmn",    "2emW",   
"CIAUSIUOSIUOSE",      "ÈIAUSIUOSIUOSE", "T",         "T",         "lmn",    "2emW",   
"DZIAUSIUOSIUOS",      "DÞIAUSIUOSIUOS", "D",         "D",         "lmn",    "2emW",   
"DZIAUSIUOSIUOSE",      "DÞIAUSIUOSIUOSE", "D",         "D",         "lmn",    "2emW",   


// ------- ivardziuotinis budvardis, 1-oji ir 2-oji linksniuotes, auksciausiasis laipsnis, mot. gimine
// balciausioji, auksciausioji
// tamsiausioji, karciausioji, saldziausioji

"IAUSIOJI",    "IAUSIOJI",    "",          "",          "lmn",    "2efv",   
"CIAUSIOJI",      "ÈIAUSIOJI", "T",         "T",         "lmn",    "2efv",   
"DZIAUSIOJI",      "DÞIAUSIOJI", "D",         "D",         "lmn",    "2efv",   

"IAUSIOSIOS",  "IAUSIOSIOS",  "",          "",          "lmn",    "2efk",   
"CIAUSIOSIOS",      "ÈIAUSIOSIOS", "T",         "T",         "lmn",    "2efk",   
"DZIAUSIOSIOS",      "DÞIAUSIOSIOS", "D",         "D",         "lmn",    "2efk",   

"IAUSIAJAI",   "IAUSIAJAI",   "",          "",          "lmn",    "2efn",   
"CIAUSIAJAI",      "ÈIAUSIAJAI", "T",         "T",         "lmn",    "2efn",   
"DZIAUSIAJAI",      "DÞIAUSIAJAI", "D",         "D",         "lmn",    "2efn",   

"IAUSIAJA",    "IAUSIÀJÀ", "",          "",          "lmn",    "2efg",   
"CIAUSIAJA",      "ÈIAUSIÀJÀ", "T",         "T",         "lmn",    "2efg",   
"DZIAUSIAJA",      "DÞIAUSIÀJÀ", "D",         "D",         "lmn",    "2efg",   

"IAUSIAJA",    "IAUSIÀJA", "",          "",          "lmn",    "2efi",   
"CIAUSIAJA",      "ÈIAUSIÀJA", "T",         "T",         "lmn",    "2efi",   
"DZIAUSIAJA",      "DÞIAUSIÀJA", "D",         "D",         "lmn",    "2efi",   

// "IAUSIOJO", "IAUSIOJO",    "",          "",          "lmn",    "2efw",   // tarm.
"IAUSIOJOJ",   "IAUSIOJOJ",   "",          "",          "lmn",    "2efw",   
"IAUSIOJOJE",  "IAUSIOJOJE",  "",          "",          "lmn",    "2efw",   
// "CIAUSIOJO",      "ÈIAUSIOJO", "T",         "T",         "lmn",    "2efw",   // tarm.
"CIAUSIOJOJ",      "ÈIAUSIOJOJ", "T",         "T",         "lmn",    "2efw",   
"CIAUSIOJOJE",      "ÈIAUSIOJOJE", "T",         "T",         "lmn",    "2efw",   
// "DZIAUSIOJO",      "DÞIAUSIOJO", "D",         "D",         "lmn",    "2efw",   // tarm.
"DZIAUSIOJOJ",      "DÞIAUSIOJOJ", "D",         "D",         "lmn",    "2efw",   
"DZIAUSIOJOJE",      "DÞIAUSIOJOJE", "D",         "D",         "lmn",    "2efw",   

"IAUSIOJI",    "IAUSIOJI",    "",          "",          "lmn",    "2efs",   
"CIAUSIOJI",      "ÈIAUSIOJI", "T",         "T",         "lmn",    "2efs",   
"DZIAUSIOJI",      "DÞIAUSIOJI", "D",         "D",         "lmn",    "2efs",   

"IAUSIOSIOS",  "IAUSIOSIOS",  "",          "",          "lmn",    "2efV",   
"CIAUSIOSIOS",      "ÈIAUSIOSIOS", "T",         "T",         "lmn",    "2efV",   
"DZIAUSIOSIOS",      "DÞIAUSIOSIOS", "D",         "D",         "lmn",    "2efV",   

"IAUSIUJU",    "IAUSIØJØ", "",          "",          "lmn",    "2efK",   
"CIAUSIUJU",      "ÈIAUSIØJØ", "T",         "T",         "lmn",    "2efK",   
"DZIAUSIUJU",      "DÞIAUSIØJØ", "D",         "D",         "lmn",    "2efK",   

"IAUSIOSIOM",  "IAUSIOSIOM",  "",          "",          "lmn",    "2efN",   
"IAUSIOSIOMS", "IAUSIOSIOMS", "",          "",          "lmn",    "2efN",   
"CIAUSIOSIOM",      "ÈIAUSIOSIOM", "T",         "T",         "lmn",    "2efN",   
"CIAUSIOSIOMS",      "ÈIAUSIOSIOMS", "T",         "T",         "lmn",    "2efN",   
"DZIAUSIOSIOM",      "DÞIAUSIOSIOM", "D",         "D",         "lmn",    "2efN",   
"DZIAUSIOSIOMS",      "DÞIAUSIOSIOMS", "D",         "D",         "lmn",    "2efN",   

"IAUSIASIAS",  "IAUSIÀSIAS", "",          "",          "lmn",    "2efG",   
"CIAUSIASIAS",      "ÈIAUSIÀSIAS", "T",         "T",         "lmn",    "2efG",   
"DZIAUSIASIAS",      "DÞIAUSIÀSIAS", "D",         "D",         "lmn",    "2efG",   

"IAUSIOSIOM",  "IAUSIOSIOM",  "",          "",          "lmn",    "2efI",   
"IAUSIOSIOMIS", "IAUSIOSIOMIS", "",          "",          "lmn",    "2efI",   
"CIAUSIOSIOM",      "ÈIAUSIOSIOM", "T",         "T",         "lmn",    "2efI",   
"CIAUSIOSIOMIS",      "ÈIAUSIOSIOMIS", "T",         "T",         "lmn",    "2efI",   
"DZIAUSIOSIOM",      "DÞIAUSIOSIOM", "D",         "D",         "lmn",    "2efI",   
"DZIAUSIOSIOMIS",      "DÞIAUSIOSIOMIS", "D",         "D",         "lmn",    "2efI",   

"IAUSIOSIOSE", "IAUSIOSIOSE", "",          "",          "lmn",    "2efW",   
"CIAUSIOSIOSE",      "ÈIAUSIOSIOSE", "T",         "T",         "lmn",    "2efW",   
"DZIAUSIOSIOSE",      "DÞIAUSIOSIOSE", "D",         "D",         "lmn",    "2efW",   


// ------------------------------------- kiekiniai skaitvardziai
// vienas

"AS",          "AS",          "",          "",          "1",      "mv",   
".VIENS",      ".VIENS",      ".VIEN",     ".VIEN",     "6",      "mv",   

"O",           "O",           "",          "",          "6",      "mk",   

"AM",          "AM",          "",          "",          "6",      "mn",   

"A",           "À",       "",          "",          "6",      "mg",   

"U",           "U",           "",          "",          "6",      "mi",   

"AM",          "AM",          "",          "",          "6",      "mw",   
"AME",         "AME",         "",          "",          "6",      "mw",   

"AS",          "AS",          "",          "",          "6",      "ms",   
".VIENS",      ".VIENS",      ".VIEN",     ".VIEN",     "6",      "ms",   


// ------------------------------------- kiekiniai skaitvardziai
// viena

"A",           "A",           "",          "",          "6",      "fv",   

"OS",          "OS",          "",          "",          "6",      "fk",   

"AI",          "AI",          "",          "",          "6",      "fn",   

"A",           "À",       "",          "",          "6",      "fg",   

"A",           "A",           "",          "",          "6",      "fi",   

// "O",        "O",           "",          "",          "6",      "fw",   // tarm.
"OJ",          "OJ",          "",          "",          "6",      "fw",   
"OJE",         "OJE",         "",          "",          "6",      "fw",   

"A",           "A",           "",          "",          "6",      "fs",   


// ------------------------------------- kiekiniai skaitvardziai, asm. ivardziai
// du, mudu, judu, jiedu, juodu

"",            "",            "",          "",          "2",      "mV",   

"DVIEJU",      "DVIEJØ",  "DU",        "DU",        "7",      "mK",   

"DVIEM",       "DVIEM",       "DU",        "DU",        "7",      "mN",   
"DVIEMS",      "DVIEMS",      "DU",        "DU",        "7",      "mN",   

"",            "",            "",          "",          "7",      "mG",   

"DVIEM",       "DVIEM",       "DU",        "DU",        "7",      "mI",   

"DVIEJUOS",    "DVIEJUOS",    "DU",        "DU",        "7",      "mW",   
"DVIEJUOSE",   "DVIEJUOSE",   "DU",        "DU",        "7",      "mW",   


// ------------------------------------- kiekiniai skaitvardziai, asm. ivardziai
// dvi, mudvi, judvi, juodvi

"DVI",         "DVI",         "DU",        "DU",        "7",      "fV",   

"DVIEJU",      "DVIEJØ",  "DU",        "DU",        "7",      "fK",   

"DVIEM",       "DVIEM",       "DU",        "DU",        "7",      "fN",   
"DVIEMS",      "DVIEMS",      "DU",        "DU",        "7",      "fN",   

"DVI",         "DVI",         "DU",        "DU",        "7",      "fG",   

"DVIEM",       "DVIEM",       "DU",        "DU",        "7",      "fI",   

"DVIEJOSE",    "DVIEJOSE",    "DU",        "DU",        "7",      "fW",   


// ------------------------------------- kiekiniai skaitvardziai
// trys

"TRYS",        "TRYS",        "TR",        "TR",        "3",      "mfV",   

"TRIJU",       "TRIJØ",   "TR",        "TR",        "8",      "mfK",   

"TRIM",        "TRIM",        "TR",        "TR",        "8",      "mfN",   
"TRIMS",       "TRIMS",       "TR",        "TR",        "8",      "mfN",   

"TRIS",        "TRIS",        "TR",        "TR",        "8",      "mfG",   

"TRIM",        "TRIM",        "TR",        "TR",        "8",      "mfI",   
"TRIMIS",      "TRIMIS",      "TR",        "TR",        "8",      "mfI",   

"TRIJUOS",     "TRIJUOS",     "TR",        "TR",        "8",      "mW",   
"TRIJUOSE",    "TRIJUOSE",    "TR",        "TR",        "8",      "mW",   
"TRIJOSE",     "TRIJOSE",     "TR",        "TR",        "8",      "fW",   


// ------------------------------------- kiekiniai skaitvardziai
// keturi, penki, ...

"I",           "I",           "",          "",          "4",      "mV",   

"IU",          "IØ",      "",          "",          "9",      "mK",   

"IEM",         "IEM",         "",          "",          "9",      "mN",   
"IEMS",        "IEMS",        "",          "",          "9",      "mN",   

"IS",          "IS",          "",          "",          "9",      "mG",   

"IAIS",        "IAIS",        "",          "",          "9",      "mI",   

"IUOS",        "IUOS",        "",          "",          "9",      "mW",   
"IUOSE",       "IUOSE",       "",          "",          "9",      "mW",   


// ------------------------------------- kiekiniai skaitvardziai
// keturios, penkios, ...

"IOS",         "IOS",         "",          "",          "9",      "fV",   // nekinta

"IU",          "IØ",      "",          "",          "9",      "fK",   // nekinta

"IOM",         "IOM",         "",          "",          "9",      "fN",   // nekinta
"IOMS",        "IOMS",        "",          "",          "9",      "fN",   // nekinta

"IAS",         "IAS",         "",          "",          "9",      "fG",   // nekinta

"IOM",         "IOM",         "",          "",          "9",      "fI",   // nekinta
"IOMIS",       "IOMIS",       "",          "",          "9",      "fI",   // nekinta

"IOSE",        "IOSE",        "",          "",          "9",      "fW",   // nekinta


// ------------------------------------- kiekiniai skaitvardziai
// vienuolika, ...

"A",           "A",           "",          "",          "0",      "v",   

"OS",          "OS",          "",          "",          "5",      "k",   

"AI",          "AI",          "",          "",          "5",      "n",   

"A",           "A",           "",          "",          "5",      "g",   

"A",           "A",           "",          "",          "5",      "i",   

// "O",        "O",           "",          "",          "5",      "w",   // tarm.
"OJ",          "OJ",          "",          "",          "5",      "w",   
"OJE",         "OJE",         "",          "",          "5",      "w",   

"A",           "A",           "",          "",          "5",      "s",   


// --------------------------------- kiekiniai skaitvardziai
// dvidesimt, trisdesimt ... (desimt nekaitomas, desimtis - daiktavardis, daugiskaitos nera)

"",            "",            "",          "",          "@",      "v",   

"IES",         "IES",         "",          "",          "`",      "k",   

"CIAI",        "ÈIAI",   "T",         "T",         "`",      "n",   

"I",           "Á",       "",          "",          "`",      "g",   

"IM",          "IM",          "",          "",          "`",      "i",   
"IMI",         "IMI",         "",          "",          "`",      "i",   
"CIA",         "ÈIA",    "T",         "T",         "`",      "i",   

"Y",           "Y",           "",          "",          "`",      "w",   
"YJ",          "YJ",          "",          "",          "`",      "w",   
"YJE",         "YJE",         "",          "",          "`",      "w",   

"IE",          "IE",          "",          "",          "`",      "s",   

"YS",          "YS",          "",          "",          "`",      "V",   

"CIU",         "ÈIØ", "T",         "T",         "`",      "K",   

"IM",          "IM",          "",          "",          "`",      "N",   
"IMS",         "IMS",         "",          "",          "`",      "N",   

"IS",          "IS",          "",          "",          "`",      "G",   

"IM",          "IM",          "",          "",          "`",      "I",   
"IMIS",        "IMIS",        "",          "",          "`",      "I",   

"YSE",         "YSE",         "",          "",          "`",      "W",   


// ------------------------------------- kiekiniai skaitvardziai
// simtas, milijonas, milijardas, ...

"AS",          "AS",          "",          "",          "[",      "v",   

"O",           "O",           "",          "",          "{",      "k",   

"UI",          "UI",          "",          "",          "{",      "n",   

"A",           "À",       "",          "",          "{",      "g",   

"U",           "U",           "",          "",          "{",      "i",   

"E",           "E",           "",          "",          "{",      "w",   

"E",           "E",           "",          "",          "{",      "s",   

"AI",          "AI",          "",          "",          "{",      "V",   

"U",           "Ø",       "",          "",          "{",      "K",   

"AM",          "AM",          "",          "",          "{",      "N",   
"AMS",         "AMS",         "",          "",          "{",      "N",   

"US",          "US",          "",          "",          "{",      "G",   

"AIS",         "AIS",         "",          "",          "{",      "I",   

"UOS",         "UOS",         "",          "",          "{",      "W",   
"UOSE",        "UOSE",        "",          "",          "{",      "W",   


// ------------------------------------- kiekiniai skaitvardziai
// tukstantis, nulis

"IS",          "IS",          "",          "",          "+",      "v",   

"IO",          "IO",          "",          "",          "-",      "k",   
"CIO",         "ÈIO",    "T",         "T",         "-",      "k",   

"IUI",         "IUI",         "",          "",          "-",      "n",   
"CIUI",        "ÈIUI",   "T",         "T",         "-",      "n",   

"I",           "Á",       "",          "",          "-",      "g",   

"IU",          "IU",          "",          "",          "-",      "i",   
"CIU",         "ÈIU",    "T",         "T",         "-",      "i",   

"Y",           "Y",           "",          "",          "-",      "w",   
"YJ",          "YJ",          "",          "",          "-",      "w",   
"YJE",         "YJE",         "",          "",          "-",      "w",   

"I",           "I",           "",          "",          "-",      "s",   

"IAI",         "IAI",         "",          "",          "-",      "V",   
"CIAI",        "ÈIAI",   "T",         "T",         "-",      "V",   

"IU",          "IØ",      "",          "",          "-",      "K",   
"CIU",         "ÈIØ", "T",         "T",         "-",      "K",   

"IAM",         "IAM",         "",          "",          "-",      "N",   
"IAMS",        "IAMS",        "",          "",          "-",      "N",   
"CIAM",        "ÈIAM",   "T",         "T",         "-",      "N",   
"CIAMS",       "ÈIAMS",  "T",         "T",         "-",      "N",   

"IUS",         "IUS",         "",          "",          "-",      "G",   
"CIUS",        "ÈIUS",   "T",         "T",         "-",      "G",   

"IAIS",        "IAIS",        "",          "",          "-",      "I",   
"CIAIS",       "ÈIAIS",  "T",         "T",         "-",      "I",   

"IUOS",        "IUOS",        "",          "",          "-",      "W",   
"IUOSE",       "IUOSE",       "",          "",          "-",      "W",   
"CIUOS",       "ÈIUOS",  "T",         "T",         "-",      "W",   
"CIUOSE",      "ÈIUOSE", "T",         "T",         "-",      "W",   


// ------------------------------------- dauginiai skaitvardziai
// vieni

"I",           "I",           "",          "",          "6",      "dmV",   

"U",           "Ø",       "",          "",          "6",      "dmK",   

"IEM",         "IEM",         "",          "",          "6",      "dmN",   
"IEMS",        "IEMS",        "",          "",          "6",      "dmN",   

"US",          "US",          "",          "",          "6",      "dmG",   

"AIS",         "AIS",         "",          "",          "6",      "dmI",   

"UOS",         "UOS",         "",          "",          "6",      "dmW",   
"UOSE",        "UOSE",        "",          "",          "6",      "dmW",   


// ------------------------------------- dauginiai skaitvardziai
// vienos

"OS",          "OS",          "",          "",          "6",      "dfV",   

"U",           "Ø",       "",          "",          "6",      "dfK",   

"OM",          "OM",          "",          "",          "6",      "dfN",   
"OMS",         "OMS",         "",          "",          "6",      "dfN",   

"AS",          "AS",          "",          "",          "6",      "dfG",   

"OM",          "OM",          "",          "",          "6",      "dfI",   
"OMIS",        "OMIS",        "",          "",          "6",      "dfI",   

"OSE",         "OSE",         "",          "",          "6",      "dfW",   


// ------------------------------------- dauginiai skaitvardziai
// vieneri, penkeri, ...

"ERI",         "ERI",         "",          "",          "69",     "dmV",   

"ERIU",        "ERIØ",    "",          "",          "69",     "dmK",   

"ERIEM",       "ERIEM",       "",          "",          "69",     "dmN",   
"ERIEMS",      "ERIEMS",      "",          "",          "69",     "dmN",   

"ERIS",        "ERIS",        "",          "",          "69",     "dmG",   
"ERIUS",       "ERIUS",       "",          "",          "69",     "dmG",   

"ERIAIS",      "ERIAIS",      "",          "",          "69",     "dmI",   

"ERIUOS",      "ERIUOS",      "",          "",          "69",     "dmW",   
"ERIUOSE",     "ERIUOSE",     "",          "",          "69",     "dmW",   


// ------------------------------------- dauginiai skaitvardziai
// vienerios, penkerios, ...

"ERIOS",       "ERIOS",       "",          "",          "69",     "dfV",   

"ERIU",        "ERIØ",    "",          "",          "69",     "dfK",   

"ERIOM",       "ERIOM",       "",          "",          "69",     "dfN",   
"ERIOMS",      "ERIOMS",      "",          "",          "69",     "dfN",   

"ERIAS",       "ERIAS",       "",          "",          "69",     "dfG",   

"ERIOM",       "ERIOM",       "",          "",          "69",     "dfI",   
"ERIOMIS",     "ERIOMIS",     "",          "",          "69",     "dfI",   

"ERIOSE",      "ERIOSE",      "",          "",          "69",     "dfW",   


// ------------------------------------- dauginiai skaitvardziai
// dveji

".DVEJI",      ".DVEJI",      "DU",        "DU",        "7",      "dmV",   

".DVEJU",      ".DVEJØ",  "DU",        "DU",        "7",      "dmK",   

".DVEJIEM",    ".DVEJIEM",    "DU",        "DU",        "7",      "dmN",   
".DVEJIEMS",   ".DVEJIEMS",   "DU",        "DU",        "7",      "dmN",   

".DVEJIS",     ".DVEJIS",     "DU",        "DU",        "7",      "dmG",   
".DVEJUS",     ".DVEJUS",     "DU",        "DU",        "7",      "dmG",   

".DVEJAIS",    ".DVEJAIS",    "DU",        "DU",        "7",      "dmI",   

".DVEJUOS",    ".DVEJUOS",    "DU",        "DU",        "7",      "dmW",   
".DVEJUOSE",   ".DVEJUOSE",   "DU",        "DU",        "7",      "dmW",   


// ------------------------------------- dauginiai skaitvardziai
// dvejos

".DVEJOS",     ".DVEJOS",     "DU",        "DU",        "7",      "dfV",   

".DVEJU",      ".DVEJØ",  "DU",        "DU",        "7",      "dfK",   

".DVEJOM",     ".DVEJOM",     "DU",        "DU",        "7",      "dfN",   
".DVEJOMS",    ".DVEJOMS",    "DU",        "DU",        "7",      "dfN",   

".DVEJAS",     ".DVEJAS",     "DU",        "DU",        "7",      "dfG",   

".DVEJOM",     ".DVEJOM",     "DU",        "DU",        "7",      "dfI",   
".DVEJOMIS",   ".DVEJOMIS",   "DU",        "DU",        "7",      "dfI",   

".DVEJOSE",    ".DVEJOSE",    "DU",        "DU",        "7",      "dfW",   


// ------------------------------------- dauginiai skaitvardziai
// treji

".TREJI",      ".TREJI",      "TR",        "TR",        "8",      "dmV",   

".TREJU",      ".TREJØ",  "TR",        "TR",        "8",      "dmK",   

".TREJIEM",    ".TREJIEM",    "TR",        "TR",        "8",      "dmN",   
".TREJIEMS",   ".TREJIEMS",   "TR",        "TR",        "8",      "dmN",   

".TREJIS",     ".TREJIS",     "TR",        "TR",        "8",      "dmG",   
".TREJUS",     ".TREJUS",     "TR",        "TR",        "8",      "dmG",   

".TREJAIS",    ".TREJAIS",    "TR",        "TR",        "8",      "dmI",   

".TREJUOS",    ".TREJUOS",    "TR",        "TR",        "8",      "dmW",   
".TREJUOSE",   ".TREJUOSE",   "TR",        "TR",        "8",      "dmW",   


// ------------------------------------- dauginiai skaitvardziai
// trejos

".TREJOS",     ".TREJOS",     "TR",        "TR",        "8",      "dfV",   

".TREJU",      ".TREJØ",  "TR",        "TR",        "8",      "dfK",   

".TREJOM",     ".TREJOM",     "TR",        "TR",        "8",      "dfN",   
".TREJOMS",    ".TREJOMS",    "TR",        "TR",        "8",      "dfN",   

".TREJAS",     ".TREJAS",     "TR",        "TR",        "8",      "dfG",   

".TREJOM",     ".TREJOM",     "TR",        "TR",        "8",      "dfI",   
".TREJOMIS",   ".TREJOMIS",   "TR",        "TR",        "8",      "dfI",   

".TREJOSE",    ".TREJOSE",    "TR",        "TR",        "8",      "dfW",   


// ------------------------------------- dauginiai skaitvardziai
// ketveri

".KETVERI",    ".KETVERI",    "KETUR",     "KETUR",     "9",      "dmV",   

".KETVERIU",   ".KETVERIØ", "KETUR",     "KETUR",     "9",      "dmK",   

".KETVERIEM",  ".KETVERIEM",  "KETUR",     "KETUR",     "9",      "dmN",   
".KETVERIEMS", ".KETVERIEMS", "KETUR",     "KETUR",     "9",      "dmN",   

".KETVERIS",   ".KETVERIS",   "KETUR",     "KETUR",     "9",      "dmG",   
".KETVERIUS",  ".KETVERIUS",  "KETUR",     "KETUR",     "9",      "dmG",   

".KETVERIAIS", ".KETVERIAIS", "KETUR",     "KETUR",     "9",      "dmI",   

".KETVERIUOS", ".KETVERIUOS", "KETUR",     "KETUR",     "9",      "dmW",   
".KETVERIUOSE", ".KETVERIUOSE", "KETUR",     "KETUR",     "9",      "dmW",   


// ------------------------------------- dauginiai skaitvardziai
// ketveri

".KETVERIOS",  ".KETVERIOS",  "KETUR",     "KETUR",     "9",      "dfV",   

".KETVERIU",   ".KETVERIØ", "KETUR",     "KETUR",     "9",      "dfK",   

".KETVERIOM",  ".KETVERIOM",  "KETUR",     "KETUR",     "9",      "dfN",   
".KETVERIOMS", ".KETVERIOMS", "KETUR",     "KETUR",     "9",      "dfN",   

".KETVERIAS",  ".KETVERIAS",  "KETUR",     "KETUR",     "9",      "dfG",   

".KETVERIOM",  ".KETVERIOM",  "KETUR",     "KETUR",     "9",      "dfI",   
".KETVERIOMIS", ".KETVERIOMIS", "KETUR",     "KETUR",     "9",      "dfI",   

".KETVERIOSE", ".KETVERIOSE", "KETUR",     "KETUR",     "9",      "dfW",   


// ------------------------------------- dauginiai skaitvardziai
// (vienetas), penketas, ...

"ETAS",        "ETAS",        "",          "",          "69",     "pv",   

"ETO",         "ETO",         "",          "",          "69",     "pk",   

"ETUI",        "ETUI",        "",          "",          "69",     "pn",   

"ETA",         "ETÀ",     "",          "",          "69",     "pg",   

"ETU",         "ETU",         "",          "",          "69",     "pi",   

"ETE",         "ETE",         "",          "",          "69",     "pw",   

"ETE",         "ETE",         "",          "",          "69",     "ps",   

"ETAI",        "ETAI",        "",          "",          "69",     "pV",   

"ETU",         "ETØ",     "",          "",          "69",     "pK",   

"ETAM",        "ETAM",        "",          "",          "69",     "pN",   
"ETAMS",       "ETAMS",       "",          "",          "69",     "pN",   

"ETUS",        "ETUS",        "",          "",          "69",     "pG",   

"ETAIS",       "ETAIS",       "",          "",          "69",     "pI",   

"ETUOS",       "ETUOS",       "",          "",          "69",     "pW",   
"ETUOSE",      "ETUOSE",      "",          "",          "69",     "pW",   


// ------------------------------------- dauginiai skaitvardziai
// dvejetas

".DVEJETAS",   ".DVEJETAS",   "DU",        "DU",        "7",      "pv",   

".DVEJETO",    ".DVEJETO",    "DU",        "DU",        "7",      "pk",   

".DVEJETUI",   ".DVEJETUI",   "DU",        "DU",        "7",      "pn",   

".DVEJETA",    ".DVEJETÀ", "DU",        "DU",        "7",      "pg",   

".DVEJETU",    ".DVEJETU",    "DU",        "DU",        "7",      "pi",   

".DVEJETE",    ".DVEJETE",    "DU",        "DU",        "7",      "pw",   

".DVEJETE",    ".DVEJETE",    "DU",        "DU",        "7",      "ps",   

".DVEJETAI",   ".DVEJETAI",   "DU",        "DU",        "7",      "pV",   

".DVEJETU",    ".DVEJETØ", "DU",        "DU",        "7",      "pK",   

".DVEJETAM",   ".DVEJETAM",   "DU",        "DU",        "7",      "pN",   
".DVEJETAMS",  ".DVEJETAMS",  "DU",        "DU",        "7",      "pN",   

".DVEJETUS",   ".DVEJETUS",   "DU",        "DU",        "7",      "pG",   

".DVEJETAIS",  ".DVEJETAIS",  "DU",        "DU",        "7",      "pI",   

".DVEJETUOS",  ".DVEJETUOS",  "DU",        "DU",        "7",      "pW",   
".DVEJETUOSE", ".DVEJETUOSE", "DU",        "DU",        "7",      "pW",   


// ------------------------------------- dauginiai skaitvardziai
// trejetas

".TREJETAS",   ".TREJETAS",   "TR",        "TR",        "8",      "pv",   

".TREJETO",    ".TREJETO",    "TR",        "TR",        "8",      "pk",   

".TREJETUI",   ".TREJETUI",   "TR",        "TR",        "8",      "pn",   

".TREJETA",    ".TREJETÀ", "TR",        "TR",        "8",      "pg",   

".TREJETU",    ".TREJETU",    "TR",        "TR",        "8",      "pi",   

".TREJETE",    ".TREJETE",    "TR",        "TR",        "8",      "pw",   

".TREJETE",    ".TREJETE",    "TR",        "TR",        "8",      "ps",   

".TREJETAI",   ".TREJETAI",   "TR",        "TR",        "8",      "pV",   

".TREJETU",    ".TREJETØ", "TR",        "TR",        "8",      "pK",   

".TREJETAM",   ".TREJETAM",   "TR",        "TR",        "8",      "pN",   
".TREJETAMS",  ".TREJETAMS",  "TR",        "TR",        "8",      "pN",   

".TREJETUS",   ".TREJETUS",   "TR",        "TR",        "8",      "pG",   

".TREJETAIS",  ".TREJETAIS",  "TR",        "TR",        "8",      "pI",   

".TREJETUOS",  ".TREJETUOS",  "TR",        "TR",        "8",      "pW",   
".TREJETUOSE", ".TREJETUOSE", "TR",        "TR",        "8",      "pW",   



// ------------------------------------- dauginiai skaitvardziai
// ketvertas

".KETVERTAS",  ".KETVERTAS",  "KETUR",     "KETUR",     "9",      "pv",   

".KETVERTO",   ".KETVERTO",   "KETUR",     "KETUR",     "9",      "pk",   

".KETVERTUI",  ".KETVERTUI",  "KETUR",     "KETUR",     "9",      "pn",   

".KETVERTA",   ".KETVERTÀ", "KETUR",     "KETUR",     "9",      "pg",   

".KETVERTU",   ".KETVERTU",   "KETUR",     "KETUR",     "9",      "pi",   

".KETVERTE",   ".KETVERTE",   "KETUR",     "KETUR",     "9",      "pw",   

".KETVERTE",   ".KETVERTE",   "KETUR",     "KETUR",     "9",      "ps",   

".KETVERTAI",  ".KETVERTAI",  "KETUR",     "KETUR",     "9",      "pV",   

".KETVERTU",   ".KETVERTØ", "KETUR",     "KETUR",     "9",      "pK",   

".KETVERTAM",  ".KETVERTAM",  "KETUR",     "KETUR",     "9",      "pN",   
".KETVERTAMS", ".KETVERTAMS", "KETUR",     "KETUR",     "9",      "pN",   

".KETVERTUS",  ".KETVERTUS",  "KETUR",     "KETUR",     "9",      "pG",   

".KETVERTAIS", ".KETVERTAIS", "KETUR",     "KETUR",     "9",      "pI",   

".KETVERTUOS", ".KETVERTUOS", "KETUR",     "KETUR",     "9",      "pW",   
".KETVERTUOSE", ".KETVERTUOSE", "KETUR",     "KETUR",     "9",      "pW",   


// ------------------------------------- kelintiniai skaitvardziai, vyr. gimine
// pirmas, penktas, ..., trecias

"AS",          "AS",          "",          "",          "]",      "mv",   
"CIAS",        "ÈIAS",   "T",         "T",         "]",      "mv",   

"O",           "O",           "",          "",          "}",      "mk",   
"CIO",         "ÈIO",    "T",         "T",         "}",      "mk",   

"AM",          "AM",          "",          "",          "}",      "mn",   
"CIAM",        "ÈIAM",   "T",         "T",         "}",      "mn",   

"A",           "À",       "",          "",          "}",      "mg",   
"CIA",         "ÈIÀ", "T",         "T",         "}",      "mg",   

"U",           "U",           "",          "",          "}",      "mi",   
"CIU",         "ÈIU",    "T",         "T",         "}",      "mi",   

"AM",          "AM",          "",          "",          "}",      "mw",   
"AME",         "AME",         "",          "",          "}",      "mw",   
"CIAM",        "ÈIAM",   "T",         "T",         "}",      "mw",   
"CIAME",       "ÈIAME",  "T",         "T",         "}",      "mw",   

"AS",          "AS",          "",          "",          "}",      "ms",   
"CIAS",        "ÈIAS",   "T",         "T",         "}",      "ms",   

"I",           "I",           "",          "",          "}",      "mV",   

"U",           "Ø",       "",          "",          "}",      "mK",   
"CIU",         "ÈIØ", "T",         "T",         "}",      "mK",   

"IEM",         "IEM",         "",          "",          "}",      "mN",   
"IEMS",        "IEMS",        "",          "",          "}",      "mN",   

"US",          "US",          "",          "",          "}",      "mG",   
"CIUS",        "ÈIUS",   "T",         "T",         "}",      "mG",   

"AIS",         "AIS",         "",          "",          "}",      "mI",   
"CIAIS",       "ÈIAIS",  "T",         "T",         "}",      "mI",   

"UOS",         "UOS",         "",          "",          "}",      "mW",   
"UOSE",        "UOSE",        "",          "",          "}",      "mW",   
"CIUOS",       "ÈIUOS",  "T",         "T",         "}",      "mW",   
"CIUOSE",      "ÈIUOSE", "T",         "T",         "}",      "mW",   


// ------------------------------------- kelintiniai skaitvardziai, mot. gimine
// pirma, penkta, ..., trecia

"A",           "A",           "",          "",          "}",      "fv",   
"CIA",         "ÈIA",    "T",         "T",         "}",      "fv",   

"OS",          "OS",          "",          "",          "}",      "fk",   
"CIOS",        "ÈIOS",   "T",         "T",         "}",      "fk",   

"AI",          "AI",          "",          "",          "}",      "fn",   
"CIAI",        "ÈIAI",   "T",         "T",         "}",      "fn",   

"A",           "À",       "",          "",          "}",      "fg",   
"CIA",         "ÈIÀ", "T",         "T",         "}",      "fg",   

"A",           "A",           "",          "",          "}",      "fi",   
"CIA",         "ÈIA",    "T",         "T",         "}",      "fi",   

// "O",        "O",           "",          "",          "}",      "fw",   // tarm.
"OJ",          "OJ",          "",          "",          "}",      "fw",   
"OJE",         "OJE",         "",          "",          "}",      "fw",   
// "CIO",      "ÈIO",    "T",         "T",         "}",      "fw",   // tarm.
"CIOJ",        "ÈIOJ",   "T",         "T",         "}",      "fw",   
"CIOJE",       "ÈIOJE",  "T",         "T",         "}",      "fw",   

"A",           "A",           "",          "",          "}",      "fs",   
"CIA",         "ÈIA",    "T",         "T",         "}",      "fs",   

"OS",          "OS",          "",          "",          "}",      "fV",   
"CIOS",        "ÈIOS",   "T",         "T",         "}",      "fV",   

"U",           "Ø",       "",          "",          "}",      "fK",   
"CIU",         "ÈIØ", "T",         "T",         "}",      "fK",   

"OM",          "OM",          "",          "",          "}",      "fN",   
"OMS",         "OMS",         "",          "",          "}",      "fN",   
"CIOM",        "ÈIOM",   "T",         "T",         "}",      "fN",   
"CIOMS",       "ÈIOMS",  "T",         "T",         "}",      "fN",   

"AS",          "AS",          "",          "",          "}",      "fG",   
"CIAS",        "ÈIAS",   "T",         "T",         "}",      "fG",   

"OM",          "OM",          "",          "",          "}",      "fI",   
"OMIS",        "OMIS",        "",          "",          "}",      "fI",   
"CIOM",        "ÈIOM",   "T",         "T",         "}",      "fI",   
"CIOMIS",      "ÈIOMIS", "T",         "T",         "}",      "fI",   

"OSE",         "OSE",         "",          "",          "}",      "fW",   
"CIOSE",       "ÈIOSE",  "T",         "T",         "}",      "fW",   


// ------------------------------------- kelintiniai skaitvardziai, niek. gimine
//

"A",           "A",           "",          "",          "}",      "o",   
"CIA",         "ÈIA",    "T",         "T",         "}",      "o",   


// ------------------------------------- kelintiniai skaitvardziai, vyr. gimine
// simtinis, tukstantinis, milijoninis

"IS",          "IS",          "",          "",          "/",      "mv",   

"IO",          "IO",          "",          "",          "*",      "mk",   

"IAM",         "IAM",         "",          "",          "*",      "mn",   

"I",           "Á",       "",          "",          "*",      "mn",   

"IU",          "IU",          "",          "",          "*",      "mi",   

"IAM",         "IAM",         "",          "",          "*",      "mw",   
"IAME",        "IAME",        "",          "",          "*",      "mw",   

"IS",          "IS",          "",          "",          "*",      "ms",   

"IAI",         "IAI",         "",          "",          "*",      "ms",   

"IU",          "IØ",      "",          "",          "*",      "mK",   

"IAM",         "IAM",         "",          "",          "*",      "mN",   
"IAMS",        "IAMS",        "",          "",          "*",      "mN",   

"IUS",         "IUS",         "",          "",          "*",      "mG",   

"IAIS",        "IAIS",        "",          "",          "*",      "mI",   

"IUOS",        "IUOS",        "",          "",          "*",      "mW",   
"IUOSE",       "IUOSE",       "",          "",          "*",      "mW",   


// ------------------------------------- kelintiniai skaitvardziai, mot. gimine
// simtine, tukstantine, milijonine

"E",           "Ë",        "",          "",          "*",      "fv",   // simtine, tukstantine, milijonine

"ES",          "ËS",       "",          "",          "*",      "fv",   

"EI",          "EI",          "",          "",          "*",      "fv",   

"E",           "Æ",       "",          "",          "*",      "fv",   

"E",           "E",           "",          "",          "*",      "fv",   

"E",           "Ë",        "",          "",          "*",      "fv",   
"EJ",          "ËJ",       "",          "",          "*",      "fv",   
"EJE",         "ËJE",      "",          "",          "*",      "fv",   

"E",           "E",           "",          "",          "*",      "fv",   

"ES",          "ËS",       "",          "",          "*",      "fv",   

"IU",          "IØ",      "",          "",          "*",      "fK",   

"EM",          "ËM",       "",          "",          "*",      "fv",   
"EMS",         "ËMS",      "",          "",          "*",      "fv",   

"ES",          "ES",          "",          "",          "*",      "fv",   

"EM",          "ËM",       "",          "",          "*",      "fv",   
"EMIS",        "ËMIS",     "",          "",          "*",      "fv",   

"ESE",         "ËSE",      "",          "",          "*",      "fv",   


// ------------------ kelintiniai skaitvardziai, aukstesnysis laipsnis, vyr. gimine
//

"ESNIS",       "ESNIS",       "",          "",          "}",      "1mv",   

"ESNIO",       "ESNIO",       "",          "",          "}",      "1mk",   

"ESNIAM",      "ESNIAM",      "",          "",          "}",      "1mn",   

"ESNI",        "ESNÁ",    "",          "",          "}",      "1mg",   

"ESNIU",       "ESNIU",       "",          "",          "}",      "1mi",   

"ESNIAM",      "ESNIAM",      "",          "",          "}",      "1mw",   
"ESNIAME",     "ESNIAME",     "",          "",          "}",      "1mw",   

"ESNIS",       "ESNIS",       "",          "",          "}",      "1ms",   

"ESNI",        "ESNI",        "",          "",          "}",      "1mV",   

"ESNIU",       "ESNIØ",   "",          "",          "}",      "1mK",   

"ESNIEM",      "ESNIEM",      "",          "",          "}",      "1mN",   
"ESNIEMS",     "ESNIEMS",     "",          "",          "}",      "1mN",   

"ESNIUS",      "ESNIUS",      "",          "",          "}",      "1mG",   

"ESNIAIS",     "ESNIAIS",     "",          "",          "}",      "1mI",   

"ESNIUOS",     "ESNIUOS",     "",          "",          "}",      "1mW",   
"ESNIUOSE",    "ESNIUOSE",    "",          "",          "}",      "1mW",   


// ------------------ kelintiniai skaitvardziai, aukstesnysis laipsnis, mot. gimine
//

"ESNE",        "ESNË",     "",          "",          "}",      "1fv",   

"ESNES",       "ESNËS",    "",          "",          "}",      "1fk",   

"ESNEI",       "ESNEI",       "",          "",          "}",      "1fn",   

"ESNE",        "ESNÆ",    "",          "",          "}",      "1fg",   

"ESNE",        "ESNE",        "",          "",          "}",      "1fi",   

// "ESNE",     "ESNË",     "",          "",          "}",      "1fw",   // tarm.
"ESNEJ",       "ESNËJ",    "",          "",          "}",      "1fw",   
"ESNEJE",      "ESNËJE",   "",          "",          "}",      "1fw",   

"ESNE",        "ESNE",        "",          "",          "}",      "1fs",   

"ESNES",       "ESNËS",    "",          "",          "}",      "1fV",   

"ESNIU",       "ESNIØ",   "",          "",          "}",      "1fK",   

"ESNEM",       "ESNËM",    "",          "",          "}",      "1fN",   
"ESNEMS",      "ESNËMS",   "",          "",          "}",      "1fN",   


"ESNES",       "ESNES",       "",          "",          "}",      "1fG",   

"ESNEM",       "ESNËM",    "",          "",          "}",      "1fI",   
"ESNEMIS",     "ESNËMIS",  "",          "",          "}",      "1fI",   

"ESNESE",      "ESNËSE",   "",          "",          "}",      "1fW",   


// ------------------ kelintiniai skaitvardziai, aukstesnysis laipsnis, niek. gimine
//

"IAU",         "IAU",         "",          "",          "}",      "1o",   
// "CIAU",      "ÈIAU",   "T",         "T",         "}",      "1o",   // nera


// ------------------ kelintiniai skaitvardziai, auksciausiasis laipsnis, vyr. gimine
//

"IAUSIAS",     "IAUSIAS",     "",          "",          "}",      "2mv",   
// "CIAUSIAS",      "ÈIAUSIAS", "T",         "T",         "}",      "2mv",   // nera

"IAUSIO",      "IAUSIO",      "",          "",          "}",      "2mk",   
// "CIAUSIO",      "ÈIAUSIO", "T",         "T",         "}",      "2mk",   // nera

"IAUSIAM",     "IAUSIAM",     "",          "",          "}",      "2mn",   
// "CIAUSIAM",      "ÈIAUSIAM", "T",         "T",         "}",      "2mn",   // nera

"IAUSIA",      "IAUSIÀ",  "",          "",          "}",      "2mg",   
// "CIAUSIA",      "ÈIAUSIÀ", "T",         "T",         "}",      "2mg",   // nera

"IAUSIU",      "IAUSIU",      "",          "",          "}",      "2mi",   
// "CIAUSIU",      "ÈIAUSIU", "T",         "T",         "}",      "2mi",   // nera

"IAUSIAM",     "IAUSIAM",     "",          "",          "}",      "2mw",   
"IAUSIAME",    "IAUSIAME",    "",          "",          "}",      "2mw",   
// "CIAUSIAM",      "ÈIAUSIAM", "",          "",          "}",      "2mw",   // nera
// "CIAUSIAME",      "ÈIAUSIAME", "T",         "T",         "}",      "2mw",   // nera

"IAUSIAS",     "IAUSIAS",     "",          "",          "}",      "2ms",   
// "CIAUSIAS",      "ÈIAUSIAS", "T",         "T",         "}",      "2ms",   // nera

"IAUSI",       "IAUSI",       "",          "",          "}",      "2mV",   
// "CIAUSI",      "ÈIAUSI", "T",         "T",         "}",      "2ms",   // nera

"IAUSIU",      "IAUSIØ",  "",          "",          "}",      "2mK",   
// "CIAUSIU",      "ÈIAUSIØ", "T",         "T",         "}",      "2mK",   // nera

"IAUSIEM",     "IAUSIEM",     "",          "",          "}",      "2mN",   
"IAUSIEMS",    "IAUSIEMS",    "",          "",          "}",      "2mN",   
// "CIAUSIEM",      "ÈIAUSIEM", "T",         "T",         "}",      "2ms",   // nera
// "CIAUSIEMS",      "ÈIAUSIEMS", "T",         "T",         "}",      "2ms",   // nera

"IAUSIUS",     "IAUSIUS",     "",          "",          "}",      "2mG",   
// "CIAUSIUS",      "ÈIAUSIUS", "T",         "T",         "}",      "2mG",   // nera

"IAUSIAIS",    "IAUSIAIS",    "",          "",          "}",      "2mI",   
// "CIAUSIAIS",      "ÈIAUSIAIS", "T",         "T",         "}",      "2mI",   // nera

"IAUSIUOS",    "IAUSIUOS",    "",          "",          "}",      "2mW",   
"IAUSIUOSE",   "IAUSIUOSE",   "",          "",          "}",      "2mW",   
// "CIAUSIUOS",      "ÈIAUSIUOS", "T",         "T",         "}",      "2mW",   // nera
// "CIAUSIUOSE",      "ÈIAUSIUOSE", "T",         "T",         "}",      "2mW",   // nera


// -------------- kelintiniai skaitvardziai, auksciausiasis laipsnis, mot. gimine
//

"IAUSIA",      "IAUSIA",      "",          "",          "}",      "2fv",   
// "CIAUSIA",      "ÈIAUSIA", "T",         "T",         "}",      "2fv",   // nera

"IAUSIOS",     "IAUSIOS",     "",          "",          "}",      "2fk",   
// "CIAUSIOS",      "ÈIAUSIOS", "T",         "T",         "}",      "2fk",   // nera

"IAUSIAI",     "IAUSIAI",     "",          "",          "}",      "2fn",   
// "CIAUSIAI",      "ÈIAUSIAI", "T",         "T",         "}",      "2fn",   // nera

"IAUSIA",      "IAUSIÀ",  "",          "",          "}",      "2fg",   
// "CIAUSIA",      "ÈIAUSIÀ", "T",         "T",         "}",      "2fg",   // nera

"IAUSIA",      "IAUSIA",      "",          "",          "}",      "2fi",   
// "CIAUSIA",      "ÈIAUSIA", "T",         "T",         "}",      "2fi",   // nera

// "IAUSIO",   "IAUSIO",      "",          "",          "}",      "2fw",   // tarm.
"IAUSIOJ",     "IAUSIOJ",     "",          "",          "}",      "2fw",   
"IAUSIOJE",    "IAUSIOJE",    "",          "",          "}",      "2fw",   
// "CIAUSIO",      "ÈIAUSIO", "T",         "T",         "}",      "2fw",   // nera, tarm.
// "CIAUSIOJ",      "ÈIAUSIOJ", "T",         "T",         "}",      "2fw",   // nera
// "CIAUSIOJE",      "ÈIAUSIOJE", "T",         "T",         "}",      "2fw",   // nera

"IAUSIA",      "IAUSIA",      "",          "",          "}",      "2fs",   
// "CIAUSIA",      "ÈIAUSIA", "T",         "T",         "}",      "2fs",   // nera

"IAUSIOS",     "IAUSIOS",     "",          "",          "}",      "2fV",   
// "CIAUSIOS",      "ÈIAUSIOS", "T",         "T",         "}",      "2fV",   // nera

"IAUSIU",      "IAUSIØ",  "",          "",          "}",      "2fK",   
// "CIAUSIU",      "ÈIAUSIØ", "T",         "T",         "}",      "2fK",   // nera

"IAUSIOM",     "IAUSIOM",     "",          "",          "}",      "2fN",   
"IAUSIOMS",    "IAUSIOMS",    "",          "",          "}",      "2fN",   
// "CIAUSIOM",      "ÈIAUSIOM", "T",         "T",         "}",      "2fN",   // nera
// "CIAUSIOMS",      "ÈIAUSIOMS", "T",         "T",         "}",      "2fN",   // nera

"IAUSIAS",     "IAUSIAS",     "",          "",          "}",      "2fG",   
// "CIAUSIAS",      "ÈIAUSIAS", "T",         "T",         "}",      "2fG",   // nera

"IAUSIOM",     "IAUSIOM",     "",          "",          "}",      "2fI",   
"IAUSIOMS",    "IAUSIOMS",    "",          "",          "}",      "2fI",   
// "CIAUSIOM",      "ÈIAUSIOM", "T",         "T",         "}",      "2fI",   // nera
// "CIAUSIOMIS",      "ÈIAUSIOMIS", "T",         "T",         "}",      "2fI",   // nera

"IAUSIOSE",    "IAUSIOSE",    "",          "",          "}",      "2fW",   
// "CIAUSIOSE",      "ÈIAUSIOSE", "T",         "T",         "}",      "2fW",   // nera


// ---------------- kelintiniai skaitvardziai, auksciausiasis laipsnis, niek. gimine
//

"IAUSIA",      "IAUSIA",      "",          "",          "}",      "2o",   
// "CIAUSIA",      "ÈIAUSIA", "T",         "T",         "}",      "2o",   


// ---------------------- ivardziuotiniai kelintiniai skaitvardziai, vyr. gimine
//

"ASIS",        "ASIS",        "",          "",          "}",      "emv",   
"CIASIS",      "ÈIASIS", "T",         "T",         "}",      "emv",   

"OJO",         "OJO",         "",          "",          "}",      "emk",   
"CIOJO",       "ÈIOJO",  "T",         "T",         "}",      "emk",   

"AMJAM",       "AMJAM",       "",          "",          "}",      "emn",   
"CIAMJAM",      "ÈIAMJAM", "T",         "T",         "}",      "emn",   

"AJI",         "ÀJÁ", "",          "",          "}",      "emg",   
"CIAJI",       "ÈIÀJÁ", "T",         "T",         "}",      "emg",   

"UOJU",        "UOJU",        "",          "",          "}",      "emi",   
"CIUOJU",      "ÈIUOJU", "T",         "T",         "}",      "emi",   

"AJAM",        "AJAM",        "",          "",          "}",      "emw",   
"AJAME",       "AJAME",       "",          "",          "}",      "emw",   
"CIAJAM",      "ÈIAJAM", "T",         "T",         "}",      "emw",   
"CIAJAME",      "ÈIAJAME", "T",         "T",         "}",      "emw",   

"ASIS",        "ASIS",        "",          "",          "}",      "ems",   
"CIASIS",      "ÈIASIS", "T",         "T",         "}",      "ems",   

"IEJI",        "IEJI",        "",          "",          "}",      "emV",   

"UJU",         "ØJØ", "",          "",          "}",      "emK",   
"CIUJU",       "ÈIØJØ", "T",         "T",         "}",      "emK",   

"IESIEM",      "IESIEM",      "",          "",          "}",      "emN",   
"IESIEMS",     "IESIEMS",     "",          "",          "}",      "emN",   

"UOSIUS",      "UOSIUS",      "",          "",          "}",      "emG",   
"CIUOSIUS",      "ÈIUOSIUS", "T",         "T",         "}",      "emG",   

"AISIAIS",     "AISIAIS",     "",          "",          "}",      "emI",   
"CIAISIAIS",      "ÈIAISIAIS", "T",         "T",         "}",      "emI",   

"UOSIUOS",     "UOSIUOS",     "",          "",          "}",      "emW",   
"UOSIUOSE",    "UOSIUOSE",    "",          "",          "}",      "emW",   
"CIUOSIUOS",      "ÈIUOSIUOS", "T",         "T",         "}",      "emW",   
"CIUOSIUOSE",      "ÈIUOSIUOSE", "T",         "T",         "}",      "emW",   


// ------------------------ ivardziuotiniai kelintiniai skaitvardziai, mot. gimine
//

"OJI",         "OJI",         "",          "",          "}",      "efv",   
"CIOJI",       "ÈIOJI",  "T",         "T",         "}",      "efv",   

"OSIOS",       "OSIOS",       "",          "",          "}",      "efk",   
"CIOSIOS",      "ÈIOSIOS", "T",         "T",         "}",      "efk",   

"AJAI",        "AJAI",        "",          "",          "}",      "efn",   
"CIAJAI",      "ÈIAJAI", "T",         "T",         "}",      "efn",   

"AJA",         "ÀJÀ", "",          "",          "}",      "efg",   
"CIAJA",       "ÈIÀJÀ", "T",         "T",         "}",      "efg",   

"AJA",         "ÀJA",     "",          "",          "}",      "efi",   
"CIAJA",       "ÈIÀJA", "T",         "T",         "}",      "efi",   

// "OJO",      "OJO",         "",          "",          "}",      "efw",   // tarm.
"OJOJ",        "OJOJ",        "",          "",          "}",      "efw",   
"OJOJE",       "OJOJE",       "",          "",          "}",      "efw",   
// "CIOJO",      "ÈIOJO",  "T",         "T",         "}",      "efw",   // tarm.
"CIOJOJ",      "ÈIOJOJ", "T",         "T",         "}",      "efw",   
"CIOJOJE",      "ÈIOJOJE", "T",         "T",         "}",      "efw",   

"AJA",         "ÀJA",     "",          "",          "}",      "efs",   
"CIAJA",       "ÈIÀJA", "T",         "T",         "}",      "efs",   

"OSIOS",       "OSIOS",       "",          "",          "}",      "efV",   
"CIOSIOS",      "ÈIOSIOS", "T",         "T",         "}",      "efV",   

"UJU",         "ØJØ", "",          "",          "}",      "efK",   
"CIUJU",       "ÈIØJØ", "T",         "T",         "}",      "efK",   

"OSIOM",       "OSIOM",       "",          "",          "}",      "efN",   
"OSIOMS",      "OSIOMS",      "",          "",          "}",      "efN",   
"CIOSIOM",      "ÈIOSIOM", "T",         "T",         "}",      "efN",   
"CIOSIOMS",      "ÈIOSIOMS", "T",         "T",         "}",      "efN",   

"ASIAS",       "ÀSIAS",   "",          "",          "}",      "efG",   
"CIASIAS",      "ÈIÀSIAS", "T",         "T",         "}",      "efG",   

"OSIOM",       "OSIOM",       "",          "",          "}",      "efI",   
"OSIOMIS",     "OSIOMIS",     "",          "",          "}",      "efI",   
"CIOSIOM",      "ÈIOSIOM", "T",         "T",         "}",      "efI",   
"CIOSIOMIS",      "ÈIOSIOMIS", "T",         "T",         "}",      "efI",   

"OSIOSE",      "OSIOSE",      "",          "",          "}",      "efW",   
"CIOSIOSE",      "ÈIOSIOSE", "T",         "T",         "}",      "efW",   


// -- ivardziuotiniai kelintiniai skaitvardziai, aukstesnysis laipsnis, vyr. gimine
//

"ESNYSIS",     "ESNYSIS",     "",          "",          "}",      "1emv",   

"ESNIOJO",     "ESNIOJO",     "",          "",          "}",      "1emk",   

"ESNIAJAM",    "ESNIAJAM",    "",          "",          "}",      "1emn",   

"ESNIJI",      "ESNÁJÁ", "",          "",          "}",      "1emg",   

"ESNIUOJU",    "ESNIUOJU",    "",          "",          "}",      "1emi",   

"ESNIAJAM",    "ESNIAJAM",    "",          "",          "}",      "1emw",   
"ESNIAJAME",   "ESNIAJAME",   "",          "",          "}",      "1emw",   

"ESNYSIS",     "ESNYSIS",     "",          "",          "}",      "1ems",   

"ESNIEJI",     "ESNIEJI",     "",          "",          "}",      "1emV",   

"ESNIUJU",     "ESNIØJØ", "",          "",          "}",      "1emK",   

"ESNIESIEM",   "ESNIESIEM",   "",          "",          "}",      "1emN",   
"ESNIESIEMS",  "ESNIESIEMS",  "",          "",          "}",      "1emN",   

"ESNIUOSIUS",  "ESNIUOSIUS",  "",          "",          "}",      "1emG",   

"ESNIAISIAIS", "ESNIAISIAIS", "",          "",          "}",      "1emI",   

"ESNIUOSIUOS", "ESNIUOSIUOS", "",          "",          "}",      "1emW",   
"ESNIUOSIUOSE", "ESNIUOSIUOSE", "",          "",          "}",      "1emW",   


// -- ivardziuotiniai kelintiniai skaitvardziai, aukstesnysis laipsnis, mot. gimine
//

"ESNIOJI",     "ESNIOJI",     "",          "",          "}",      "1efv",   

"ESNIOSIOS",   "ESNIOSIOS",   "",          "",          "}",      "1efk",   

"ESNIAJAI",    "ESNIAJAI",    "",          "",          "}",      "1efn",   

"ESNIAJA",     "ESNIÀJÀ", "",          "",          "}",      "1efg",   

"ESNIAJA",     "ESNIÀJA", "",          "",          "}",      "1efi",   

// "ESNIOJO",  "ESNIOJO",     "",          "",          "}",      "1efw",   // tarm.
"ESNIOJOJ",    "ESNIOJOJ",    "",          "",          "}",      "1efw",   
"ESNIOJOJE",   "ESNIOJOJE",   "",          "",          "}",      "1efw",   

"ESNIOJI",     "ESNIOJI",     "",          "",          "}",      "1efs",   

"ESNIOSIOS",   "ESNIOSIOS",   "",          "",          "}",      "1efV",   

"ESNIUJU",     "ESNIØJØ", "",          "",          "}",      "1efK",   

"ESNIOSIOM",   "ESNIOSIOM",   "",          "",          "}",      "1efN",   
"ESNIOSIOMS",  "ESNIOSIOMS",  "",          "",          "}",      "1efN",   

"ESNIASIAS",   "ESNIÀSIAS", "",          "",          "}",      "1efG",   

"ESNIOSIOM",   "ESNIOSIOM",   "",          "",          "}",      "1efI",   
"ESNIOSIOMIS", "ESNIOSIOMIS", "",          "",          "}",      "1efI",   

"ESNIOSIOSE",  "ESNIOSIOSE",  "",          "",          "}",      "1efW",   


// -- ivardziuotiniai kelintiniai skaitvardziai, auksciausiasis laipsnis, vyr. gimine
//

"IAUSIASIS",   "IAUSIASIS",   "",          "",          "}",      "2emv",   
// "CIAUSIASIS",      "ÈIAUSIASIS", "T",         "T",         "}",      "2emv",   // nera

"IAUSIOJO",    "IAUSIOJO",    "",          "",          "}",      "2emk",   
// "CIAUSIOJO",      "ÈIAUSIOJO", "T",         "T",         "}",      "2emk",   // nera

"IAUSIAJAM",   "IAUSIAJAM",   "",          "",          "}",      "2emn",   
// "CIAUSIAJAM",      "ÈIAUSIAJAM", "T",         "T",         "}",      "2emn",   // nera

"IAUSIAJI",    "IAUSIÀJÁ", "",          "",          "}",      "2emg",   
// "CIAUSIAJI",      "ÈIAUSIÀJÁ", "T",         "T",         "}",      "2emg",   // nera

"IAUSIUOJU",   "IAUSIUOJU",   "",          "",          "}",      "2emi",   
// "CIAUSIUOJU",      "ÈIAUSIUOJU", "T",         "T",         "}",      "2emi",   // nera

"IAUSIAJAM",   "IAUSIAJAM",   "",          "",          "}",      "2emw",   
"IAUSIAJAME",  "IAUSIAJAME",  "",          "",          "}",      "2emw",   
// "CIAUSIAJAM",      "ÈIAUSIAJAM", "T",         "T",         "}",      "2emw",   // nera
// "CIAUSIAJAME",      "ÈIAUSIAJAME", "T",         "T",         "}",      "2emw",   // nera

"IAUSIASIS",   "IAUSIASIS",   "",          "",          "}",      "2ems",   
// "CIAUSIASIS",      "ÈIAUSIASIS", "T",         "T",         "}",      "2ems",   // nera

"IAUSIEJI",    "IAUSIEJI",    "",          "",          "}",      "2emV",   
// "CIAUSIEJI",      "ÈIAUSIEJI", "T",         "T",         "}",      "2emV",   // nera

"IAUSIUJU",    "IAUSIØJØ", "",          "",          "}",      "2emK",   
// "CIAUSIUJU",      "ÈIAUSIØJØ", "T",         "T",         "}",      "2emK",   // nera

"IAUSIESIEM",  "IAUSIESIEM",  "",          "",          "}",      "2emN",   
"IAUSIESIEMS", "IAUSIESIEMS", "",          "",          "}",      "2emN",   
// "CIAUSIESIEM",      "ÈIAUSIESIEM", "T",         "T",         "}",      "2emN",   // nera
// "CIAUSIESIEMS",      "ÈIAUSIESIEMS", "T",         "T",         "}",      "2emN",   // nera

"IAUSIUOSIUS", "IAUSIUOSIUS", "",          "",          "}",      "2emG",   
// "CIAUSIUOSIUS",      "ÈIAUSIUOSIUS", "T",         "T",         "}",      "2emG",   // nera

"IAUSIASIAIS", "IAUSIASIAIS", "",          "",          "}",      "2emI",   
// "CIAUSIASIAIS",      "ÈIAUSIASIAIS", "T",         "T",         "}",      "2emI",   // nera

"IAUSIUOSIUOS", "IAUSIUOSIUOS", "",          "",          "}",      "2emW",   
"IAUSIUOSIUOSE", "IAUSIUOSIUOSE", "",          "",          "}",      "2emW",   
// "CIAUSIUOSIUOS",      "ÈIAUSIUOSIUOS", "T",         "T",         "}",      "2emW",   // nera
// "CIAUSIUOSIUOSE",      "ÈIAUSIUOSIUOSE", "T",         "T",         "}",      "2emW",   // nera


// -- ivardziuotiniai kelintiniai skaitvardziai, auksciausiasis laipsnis, mot. gimine
//

"IAUSIOJI",    "IAUSIOJI",    "",          "",          "}",      "2efv",   
// "CIAUSIOJI",      "ÈIAUSIOJI", "T",         "T",         "}",      "2efv",   // nera

"IAUSIOSIOS",  "IAUSIOSIOS",  "",          "",          "}",      "2efk",   
// "CIAUSIOSIOS",      "ÈIAUSIOSIOS", "T",         "T",         "}",      "2efk",   // nera

"IAUSIAJAI",   "IAUSIAJAI",   "",          "",          "}",      "2efn",   
// "CIAUSIAJAI",      "ÈIAUSIAJAI", "T",         "T",         "}",      "2efn",   // nera

"IAUSIAJA",    "IAUSIÀJÀ", "",          "",          "}",      "2efg",   
// "CIAUSIAJA",      "ÈIAUSIÀJÀ", "T",         "T",         "}",      "2efg",   // nera

"IAUSIAJA",    "IAUSIÀJA", "",          "",          "}",      "2efi",   
// "CIAUSIAJA",      "ÈIAUSIÀJA", "T",         "T",         "}",      "2efi",   // nera

// "IAUSIOJO", "IAUSIOJO",    "",          "",          "}",      "2efw",   // tarm.
"IAUSIOJOJ",   "IAUSIOJOJ",   "",          "",          "}",      "2efw",   
"IAUSIOJOJE",  "IAUSIOJOJE",  "",          "",          "}",      "2efw",   
// "CIAUSIOJO",      "ÈIAUSIOJO", "T",         "T",         "}",      "2efw",   // nera, tarm.
// "CIAUSIOJOJ",      "ÈIAUSIOJOJ", "T",         "T",         "}",      "2efw",   // nera
// "CIAUSIOJOJE",      "ÈIAUSIOJOJE", "T",         "T",         "}",      "2efw",   // nera

"IAUSIOJI",    "IAUSIOJI",    "",          "",          "}",      "2efs",   
// "CIAUSIOJI",      "ÈIAUSIOJI", "T",         "T",         "}",      "2efs",   // nera

"IAUSIOSIOS",  "IAUSIOSIOS",  "",          "",          "}",      "2efV",   
// "CIAUSIOSIOS",      "ÈIAUSIOSIOS", "T",         "T",         "}",      "2efV",   // nera

"IAUSIUJU",    "IAUSIØJØ", "",          "",          "}",      "2efK",   
// "CIAUSIUJU",      "ÈIAUSIØJØ", "T",         "T",         "}",      "2efK",   // nera

"IAUSIOSIOM",  "IAUSIOSIOM",  "",          "",          "}",      "2efN",   
"IAUSIOSIOMS", "IAUSIOSIOMS", "",          "",          "}",      "2efN",   
// "CIAUSIOSIOM",      "ÈIAUSIOSIOM", "T",         "T",         "}",      "2efN",   // nera
// "CIAUSIOSIOMS",      "ÈIAUSIOSIOMS", "T",         "T",         "}",      "2efN",   // nera

"IAUSIASIAS",  "IAUSIÀSIAS", "",          "",          "}",      "2efG",   
// "CIAUSIASIAS",      "ÈIAUSIÀSIAS", "T",         "T",         "}",      "2efG",   // nera

"IAUSIOSIOM",  "IAUSIOSIOM",  "",          "",          "}",      "2efI",   
"IAUSIOSIOMIS", "IAUSIOSIOMIS", "",          "",          "}",      "2efI",   
// "CIAUSIOSIOM",      "ÈIAUSIOSIOM", "T",         "T",         "}",      "2efI",   // nera
// "CIAUSIOSIOMIS",      "ÈIAUSIOSIOMIS", "T",         "T",         "}",      "2efI",   // nera

"IAUSIOSIOSE", "IAUSIOSIOSE", "",          "",          "}",      "2efW",   
// "CIAUSIOSIOSE",      "ÈIAUSIOSIOSE", "T",         "T",         "}",      "2efW",   // nera


// -------------------- asmeniniai ivardziai
// as, mes

"",            "",            "",          "",          "^",      "v",   

".MANES",      ".MANÆS",  "AS",        "AÐ",   "~",      "k",   

".MAN",        ".MAN",        "AS",        "AÐ",   "~",      "n",   

".MANE",       ".MANE",       "AS",        "AÐ",   "~",      "g",   

".MANIM",      ".MANIM",      "AS",        "AÐ",   "~",      "i",   
".MANIMI",     ".MANIMI",     "AS",        "AÐ",   "~",      "i",   

".MANY",       ".MANY",       "AS",        "AÐ",   "~",      "w",   
".MANYJ",      ".MANYJ",      "AS",        "AÐ",   "~",      "w",   
".MANYJE",     ".MANYJE",     "AS",        "AÐ",   "~",      "w",   

"",            "",            "",          "",          "~",      "s",   

".MES",        ".MES",        "AS",        "AÐ",   "~",      "V",   

".MUS",        ".MÛS",    "AS",        "AÐ",   "~",      "K",   
".MUSU",       ".MÛSØ", "AS",        "AÐ",   "~",      "K",   

".MUM",        ".MUM",        "AS",        "AÐ",   "~",      "N",   
".MUMS",       ".MUMS",       "AS",        "AÐ",   "~",      "N",   

".MUS",        ".MUS",        "AS",        "AÐ",   "~",      "G",   

".MUM",        ".MUM",        "AS",        "AÐ",   "~",      "I",   
".MUMIS",      ".MUMIS",      "AS",        "AÐ",   "~",      "I",   

".MUMYSE",     ".MUMYSE",     "AS",        "AÐ",   "~",      "W",   


// -------------------- asmeniniai ivardziai
// tu, jus

"",            "",            "",          "",          "?",      "v",   

".TAVES",      ".TAVÆS",  "TU",        "TU",        "!",      "k",   

".TAU",        ".TAU",        "TU",        "TU",        "!",      "n",   

".TAVE",       ".TAVE",       "TU",        "TU",        "!",      "g",   

".TAVIM",      ".TAVIM",      "TU",        "TU",        "!",      "i",   
".TAVIMI",     ".TAVIMI",     "TU",        "TU",        "!",      "i",   

".TAVY",       ".TAVY",       "TU",        "TU",        "!",      "w",   
".TAVYJ",      ".TAVYJ",      "TU",        "TU",        "!",      "w",   
".TAVYJE",     ".TAVYJE",     "TU",        "TU",        "!",      "w",   

"",            "",            "",          "",          "!",      "s",   

".JUS",        ".JÛS",    "TU",        "TU",        "!",      "V",   

".JUS",        ".JÛS",    "TU",        "TU",        "!",      "K",   
".JUSU",       ".JÛSØ", "TU",        "TU",        "!",      "K",   

".JUM",        ".JUM",        "TU",        "TU",        "!",      "N",   
".JUMS",       ".JUMS",       "TU",        "TU",        "!",      "N",   

".JUS",        ".JUS",        "TU",        "TU",        "!",      "G",   

".JUM",        ".JUM",        "TU",        "TU",        "!",      "I",   
".JUMIS",      ".JUMIS",      "TU",        "TU",        "!",      "I",   

".JUMYSE",     ".JUMYSE",     "TU",        "TU",        "!",      "W",   


// ------- asmeniniai, parodomieji, klausiamieji ivardziai, vyr. gimine
// jis, sis, tas, toks, kas, koks, kuris

"AS",          "AS",          "",          "",          ",",      "mv",   
".JIS",        ".JIS",        ".J",        ".J",        ",",      "mv",   
"IS",          "IS",          "",          "",          ";",      "mv",   
"S",           "S",           "",          "",          ";",      "mv",   

"O",           "O",           "",          "",          ".",      "mk",   
"IO",          "IO",          "",          "",          ":",      "mk",   
"IENO",        "IENO",        "",          "",          ".",      "mk",   // kieno

"AM",          "AM",          "",          "",          ".",      "mn",   
"IAM",         "IAM",         "",          "",          ":",      "mn",   

"A",           "À",       "",          "",          ".",      "mg",   
"I",           "Á",       "",          "",          ".:",     "mg",   

"UO",          "UO",          "",          "",          ".",      "mi",   
"IUO",         "IUO",         "",          "",          ":",      "mi",   

"AM",          "AM",          "",          "",          ".",      "mw",   
"AME",         "AME",         "",          "",          ".",      "mw",   
"IAM",         "IAM",         "",          "",          ":",      "mw",   
"IAME",        "IAME",        "",          "",          ":",      "mw",   

"AS",          "AS",          "",          "",          ".",      "ms",   
"IS",          "IS",          "",          "",          ":",      "ms",   
// "IS",       "IS",          "",          "",          ".",      "ms",   // nera
"S",           "S",           "",          "",          ":",      "ms",   

"IE",          "IE",          "",          "",          ".:",     "mV",   

"U",           "Û",       "",          "",          ".",      "mK",   
"IU",          "IÛ",      "",          "",          ":",      "mK",   

"IEM",         "IEM",         "",          "",          ".:",     "mN",   
"IEMS",        "IEMS",        "",          "",          ".:",     "mN",   

"UOS",         "UOS",         "",          "",          ".",      "mG",   
"IUOS",        "IUOS",        "",          "",          ":",      "mG",   

"AIS",         "AIS",         "",          "",          ".",      "mI",   
"IAIS",        "IAIS",        "",          "",          ":",      "mI",   

"UOS",         "UOS",         "",          "",          ".",      "mW",   
"IUOS",        "IUOS",        "",          "",          ":",      "mW",   
"UOSE",        "UOSE",        "",          "",          ".",      "mW",   
"IUOSE",       "IUOSE",       "",          "",          ":",      "mW",   


// ------- asmeniniai, parodomieji, klausiamieji ivardziai, mot. gimine
// ji, si, ta, tokia, kokia, kuri

"A",           "A",           "",          "",          ",",      "fv",   
"I",           "I",           "",          "",          ",;",     "fv",   
"IA",          "IA",          "",          "",          ";",      "fv",   

"OS",          "OS",          "",          "",          ".",      "fk",   
"IOS",         "IOS",         "",          "",          ":",      "fk",   

"AI",          "AI",          "",          "",          ".",      "fn",   
"IAI",         "IAI",         "",          "",          ":",      "fn",   

"A",           "À",       "",          "",          ".",      "fg",   
"IA",          "IÀ",      "",          "",          ".:",     "fg",   

"A",           "A",           "",          "",          ".",      "fi",   
"IA",          "IA",          "",          "",          ":",      "fi",   

// "O",        "O",           "",          "",          ".",      "fw",   // tarm.
"OJ",          "OJ",          "",          "",          ".",      "fw",   
"OJE",         "OJE",         "",          "",          ".",      "fw",   
// "IO",       "IO",          "",          "",          ":",      "fw",   // tarm.
"IOJ",         "IOJ",         "",          "",          ":",      "fw",   
"IOJE",        "IOJE",        "",          "",          ":",      "fw",   

"A",           "A",           "",          "",          ".",      "fs",   
"I",           "I",           "",          "",          ":",      "fs",   
// "I",        "I",           "",          "",          ".",      "fs",   // nera
"IA",          "IA",          "",          "",          ":",      "fs",   

"OS",          "OS",          "",          "",          ".",      "fV",   
"IOS",         "IOS",         "",          "",          ":",      "fV",   

"U",           "Û",       "",          "",          ".",      "fK",   
"IU",          "IÛ",      "",          "",          ":",      "fK",   

"OM",          "OM",          "",          "",          ".",      "fN",   
"OMS",         "OMS",         "",          "",          ".",      "fN",   
"IOM",         "IOM",         "",          "",          ":",      "fN",   
"IOMS",        "IOMS",        "",          "",          ":",      "fN",   

"AS",          "AS",          "",          "",          ".",      "fG",   
"IAS",         "IAS",         "",          "",          ":",      "fG",   

"OM",          "OM",          "",          "",          ".",      "fI",   
"OMIS",        "OMIS",        "",          "",          ".",      "fI",   
"IOM",         "IOM",         "",          "",          ":",      "fI",   
"IOMIS",       "IOMIS",       "",          "",          ":",      "fI",   

"OSE",         "OSE",         "",          "",          ".",      "fW",   
"IOSE",        "IOSE",        "",          "",          ":",      "fW",   

// ------- pazymimasis ivardis, vyr. gimine
// pats

"S",           "S",           "",          "",          ">",      "mv",   

"IES",         "IES",         "",          "",          "<",      "mk",   
"CIO",         "ÈIO",    "T",         "T",         "<",      "mk",   

"CIAM",        "ÈIAM",   "T",         "T",         "<",      "mn",   

"I",           "Á",       "",          "",          "<",      "mg",   

"CIU",         "ÈIU",    "T",         "T",         "<",      "mi",   

"CIAM",        "ÈIAM",   "T",         "T",         "<",      "mw",   
"CIAME",       "ÈIAME",  "T",         "T",         "<",      "mw",   

"S",           "S",           "",          "",          "<",      "ms",   

"YS",          "YS",          "",          "",          "<",      "mV",   

"CIU",          "ÈIÛ", "T",         "T",         "<",      "mK",   

"IEM",         "IEM",         "",          "",          "<",      "mN",   
"IEMS",        "IEMS",        "",          "",          "<",      "mN",   

"CIUS",        "ÈIUS",   "T",         "T",         "<",      "mG",   

"CIAIS",       "ÈIAIS",  "T",         "T",         "<",      "mI",   

"CIUOS",       "ÈIUOS",  "T",         "T",         "<",      "mW",   
"CIUOSE",      "ÈIUOSE", "T",         "T",         "<",      "mW",   


// ------- pazymimasis ivardis, mot. gimine
// pati

"I",           "I",           "",          "",          "<",      "fv",   

"CIOS",        "ÈIOS",   "T",         "T",         "<",      "fk",   

"CIAI",        "ÈIAI",   "T",         "T",         "<",      "fn",   

"IA",          "IÀ",      "",          "",          "<",      "fg",   

"CIA",         "ÈIA",    "T",         "T",         "<",      "fi",   

// "CIO",      "ÈIO",    "T",         "T",         "<",      "fw",   // tarm.
"CIOJ",        "ÈIOJ",   "T",         "T",         "<",      "fw",   
"CIOJE",       "ÈIOJE",  "T",         "T",         "<",      "fw",   

"I",           "I",           "",          "",          "<",      "fs",   

"CIOS",        "ÈIOS",   "T",         "T",         "<",      "fV",   

"CIU",          "ÈIÛ", "T",         "T",         "<",      "fK",   

"CIOM",        "ÈIOM",   "T",         "T",         "<",      "fN",   
"CIOMS",       "ÈIOMS",  "T",         "T",         "<",      "fN",   

"CIAS",        "ÈIAS",   "T",         "T",         "<",      "fG",   

"CIOM",        "ÈIOM",   "T",         "T",         "<",      "fI",   
"CIOMIS",      "ÈIOMIS", "T",         "T",         "<",      "fI",   

"CIOSE",       "ÈIOSE",  "T",         "T",         "<",      "fW",   


// ------- veiksmazodzio bendratis
// negalima trumpinti iki kamieno - "T" minksteja i "È" - pjaunasi su budvardziais ("2m...") !!!

"TI",          "TI",       "T",     "T",        ")",      "",   // mesti
"T",           "T",        "T",     "T",        "(",      "",   // mest

// "GAIVINTI",      "GAIVINTI",    "GAIVINT",   "GAIVINT",        ")",      "",   // suveikia "INTI"
// "MARINTI",      "MARINTI",    "MARINT",   "MARINT",        ")",      "",   // suveikia "INTI"
// "PINTI",      "PINTI",    "PINT",   "PINT",        ")",      "",   // suveikia "INTI"


// ------- veiksmazodzio bendraties sangrazine forma
"TIS",         "TIS",         "T",         "T",         "(",      "",   // nestis


// ------- veiksmazodzio tiesiogine nuosaka, esamasis laikas, a asmenuote
// nesa, kelia, svencia, audzia

"U",           "U",           "",          "",          "q",      "a",   
"IU",          "IU",          "",          "",          "q",      "a",   
"CIU",         "ÈIU",    "T",         "T",         "q",      "a",   
"DZIU",        "DÞIU",   "D",         "D",         "q",      "a",   

"I",           "I",           "",          "",          "q",      "t",   

"A",           "A",           "",          "",          "Q",      "j",   
"IA",          "IA",          "",          "",          "Q",      "j",   
"CIA",         "ÈIA",    "T",         "T",         "Q",      "j",   
"DZIA",        "DÞIA",   "D",         "D",         "Q",      "j",   

"AM",          "AM",          "",          "",          "q",      "A",   
"AME",         "AME",         "",          "",          "q",      "A",   
"IAM",         "IAM",         "",          "",          "q",      "A",   
"IAME",        "IAME",        "",          "",          "q",      "A",   
"CIAM",        "ÈIAM",   "T",         "T",         "q",      "A",   
"CIAME",       "ÈIAME",  "T",         "T",         "q",      "A",   
"DZIAM",       "DÞIAM",  "D",         "D",         "q",      "A",   
"DZIAME",      "DÞIAME", "D",         "D",         "q",      "A",   

"AT",          "AT",          "",          "",          "q",      "T",   
"ATE",         "ATE",         "",          "",          "q",      "T",   
"IAT",         "IAT",         "",          "",          "q",      "T",   
"IATE",        "IATE",        "",          "",          "q",      "T",   
"CIAT",        "ÈIAT",   "T",         "T",         "q",      "T",   
"CIATE",       "ÈIATE",  "T",         "T",         "q",      "T",   
"DZIAT",       "DÞIAT",  "D",         "D",         "q",      "T",   
"DZIATE",      "DÞIATE", "D",         "D",         "q",      "T",   

"A",           "A",           "",          "",          "q",      "J",   
"IA",          "IA",          "",          "",          "q",      "J",   
"CIA",         "ÈIA",    "T",         "T",         "q",      "J",   
"DZIA",        "DÞIA",   "D",         "D",         "q",      "J",   


// ------- veiksmazodzio tiesiogine nuosaka, esamasis laikas, i asmenuote
// tyli, svyti, budi

"IU",          "IU",          "",          "",          "q",      "a",   
"CIU",         "ÈIU",    "T",         "T",         "q",      "a",   // nera
"DZIU",        "DÞIU",   "D",         "D",         "q",      "a",   

"I",           "I",           "",          "",          "q",      "t",   

"I",           "I",           "",          "",          "Q",      "j",   

"IM",          "IM",          "",          "",          "q",      "A",   
"IME",         "IME",         "",          "",          "q",      "A",   

"IT",          "IT",          "",          "",          "q",      "T",   
"ITE",         "ITE",         "",          "",          "q",      "T",   

"I",           "I",           "",          "",          "q",      "J",   


// ------- veiksmazodzio tiesiogine nuosaka, esamasis laikas, o asmenuote
// mato

"AU",          "AU",          "",          "",          "q",      "a",   

"AI",          "AI",          "",          "",          "q",      "t",   

"O",           "O",           "",          "",          "Q",      "j",   

"OM",          "OM",          "",          "",          "q",      "A",   
"OME",         "OME",         "",          "",          "q",      "A",   

"OT",          "OT",          "",          "",          "q",      "T",   
"OTE",         "OTE",         "",          "",          "q",      "T",   

"O",           "O",           "",          "",          "q",      "J",   


// ------- veiksmazodzio tiesiogine nuosaka, esamasis laikas, a asmenuote, sangrazine forma
// nesasi, keliasi, svenciasi, audziasi

"UOSI",        "UOSI",        "",          "",          "q",      "xa",   
"IUOSI",       "IUOSI",       "",          "",          "q",      "xa",   
"CIUOSI",      "ÈIUOSI", "T",         "T",         "q",      "xa",   
"DZIUOSI",      "DÞIUOSI", "D",         "D",         "q",      "xa",   

"IESI",        "IESI",        "",          "",          "q",      "xt",   

"ASI",         "ASI",         "",          "",          "Q",      "xj",   
"IASI",        "IASI",        "",          "",          "Q",      "xj",   
"CIASI",       "ÈIASI",  "T",         "T",         "Q",      "xj",   
"DZIASI",      "DÞIASI", "D",         "D",         "Q",      "xj",   

"AMES",        "AMËS",     "",          "",          "q",      "xA",   
"IAMES",       "IAMËS",    "",          "",          "q",      "xA",   
"CIAMES",         "ÈIAMËS", "T",         "T",         "q",      "xA",   
"DZIAMES",         "DÞIAMËS", "D",         "D",         "q",      "xA",   

"ATES",        "ATËS",     "",          "",          "q",      "xT",   
"IATES",       "IATËS",    "",          "",          "q",      "xT",   
"CIATES",         "ÈIATËS", "T",         "T",         "q",      "xT",   
"DZIATES",         "DÞIATËS", "D",         "D",         "q",      "xT",   

"ASI",         "ASI",         "",          "",          "q",      "xJ",   
"IASI",        "IASI",        "",          "",          "q",      "xJ",   
"CIASI",       "ÈIASI",  "T",         "T",         "q",      "xJ",   
"DZIASI",      "DÞIASI", "D",         "D",         "q",      "xJ",   


// ------- veiksmazodzio tiesiogine nuosaka, esamasis laikas, i asmenuote, sangrazine forma
// tyli, svyti, budi

"IUOSI",       "IUOSI",       "",          "",          "q",      "xa",   
"CIUOSI",      "ÈIUOSI", "T",         "T",         "q",      "xa",   
"DZIUOSI",      "DÞIUOSI", "D",         "D",         "q",      "xa",   

"IESI",        "IESI",        "",          "",          "q",      "xt",   

"ISI",         "ISI",         "",          "",          "Q",      "xj",   

"IMES",        "IMËS",     "",          "",          "q",      "xA",   

"ITES",        "ITËS",     "",          "",          "q",      "xT",   

"ISI",         "ISI",         "",          "",          "q",      "xJ",   


// ------- veiksmazodzio tiesiogine nuosaka, esamasis laikas, o asmenuote, sangrazine forma
// mato

"AUSI",        "AUSI",        "",          "",          "q",      "xa",   

"AISI",        "AISI",        "",          "",          "q",      "xt",   

"OSI",         "OSI",         "",          "",          "Q",      "xj",   

"OMES",        "OMËS",     "",          "",          "q",      "xA",   

"OTES",        "OTËS",     "",          "",          "q",      "xT",   

"OSI",         "OSI",         "",          "",          "q",      "xJ",   


// ------- veiksmazodzio tiesiogine nuosaka, butasis kartinis laikas, o asmenuote
// dirbo, galejo

"AU",          "AU",          "",          "",          "r",      "a",   

"AI",          "AI",          "",          "",          "r",      "t",   

"O",           "O",           "",          "",          "R",      "j",   

"OM",          "OM",          "",          "",          "r",      "A",   
"OME",         "OME",         "",          "",          "r",      "A",   

"OT",          "OT",          "",          "",          "r",      "T",   
"OTE",         "OTE",         "",          "",          "r",      "T",   

"O",           "O",           "",          "",          "r",      "J",   


// ------- veiksmazodzio tiesiogine nuosaka, butasis kartinis laikas, e asmenuote
// nese, kele, svente, aude

"IAU",         "IAU",         "",          "",          "r",      "a",   
"CIAU",        "ÈIAU",   "T",         "T",         "r",      "a",   
"DZIAU",       "DÞIAU",  "D",         "D",         "r",      "a",   

"EI",          "EI",          "",          "",          "r",      "t",   

"E",           "Ë",        "",          "",          "R",      "j",   

"EM",          "ËM",       "",          "",          "r",      "A",   
"EME",         "ËME",      "",          "",          "r",      "A",   

"ET",          "ËT",       "",          "",          "r",      "T",   
"ETE",         "ËTE",      "",          "",          "r",      "T",   

"E",           "Ë",        "",          "",          "r",      "J",   


// ------- veiksmazodzio tiesiogine nuosaka, butasis kartinis laikas, o asmenuote, sangrazine forma
// dirbosi, ejosi

"AUSI",        "AUSI",        "",          "",          "r",      "xa",   

"AISI",        "AISI",        "",          "",          "r",      "xt",   

"OSI",         "OSI",         "",          "",          "R",      "xj",   

"OMES",        "OMËS",     "",          "",          "r",      "xA",   

"OTES",        "OTËS",     "",          "",          "r",      "xT",   

"OSI",         "OSI",         "",          "",          "r",      "xJ",   


// ------- veiksmazodzio tiesiogine nuosaka, butasis kartinis laikas, e asmenuote, sangrazine forma
// nesesi, kelesi, sventesi, audesi

"IAUSI",       "IAUSI",       "",          "",          "r",      "a",   
"CIAUSI",      "ÈIAUSI", "T",         "T",         "r",      "a",   
"DZIAUSI",      "DÞIAUSI", "D",         "D",         "r",      "a",   

"EISI",        "EISI",        "",          "",          "r",      "t",   

"ESI",         "ËSI",      "",          "",          "R",      "j",   

"EMES",        "ËMËS",  "",          "",          "r",      "A",   

"ETES",        "ËTËS",  "",          "",          "r",      "T",   

"ESI",         "ËSI",      "",          "",          "r",      "J",   


// ------- veiksmazodzio tiesiogine nuosaka, butasis dazninis laikas
// dirbdavo, galedavo

"DAVAU",       "DAVAU",       "T",         "T",         "(",      "ba",   

"DAVAI",       "DAVAI",       "T",         "T",         "(",      "bt",   

"DAVO",        "DAVO",        "T",         "T",         "(",      "bj",   

"DAVOM",       "DAVOM",       "T",         "T",         "(",      "bA",   
"DAVOME",      "DAVOME",      "T",         "T",         "(",      "bA",   

"DAVOT",       "DAVOT",       "T",         "T",         "(",      "bT",   
"DAVOTE",      "DAVOTE",      "T",         "T",         "(",      "bT",   

"DAVO",        "DAVO",        "T",         "T",         "(",      "bJ",   


// ------- veiksmazodzio tiesiogine nuosaka, butasis dazninis laikas, sangrazine forma
// dirbdavosi, galedavosi

"DAVAUSI",     "DAVAUSI",     "T",         "T",         "(",      "xba",   

"DAVAISI",     "DAVAISI",     "T",         "T",         "(",      "xbt",   

"DAVOSI",      "DAVOSI",      "T",         "T",         "(",      "xbj",   

"DAVOMES",     "DAVOMËS",  "T",         "T",         "(",      "xbA",   

"DAVOTES",     "DAVOTËS",  "T",         "T",         "(",      "xbT",   

"DAVOSI",      "DAVOSI",      "T",         "T",         "(",      "xbJ",   


// ------- veiksmazodzio tiesiogine nuosaka, busimasis laikas
// dirbs

"IU",          "IU",          "",          "",          "s",      "a",   

"I",           "I",           "",          "",          "s",      "t",   

"",            "",            "",          "",          "S",      "j",   
"EIS",         "EIS",         "EIT",       "EIT",       "S",      "j",   // eis - eiti - suveikia esamasis I linksniuotes "is"
".RIS",        ".RIS",        "RYT",       "RYT",       "S",      "j",   // ris - ryti - suveikia esamasis I linksniuotes "is"
"SIRIS",       "SIRIS",       "SIRYT",     "SIRYT",     "S",      "j",   // apsiris - apsiryti - suveikia esamasis I linksniuotes "is"
"PRARIS",      "PRARIS",      "PRARYT",    "PRARYT",    "S",      "j",   // praris - praryti - suveikia esamasis I linksniuotes "is"
".KIS",        ".KIS",        "KIST",      "KIST",      "S",      "j",   // kis - kisti - suveikia esamasis I linksniuotes "is"
".PIS",        ".PIS",        "PIST",      "PIST",      "S",      "j",   // pis - suveikia esamasis I linksniuotes "is"
"ÐPIS",        "ÐPIS",        "ÐPIST",     "ÐPIST",     "S",      "j",   // ispis - suveikia esamasis I linksniuotes "is"
".GIS",        ".GIS",        "GYT",       "GYT",       "S",      "j",   // gis - gyti - suveikia esamasis I linksniuotes "is"
"PAGIS",       "PAGIS",       "PAGYT",     "PAGYT",     "S",      "j",   // pagis - pagyti - suveikia esamasis I linksniuotes "is"
".LIS",        ".LIS",        "LYT",       "LYT",       "S",      "j",   // lis - lyti - suveikia esamasis I linksniuotes "is"
".PALIS",      ".PALIS",      "PALYT",     "PALYT",     "S",      "j",   // palis - palyti - suveikia esamasis I linksniuotes "is"

"IM",          "IM",          "",          "",          "s",      "A",   
"IME",         "IME",         "",          "",          "s",      "A",   

"IT",          "IT",          "",          "",          "s",      "T",   
"ITE",         "ITE",         "",          "",          "s",      "T",   

"",            "",            "",          "",          "s",      "J",   


// ------- veiksmazodzio tiesiogine nuosaka, busimasis laikas, sangrazine forma
// dirbsis

"IUOSI",       "IUOSI",       "",          "",          "s",      "xa",   

"IESI",        "IESI",        "",          "",          "s",      "xt",   

"IS",          "IS",          "",          "",          "S",      "xj",   

"IMES",        "IMËS",     "",          "",          "s",      "xA",   

"ITES",        "ITËS",     "",          "",          "s",      "xT",   

"IS",          "IS",          "",          "",          "s",      "xJ",   


// ------- veiksmazodzio tariamoji nuosaka
// dirbtu

"CAIU",        "ÈAIU",   "T",         "T",         "(",      "ha",   

"TUM",         "TUM",         "T",         "T",         "(",      "ht",   
"TUMEI",       "TUMEI",       "T",         "T",         "(",      "ht",   

"TU",          "TØ",      "T",         "T",         "(",      "hj",   

"TUME",        "TUME",        "T",         "T",         "(",      "hA",   
"TUMEME",      "TUMËME",   "T",         "T",         "(",      "hA",   

"TUTE",        "TUTE",        "T",         "T",         "(",      "hT",   
"TUMETE",      "TUMËTE",   "T",         "T",         "(",      "hT",   

"TU",          "TØ",      "T",         "T",         "(",      "hJ",   


// ------- veiksmazodzio tariamoji nuosaka, sangrazine forma
// nestusi

"CAIUSI",      "ÈAIUSI", "T",         "T",         "(",      "xha",   

"TUMEISI",     "TUMEISI",     "T",         "T",         "(",      "xht",   

"TUSI",        "TØSI",    "T",         "T",         "(",      "xhj",   

"TUMES",       "TUMËS",    "T",         "T",         "(",      "xhA",   
"TUMEMES",       "TUMËMËS", "T",         "T",         "(",      "xhA",   

"TUTES",       "TUTËS",    "T",         "T",         "(",      "xhT",   
"TUMETES",       "TUMËTËS", "T",         "T",         "(",      "xhT",   

"TUSI",        "TØSI",    "T",         "T",         "(",      "xhJ",   


// ------- veiksmazodzio liepiamoji nuosaka
// dirbk

"",            "",            "",          "",          "Z",      "zt",   
"KI",          "KI",          "K",         "K",         "Z",      "zt",

"A",           "A",           "",          "",          "q",      "zj",   
"IA",          "IA",          "",          "",          "q",      "zj",   
"CIA",         "ÈIA",    "T",         "T",         "q",      "zj",   
"DZIA",        "DÞIA",   "D",         "D",         "q",      "zj",   
"I",           "I",           "",          "",          "q",      "zj",   
"O",           "O",           "",          "",          "q",      "zj",   

"KIM",         "KIM",         "K",         "K",         "z",      "zA",   
"KIME",        "KIME",        "K",         "K",         "z",      "zA",   

"KIT",         "KIT",         "K",         "K",         "z",      "zT",   
"KITE",        "KITE",        "K",         "K",         "z",      "zT",   

"A",           "A",           "",          "",          "q",      "zJ",   
"IA",          "IA",          "",          "",          "q",      "zJ",   
"CIA",         "ÈIA",    "T",         "T",         "q",      "zJ",   
"DZIA",        "DÞIA",   "D",         "D",         "q",      "zJ",   
"I",           "I",           "",          "",          "q",      "zJ",   
"O",           "O",           "",          "",          "q",      "zJ",   


// ------- veiksmazodzio liepiamoji nuosaka, sangrazine forma
// neskis

// "KIS",      "KIS",         "K",         "K",         "z",      "xzt",   // !!! pjaunasi su santykis, akis, ...

"ASI",         "ASI",         "",          "",          "q",      "xzj",   
"IASI",        "IASI",        "",          "",          "q",      "xzj",   
"CIASI",       "ÈIASI",  "T",         "T",         "q",      "xzj",   
"DZIASI",      "DÞIASI", "D",         "D",         "q",      "xzj",   
"ISI",         "ISI",         "",          "",          "q",      "xzj",   
"OSI",         "OSI",         "",          "",          "q",      "xzj",   

"KIMES",       "KIMËS",    "K",         "K",         "z",      "xzA",   

"KITES",       "KITËS",    "K",         "K",         "z",      "xzT",   

"ASI",         "ASI",         "",          "",          "q",      "xzJ",   
"IASI",        "IASI",        "",          "",          "q",      "xzJ",   
"CIASI",       "ÈIASI",  "T",         "T",         "q",      "xzJ",   
"DZIASI",      "DÞIASI", "D",         "D",         "q",      "xzJ",   

"ISI",         "ISI",         "",          "",          "q",      "xzJ",   
"OSI",         "OSI",         "",          "",          "q",      "xzJ",   


// ------- veikiamasis esamojo laiko dalyvis, vyr. gimine
// suprantantis, keliantis, jauciantis, snaudziantis, tylintis, sakantis

"ANTIS",       "ANTIS",       "",          "",          "q",      "lmv",   
"AS",          "ÀS",      "",          "",          "q",      "lmv",   
"IANTIS",      "IANTIS",      "",          "",          "q",      "lmv",   
"IAS",         "IÀS",     "",          "",          "q",      "lmv",   
"CIANTIS",      "ÈIANTIS", "T",         "T",         "q",      "lmv",   
"CIAS",        "ÈIÀS", "T",         "T",         "q",      "lmv",   
"DZIANTIS",      "DÞIANTIS", "D",         "D",         "q",      "lmv",   
"DZIAS",       "DÞIÀS", "D",         "D",         "q",      "lmv",   
"INTIS",       "INTIS",       "",          "",          "q",      "lmv",   
"IS",          "ÁS",      "",          "",          "q",      "lmv",   

"ANCIO",       "ANÈIO",  "",          "",          "q",      "lmk",   
"IANCIO",      "IANÈIO", "",          "",          "q",      "lmk",   
"CIANCIO",           "ÈIANÈIO", "T",         "T",         "q",      "lmk",   
"DZIANCIO",           "DÞIANÈIO", "D",         "D",         "q",      "lmk",   
"INCIO",       "INÈIO",  "",          "",          "q",      "lmk",   

"ANCIAM",      "ANÈIAM", "",          "",          "q",      "lmn",   
"IANCIAM",      "IANÈIAM", "",          "",          "q",      "lmn",   
"CIANCIAM",           "ÈIANÈIAM", "T",         "T",         "q",      "lmn",   
"DZIANCIAM",           "DÞIANÈIAM", "D",         "D",         "q",      "lmn",   
"INCIAM",      "INÈIAM", "",          "",          "q",      "lmn",   

"ANTI",        "ANTÁ",    "",          "",          "q",      "lmg",   
"IANTI",       "IANTÁ",   "",          "",          "q",      "lmg",   
"CIANTI",      "ÈIANTÁ", "T",         "T",         "q",      "lmg",   
"DZIANTI",      "DÞIANTÁ", "D",         "D",         "q",      "lmg",   
// "INTI",        "INTÁ",    "",          "",          "q",      "lmg",   // suveikia su bendratimis gaivinti, marinti, pinti

"ANCIU",       "ANÈIU",  "",          "",          "q",      "lmi",   
"IANCIU",      "IANÈIU", "",          "",          "q",      "lmi",   
"CIANCIU",           "ÈIANÈIU", "T",         "T",         "q",      "lmi",   
"DZIANCIU",           "DÞIANÈIU", "D",         "D",         "q",      "lmi",   
"INCIU",       "INÈIU",  "",          "",          "q",      "lmi",   

"ANCIAM",      "ANÈIAM", "",          "",          "q",      "lmw",   
"ANCIAME",      "ANÈIAME", "",          "",          "q",      "lmw",   
"IANCIAM",      "IANÈIAM", "",          "",          "q",      "lmw",   
"IANCIAME",      "IANÈIAME", "",          "",          "q",      "lmw",   
"CIANCIAM",           "ÈIANÈIAM", "T",         "T",         "q",      "lmw",   
"CIANCIAME",           "ÈIANÈIAME", "T",         "T",         "q",      "lmw",   
"DZIANCIAM",           "DÞIANÈIAM", "D",         "D",         "q",      "lmw",   
"DZIANCIAME",           "DÞIANÈIAME", "D",         "D",         "q",      "lmw",   
"INCIAM",      "INÈIAM", "",          "",          "q",      "lmw",   
"INCIAME",      "INÈIAME", "",          "",          "q",      "lmw",   

"ANTIS",       "ANTIS",       "",          "",          "q",      "lms",   
"AS",          "ÀS",      "",          "",          "q",      "lms",   
"IANTIS",      "IANTIS",      "",          "",          "q",      "lms",   
"IAS",         "IÀS",     "",          "",          "q",      "lms",   
"CIANTIS",      "ÈIANTIS", "T",         "T",         "q",      "lms",   
"CIAS",        "ÈIÀS", "T",         "T",         "q",      "lms",   
"DZIANTIS",      "DÞIANTIS", "D",         "D",         "q",      "lms",   
"DZIAS",       "DÞIÀS", "D",         "D",         "q",      "lms",   
"INTIS",       "INTIS",       "",          "",          "q",      "lms",   
"IS",          "ÁS",      "",          "",          "q",      "lms",   

"ANTYS",       "ANTYS",       "",          "",          "q",      "lmV",   
"A",           "À",       "",          "",          "q",      "lmV",   
"IANTYS",      "IANTYS",      "",          "",          "q",      "lmV",   
"IA",          "IÀ",      "",          "",          "q",      "lmV",   
"CIANTYS",      "ÈIANTYS", "T",         "T",         "q",      "lmV",   
"CIA",         "ÈIÀ", "T",         "T",         "q",      "lmV",   
"DZIANTYS",      "DÞIANTYS", "D",         "D",         "q",      "lmV",   
"DZIA",        "DÞIÀ", "D",         "D",         "q",      "lmV",   
"INTYS",       "INTYS",       "",          "",          "q",      "lmV",   
"I",           "Á",       "",          "",          "q",      "lmV",   

"ANCIU",       "ANÈIØ", "",          "",          "q",      "lmK",   
"IANCIU",      "IANÈIØ", "",          "",          "q",      "lmK",   
"CIANCIU",           "ÈIANÈIØ", "T",         "T",         "q",      "lmK",   
"DZIANCIU",           "DÞIANÈIØ", "D",         "D",         "q",      "lmK",   
"INCIU",       "INÈIØ", "",          "",          "q",      "lmK",   

"ANTIEM",      "ANTIEM",      "",          "",          "q",      "lmN",   
"ANTIEMS",     "ANTIEMS",     "",          "",          "q",      "lmN",   
"IANTIEM",     "IANTIEM",     "",          "",          "q",      "lmN",   
"IANTIEMS",    "IANTIEMS",    "",          "",          "q",      "lmN",   
"CIANTIEM",      "ÈIANTIEM", "T",         "T",         "q",      "lmN",   
"CIANTIEMS",      "ÈIANTIEMS", "T",         "T",         "q",      "lmN",   
"DZIANTIEM",      "DÞIANTIEM", "D",         "D",         "q",      "lmN",   
"DZIANTIEMS",      "DÞIANTIEMS", "D",         "D",         "q",      "lmN",   
"INTIEM",      "INTIEM",      "",          "",          "q",      "lmN",   
"INTIEMS",     "INTIEMS",     "",          "",          "q",      "lmN",   

"ANCIUS",      "ANÈIUS", "",          "",          "q",      "lmG",   
"IANCIUS",      "IANÈIUS", "",          "",          "q",      "lmG",   
"CIANCIUS",           "ÈIANÈIUS", "T",         "T",         "q",      "lmG",   
"DZIANCIUS",           "DÞIANÈIUS", "D",         "D",         "q",      "lmG",   
"INCIUS",      "INÈIUS", "",          "",          "q",      "lmG",   

"ANCIAIS",      "ANÈIAIS", "",          "",          "q",      "lmI",   
"IANCIAIS",      "IANÈIAIS", "",          "",          "q",      "lmI",   
"CIANCIAIS",           "ÈIANÈIAIS", "T",         "T",         "q",      "lmI",   
"DZIANCIAIS",           "DÞIANÈIAIS", "D",         "D",         "q",      "lmI",   
"INCIAIS",      "INÈIAIS", "",          "",          "q",      "lmI",   

"ANCIUOS",      "ANÈIUOS", "",          "",          "q",      "lmW",   
"ANCIUOSE",      "ANÈIUOSE", "",          "",          "q",      "lmW",   
"IANCIUOS",      "IANÈIUOS", "",          "",          "q",      "lmW",   
"IANCIUOSE",      "IANÈIUOSE", "",          "",          "q",      "lmW",   
"CIANCIUOS",           "ÈIANÈIUOS", "T",         "T",         "q",      "lmW",   
"CIANCIUOSE",           "ÈIANÈIUOSE", "T",         "T",         "q",      "lmW",   
"DZIANCIUOS",           "DÞIANÈIUOS", "D",         "D",         "q",      "lmW",   
"DZIANCIUOSE",           "DÞIANÈIUOSE", "D",         "D",         "q",      "lmW",   
"INCIUOS",      "INÈIUOS", "",          "",          "q",      "lmW",   
"INCIUOSE",      "INÈIUOSE", "",          "",          "q",      "lmW",   


// ------- veikiamasis esamojo laiko dalyvis, vyr. gimine, sangrazine forma
// jauciasis

"ASIS",        "ÀSIS",    "",          "",          "q",      "xlmv",   
"IASIS",       "IÀSIS",   "",          "",          "q",      "xlmv",   
"CIASIS",      "ÈIÀSIS", "T",         "T",         "q",      "xlmv",   
"DZIASIS",      "DÞIÀSIS", "D",         "D",         "q",      "xlmv",   
"ISIS",        "ÁSIS",    "",          "",          "q",      "xlmv",   

"ASI",         "ÀSI",     "",          "",          "q",      "xlmV",   
"IASI",        "IÀSI",    "",          "",          "q",      "xlmV",   
"CIASI",       "ÈIÀSI", "T",         "T",         "q",      "xlmV",   
"DZIASI",      "DÞIÀSI", "D",         "D",         "q",      "xlmV",   
"ISI",         "ÁSI",     "",          "",          "q",      "xlmV",   


// ------- veikiamasis esamojo laiko dalyvis, mot. gimine
// suprantanti, kelianti, jaucianti, snaudzianti, tylinti, sakanti

"ANTI",        "ANTI",        "",          "",          "q",      "lfv",   
"IANTI",       "IANTI",       "",          "",          "q",      "lfv",   
"CIANTI",      "ÈIANTI", "T",         "T",         "q",      "lfv",   
"DZIANTI",      "DÞIANTI", "D",         "D",         "q",      "lfv",   
// "INTI",        "INTI",        "",          "",          "q",      "lfv",      // suveikia su bendratimis gaivinti, marinti, pinti

"ANCIOS",      "ANÈIOS", "",          "",          "q",      "lfk",   
"IANCIOS",      "IANÈIOS", "",          "",          "q",      "lfk",   
"CIANCIOS",           "ÈIANÈIOS", "T",         "T",         "q",      "lfk",   
"DZIANCIOS",           "DÞIANÈIOS", "D",         "D",         "q",      "lfk",   
"INCIOS",      "INÈIOS", "",          "",          "q",      "lfk",   

"ANCIAI",      "ANÈIAI", "",          "",          "q",      "lfn",   
"IANCIAI",      "IANÈIAI", "",          "",          "q",      "lfn",   
"CIANCIAI",           "ÈIANÈIAI", "T",         "T",         "q",      "lfn",   
"DZIANCIAI",           "DÞIANÈIAI", "D",         "D",         "q",      "lfn",   
"INCIAI",      "INÈIAI", "",          "",          "q",      "lfn",   

"ANCIA",       "ANÈIÀ", "",          "",          "q",      "lfg",   
"IANCIA",      "IANÈIÀ", "",          "",          "q",      "lfg",   
"CIANCIA",           "ÈIANÈIÀ", "T",         "T",         "q",      "lfg",   
"DZIANCIA",           "DÞIANÈIÀ", "D",         "D",         "q",      "lfg",   
"INCIA",       "INÈIÀ", "",          "",          "q",      "lfg",   

"ANCIA",       "ANÈIA",  "",          "",          "q",      "lfi",   
"IANCIA",      "IANÈIA", "",          "",          "q",      "lfi",   
"CIANCIA",           "ÈIANÈIA", "T",         "T",         "q",      "lfi",   
"DZIANCIA",           "DÞIANÈIA", "D",         "D",         "q",      "lfi",   
"INCIA",       "INÈIA",  "",          "",          "q",      "lfi",   

// "ANCIO",      "ANÈIO",  "",          "",          "q",      "lfw",   // tarm.
"ANCIOJ",      "ANÈIOJ", "",          "",          "q",      "lfw",   
"ANCIOJE",      "ANÈIOJE", "",          "",          "q",      "lfw",   
// "IANCIO",      "IANÈIO", "",          "",          "q",      "lfw",   // tarm.
"IANCIOJ",      "IANÈIOJ", "",          "",          "q",      "lfw",   
"IANCIOJE",      "IANÈIOJE", "",          "",          "q",      "lfw",   
// "CIANCIO",           "ÈIANÈIO", "T",         "T",         "q",      "lfw",   // tarm.
"CIANCIOJ",           "ÈIANÈIOJ", "T",         "T",         "q",      "lfw",   
"CIANCIOJE",           "ÈIANÈIOJE", "T",         "T",         "q",      "lfw",   
// "DZIANCIO",           "DÞIANÈIO", "D",         "D",         "q",      "lfw",   // tarm.
"DZIANCIOJ",           "DÞIANÈIOJ", "D",         "D",         "q",      "lfw",   
"DZIANCIOJE",           "DÞIANÈIOJE", "D",         "D",         "q",      "lfw",   
// "INCIO",      "INÈIO",  "",          "",          "q",      "lfw",   // tarm.
"INCIOJ",      "INÈIOJ", "",          "",          "q",      "lfw",   
"INCIOJE",      "INÈIOJE", "",          "",          "q",      "lfw",   

"ANTI",        "ANTI",        "",          "",          "q",      "lfs",   
"IANTI",       "IANTI",       "",          "",          "q",      "lfs",   
"CIANTI",      "ÈIANTI", "T",         "T",         "q",      "lfs",   
"DZIANTI",      "DÞIANTI", "D",         "D",         "q",      "lfs",   
// "INTI",        "INTI",        "",          "",          "q",      "lfs",      // suveikia su bendratimis gaivinti, marinti, pinti

"ANCIOS",      "ANÈIOS", "",          "",          "q",      "lfV",   
"IANCIOS",      "IANÈIOS", "",          "",          "q",      "lfV",   
"CIANCIOS",           "ÈIANÈIOS", "T",         "T",         "q",      "lfV",   
"DZIANCIOS",           "DÞIANÈIOS", "D",         "D",         "q",      "lfV",   
"INCIOS",      "INÈIOS", "",          "",          "q",      "lfV",   

"ANCIU",       "ANÈIØ", "",          "",          "q",      "lfK",   
"IANCIU",      "IANÈIØ", "",          "",          "q",      "lfK",   
"CIANCIU",           "ÈIANÈIØ", "T",         "T",         "q",      "lfK",   
"DZIANCIU",           "DÞIANÈIØ", "D",         "D",         "q",      "lfK",   
"INCIU",       "INÈIØ", "",          "",          "q",      "lfK",   

"ANCIOM",      "ANÈIOM", "",          "",          "q",      "lfN",   
"ANCIOMS",      "ANÈIOMS", "",          "",          "q",      "lfN",   
"IANCIOM",      "IANÈIOM", "",          "",          "q",      "lfN",   
"IANCIOMS",      "IANÈIOMS", "",          "",          "q",      "lfN",   
"CIANCIOM",           "ÈIANÈIOM", "T",         "T",         "q",      "lfN",   
"CIANCIOMS",           "ÈIANÈIOMS", "T",         "T",         "q",      "lfN",   
"DZIANCIOM",           "DÞIANÈIOM", "D",         "D",         "q",      "lfN",   
"DZIANCIOMS",           "DÞIANÈIOMS", "D",         "D",         "q",      "lfN",   
"INCIOM",      "INÈIOM", "",          "",          "q",      "lfN",   
"INCIOMS",      "INÈIOMS", "",          "",          "q",      "lfN",   

"ANCIAS",      "ANÈIAS", "",          "",          "q",      "lfG",   
"IANCIAS",      "IANÈIAS", "",          "",          "q",      "lfG",   
"CIANCIAS",           "ÈIANÈIAS", "T",         "T",         "q",      "lfG",   
"DZIANCIAS",           "DÞIANÈIAS", "D",         "D",         "q",      "lfG",   
"INCIAS",      "INÈIAS", "",          "",          "q",      "lfG",   

"ANCIOM",      "ANÈIOM", "",          "",          "q",      "lfI",   
"ANCIOMIS",      "ANÈIOMIS", "",          "",          "q",      "lfI",   
"IANCIOM",      "IANÈIOM", "",          "",          "q",      "lfI",   
"IANCIOMIS",      "IANÈIOMIS", "",          "",          "q",      "lfI",   
"CIANCIOM",           "ÈIANÈIOM", "T",         "T",         "q",      "lfI",   
"CIANCIOMIS",           "ÈIANÈIOMIS", "T",         "T",         "q",      "lfI",   
"DZIANCIOM",           "DÞIANÈIOM", "D",         "D",         "q",      "lfI",   
"DZIANCIOMIS",           "DÞIANÈIOMIS", "D",         "D",         "q",      "lfI",   
"INCIOM",      "INÈIOM", "",          "",          "q",      "lfI",   
"INCIOMIS",      "INÈIOMIS", "",          "",          "q",      "lfI",   

"ANCIOSE",      "ANÈIOSE", "",          "",          "q",      "lfW",   
"IANCIOSE",      "IANÈIOSE", "",          "",          "q",      "lfW",   
"CIANCIOSE",           "ÈIANÈIOSE", "T",         "T",         "q",      "lfW",   
"DZIANCIOSE",           "DÞIANÈIOSE", "D",         "D",         "q",      "lfW",   
"INCIOSE",      "INÈIOSE", "",          "",          "q",      "lfW",   


// ------- veikiamasis ivardziuotinis esamojo laiko dalyvis, vyr. gimine
// keliantysis

"ANTYSIS",     "ANTYSIS",     "",          "",          "q",      "elmv",   
"IANTYSIS",    "IANTYSIS",    "",          "",          "q",      "elmv",   
"CIANTYSIS",      "ÈIANTYSIS", "T",         "T",         "q",      "elmv",   
"DZIANTYSIS",      "DÞIANTYSIS", "D",         "D",         "q",      "elmv",   
"INTYSIS",     "INTYSIS",     "",          "",          "q",      "elmv",   

"ANCIOJO",      "ANÈIOJO", "",          "",          "q",      "elmk",   
"IANCIOJO",      "IANÈIOJO", "",          "",          "q",      "elmk",   
"CIANCIOJO",           "ÈIANÈIOJO", "T",         "T",         "q",      "elmk",   
"DZIANCIOJO",           "DÞIANÈIOJO", "D",         "D",         "q",      "elmk",   
"INCIOJO",      "INÈIOJO", "",          "",          "q",      "elmk",   

"ANCIAJAM",      "ANÈIAJAM", "",          "",          "q",      "elmn",   
"IANCIAJAM",      "IANÈIAJAM", "",          "",          "q",      "elmn",   
"CIANCIAJAM",           "ÈIANÈIAJAM", "T",         "T",         "q",      "elmn",   
"DZIANCIAJAM",           "DÞIANÈIAJAM", "D",         "D",         "q",      "elmn",   
"INCIAJAM",      "INÈIAJAM", "",          "",          "q",      "elmn",   

"ANTIJI",      "ANTÁJÁ", "",          "",          "q",      "elmg",   
"IANTIJI",     "IANTÁJÁ", "",          "",          "q",      "elmg",   
"CIANTIJI",      "ÈIANTÁJÁ", "T",         "T",         "q",      "elmg",   
"DZIANTIJI",      "DÞIANTÁJÁ", "D",         "D",         "q",      "elmg",   
"INTIJI",      "INTÁJÁ", "",          "",          "q",      "elmg",   

"ANCIUOJU",      "ANÈIUOJU", "",          "",          "q",      "elmi",   
"IANCIUOJU",      "IANÈIUOJU", "",          "",          "q",      "elmi",   
"CIANCIUOJU",           "ÈIANÈIUOJU", "T",         "T",         "q",      "elmi",   
"DZIANCIUOJU",           "DÞIANÈIUOJU", "D",         "D",         "q",      "elmi",   
"INCIUOJU",      "INÈIUOJU", "",          "",          "q",      "elmi",   

"ANCIAJAM",      "ANÈIAJAM", "",          "",          "q",      "elmw",   
"ANCIAJAME",      "ANÈIAJAME", "",          "",          "q",      "elmw",   
"IANCIAJAM",      "IANÈIAJAM", "",          "",          "q",      "elmw",   
"IANCIAJAME",      "IANÈIAJAME", "",          "",          "q",      "elmw",   
"CIANCIAJAM",           "ÈIANÈIAJAM", "T",         "T",         "q",      "elmw",   
"CIANCIAJAME",           "ÈIANÈIAJAME", "T",         "T",         "q",      "elmw",   
"DZIANCIAJAM",           "DÞIANÈIAJAM", "D",         "D",         "q",      "elmw",   
"DZIANCIAJAME",           "DÞIANÈIAJAME", "D",         "D",         "q",      "elmw",   
"INCIAJAM",      "INÈIAJAM", "",          "",          "q",      "elmw",   
"INCIAJAME",      "INÈIAJAME", "",          "",          "q",      "elmw",   

"ANTYSIS",     "ANTYSIS",     "",          "",          "q",      "elms",   
"IANTYSIS",    "IANTYSIS",    "",          "",          "q",      "elms",   
"CIANTYSIS",      "ÈIANTYSIS", "T",         "T",         "q",      "elms",   
"DZIANTYSIS",      "DÞIANTYSIS", "D",         "D",         "q",      "elms",   
"INTYSIS",     "INTYSIS",     "",          "",          "q",      "elms",   

"ANTIEJI",     "ANTIEJI",     "",          "",          "q",      "elmV",   
"IANTIEJI",    "IANTIEJI",    "",          "",          "q",      "elmV",   
"CIANTIEJI",      "ÈIANTIEJI", "T",         "T",         "q",      "elmV",   
"DZIANTIEJI",      "DÞIANTIEJI", "D",         "D",         "q",      "elmV",   
"INTIEJI",     "INTIEJI",     "",          "",          "q",      "elmV",   

"ANCIUJU",      "ANÈIØJØ", "",          "",          "q",      "elmK",   
"IANCIUJU",      "IANÈIØJØ", "",          "",          "q",      "elmK",   
"CIANCIUJU",           "ÈIANÈIØJØ", "T",         "T",         "q",      "elmK",   
"DZIANCIUJU",           "DÞIANÈIØJØ", "D",         "D",         "q",      "elmK",   
"INCIUJU",      "INÈIØJØ", "",          "",          "q",      "elmK",   

"ANTIESIEM",   "ANTIESIEM",   "",          "",          "q",      "elmN",   
"ANTIESIEMS",  "ANTIESIEMS",  "",          "",          "q",      "elmN",   
"IANTIESIEM",  "IANTIESIEM",  "",          "",          "q",      "elmN",   
"IANTIESIEMS", "IANTIESIEMS", "",          "",          "q",      "elmN",   
"CIANTIESIEM",      "ÈIANTIESIEM", "T",         "T",         "q",      "elmN",   
"CIANTIESIEMS",      "ÈIANTIESIEMS", "T",         "T",         "q",      "elmN",   
"DZIANTIESIEM",      "DÞIANTIESIEM", "D",         "D",         "q",      "elmN",   
"DZIANTIESIEMS",      "DÞIANTIESIEMS", "D",         "D",         "q",      "elmN",   
"INTIESIEM",   "INTIESIEM",   "",          "",          "q",      "elmN",   
"INTIESIEMS",  "INTIESIEMS",  "",          "",          "q",      "elmN",   

"ANCIUOSIUS",      "ANÈIUOSIUS", "",          "",          "q",      "elmG",   
"IANCIUOSIUS",      "IANÈIUOSIUS", "",          "",          "q",      "elmG",   
"CIANCIUOSIUS",           "ÈIANÈIUOSIUS", "T",         "T",         "q",      "elmG",   
"DZIANCIUOSIUS",           "DÞIANÈIUOSIUS", "D",         "D",         "q",      "elmG",   
"INCIUOSIUS",      "INÈIUOSIUS", "",          "",          "q",      "elmG",   

"ANCIAISIAIS",      "ANÈIAISIAIS", "",          "",          "q",      "elmI",   
"IANCIAISIAIS",      "IANÈIAISIAIS", "",          "",          "q",      "elmI",   
"CIANCIAISIAIS",           "ÈIANÈIAISIAIS", "T",         "T",         "q",      "elmI",   
"DZIANCIAISIAIS",           "DÞIANÈIAISIAIS", "D",         "D",         "q",      "elmI",   
"INCIAISIAIS",      "INÈIAISIAIS", "",          "",          "q",      "elmI",   

"ANCIUOSIUOS",      "ANÈIUOSIUOS", "",          "",          "q",      "elmW",   
"ANCIUOSIUOSE",      "ANÈIUOSIUOSE", "",          "",          "q",      "elmW",   
"IANCIUOSIUOS",      "IANÈIUOSIUOS", "",          "",          "q",      "elmW",   
"IANCIUOSIUOSE",      "IANÈIUOSIUOSE", "",          "",          "q",      "elmW",   
"CIANCIUOSIUOS",           "ÈIANÈIUOSIUOS", "T",         "T",         "q",      "elmW",   
"CIANCIUOSIUOSE",           "ÈIANÈIUOSIUOSE", "T",         "T",         "q",      "elmW",   
"DZIANCIUOSIUOS",           "DÞIANÈIUOSIUOS", "D",         "D",         "q",      "elmW",   
"DZIANCIUOSIUOSE",           "DÞIANÈIUOSIUOSE", "D",         "D",         "q",      "elmW",   
"INCIUOSIUOS",      "INÈIUOSIUOS", "",          "",          "q",      "elmW",   
"INCIUOSIUOSE",      "INÈIUOSIUOSE", "",          "",          "q",      "elmW",   


// ------- veikiamasis ivardziuotinis esamojo laiko dalyvis, mot. gimine
// keliancioji

"ANCIOJI",      "ANÈIOJI", "",          "",          "q",      "elfv",   
"IANCIOJI",      "IANÈIOJI", "",          "",          "q",      "elfv",   
"CIANCIOJI",           "ÈIANÈIOJI", "T",         "T",         "q",      "elfv",   
"DZIANCIOJI",           "DÞIANÈIOJI", "D",         "D",         "q",      "elfv",   
"INCIOJI",      "INÈIOJI", "",          "",          "q",      "elfv",   

"ANCIOSIOS",      "ANÈIOSIOS", "",          "",          "q",      "elfk",   
"IANCIOSIOS",      "IANÈIOSIOS", "",          "",          "q",      "elfk",   
"CIANCIOSIOS",           "ÈIANÈIOSIOS", "T",         "T",         "q",      "elfk",   
"DZIANCIOSIOS",           "DÞIANÈIOSIOS", "D",         "D",         "q",      "elfk",   
"INCIOSIOS",      "INÈIOSIOS", "",          "",          "q",      "elfk",   

"ANCIAJAI",      "ANÈIAJAI", "",          "",          "q",      "elfn",   
"IANCIAJAI",      "IANÈIAJAI", "",          "",          "q",      "elfn",   
"CIANCIAJAI",           "ÈIANÈIAJAI", "T",         "T",         "q",      "elfn",   
"DZIANCIAJAI",           "DÞIANÈIAJAI", "D",         "D",         "q",      "elfn",   
"INCIAJAI",      "INÈIAJAI", "",          "",          "q",      "elfn",   

"ANCIAJA",      "ANÈIÀJÀ", "",          "",          "q",      "elfg",   
"IANCIAJA",      "IANÈIÀJÀ", "",          "",          "q",      "elfg",   
"CIANCIAJA",           "ÈIANÈIÀJÀ", "T",         "T",         "q",      "elfg",   
"DZIANCIAJA",           "DÞIANÈIÀJÀ", "D",         "D",         "q",      "elfg",   
"INCIAJA",      "INÈIÀJÀ", "",          "",          "q",      "elfg",   

"ANCIAJA",      "ANÈIÀJA", "",          "",          "q",      "elfi",   
"IANCIAJA",      "IANÈIÀJA", "",          "",          "q",      "elfi",   
"CIANCIAJA",           "ÈIANÈIÀJA", "T",         "T",         "q",      "elfi",   
"DZIANCIAJA",           "DÞIANÈIÀJA", "D",         "D",         "q",      "elfi",   
"INCIAJA",      "INÈIÀJA", "",          "",          "q",      "elfi",   

// "ANCIOJO",      "ANÈIOJO", "",          "",          "q",      "elfw",   // tarm.
"ANCIOJOJ",      "ANÈIOJOJ", "",          "",          "q",      "elfw",   
"ANCIOJOJE",      "ANÈIOJOJE", "",          "",          "q",      "elfw",   
// "IANCIOJO",      "IANÈIOJO", "",          "",          "q",      "elfw",   // tarm.
"IANCIOJOJ",      "IANÈIOJOJ", "",          "",          "q",      "elfw",   
"IANCIOJOJE",      "IANÈIOJOJE", "",          "",          "q",      "elfw",   
// "CIANCIOJO",           "ÈIANÈIOJO", "T",         "T",         "q",      "elfw",   // tarm.
"CIANCIOJOJ",           "ÈIANÈIOJOJ", "T",         "T",         "q",      "elfw",   
"CIANCIOJOJE",           "ÈIANÈIOJOJE", "T",         "T",         "q",      "elfw",   
// "DZIANCIOJO",           "DÞIANÈIOJO", "D",         "D",         "q",      "elfw",   // tarm.
"DZIANCIOJOJ",           "DÞIANÈIOJOJ", "D",         "D",         "q",      "elfw",   
"DZIANCIOJOJE",           "DÞIANÈIOJOJE", "D",         "D",         "q",      "elfw",   
// "INCIOJO",      "INÈIOJO", "",          "",          "q",      "elfw",   // tarm.
"INCIOJOJ",      "INÈIOJOJ", "",          "",          "q",      "elfw",   
"INCIOJOJE",      "INÈIOJOJE", "",          "",          "q",      "elfw",   

"ANCIOJI",      "ANÈIOJI", "",          "",          "q",      "elfs",   
"IANCIOJI",      "IANÈIOJI", "",          "",          "q",      "elfs",   
"CIANCIOJI",           "ÈIANÈIOJI", "T",         "T",         "q",      "elfs",   
"DZIANCIOJI",           "DÞIANÈIOJI", "D",         "D",         "q",      "elfs",   
"INCIOJI",      "INÈIOJI", "",          "",          "q",      "elfs",   

"ANCIOSIOS",      "ANÈIOSIOS", "",          "",          "q",      "elfV",   
"IANCIOSIOS",      "IANÈIOSIOS", "",          "",          "q",      "elfV",   
"CIANCIOSIOS",           "ÈIANÈIOSIOS", "T",         "T",         "q",      "elfV",   
"DZIANCIOSIOS",           "DÞIANÈIOSIOS", "D",         "D",         "q",      "elfV",   
"INCIOSIOS",      "INÈIOSIOS", "",          "",          "q",      "elfV",   

"ANCIUJU",      "ANÈIØJØ", "",          "",          "q",      "elfK",   
"IANCIUJU",      "IANÈIØJØ", "",          "",          "q",      "elfK",   
"CIANCIUJU",           "ÈIANÈIØJØ", "T",         "T",         "q",      "elfK",   
"DZIANCIUJU",           "DÞIANÈIØJØ", "D",         "D",         "q",      "elfK",   
"INCIUJU",      "INÈIØJØ", "",          "",          "q",      "elfK",   

"ANCIOSIOM",      "ANÈIOSIOM", "",          "",          "q",      "elfN",   
"ANCIOSIOMS",      "ANÈIOSIOMS", "",          "",          "q",      "elfN",   
"IANCIOSIOM",      "IANÈIOSIOM", "",          "",          "q",      "elfN",   
"IANCIOSIOMS",      "IANÈIOSIOMS", "",          "",          "q",      "elfN",   
"CIANCIOSIOM",           "ÈIANÈIOSIOM", "T",         "T",         "q",      "elfN",   
"CIANCIOSIOMS",           "ÈIANÈIOSIOMS", "T",         "T",         "q",      "elfN",   
"DZIANCIOSIOM",           "DÞIANÈIOSIOM", "D",         "D",         "q",      "elfN",   
"DZIANCIOSIOMS",           "DÞIANÈIOSIOMS", "D",         "D",         "q",      "elfN",   
"INCIOSIOM",      "INÈIOSIOM", "",          "",          "q",      "elfN",   
"INCIOSIOMS",      "INÈIOSIOMS", "",          "",          "q",      "elfN",   

"ANCIASIAS",      "ANÈIÀSIAS", "",          "",          "q",      "elfG",   
"IANCIASIAS",      "IANÈIÀSIAS", "",          "",          "q",      "elfG",   
"CIANCIASIAS",           "ÈIANÈIÀSIAS", "T",         "T",         "q",      "elfG",   
"DZIANCIASIAS",           "DÞIANÈIÀSIAS", "D",         "D",         "q",      "elfG",   
"INCIASIAS",      "INÈIÀSIAS", "",          "",          "q",      "elfG",   

"ANCIOSIOM",      "ANÈIOSIOM", "",          "",          "q",      "elfI",   
"ANCIOSIOMIS",      "ANÈIOSIOMIS", "",          "",          "q",      "elfI",   
"IANCIOSIOM",      "IANÈIOSIOM", "",          "",          "q",      "elfI",   
"IANCIOSIOMIS",      "IANÈIOSIOMIS", "",          "",          "q",      "elfI",   
"CIANCIOSIOM",           "ÈIANÈIOSIOM", "T",         "T",         "q",      "elfI",   
"CIANCIOSIOMIS",           "ÈIANÈIOSIOMIS", "T",         "T",         "q",      "elfI",   
"DZIANCIOSIOM",           "DÞIANÈIOSIOM", "D",         "D",         "q",      "elfI",   
"DZIANCIOSIOMIS",           "DÞIANÈIOSIOMIS", "D",         "D",         "q",      "elfI",   
"INCIOSIOM",      "INÈIOSIOM", "",          "",          "q",      "elfI",   
"INCIOSIOMIS",      "INÈIOSIOMIS", "",          "",          "q",      "elfI",   

"ANCIOSIOSE",      "ANÈIOSIOSE", "",          "",          "q",      "elfW",   
"IANCIOSIOSE",      "IANÈIOSIOSE", "",          "",          "q",      "elfW",   
"CIANCIOSIOSE",           "ÈIANÈIOSIOSE", "T",         "T",         "q",      "elfW",   
"DZIANCIOSIOSE",           "DÞIANÈIOSIOSE", "D",         "D",         "q",      "elfW",   
"INCIOSIOSE",      "INÈIOSIOSE", "",          "",          "q",      "elfW",   


// ------- veikiamasis butojo k. laiko dalyvis, vyr. gimine
// suprates, keles, jautes, snaudes, tylejes, sakes

"ES",          "ÆS",      "",          "",          "r",      "lmv",   

"USIO",        "USIO",        "",          "",          "r",      "lmk",   
"IUSIO",       "IUSIO",       "",          "",          "r",      "lmk",   

"USIAM",       "USIAM",       "",          "",          "r",      "lmn",   
"IUSIAM",      "IUSIAM",      "",          "",          "r",      "lmn",   

"USI",         "USÁ",     "",          "",          "r",      "lmg",   
"IUSI",        "IUSÁ",    "",          "",          "r",      "lmg",   

"USIU",        "USIU",        "",          "",          "r",      "lmi",   
"IUSIU",       "IUSIU",       "",          "",          "r",      "lmi",   

"USIAM",       "USIAM",       "",          "",          "r",      "lmw",   
"IUSIAM",      "IUSIAM",      "",          "",          "r",      "lmw",   
"USIAME",      "USIAME",      "",          "",          "r",      "lmw",   
"IUSIAME",     "IUSIAME",     "",          "",          "r",      "lmw",   

"ES",          "ÆS",      "",          "",          "r",      "lms",   

"E",           "Æ",       "",          "",          "r",      "lmV",   

"USIU",        "USIØ",    "",          "",          "r",      "lmK",   
"IUSIU",       "IUSIØ",   "",          "",          "r",      "lmK",   

"USIEM",       "USIEM",       "",          "",          "r",      "lmN",   
"IUSIEM",      "IUSIEM",      "",          "",          "r",      "lmN",   
"USIEMS",      "USIEMS",      "",          "",          "r",      "lmN",   
"IUSIEMS",     "IUSIEMS",     "",          "",          "r",      "lmN",   

"USIUS",       "USIUS",       "",          "",          "r",      "lmG",   
"IUSIUS",      "IUSIUS",      "",          "",          "r",      "lmG",   

"USIAIS",      "USIAIS",      "",          "",          "r",      "lmI",   
"IUSIAIS",     "IUSIAIS",     "",          "",          "r",      "lmI",   

"USIUOS",      "USIUOS",      "",          "",          "r",      "lmW",   
"IUSIUOS",     "IUSIUOS",     "",          "",          "r",      "lmW",   
"USIUOSE",     "USIUOSE",     "",          "",          "r",      "lmW",   
"IUSIUOSE",    "IUSIUOSE",    "",          "",          "r",      "lmW",   


// ------- veikiamasis butojo k. laiko dalyvis, vyr. gimine, sangrazine forma
// jautesis

"ESIS",        "ÆSIS",    "",          "",          "r",      "xlmv",   

"ESI",         "ÆSI",     "",          "",          "r",      "xlmV",   


// ------- veikiamasis butojo k. laiko dalyvis, mot. gimine
// supratusi, kelusi, jautusi, snaudusi, tylejusi, sakiusi

"US",          "US",          "",          "",          "r",      "lfv",   
"IUS",         "IUS",         "",          "",          "r",      "lfv",   
"USI",         "USI",         "",          "",          "r",      "lfv",   
"IUSI",        "IUSI",        "",          "",          "r",      "lfv",   

"USIOS",       "USIOS",       "",          "",          "r",      "lfk",   
"IUSIOS",      "IUSIOS",      "",          "",          "r",      "lfk",   

"USIAI",       "USIAI",       "",          "",          "r",      "lfn",   
"IUSIAI",      "IUSIAI",      "",          "",          "r",      "lfn",   

"USIA",        "USIÀ",    "",          "",          "r",      "lfg",   
"IUSIA",       "IUSIÀ",   "",          "",          "r",      "lfg",   

"USIA",        "USIA",        "",          "",          "r",      "lfi",   
"IUSIA",       "IUSIA",       "",          "",          "r",      "lfi",   

// "USIO",     "USIO",        "",          "",          "r",      "lfw",   // tarm.
"USIOJ",       "USIOJ",       "",          "",          "r",      "lfw",   
"USIOJE",      "USIOJE",      "",          "",          "r",      "lfw",   
// "IUSIO",    "IUSIO",       "",          "",          "r",      "lfw",   // tarm.
"IUSIOJ",      "IUSIOJ",      "",          "",          "r",      "lfw",   
"IUSIOJE",     "IUSIOJE",     "",          "",          "r",      "lfw",   

"US",          "US",          "",          "",          "r",      "lfs",   
"IUS",         "IUS",         "",          "",          "r",      "lfs",   
"USI",         "USI",         "",          "",          "r",      "lfs",   
"IUSI",        "IUSI",        "",          "",          "r",      "lfs",   

"USIOS",       "USIOS",       "",          "",          "r",      "lfV",   
"IUSIOS",      "IUSIOS",      "",          "",          "r",      "lfV",   

"USIU",        "USIØ",    "",          "",          "r",      "lfK",   
"IUSIU",       "IUSIØ",   "",          "",          "r",      "lfK",   

"USIOM",       "USIOM",       "",          "",          "r",      "lfN",   
"USIOMS",      "USIOMS",      "",          "",          "r",      "lfN",   
"IUSIOM",      "IUSIOM",      "",          "",          "r",      "lfN",   
"IUSIOMS",     "IUSIOMS",     "",          "",          "r",      "lfN",   

"USIAS",       "USIAS",       "",          "",          "r",      "lfG",   
"IUSIAS",      "IUSIAS",      "",          "",          "r",      "lfG",   

"USIOM",       "USIOM",       "",          "",          "r",      "lfI",   
"USIOMIS",     "USIOMIS",     "",          "",          "r",      "lfI",   
"IUSIOM",      "IUSIOM",      "",          "",          "r",      "lfI",   
"IUSIOMIS",    "IUSIOMIS",    "",          "",          "r",      "lfI",   

"USIOSE",      "USIOSE",      "",          "",          "r",      "lfW",   
"IUSIOSE",     "IUSIOSE",     "",          "",          "r",      "lfW",   


// ------- veikiamasis ivardziuotinis butojo k. laiko dalyvis, vyr. gimine
// dirbusysis

"USYSIS",      "USYSIS",      "",          "",          "r",      "elmv",   
"IUSYSIS",     "IUSYSIS",     "",          "",          "r",      "elmv",   

"USIOJO",      "USIOJO",      "",          "",          "r",      "elmk",   
"IUSIOJO",     "IUSIOJO",     "",          "",          "r",      "elmk",   


"USIAJAM",     "USIAJAM",     "",          "",          "r",      "elmn",   
"IUSIAJAM",    "IUSIAJAM",    "",          "",          "r",      "elmn",   

"USIJI",       "USÁJÁ", "",          "",          "r",      "elmg",   
"IUSIJI",      "IUSÁJÁ", "",          "",          "r",      "elmg",   

"USIUOJU",     "USIUOJU",     "",          "",          "r",      "elmi",   
"IUSIUOJU",    "IUSIUOJU",    "",          "",          "r",      "elmi",   

"USIAJAM",     "USIAJAM",     "",          "",          "r",      "elmw",   
"IUSIAJAM",    "IUSIAJAM",    "",          "",          "r",      "elmw",   
"USIAJAME",    "USIAJAME",    "",          "",          "r",      "elmw",   
"IUSIAJAME",   "IUSIAJAME",   "",          "",          "r",      "elmw",   

"USYSIS",      "USYSIS",      "",          "",          "r",      "elms",   
"IUSYSIS",     "IUSYSIS",     "",          "",          "r",      "elms",   

"USIEJI",      "USIEJI",      "",          "",          "r",      "elmV",   
"IUSIEJI",     "IUSIEJI",     "",          "",          "r",      "elmV",   

"USIUJU",      "USIØJØ", "",          "",          "r",      "elmK",   
"IUSIUJU",     "IUSIØJØ", "",          "",          "r",      "elmK",   

"USIESIEM",    "USIESIEM",    "",          "",          "r",      "elmN",   
"IUSIESIEM",   "IUSIESIEM",   "",          "",          "r",      "elmN",   
"USIESIEMS",   "USIESIEMS",   "",          "",          "r",      "elmN",   
"IUSIESIEMS",  "IUSIESIEMS",  "",          "",          "r",      "elmN",   

"USIUOSIUS",   "USIUOSIUS",   "",          "",          "r",      "elmG",   
"IUSIUOSIUS",  "IUSIUOSIUS",  "",          "",          "r",      "elmG",   

"USIAISIAIS",  "USIAISIAIS",  "",          "",          "r",      "elmI",   
"IUSIAISIAIS", "IUSIAISIAIS", "",          "",          "r",      "elmI",   

"USIUOSIUOS",  "USIUOSIUOS",  "",          "",          "r",      "elmW",   
"IUSIUOSIUOS", "IUSIUOSIUOS", "",          "",          "r",      "elmW",   
"USIUOSIUOSE", "USIUOSIUOSE", "",          "",          "r",      "elmW",   
"IUSIUOSIUOSE", "IUSIUOSIUOSE", "",          "",          "r",      "elmW",   


// ------- veikiamasis ivardziuotinis butojo k. laiko dalyvis, mot. gimine
// dirbusioji

"USIOJI",      "USIOJI",      "",          "",          "r",      "elfv",   
"IUSIOJI",     "IUSIOJI",     "",          "",          "r",      "elfv",   
"USIOJI",      "USIOJI",      "",          "",          "r",      "elfv",   
"IUSIOJI",     "IUSIOJI",     "",          "",          "r",      "elfv",   

"USIOSIOS",    "USIOSIOS",    "",          "",          "r",      "elfk",   
"IUSIOSIOS",   "IUSIOSIOS",   "",          "",          "r",      "elfk",   

"USIAJAI",     "USIAJAI",     "",          "",          "r",      "elfn",   
"IUSIAJAI",    "IUSIAJAI",    "",          "",          "r",      "elfn",   

"USIAJA",      "USIÀJÀ", "",          "",          "r",      "elfg",   
"IUSIAJA",     "IUSIÀJÀ", "",          "",          "r",      "elfg",   

"USIAJA",      "USIÀJA",  "",          "",          "r",      "elfi",   
"IUSIAJA",     "IUSIÀJA", "",          "",          "r",      "elfi",   

// "USIOJO",   "USIOJO",      "",          "",          "r",      "elfw",   // tarm.
"USIOJOJ",     "USIOJOJ",     "",          "",          "r",      "elfw",   
"USIOJOJE",    "USIOJOJE",    "",          "",          "r",      "elfw",   
// "IUSIOJO",  "IUSIOJO",     "",          "",          "r",      "elfw",   // tarm.
"IUSIOJOJ",    "IUSIOJOJ",    "",          "",          "r",      "elfw",   
"IUSIOJOJE",   "IUSIOJOJE",   "",          "",          "r",      "elfw",   

"USIOJI",      "USIOJI",      "",          "",          "r",      "elfs",   
"IUSIOJI",     "IUSIOJI",     "",          "",          "r",      "elfs",   
"USIOJI",      "USIOJI",      "",          "",          "r",      "elfs",   
"IUSIOJI",     "IUSIOJI",     "",          "",          "r",      "elfs",   

"USIOSIOS",    "USIOSIOS",    "",          "",          "r",      "elfV",   
"IUSIOSIOS",   "IUSIOSIOS",   "",          "",          "r",      "elfV",   

"USIUJU",      "USIØJØ", "",          "",          "r",      "elfK",   
"IUSIUJU",     "IUSIØJØ", "",          "",          "r",      "elfK",   

"USIOSIOM",    "USIOSIOM",    "",          "",          "r",      "elfN",   
"USIOSIOMS",   "USIOSIOMS",   "",          "",          "r",      "elfN",   
"IUSIOSIOM",   "IUSIOSIOM",   "",          "",          "r",      "elfN",   
"IUSIOSIOMS",  "IUSIOSIOMS",  "",          "",          "r",      "elfN",   

"USIASIAS",    "USIÀSIAS", "",          "",          "r",      "elfG",   
"IUSIASIAS",   "IUSIÀSIAS", "",          "",          "r",      "elfG",   

"USIOSIOM",    "USIOSIOM",    "",          "",          "r",      "elfI",   
"USIOSIOMIS",  "USIOSIOMIS",  "",          "",          "r",      "elfI",   
"IUSIOSIOM",   "IUSIOSIOM",   "",          "",          "r",      "elfI",   
"IUSIOSIOMIS", "IUSIOSIOMIS", "",          "",          "r",      "elfI",   

"USIOSIOSE",   "USIOSIOSE",   "",          "",          "r",      "elfW",   
"IUSIOSIOSE",  "IUSIOSIOSE",  "",          "",          "r",      "elfW",   


// ------- veikiamasis butojo d. laiko dalyvis, vyr. gimine
// dirbdaves

"DAVES",       "DAVÆS",   "T",         "T",         "(",      "lbmv",   

"DAVUSIO",     "DAVUSIO",     "T",         "T",         "(",      "lbmk",   

"DAVUSIAM",    "DAVUSIAM",    "T",         "T",         "(",      "lbmn",   

"DAVUSI",      "DAVUSÁ",  "T",         "T",         "(",      "lbmg",   

"DAVUSIU",     "DAVUSIU",     "T",         "T",         "(",      "lbmi",   

"DAVUSIAM",    "DAVUSIAM",    "T",         "T",         "(",      "lbmw",   
"DAVUSIAME",   "DAVUSIAME",   "T",         "T",         "(",      "lbmw",   

"DAVES",       "DAVÆS",   "T",         "T",         "(",      "lbms",   

"DAVE",        "DAVÆ",    "T",         "T",         "(",      "lbmV",   

"DAVUSIU",     "DAVUSIØ", "T",         "T",         "(",      "lbmK",   

"DAVUSIEM",    "DAVUSIEM",    "T",         "T",         "(",      "lbmN",   
"DAVUSIEMS",   "DAVUSIEMS",   "T",         "T",         "(",      "lbmN",   

"DAVUSIUS",    "DAVUSIUS",    "T",         "T",         "(",      "lbmG",   

"DAVUSIAIS",   "DAVUSIAIS",   "T",         "T",         "(",      "lbmI",   

"DAVUSIUOS",   "DAVUSIUOS",   "T",         "T",         "(",      "lbmW",   
"DAVUSIUOSE",  "DAVUSIUOSE",  "T",         "T",         "(",      "lbmW",   


// ------- veikiamasis butojo d. laiko dalyvis, vyr. gimine, sangrazine forma
// duodavesis

"DAVESIS",     "DAVÆSIS", "T",         "T",         "(",      "xlbmv",   

"DAVESI",      "DAVÆSI",  "T",         "T",         "(",      "xlbmV",   


// ------- veikiamasis butojo d. laiko dalyvis, mot. gimine
// dirbdavusi

"DAVUS",       "DAVUS",       "T",         "T",         "(",      "lbfv",   
"DAVUSI",      "DAVUSI",      "T",         "T",         "(",      "lbfv",   

"DAVUSIOS",    "DAVUSIOS",    "T",         "T",         "(",      "lbfk",   

"DAVUSIAI",    "DAVUSIAI",    "T",         "T",         "(",      "lbfn",   

"DAVUSIA",     "DAVUSIÀ", "T",         "T",         "(",      "lbfg",   

"DAVUSIA",     "DAVUSIA",     "T",         "T",         "(",      "lbfi",   

// "DAVUSIO",  "DAVUSIO",     "T",         "T",         "(",      "lbfw",   // tarm.
"DAVUSIOJ",    "DAVUSIOJ",    "T",         "T",         "(",      "lbfw",   
"DAVUSIOJE",   "DAVUSIOJE",   "T",         "T",         "(",      "lbfw",   

"DAVUS",       "DAVUS",       "T",         "T",         "(",      "lbfs",   
"DAVUSI",      "DAVUSI",      "T",         "T",         "(",      "lbfs",   

"DAVUSIOS",    "DAVUSIOS",    "T",         "T",         "(",      "lbfV",   

"DAVUSIU",     "DAVUSIØ", "T",         "T",         "(",      "lbfK",   

"DAVUSIOM",    "DAVUSIOM",    "T",         "T",         "(",      "lbfN",   
"DAVUSIOMS",   "DAVUSIOMS",   "T",         "T",         "(",      "lbfN",   

"DAVUSIAS",    "DAVUSIAS",    "T",         "T",         "(",      "lbfG",   

"DAVUSIOM",    "DAVUSIOM",    "T",         "T",         "(",      "lbfI",   
"DAVUSIOMIS",  "DAVUSIOMIS",  "T",         "T",         "(",      "lbfI",   


"DAVUSIOSE",   "DAVUSIOSE",   "T",         "T",         "(",      "lbfW",   


// ------- veikiamasis ivardziuotinis butojo d. laiko dalyvis, vyr. gimine
// duodavesysis

"DAVUSYSIS",   "DAVUSYSIS",   "T",         "T",         "(",      "elbmv",   

"DAVUSIOJO",   "DAVUSIOJO",   "T",         "T",         "(",      "elbmk",   

"DAVUSIAJAM",  "DAVUSIAJAM",  "T",         "T",         "(",      "elbmn",   

"DAVUSIJI",    "DAVUSÁJÁ", "T",         "T",         "(",      "elbmg",   

"DAVUSIUOJU",  "DAVUSIUOJU",  "T",         "T",         "(",      "elbmi",   

"DAVUSIAJAM",  "DAVUSIAJAM",  "T",         "T",         "(",      "elbmw",   
"DAVUSIAJAME", "DAVUSIAJAME", "T",         "T",         "(",      "elbmw",   

"DAVUSYSIS",   "DAVUSYSIS",   "T",         "T",         "(",      "elbms",   

"DAVUSIEJI",   "DAVUSIEJI",   "T",         "T",         "(",      "elbmV",   

"DAVUSIUJU",   "DAVUSIØJØ", "T",         "T",         "(",      "elbmK",   

"DAVUSIESIEM", "DAVUSIESIEM", "T",         "T",         "(",      "elbmN",   
"DAVUSIESIEMS", "DAVUSIESIEMS", "T",         "T",         "(",      "elbmN",   

"DAVUSIUOSIUS", "DAVUSIUOSIUS", "T",         "T",         "(",      "elbmG",   

"DAVUSIAISIAIS", "DAVUSIAISIAIS", "T",         "T",         "(",      "elbmI",   

"DAVUSIUOSIUOS", "DAVUSIUOSIUOS", "T",         "T",         "(",      "elbmW",   
"DAVUSIUOSIUOSE", "DAVUSIUOSIUOSE", "T",         "T",         "(",      "elbmW",   



// ------- veikiamasis ivardziuotinis butojo d. laiko dalyvis, mot. gimine
// dirbdavusioji

"DAVUSIOJI",   "DAVUSIOJI",   "T",         "T",         "(",      "elbfv",   

"DAVUSIOSIOS", "DAVUSIOSIOS", "T",         "T",         "(",      "elbfk",   

"DAVUSIAJAI",  "DAVUSIAJAI",  "T",         "T",         "(",      "elbfn",   

"DAVUSIAJA",   "DAVUSIÀJÀ", "T",         "T",         "(",      "elbfg",   

"DAVUSIAJA",   "DAVUSIÀJA", "T",         "T",         "(",      "elbfi",   

// "DAVUSIOJO", "DAVUSIOJO",   "T",         "T",         "(",      "elbfw",   // tarm.
"DAVUSIOJOJ",  "DAVUSIOJOJ",  "T",         "T",         "(",      "elbfw",   
"DAVUSIOJOJE", "DAVUSIOJOJE", "T",         "T",         "(",      "elbfw",   

"DAVUSIOJI",   "DAVUSIOJI",   "T",         "T",         "(",      "elbfs",   

"DAVUSIOSIOS", "DAVUSIOSIOS", "T",         "T",         "(",      "elbfV",   

"DAVUSIUJU",   "DAVUSIØJØ", "T",         "T",         "(",      "elbfK",   

"DAVUSIOSIOM", "DAVUSIOSIOM", "T",         "T",         "(",      "elbfN",   
"DAVUSIOSIOMS", "DAVUSIOSIOMS", "T",         "T",         "(",      "elbfN",   

"DAVUSIASIAS", "DAVUSIÀSIAS", "T",         "T",         "(",      "elbfG",   

"DAVUSIOSIOM", "DAVUSIOSIOM", "T",         "T",         "(",      "elbfI",   
"DAVUSIOSIOMIS", "DAVUSIOSIOMIS", "T",         "T",         "(",      "elbfI",   

"DAVUSIOSIOSE", "DAVUSIOSIOSE", "T",         "T",         "(",      "elbfW",   


// ------- veikiamasis busimojo laiko dalyvis, vyr. gimine
// dirbsiantis

"IANTIS",      "IANTIS",      "",          "",          "s",      "lmv",   

"IANCIO",      "IANÈIO", "",          "",          "s",      "lmk",   

"IANCIAM",      "IANÈIAM", "",          "",          "s",      "lmn",   

"IANTI",       "IANTÁ",   "",          "",          "s",      "lmg",   

"IANCIU",      "IANÈIU", "",          "",          "s",      "lmi",   

"IANCIAM",      "IANÈIAM", "",          "",          "s",      "lmw",   
"IANCIAME",      "IANÈIAME", "",          "",          "s",      "lmw",   

"IANTIS",      "IANTIS",      "",          "",          "s",      "lms",   

"IANTYS",      "IANTYS",      "",          "",          "s",      "lmV",   

"IANCIU",      "IANÈIØ", "",          "",          "s",      "lmK",   

"IANTIEM",     "IANTIEM",     "",          "",          "s",      "lmN",   
"IANTIEMS",    "IANTIEMS",    "",          "",          "s",      "lmN",   

"IANCIUS",      "IANÈIUS", "",          "",          "s",      "lmG",   

"IANCIAIS",      "IANÈIAIS", "",          "",          "s",      "lmI",   

"IANCIUOS",      "IANÈIUOS", "",          "",          "s",      "lmW",   
"IANCIUOSE",      "IANÈIUOSE", "",          "",          "s",      "lmW",   


// ------- veikiamasis busimojo laiko dalyvis, mot. gimimine
// dirbsianti

"IANTI",       "IANTI",       "",          "",          "s",      "lfv",   

"IANCIOS",      "IANÈIOS", "",          "",          "s",      "lfk",   

"IANCIAI",      "IANÈIAI", "",          "",          "s",      "lfn",   

"IANCIA",      "IANCIÀ",  "",          "",          "s",      "lfg",   

"IANCIA",      "IANÈIA", "",          "",          "s",      "lfi",   

"IANCIOJ",      "IANÈIOJ", "",          "",          "s",      "lfw",   
"IANCIOJE",      "IANÈIOJE", "",          "",          "s",      "lfw",   

"IANTI",       "IANTI",       "",          "",          "s",      "lfs",   

"IANCIOS",      "IANÈIOS", "",          "",          "s",      "lfV",   

"IANCIU",      "IANÈIØ", "",          "",          "s",      "lfK",   

"IANCIOM",      "IANÈIOM", "",          "",          "s",      "lfN",   
"IANCIOMS",      "IANÈIOMS", "",          "",          "s",      "lfN",   

"IANCIAS",      "IANÈIAS", "",          "",          "s",      "lfG",   

"IANCIOM",      "IANÈIOM", "",          "",          "s",      "lfI",   
"IANCIOMIS",      "IANÈIOMIS", "",          "",          "s",      "lfI",   

"IANCIOSE",      "IANÈIOSE", "",          "",          "s",      "lfW",   


// ------- veikiamasis ivardziuotinis busimojo laiko dalyvis, vyr. gimine
// dirbsiantysis

"IANTYSIS",    "IANTYSIS",    "",          "",          "s",      "elmv",   

"IANCIOJO",      "IANÈIOJO", "",          "",          "s",      "elmk",   

"IANCIAJAM",      "IANÈIAJAM", "",          "",          "s",      "elmn",   

"IANTIJI",     "IANTÁJÁ", "",          "",          "s",      "elmg",   

"IANCIUOJU",      "IANÈIUOJU", "",          "",          "s",      "elmi",   

"IANCIAJAM",      "IANÈIAJAM", "",          "",          "s",      "elmw",   
"IANCIAJAME",      "IANÈIAJAME", "",          "",          "s",      "elmw",   

"IANTYSIS",    "IANTYSIS",    "",          "",          "s",      "elms",   

"IANTIEJI",    "IANTIEJI",    "",          "",          "s",      "elmV",   

"IANCIUJU",      "IANÈIØJØ", "",          "",          "s",      "elmK",   

"IANTIESIEM",  "IANTIESIEM",  "",          "",          "s",      "elmN",   
"IANTIESIEMS", "IANTIESIEMS", "",          "",          "s",      "elmN",   

"IANCIUOSIUS",      "IANÈIUOSIUS", "",          "",          "s",      "elmG",   

"IANCIAISIAIS",      "IANÈIAISIAIS", "",          "",          "s",      "elmI",   

"IANCIUOSIUOS",      "IANÈIUOSIUOS", "",          "",          "s",      "elmW",   
"IANCIUOSIUOSE",      "IANÈIUOSIUOSE", "",          "",          "s",      "elmW",   


// ------- veikiamasis ivardziuotinis busimojo laiko dalyvis, mot. gimimine
// dirbsiancioji

"IANCIOJI",      "IANÈIOJI", "",          "",          "s",      "elfv",   

"IANCIOSIOS",      "IANÈIOSIOS", "",          "",          "s",      "elfk",   

"IANCIAJAI",      "IANÈIAJAI", "",          "",          "s",      "elfn",   

"IANCIAJA",      "IANÈIÀJÀ", "",          "",          "s",      "elfg",   

"IANCIAJA",      "IANÈIÀJA", "",          "",          "s",      "elfi",   

"IANCIOJOJ",      "IANÈIOJOJ", "",          "",          "s",      "elfw",   
"IANCIOJOJE",      "IANÈIOJOJE", "",          "",          "s",      "elfw",   

"IANCIOJI",      "IANÈIOJI", "",          "",          "s",      "elfs",   

"IANCIOSIOS",      "IANÈIOSIOS", "",          "",          "s",      "elfV",   

"IANCIUJU",      "IANÈIØJØ", "",          "",          "s",      "elfK",   

"IANCIOSIOM",      "IANÈIOSIOM", "",          "",          "s",      "elfN",   
"IANCIOSIOMS",      "IANÈIOSIOMS", "",          "",          "s",      "elfN",   

"IANCIASIAS",      "IANÈIÀSIAS", "",          "",          "s",      "elfG",   

"IANCIOSIOM",      "IANÈIOSIOM", "",          "",          "s",      "elfI",   
"IANCIOSIOMIS",      "IANÈIOSIOMIS", "",          "",          "s",      "elfI",   

"IANCIOSIOSE",      "IANÈIOSIOSE", "",          "",          "s",      "elfW",   


// ------- neveikiamasis esamojo laiko dalyvis, vyr. gimine
// suprantamas, keliamas, jauciamas, snaudziamas, tylimas, sakomas
// -imas pjaunasi su jungimas, ejimas..., arimas, Rimas, ... !!!

"AMAS",        "AMAS",        "",          "",          "q",      "cmv",   
"IAMAS",       "IAMAS",       "",          "",          "q",      "cmv",   
"CIAMAS",      "ÈIAMAS", "T",         "T",         "q",      "cmv",   
"DZIAMAS",      "DÞIAMAS", "D",         "D",         "q",      "cmv",   
// "IMAS",     "IMAS",        "",          "",          "q",      "cmv",   
"OMAS",        "OMAS",        "",          "",          "q",      "cmv",   
".ADOMAS",     ".ADOMAS",     "ADOM",      "ADOM",          "q",      "cmv",   
"ONOMAS",      "ONOMAS",      "ONOM",      "ONOM",          "q",      "cmv",   // ekonomas, agronomas

"AMO",         "AMO",         "",          "",          "q",      "cmk",   
"IAMO",        "IAMO",        "",          "",          "q",      "cmk",   
"CIAMO",       "ÈIAMO",  "T",         "T",         "q",      "cmk",   
"DZIAMO",      "DÞIAMO", "D",         "D",         "q",      "cmk",   
// "IMO",      "IMO",         "",          "",          "q",      "cmv",   
"OMO",         "OMO",         "",          "",          "q",      "cmv",   

"AMAM",        "AMAM",        "",          "",          "q",      "cmn",   
"IAMAM",       "IAMAM",       "",          "",          "q",      "cmn",   
"CIAMAM",      "ÈIAMAM", "T",         "T",         "q",      "cmn",   
"DZIAMAM",      "DÞIAMAM", "D",         "D",         "q",      "cmn",   
"IMAM",        "IMAM",        "",          "",          "q",      "cmn",   
"OMAM",        "OMAM",        "",          "",          "q",      "cmn",   

"AMA",         "AMÀ",     "",          "",          "q",      "cmg",   
"IAMA",        "IAMÀ",    "",          "",          "q",      "cmg",   
"CIAMA",       "ÈIAMÀ", "T",         "T",         "q",      "cmg",   
"DZIAMA",      "DÞIAMÀ", "D",         "D",         "q",      "cmg",   
// "IMA",      "IMÀ",     "",          "",          "q",      "cmg",   
"OMA",         "OMÀ",     "",          "",          "q",      "cmg",   

"AMU",         "AMU",         "",          "",          "q",      "cmi",   
"IAMU",        "IAMU",        "",          "",          "q",      "cmi",   
"CIAMU",       "ÈIAMU",  "T",         "T",         "q",      "cmi",   
"DZIAMU",      "DÞIAMU", "D",         "D",         "q",      "cmi",   
// "IMU",      "IMU",         "",          "",          "q",      "cmi",   
"OMU",         "OMU",         "",          "",          "q",      "cmi",   

"AMAM",        "AMAM",        "",          "",          "q",      "cmw",   
"AMAME",       "AMAME",       "",          "",          "q",      "cmw",   
"IAMAM",       "IAMAM",       "",          "",          "q",      "cmw",   
"IAMAME",      "IAMAME",      "",          "",          "q",      "cmw",   
"CIAMAM",      "ÈIAMAM", "T",         "T",         "q",      "cmw",   
"CIAMAME",      "ÈIAMAME", "T",         "T",         "q",      "cmw",   
"DZIAMAM",      "DÞIAMAM", "D",         "D",         "q",      "cmw",   
"DZIAMAME",      "DÞIAMAME", "D",         "D",         "q",      "cmw",   
"IMAM",        "IMAM",        "",          "",          "q",      "cmw",   
"IMAME",       "IMAME",       "",          "",          "q",      "cmw",   
"OMAM",        "OMAM",        "",          "",          "q",      "cmw",   
"OMAME",       "OMAME",       "",          "",          "q",      "cmw",   

"AMAS",        "AMAS",        "",          "",          "q",      "cms",   
"IAMAS",       "IAMAS",       "",          "",          "q",      "cms",   
"CIAMAS",      "ÈIAMAS", "T",         "T",         "q",      "cms",   
"DZIAMAS",      "DÞIAMAS", "D",         "D",         "q",      "cms",   
// "IMAS",     "IMAS",        "",          "",          "q",      "cms",   
"OMAS",        "OMAS",        "",          "",          "q",      "cms",   

"AMI",         "AMI",         "",          "",          "q",      "cmV",   
"IAMI",        "IAMI",        "",          "",          "q",      "cmV",   
"CIAMI",       "ÈIAMI",  "T",         "T",         "q",      "cmV",   
"DZIAMI",      "DÞIAMI", "D",         "D",         "q",      "cmV",   
"IMI",         "IMI",         "",          "",          "q",      "cmV",   
"OMI",         "OMI",         "",          "",          "q",      "cmV",   

"AMU",         "AMØ",     "",          "",          "q",      "cmK",   
"IAMU",        "IAMØ",    "",          "",          "q",      "cmK",   
"CIAMU",       "ÈIAMØ", "T",         "T",         "q",      "cmK",   
"DZIAMU",      "DÞIAMØ", "D",         "D",         "q",      "cmK",   
// "IMU",      "IMØ",     "",          "",          "q",      "cmK",   
"OMU",         "OMØ",     "",          "",          "q",      "cmK",   

"AMIEM",       "AMIEM",       "",          "",          "q",      "cmN",   
"AMIEMS",      "AMIEMS",      "",          "",          "q",      "cmN",   
"IAMIEM",      "IAMIEM",      "",          "",          "q",      "cmN",   
"IAMIEMS",     "IAMIEMS",     "",          "",          "q",      "cmN",   
"CIAMIEM",      "ÈIAMIEM", "T",         "T",         "q",      "cmN",   
"CIAMIEMS",      "ÈIAMIEMS", "T",         "T",         "q",      "cmN",   
"DZIAMIEM",      "DÞIAMIEM", "D",         "D",         "q",      "cmN",   
"DZIAMIEMS",      "DÞIAMIEMS", "D",         "D",         "q",      "cmN",   
"IMIEM",       "IMIEM",       "",          "",          "q",      "cmN",   
"IMIEMS",      "IMIEMS",      "",          "",          "q",      "cmN",   
"OMIEM",       "OMIEM",       "",          "",          "q",      "cmN",   
"OMIEMS",      "OMIEMS",      "",          "",          "q",      "cmN",   

"AMUS",        "AMUS",        "",          "",          "q",      "cmG",   
"IAMUS",       "IAMUS",       "",          "",          "q",      "cmG",   
"CIAMUS",      "ÈIAMUS", "T",         "T",         "q",      "cmG",   
"DZIAMUS",      "DÞIAMUS", "D",         "D",         "q",      "cmG",   
// "IMUS",     "IMUS",        "",          "",          "q",      "cmG",   
"OMUS",        "OMUS",        "",          "",          "q",      "cmG",   

"AMAIS",       "AMAIS",       "",          "",          "q",      "cmI",   
"IAMAIS",      "IAMAIS",      "",          "",          "q",      "cmI",   
"CIAMAIS",      "ÈIAMAIS", "T",         "T",         "q",      "cmI",   
"DZIAMAIS",      "DÞIAMAIS", "D",         "D",         "q",      "cmI",   
// "IMAIS",    "IMAIS",       "",          "",          "q",      "cmI",   
"OMAIS",       "OMAIS",       "",          "",          "q",      "cmI",   

"AMUOS",       "AMUOS",       "",          "",          "q",      "cmW",   
"AMUOSE",      "AMUOSE",      "",          "",          "q",      "cmW",   
"IAMUOS",      "IAMUOS",      "",          "",          "q",      "cmW",   
"IAMUOSE",     "IAMUOSE",     "",          "",          "q",      "cmW",   
"CIAMUOS",      "ÈIAMUOS", "T",         "T",         "q",      "cmW",   
"CIAMUOSE",      "ÈIAMUOSE", "T",         "T",         "q",      "cmW",   
"DZIAMUOS",      "DÞIAMUOS", "D",         "D",         "q",      "cmW",   
"DZIAMUOSE",      "DÞIAMUOSE", "D",         "D",         "q",      "cmW",   
// "IMUOS",    "IMUOS",       "",          "",          "q",      "cmW",   
// "IMUOSE",   "IMUOSE",      "",          "",          "q",      "cmW",   
"OMUOS",       "OMUOS",       "",          "",          "q",      "cmW",   
"OMUOSE",      "OMUOSE",      "",          "",          "q",      "cmW",   


// ------- neveikiamasis esamojo laiko dalyvis, mot. gimine
// suprantama, keliama, jauciama, snaudziama, tylima, sakoma
// -imas pjaunasi su jungimas, ejimas..., arimas, Rimas, ... !!!

"AMA",         "AMA",         "",          "",          "q",      "cfv",   
"IAMA",        "IAMA",        "",          "",          "q",      "cfv",   
"CIAMA",       "ÈIAMA",  "T",         "T",         "q",      "cfv",   
"DZIAMA",      "DÞIAMA", "D",         "D",         "q",      "cfv",   
// "IMA",      "IMA",         "",          "",          "q",      "cfv",   
"OMA",         "OMA",         "",          "",          "q",      "cfv",   

"AMOS",        "AMOS",        "",          "",          "q",      "cfk",   
"IAMOS",       "IAMOS",       "",          "",          "q",      "cfk",   
"CIAMOS",      "ÈIAMOS", "T",         "T",         "q",      "cfk",   
"DZIAMOS",      "DÞIAMOS", "D",         "D",         "q",      "cfk",   
// "IMOS",     "IMOS",        "",          "",          "q",      "cfk",   
"OMOS",        "OMOS",        "",          "",          "q",      "cfk",   

"AMAI",        "AMAI",        "",          "",          "q",      "cfn",   
"IAMAI",       "IAMAI",       "",          "",          "q",      "cfn",   
"CIAMAI",      "ÈIAMAI", "T",         "T",         "q",      "cfn",   
"DZIAMAI",      "DÞIAMAI", "D",         "D",         "q",      "cfn",   
// "IMAI",     "IMAI",        "",          "",          "q",      "cfn",   
"OMAI",        "OMAI",        "",          "",          "q",      "cfn",   

"AMA",         "AMÀ",     "",          "",          "q",      "cfg",   
"IAMA",        "IAMÀ",    "",          "",          "q",      "cfg",   
"CIAMA",       "ÈIAMÀ", "T",         "T",         "q",      "cfg",   
"DZIAMA",      "DÞIAMÀ", "D",         "D",         "q",      "cfg",   
// "IMA",      "IMÀ",     "",          "",          "q",      "cfg",   
"OMA",         "OMÀ",     "",          "",          "q",      "cfg",   

"AMA",         "AMA",         "",          "",          "q",      "cfi",   
"IAMA",        "IAMA",        "",          "",          "q",      "cfi",   
"CIAMA",       "ÈIAMA",  "T",         "T",         "q",      "cfi",   
"DZIAMA",      "DÞIAMA", "D",         "D",         "q",      "cfi",   
// "IMA",      "IMA",         "",          "",          "q",      "cfi",   
"OMA",         "OMA",         "",          "",          "q",      "cfi",   

// "AMO",      "AMO",         "",          "",          "q",      "cfw",   // tarm.
"AMOJ",        "AMOJ",        "",          "",          "q",      "cfw",   
"AMOJE",       "AMOJE",       "",          "",          "q",      "cfw",   
// "IAMO",     "IAMO",        "",          "",          "q",      "cfw",   // tarm.
"IAMOJ",       "IAMOJ",       "",          "",          "q",      "cfw",   
"IAMOJE",      "IAMOJE",      "",          "",          "q",      "cfw",   
// "CIAMO",      "ÈIAMO",  "T",         "T",         "q",      "cfw",   // tarm.
"CIAMOJ",      "ÈIAMOJ", "T",         "T",         "q",      "cfw",   
"CIAMOJE",      "ÈIAMOJE", "T",         "T",         "q",      "cfw",   
// "DZIAMO",      "DÞIAMO", "D",         "D",         "q",      "cfw",   // tarm.
"DZIAMOJ",      "DÞIAMOJ", "D",         "D",         "q",      "cfw",   
"DZIAMOJE",      "DÞIAMOJE", "D",         "D",         "q",      "cfw",   
// "IMO",      "IMO",         "",          "",          "q",      "cfw",   // tarm.
// "IMOJ",     "IMOJ",        "",          "",          "q",      "cfw",   
// "IMOJE",    "IMOJE",       "",          "",          "q",      "cfw",   
// "OMO",      "OMO",         "",          "",          "q",      "cfw",   // tarm.
"OMOJ",        "OMOJ",        "",          "",          "q",      "cfw",   
"OMOJE",       "OMOJE",       "",          "",          "q",      "cfw",   

"AMA",         "AMA",         "",          "",          "q",      "cfs",   
"IAMA",        "IAMA",        "",          "",          "q",      "cfs",   
"CIAMA",       "ÈIAMA",  "T",         "T",         "q",      "cfs",   
"DZIAMA",      "DÞIAMA", "D",         "D",         "q",      "cfs",   
// "IMA",      "IMA",         "",          "",          "q",      "cfs",   
"OMA",         "OMA",         "",          "",          "q",      "cfs",   

"AMOS",        "AMOS",        "",          "",          "q",      "cfV",   
"IAMOS",       "IAMOS",       "",          "",          "q",      "cfV",   
"CIAMOS",      "ÈIAMOS", "T",         "T",         "q",      "cfV",   
"DZIAMOS",      "DÞIAMOS", "D",         "D",         "q",      "cfV",   
// "IMOS",     "IMOS",        "",          "",          "q",      "cfV",   
"OMOS",        "OMOS",        "",          "",          "q",      "cfV",   

"AMU",         "AMØ",     "",          "",          "q",      "cfK",   
"IAMU",        "IAMØ",    "",          "",          "q",      "cfK",   
"CIAMU",       "ÈIAMØ", "T",         "T",         "q",      "cfK",   
"DZIAMU",      "DÞIAMØ", "D",         "D",         "q",      "cfK",   
// "IMU",      "IMØ",     "",          "",          "q",      "cfK",   
"OMU",         "OMØ",     "",          "",          "q",      "cfK",   

"AMOM",        "AMOM",        "",          "",          "q",      "cfN",   
"AMOMS",       "AMOMS",       "",          "",          "q",      "cfN",   
"IAMOM",       "IAMOM",       "",          "",          "q",      "cfN",   
"IAMOMS",      "IAMOMS",      "",          "",          "q",      "cfN",   
"CIAMOM",      "ÈIAMOM", "T",         "T",         "q",      "cfN",   
"CIAMOMS",      "ÈIAMOMS", "T",         "T",         "q",      "cfN",   
"DZIAMOM",      "DÞIAMOM", "D",         "D",         "q",      "cfN",   
"DZIAMOMS",      "DÞIAMOMS", "D",         "D",         "q",      "cfN",   
// "IMOM",     "IMOM",        "",          "",          "q",      "cfN",   
// "IMOMS",    "IMOMS",       "",          "",          "q",      "cfN",   
"OMOM",        "OMOM",        "",          "",          "q",      "cfN",   
"OMOMS",       "OMOMS",       "",          "",          "q",      "cfN",   

"AMAS",        "AMAS",        "",          "",          "q",      "cfG",   
"IAMAS",       "IAMAS",       "",          "",          "q",      "cfG",   
"CIAMAS",      "ÈIAMAS", "T",         "T",         "q",      "cfG",   
"DZIAMAS",      "DÞIAMAS", "D",         "D",         "q",      "cfG",   
// "IMAS",     "IMAS",        "",          "",          "q",      "cfG",   
"OMAS",        "OMAS",        "",          "",          "q",      "cfG",   

"AMOM",        "AMOM",        "",          "",          "q",      "cfI",   
"AMOMIS",      "AMOMIS",      "",          "",          "q",      "cfI",   
"IAMOM",       "IAMOM",       "",          "",          "q",      "cfI",   
"IAMOMIS",     "IAMOMIS",     "",          "",          "q",      "cfI",   
"CIAMOM",      "ÈIAMOM", "T",         "T",         "q",      "cfI",   
"CIAMOMIS",      "ÈIAMOMIS", "T",         "T",         "q",      "cfI",   
"DZIAMOM",      "DÞIAMOM", "D",         "D",         "q",      "cfI",   
"DZIAMOMIS",      "DÞIAMOMIS", "D",         "D",         "q",      "cfI",   
// "IMOM",     "IMOM",        "",          "",          "q",      "cfI",   
// "IMOMIS",   "IMOMIS",      "",          "",          "q",      "cfI",   
"OMOM",        "OMOM",        "",          "",          "q",      "cfI",   
"OMOMIS",      "OMOMIS",      "",          "",          "q",      "cfI",   

"AMOSE",       "AMOSE",       "",          "",          "q",      "cfW",   
"IAMOSE",      "IAMOSE",      "",          "",          "q",      "cfW",   
"CIAMOSE",      "ÈIAMOSE", "T",         "T",         "q",      "cfW",   
"DZIAMOSE",      "DÞIAMOSE", "D",         "D",         "q",      "cfW",   
// "IMOSE",    "IMOSE",       "",          "",          "q",      "cfW",   
"OMOSE",       "OMOSE",       "",          "",          "q",      "cfW",   


// ------- neveikiamasis esamojo laiko dalyvis, niek. gimine
// suprantama, keliama, jauciama, snaudziama, tylima, sakoma

"AMA",         "AMA",         "",          "",          "q",      "co",   
"IAMA",        "IAMA",        "",          "",          "q",      "co",   
"CIAMA",       "ÈIAMA",  "T",         "T",         "q",      "co",   
"DZIAMA",      "DÞIAMA", "D",         "D",         "q",      "co",   
// "IMA",      "IMA",         "",          "",          "q",      "co",   
"OMA",         "OMA",         "",          "",          "q",      "co",   


// ------- neveikiamasis ivardziuotinis esamojo laiko dalyvis, vyr. gimine
// keliamasis, mokomasis

"AMASIS",      "AMASIS",      "",          "",          "q",      "ecmv",   
"IAMASIS",     "IAMASIS",     "",          "",          "q",      "ecmv",   
"CIAMASIS",      "ÈIAMASIS", "T",         "T",         "q",      "ecmv",   
"DZIAMASIS",      "DÞIAMASIS", "D",         "D",         "q",      "ecmv",   
"IMASIS",      "IMASIS",      "",          "",          "q",      "ecmv",   
"OMASIS",      "OMASIS",      "",          "",          "q",      "ecmv",   

"AMOJO",       "AMOJO",       "",          "",          "q",      "ecmk",   
"IAMOJO",      "IAMOJO",      "",          "",          "q",      "ecmk",   
"CIAMOJO",      "ÈIAMOJO", "T",         "T",         "q",      "ecmk",   
"DZIAMOJO",      "DÞIAMOJO", "D",         "D",         "q",      "ecmk",   
"IMOJO",       "IMOJO",       "",          "",          "q",      "ecmk",   
"OMOJO",       "OMOJO",       "",          "",          "q",      "ecmk",   

"AMAJAM",      "AMAJAM",      "",          "",          "q",      "ecmn",   
"IAMAJAM",     "IAMAJAM",     "",          "",          "q",      "ecmn",   
"CIAMAJAM",      "ÈIAMAJAM", "T",         "T",         "q",      "ecmn",   
"DZIAMAJAM",      "DÞIAMAJAM", "D",         "D",         "q",      "ecmn",   
"IMAJAM",      "IMAJAM",      "",          "",          "q",      "ecmn",   
"OMAJAM",      "OMAJAM",      "",          "",          "q",      "ecmn",   

"AMAJI",       "AMÀJÁ", "",          "",          "q",      "ecmg",   
"IAMAJI",      "IAMÀJÁ", "",          "",          "q",      "ecmg",   
"CIAMAJI",      "ÈIAMÀJÁ", "T",         "T",         "q",      "ecmg",   
"DZIAMAJI",      "DÞIAMÀJÁ", "D",         "D",         "q",      "ecmg",   
"IMAJI",       "IMÀJÁ", "",          "",          "q",      "ecmg",   
"OMAJI",       "OMÀJÁ", "",          "",          "q",      "ecmg",   

"AMUOJU",      "AMUOJU",      "",          "",          "q",      "ecmi",   
"IAMUOJU",     "IAMUOJU",     "",          "",          "q",      "ecmi",   
"CIAMUOJU",      "ÈIAMUOJU", "T",         "T",         "q",      "ecmi",   
"DZIAMUOJU",      "DÞIAMUOJU", "D",         "D",         "q",      "ecmi",   
"IMUOJU",      "IMUOJU",      "",          "",          "q",      "ecmi",   
"OMUOJU",      "OMUOJU",      "",          "",          "q",      "ecmi",   

"AMAJAM",      "AMAJAM",      "",          "",          "q",      "ecmw",   
"AMAJAME",     "AMAJAME",     "",          "",          "q",      "ecmw",   
"IAMAJAM",     "IAMAJAM",     "",          "",          "q",      "ecmw",   
"IAMAJAME",    "IAMAJAME",    "",          "",          "q",      "ecmw",   
"CIAMAJAM",      "ÈIAMAJAM", "T",         "T",         "q",      "ecmw",   
"CIAMAJAME",      "ÈIAMAJAME", "T",         "T",         "q",      "ecmw",   
"DZIAMAJAM",      "DÞIAMAJAM", "D",         "D",         "q",      "ecmw",   
"DZIAMAJAME",      "DÞIAMAJAME", "D",         "D",         "q",      "ecmw",   
"IMAJAM",      "IMAJAM",      "",          "",          "q",      "ecmw",   
"IMAJAME",     "IMAJAME",     "",          "",          "q",      "ecmw",   
"OMAJAM",      "OMAJAM",      "",          "",          "q",      "ecmw",   
"OMAJAME",     "OMAJAME",     "",          "",          "q",      "ecmw",   

"AMASIS",      "AMASIS",      "",          "",          "q",      "ecms",   
"IAMASIS",     "IAMASIS",     "",          "",          "q",      "ecms",   
"CIAMASIS",      "ÈIAMASIS", "T",         "T",         "q",      "ecms",   
"DZIAMASIS",      "DÞIAMASIS", "D",         "D",         "q",      "ecms",   
"IMASIS",      "IMASIS",      "",          "",          "q",      "ecms",   
"OMASIS",      "OMASIS",      "",          "",          "q",      "ecms",   

"AMIEJI",      "AMIEJI",      "",          "",          "q",      "ecmV",   
"IAMIEJI",     "IAMIEJI",     "",          "",          "q",      "ecmV",   
"CIAMIEJI",      "ÈIAMIEJI", "T",         "T",         "q",      "ecmV",   
"DZIAMIEJI",      "DÞIAMIEJI", "D",         "D",         "q",      "ecmV",   
"IMIEJI",      "IMIEJI",      "",          "",          "q",      "ecmV",   
"OMIEJI",      "OMIEJI",      "",          "",          "q",      "ecmV",   

"AMUJU",       "AMØJØ", "",          "",          "q",      "ecmK",   
"IAMUJU",      "IAMØJØ", "",          "",          "q",      "ecmK",   
"CIAMUJU",      "ÈIAMØJØ", "T",         "T",         "q",      "ecmK",   
"DZIAMUJU",      "DÞIAMØJØ", "D",         "D",         "q",      "ecmK",   
"IMUJU",         "IMØJØ", "",          "",          "q",      "ecmK",   
"OMUJU",         "OMØJØ", "",          "",          "q",      "ecmK",   

"AMIESIEM",    "AMIESIEM",    "",          "",          "q",      "ecmN",   
"AMIESIEMS",   "AMIESIEMS",   "",          "",          "q",      "ecmN",   
"IAMIESIEM",   "IAMIESIEM",   "",          "",          "q",      "ecmN",   
"IAMIESIEMS",  "IAMIESIEMS",  "",          "",          "q",      "ecmN",   
"CIAMIESIEM",      "ÈIAMIESIEM", "T",         "T",         "q",      "ecmN",   
"CIAMIESIEMS",      "ÈIAMIESIEMS", "T",         "T",         "q",      "ecmN",   
"DZIAMIESIEM",      "DÞIAMIESIEM", "D",         "D",         "q",      "ecmN",   
"DZIAMIESIEMS",      "DÞIAMIESIEMS", "D",         "D",         "q",      "ecmN",   
"IMIESIEM",    "IMIESIEM",    "",          "",          "q",      "ecmN",   
"IMIESIEMS",   "IMIESIEMS",   "",          "",          "q",      "ecmN",   
"OMIESIEM",    "OMIESIEM",    "",          "",          "q",      "ecmN",   
"OMIESIEMS",   "OMIESIEMS",   "",          "",          "q",      "ecmN",   

"AMUOSIUS",    "AMUOSIUS",    "",          "",          "q",      "ecmG",   
"IAMUOSIUS",   "IAMUOSIUS",   "",          "",          "q",      "ecmG",   
"CIAMUOSIUS",      "ÈIAMUOSIUS", "T",         "T",         "q",      "ecmG",   
"DZIAMUOSIUS",      "DÞIAMUOSIUS", "D",         "D",         "q",      "ecmG",   
"IMUOSIUS",    "IMUOSIUS",    "",          "",          "q",      "ecmG",   
"OMUOSIUS",    "OMUOSIUS",    "",          "",          "q",      "ecmG",   

"AMAISIAIS",   "AMAISIAIS",   "",          "",          "q",      "ecmI",   

"IAMAISIAIS",  "IAMAISIAIS",  "",          "",          "q",      "ecmI",   
"CIAMAISIAIS",      "ÈIAMAISIAIS", "T",         "T",         "q",      "ecmI",   
"DZIAMAISIAIS",      "DÞIAMAISIAIS", "D",         "D",         "q",      "ecmI",   
"IMAISIAIS",   "IMAISIAIS",   "",          "",          "q",      "ecmI",   
"OMAISIAIS",   "OMAISIAIS",   "",          "",          "q",      "ecmI",   

"AMUOSIUOS",   "AMUOSIUOS",   "",          "",          "q",      "ecmW",   
"AMUOSIUOSE",  "AMUOSIUOSE",  "",          "",          "q",      "ecmW",   
"IAMUOSIUOS",  "IAMUOSIUOS",  "",          "",          "q",      "ecmW",   
"IAMUOSIUOSE", "IAMUOSIUOSE", "",          "",          "q",      "ecmW",   
"CIAMUOSIUOS",      "ÈIAMUOSIUOS", "T",         "T",         "q",      "ecmW",   
"CIAMUOSIUOSE",      "ÈIAMUOSIUOSE", "T",         "T",         "q",      "ecmW",   
"DZIAMUOSIUOS",      "DÞIAMUOSIUOS", "D",         "D",         "q",      "ecmW",   
"DZIAMUOSIUOSE",      "DÞIAMUOSIUOSE", "D",         "D",         "q",      "ecmW",   
"IMUOSIUOS",   "IMUOSIUOS",   "",          "",          "q",      "ecmW",   
"IMUOSIUOSE",  "IMUOSIUOSE",  "",          "",          "q",      "ecmW",   
"OMUOSIUOS",   "OMUOSIUOS",   "",          "",          "q",      "ecmW",   
"OMUOSIUOSE",  "OMUOSIUOSE",  "",          "",          "q",      "ecmW",   


// ------- neveikiamasis ivardziuotinis esamojo laiko dalyvis, mot. gimine
// keliamoji

"AMOJI",       "AMOJI",       "",          "",          "q",      "ecfv",   
"IAMOJI",      "IAMOJI",      "",          "",          "q",      "ecfv",   
"CIAMOJI",      "ÈIAMOJI", "T",         "T",         "q",      "ecfv",   
"DZIAMOJI",      "DÞIAMOJI", "D",         "D",         "q",      "ecfv",   
"IMOJI",       "IMOJI",       "",          "",          "q",      "ecfv",   
"OMOJI",       "OMOJI",       "",          "",          "q",      "ecfv",   

"AMOSIOS",     "AMOSIOS",     "",          "",          "q",      "ecfk",   
"IAMOSIOS",    "IAMOSIOS",    "",          "",          "q",      "ecfk",   
"CIAMOSIOS",      "ÈIAMOSIOS", "T",         "T",         "q",      "ecfk",   
"DZIAMOSIOS",      "DÞIAMOSIOS", "D",         "D",         "q",      "ecfk",   
"IMOSIOS",     "IMOSIOS",     "",          "",          "q",      "ecfk",   
"OMOSIOS",     "OMOSIOS",     "",          "",          "q",      "ecfk",   

"AMAJAI",      "AMAJAI",      "",          "",          "q",      "ecfn",   
"IAMAJAI",     "IAMAJAI",     "",          "",          "q",      "ecfn",   
"CIAMAJAI",      "ÈIAMAJAI", "T",         "T",         "q",      "ecfn",   
"DZIAMAJAI",      "DÞIAMAJAI", "D",         "D",         "q",      "ecfn",   
"IMAJAI",      "IMAJAI",      "",          "",          "q",      "ecfn",   
"OMAJAI",      "OMAJAI",      "",          "",          "q",      "ecfn",   

"AMAJA",         "AMÀJÀ", "",          "",          "q",      "ecfg",   
"IAMAJA",         "IAMÀJÀ", "",          "",          "q",      "ecfg",   
"CIAMAJA",              "ÈIAMÀJÀ", "T",         "T",         "q",      "ecfg",   
"DZIAMAJA",              "DÞIAMÀJÀ", "D",         "D",         "q",      "ecfg",   
"IMAJA",         "IMÀJÀ", "",          "",          "q",      "ecfg",   
"OMAJA",         "OMÀJÀ", "",          "",          "q",      "ecfg",   

"AMAJA",       "AMÀJA",   "",          "",          "q",      "ecfi",   
"IAMAJA",      "IAMÀJA",  "",          "",          "q",      "ecfi",   
"CIAMAJA",          "ÈIAMÀJA", "T",         "T",         "q",      "ecfi",   
"DZIAMAJA",          "DÞIAMÀJA", "D",         "D",         "q",      "ecfi",   
"IMAJA",       "IMÀJA",   "",          "",          "q",      "ecfi",   
"OMAJA",       "OMÀJA",   "",          "",          "q",      "ecfi",   

// "AMOJO",    "AMOJO",       "",          "",          "q",      "ecfw",   // tarm.
"AMOJOJ",      "AMOJOJ",      "",          "",          "q",      "ecfw",   
"AMOJOJE",     "AMOJOJE",     "",          "",          "q",      "ecfw",   
// "IAMOJO",   "IAMOJO",      "",          "",          "q",      "ecfw",   // tarm.
"IAMOJOJ",     "IAMOJOJ",     "",          "",          "q",      "ecfw",   
"IAMOJOJE",    "IAMOJOJE",    "",          "",          "q",      "ecfw",   
// "CIAMOJO",      "ÈIAMOJO", "T",         "T",         "q",      "ecfw",   // tarm.
"CIAMOJOJ",      "ÈIAMOJOJ", "T",         "T",         "q",      "ecfw",   
"CIAMOJOJE",      "ÈIAMOJOJE", "T",         "T",         "q",      "ecfw",   
// "DZIAMOJO",      "DÞIAMOJO", "D",         "D",         "q",      "ecfw",   // tarm.
"DZIAMOJOJ",      "DÞIAMOJOJ", "D",         "D",         "q",      "ecfw",   
"DZIAMOJOJE",      "DÞIAMOJOJE", "D",         "D",         "q",      "ecfw",   
// "IMOJO",    "IMOJO",       "",          "",          "q",      "ecfw",   // tarm.
"IMOJOJ",      "IMOJOJ",      "",          "",          "q",      "ecfw",   
"IMOJOJE",     "IMOJOJE",     "",          "",          "q",      "ecfw",   
// "OMOJO",    "OMOJO",       "",          "",          "q",      "ecfw",   // tarm.
"OMOJOJ",      "OMOJOJ",      "",          "",          "q",      "ecfw",   
"OMOJOJE",     "OMOJOJE",     "",          "",          "q",      "ecfw",   

"AMOJI",       "AMOJI",       "",          "",          "q",      "ecfs",   
"IAMOJI",      "IAMOJI",      "",          "",          "q",      "ecfs",   
"CIAMOJI",      "ÈIAMOJI", "T",         "T",         "q",      "ecfs",   
"DZIAMOJI",      "DÞIAMOJI", "D",         "D",         "q",      "ecfs",   
"IMOJI",       "IMOJI",       "",          "",          "q",      "ecfs",   
"OMOJI",       "OMOJI",       "",          "",          "q",      "ecfs",   

"AMOSIOS",     "AMOSIOS",     "",          "",          "q",      "ecfV",   
"IAMOSIOS",    "IAMOSIOS",    "",          "",          "q",      "ecfV",   
"CIAMOSIOS",      "ÈIAMOSIOS", "T",         "T",         "q",      "ecfV",   
"DZIAMOSIOS",      "DÞIAMOSIOS", "D",         "D",         "q",      "ecfV",   
"IMOSIOS",     "IMOSIOS",     "",          "",          "q",      "ecfV",   
"OMOSIOS",     "OMOSIOS",     "",          "",          "q",      "ecfV",   

"AMUJU",         "AMØJØ", "",          "",          "q",      "ecfK",   
"IAMUJU",         "IAMØJØ", "",          "",          "q",      "ecfK",   

"CIAMUJU",              "ÈIAMØJØ", "T",         "T",         "q",      "ecfK",   
"DZIAMUJU",              "DÞIAMØJØ", "D",         "D",         "q",      "ecfK",   
"IMUJU",         "IMØJØ", "",          "",          "q",      "ecfK",   
"OMUJU",         "OMØJØ", "",          "",          "q",      "ecfK",   

"AMOSIOM",     "AMOSIOM",     "",          "",          "q",      "ecfN",   
"AMOSIOMS",    "AMOSIOMS",    "",          "",          "q",      "ecfN",   
"IAMOSIOM",    "IAMOSIOM",    "",          "",          "q",      "ecfN",   
"IAMOSIOMS",   "IAMOSIOMS",   "",          "",          "q",      "ecfN",   
"CIAMOSIOM",      "ÈIAMOSIOM", "T",         "T",         "q",      "ecfN",   
"CIAMOSIOMS",      "ÈIAMOSIOMS", "T",         "T",         "q",      "ecfN",   
"DZIAMOSIOM",      "DÞIAMOSIOM", "D",         "D",         "q",      "ecfN",   
"DZIAMOSIOMS",      "DÞIAMOSIOMS", "D",         "D",         "q",      "ecfN",   
"IMOSIOM",     "IMOSIOM",     "",          "",          "q",      "ecfN",   
"IMOSIOMS",    "IMOSIOMS",    "",          "",          "q",      "ecfN",   
"OMOSIOM",     "OMOSIOM",     "",          "",          "q",      "ecfN",   
"OMOSIOMS",    "OMOSIOMS",    "",          "",          "q",      "ecfN",   

"AMASIAS",     "AMÀSIAS", "",          "",          "q",      "ecfG",   
"IAMASIAS",     "IAMÀSIAS", "",          "",          "q",      "ecfG",   
"CIAMASIAS",          "ÈIAMÀSIAS", "T",         "T",         "q",      "ecfG",   
"DZIAMASIAS",          "DÞIAMÀSIAS", "D",         "D",         "q",      "ecfG",   
"IMASIAS",     "IMÀSIAS", "",          "",          "q",      "ecfG",   
"OMASIAS",     "OMÀSIAS", "",          "",          "q",      "ecfG",   

"AMOSIOM",     "AMOSIOM",     "",          "",          "q",      "ecfI",   
"AMOSIOMIS",   "AMOSIOMIS",   "",          "",          "q",      "ecfI",   
"IAMOSIOM",    "IAMOSIOM",    "",          "",          "q",      "ecfI",   
"IAMOSIOMIS",  "IAMOSIOMIS",  "",          "",          "q",      "ecfI",   
"CIAMOSIOM",      "ÈIAMOSIOM", "T",         "T",         "q",      "ecfI",   
"CIAMOSIOMIS",      "ÈIAMOSIOMIS", "T",         "T",         "q",      "ecfI",   
"DZIAMOSIOM",      "DÞIAMOSIOM", "D",         "D",         "q",      "ecfI",   
"DZIAMOSIOMIS",      "DÞIAMOSIOMIS", "D",         "D",         "q",      "ecfI",   
"IMOSIOM",     "IMOSIOM",     "",          "",          "q",      "ecfI",   
"IMOSIOMIS",   "IMOSIOMIS",   "",          "",          "q",      "ecfI",   
"OMOSIOM",     "OMOSIOM",     "",          "",          "q",      "ecfI",   
"OMOSIOMIS",   "OMOSIOMIS",   "",          "",          "q",      "ecfI",   

"AMOSIOSE",    "AMOSIOSE",    "",          "",          "q",      "ecfW",   
"IAMOSIOSE",   "IAMOSIOSE",   "",          "",          "q",      "ecfW",   
"CIAMOSIOSE",      "ÈIAMOSIOSE", "T",         "T",         "q",      "ecfW",   
"DZIAMOSIOSE",      "DÞIAMOSIOSE", "D",         "D",         "q",      "ecfW",   
"IMOSIOSE",    "IMOSIOSE",    "",          "",          "q",      "ecfW",   
"OMOSIOSE",    "OMOSIOSE",    "",          "",          "q",      "ecfW",   


// ------- neveikiamasis esamojo laiko dalyvis, vyr. gimine, aukstesnysis laipsnis
// suprantamesnis

"AMESNIS",     "AMESNIS",     "",          "",          "q",      "1cmv",   
"IAMESNIS",    "IAMESNIS",    "",          "",          "q",      "1cmv",   
"CIAMESNIS",      "ÈIAMESNIS", "T",         "T",         "q",      "1cmv",   
"DZIAMESNIS",      "DÞIAMESNIS", "D",         "D",         "q",      "1cmv",   
"IMESNIS",     "IMESNIS",     "",          "",          "q",      "1cmv",   
"OMESNIS",     "OMESNIS",     "",          "",          "q",      "1cmv",   

"AMESNIO",     "AMESNIO",     "",          "",          "q",      "1cmk",   
"IAMESNIO",    "IAMESNIO",    "",          "",          "q",      "1cmk",   
"CIAMESNIO",      "ÈIAMESNIO", "T",         "T",         "q",      "1cmk",   
"DZIAMESNIO",      "DÞIAMESNIO", "D",         "D",         "q",      "1cmk",   
"IMESNIO",     "IMESNIO",     "",          "",          "q",      "1cmv",   
"OMESNIO",     "OMESNIO",     "",          "",          "q",      "1cmv",   

"AMESNIAM",    "AMESNIAM",    "",          "",          "q",      "1cmn",   
"IAMESNIAM",   "IAMESNIAM",   "",          "",          "q",      "1cmn",   
"CIAMESNIAM",      "ÈIAMESNIAM", "T",         "T",         "q",      "1cmn",   
"DZIAMESNIAM",      "DÞIAMESNIAM", "D",         "D",         "q",      "1cmn",   
"IMESNIAM",    "IMESNIAM",    "",          "",          "q",      "1cmn",   
"OMESNIAM",    "OMESNIAM",    "",          "",          "q",      "1cmn",   

"AMESNI",      "AMESNÁ",  "",          "",          "q",      "1cmg",   
"IAMESNI",     "IAMESNÁ", "",          "",          "q",      "1cmg",   
"CIAMESNI",          "ÈIAMESNÁ", "T",         "T",         "q",      "1cmg",   
"DZIAMESNI",          "DÞIAMESNÁ", "D",         "D",         "q",      "1cmg",   
"IMESNI",      "IMESNÁ",  "",          "",          "q",      "1cmg",   
"OMESNI",      "OMESNÁ",  "",          "",          "q",      "1cmg",   

"AMESNIU",     "AMESNIU",     "",          "",          "q",      "1cmi",   
"IAMESNIU",    "IAMESNIU",    "",          "",          "q",      "1cmi",   
"CIAMESNIU",      "ÈIAMESNIU", "T",         "T",         "q",      "1cmi",   
"DZIAMESNIU",      "DÞIAMESNIU", "D",         "D",         "q",      "1cmi",   
"IMESNIU",     "IMESNIU",     "",          "",          "q",      "1cmi",   
"OMESNIU",     "OMESNIU",     "",          "",          "q",      "1cmi",   

"AMESNIAM",    "AMESNIAM",    "",          "",          "q",      "1cmw",   
"AMESNIAME",   "AMESNIAME",   "",          "",          "q",      "1cmw",   
"IAMESNIAM",   "IAMESNIAM",   "",          "",          "q",      "1cmw",   
"IAMESNIAME",  "IAMESNIAME",  "",          "",          "q",      "1cmw",   
"CIAMESNIAM",      "ÈIAMESNIAM", "T",         "T",         "q",      "1cmw",   
"CIAMESNIAME",      "ÈIAMESNIAME", "T",         "T",         "q",      "1cmw",   
"DZIAMESNIAM",      "DÞIAMESNIAM", "D",         "D",         "q",      "1cmw",   
"DZIAMESNIAME",      "DÞIAMESNIAME", "D",         "D",         "q",      "1cmw",   
"IMESNIAM",    "IMESNIAM",    "",          "",          "q",      "1cmw",   
"IMESNIAME",   "IMESNIAME",   "",          "",          "q",      "1cmw",   
"OMESNIAM",    "OMESNIAM",    "",          "",          "q",      "1cmw",   
"OMESNIAME",   "OMESNIAME",   "",          "",          "q",      "1cmw",   

"AMESNIS",     "AMESNIS",     "",          "",          "q",      "1cms",   
"IAMESNIS",    "IAMESNIS",    "",          "",          "q",      "1cms",   
"CIAMESNIS",      "ÈIAMESNIS", "T",         "T",         "q",      "1cms",   
"DZIAMESNIS",      "DÞIAMESNIS", "D",         "D",         "q",      "1cms",   
"IMESNIS",     "IMESNIS",     "",          "",          "q",      "1cms",   
"OMESNIS",     "OMESNIS",     "",          "",          "q",      "1cms",   

"AMESNI",      "AMESNI",      "",          "",          "q",      "1cmV",   
"IAMESNI",     "IAMESNI",     "",          "",          "q",      "1cmV",   
"CIAMESNI",      "ÈIAMESNI", "T",         "T",         "q",      "1cmV",   
"DZIAMESNI",      "DÞIAMESNI", "D",         "D",         "q",      "1cmV",   
"IMESNI",      "IMESNI",      "",          "",          "q",      "1cmV",   
"OMESNI",      "OMESNI",      "",          "",          "q",      "1cmV",   

"AMESNIU",     "AMESNIØ", "",          "",          "q",      "1cmK",   
"IAMESNIU",     "IAMESNIØ", "",          "",          "q",      "1cmK",   
"CIAMESNIU",          "ÈIAMESNIØ", "T",         "T",         "q",      "1cmK",   
"DZIAMESNIU",          "DÞIAMESNIØ", "D",         "D",         "q",      "1cmK",   
"IMESNIU",     "IMESNIØ", "",          "",          "q",      "1cmK",   
"OMESNIU",     "OMESNIØ", "",          "",          "q",      "1cmK",   

"AMESNIEM",    "AMESNIEM",    "",          "",          "q",      "1cmN",   
"AMESNIEMS",   "AMESNIEMS",   "",          "",          "q",      "1cmN",   
"IAMESNIEM",   "IAMESNIEM",   "",          "",          "q",      "1cmN",   
"IAMESNIEMS",  "IAMESNIEMS",  "",          "",          "q",      "1cmN",   
"CIAMESNIEM",      "ÈIAMESNIEM", "T",         "T",         "q",      "1cmN",   
"CIAMESNIEMS",      "ÈIAMESNIEMS", "T",         "T",         "q",      "1cmN",   
"DZIAMESNIEM",      "DÞIAMESNIEM", "D",         "D",         "q",      "1cmN",   
"DZIAMESNIEMS",      "DÞIAMESNIEMS", "D",         "D",         "q",      "1cmN",   
"IMESNIEM",    "IMESNIEM",    "",          "",          "q",      "1cmN",   
"IMESNIEMS",   "IMESNIEMS",   "",          "",          "q",      "1cmN",   
"OMESNIEM",    "OMESNIEM",    "",          "",          "q",      "1cmN",   
"OMESNIEMS",   "OMESNIEMS",   "",          "",          "q",      "1cmN",   

"AMESNIUS",    "AMESNIUS",    "",          "",          "q",      "1cmG",   
"IAMESNIUS",   "IAMESNIUS",   "",          "",          "q",      "1cmG",   
"CIAMESNIUS",      "ÈIAMESNIUS", "T",         "T",         "q",      "1cmG",   
"DZIAMESNIUS",      "DÞIAMESNIUS", "D",         "D",         "q",      "1cmG",   
"IMESNIUS",    "IMESNIUS",    "",          "",          "q",      "1cmG",   
"OMESNIUS",    "OMESNIUS",    "",          "",          "q",      "1cmG",   

"AMESNIAIS",   "AMESNIAIS",   "",          "",          "q",      "1cmI",   
"IAMESNIAIS",  "IAMESNIAIS",  "",          "",          "q",      "1cmI",   
"CIAMESNIAIS",      "ÈIAMESNIAIS", "T",         "T",         "q",      "1cmI",   
"DZIAMESNIAIS",      "DÞIAMESNIAIS", "D",         "D",         "q",      "1cmI",   
"IMESNIAIS",   "IMESNIAIS",   "",          "",          "q",      "1cmI",   
"OMESNIAIS",   "OMESNIAIS",   "",          "",          "q",      "1cmI",   

"AMESNIUOS",   "AMESNIUOS",   "",          "",          "q",      "1cmW",   
"AMESNIUOSE",  "AMESNIUOSE",  "",          "",          "q",      "1cmW",   
"IAMESNIUOS",  "IAMESNIUOS",  "",          "",          "q",      "1cmW",   
"IAMESNIUOSE", "IAMESNIUOSE", "",          "",          "q",      "1cmW",   
"CIAMESNIUOS",      "ÈIAMESNIUOS", "T",         "T",         "q",      "1cmW",   
"CIAMESNIUOSE",      "ÈIAMESNIUOSE", "T",         "T",         "q",      "1cmW",   
"DZIAMESNIUOS",      "DÞIAMESNIUOS", "D",         "D",         "q",      "1cmW",   
"DZIAMESNIUOSE",      "DÞIAMESNIUOSE", "D",         "D",         "q",      "1cmW",   
"IMESNIUOS",   "IMESNIUOS",   "",          "",          "q",      "1cmW",   
"IMESNIUOSE",  "IMESNIUOSE",  "",          "",          "q",      "1cmW",   
"OMESNIUOS",   "OMESNIUOS",   "",          "",          "q",      "1cmW",   
"OMESNIUOSE",  "OMESNIUOSE",  "",          "",          "q",      "1cmW",   


// ------- neveikiamasis esamojo laiko dalyvis, mot. gimine, aukstesnysis laipsnis
// suprantamesne

"AMESNE",      "AMESNË",   "",          "",          "q",      "1cfv",   
"IAMESNE",     "IAMESNË",  "",          "",          "q",      "1cfv",   
"CIAMESNE",         "ÈIAMESNË", "T",         "T",         "q",      "1cfv",   
"DZIAMESNE",         "DÞIAMESNË", "D",         "D",         "q",      "1cfv",   
"IMESNE",      "IMESNË",   "",          "",          "q",      "1cfv",   
"OMESNE",      "OMESNË",   "",          "",          "q",      "1cfv",   

"AMESNES",     "AMESNËS",  "",          "",          "q",      "1cfk",   
"IAMESNES",    "IAMESNËS", "",          "",          "q",      "1cfk",   
"CIAMESNES",         "ÈIAMESNËS", "T",         "T",         "q",      "1cfk",   
"DZIAMESNES",         "DÞIAMESNËS", "D",         "D",         "q",      "1cfk",   
"IMESNES",     "IMESNËS",  "",          "",          "q",      "1cfk",   
"OMESNES",     "OMESNËS",  "",          "",          "q",      "1cfk",   

"AMESNEI",     "AMESNEI",     "",          "",          "q",      "1cfn",   

"IAMESNEI",    "IAMESNEI",    "",          "",          "q",      "1cfn",   
"CIAMESNEI",      "ÈIAMESNEI", "T",         "T",         "q",      "1cfn",   
"DZIAMESNEI",      "DÞIAMESNEI", "D",         "D",         "q",      "1cfn",   
"IMESNEI",     "IMESNEI",     "",          "",          "q",      "1cfn",   
"OMESNEI",     "OMESNEI",     "",          "",          "q",      "1cfn",   

"AMESNE",      "AMESNÆ",  "",          "",          "q",      "1cfg",   
"IAMESNE",     "IAMESNÆ", "",          "",          "q",      "1cfg",   
"CIAMESNE",          "ÈIAMESNÆ", "T",         "T",         "q",      "1cfg",   
"DZIAMESNE",          "DÞIAMESNÆ", "D",         "D",         "q",      "1cfg",   
"IMESNE",      "IMESNÆ",  "",          "",          "q",      "1cfg",   
"OMESNE",      "OMESNÆ",  "",          "",          "q",      "1cfg",   

"AMESNE",      "AMESNE",      "",          "",          "q",      "1cfi",   
"IAMESNE",     "IAMESNE",     "",          "",          "q",      "1cfi",   
"CIAMESNE",      "ÈIAMESNE", "T",         "T",         "q",      "1cfi",   
"DZIAMESNE",      "DÞIAMESNE", "D",         "D",         "q",      "1cfi",   
"IMESNE",      "IMESNE",      "",          "",          "q",      "1cfi",   
"OMESNE",      "OMESNE",      "",          "",          "q",      "1cfi",   

// "AMESNE",    "AMESNË",   "",          "",          "q",      "1cfw",   // tarm.
"AMESNEJ",     "AMESNËJ",  "",          "",          "q",      "1cfw",   
"AMESNEJE",    "AMESNËJE", "",          "",          "q",      "1cfw",   
// "IAMESNE",    "IAMESNË",  "",          "",          "q",      "1cfw",   // tarm.
"IAMESNEJ",    "IAMESNËJ", "",          "",          "q",      "1cfw",   
"IAMESNEJE",    "IAMESNËJE", "",          "",          "q",      "1cfw",   
// "CIAMESNE",         "ÈIAMESNË", "T",         "T",         "q",      "1cfw",   // tarm.
"CIAMESNEJ",         "ÈIAMESNËJ", "T",         "T",         "q",      "1cfw",   
"CIAMESNEJE",         "ÈIAMESNËJE", "T",         "T",         "q",      "1cfw",   
// "DZIAMESNE",         "DÞIAMESNË", "D",         "D",         "q",      "1cfw",   // tarm.
"DZIAMESNEJ",         "DÞIAMESNËJ", "D",         "D",         "q",      "1cfw",   
"DZIAMESNEJE",         "DÞIAMESNËJE", "D",         "D",         "q",      "1cfw",   
// "IMESNE",    "IMESNË",   "",          "",          "q",      "1cfw",   // tarm.
"IMESNEJ",     "IMESNËJ",  "",          "",          "q",      "1cfw",   
"IMESNEJE",    "IMESNËJE", "",          "",          "q",      "1cfw",   
// "OMESNE",    "OMESNË",   "",          "",          "q",      "1cfw",   // tarm.
"OMESNEJ",     "OMESNËJ",  "",          "",          "q",      "1cfw",   
"OMESNEJE",    "OMESNËJE", "",          "",          "q",      "1cfw",   

"AMESNE",      "AMESNE",      "",          "",          "q",      "1cfs",   
"IAMESNE",     "IAMESNE",     "",          "",          "q",      "1cfs",   
"CIAMESNE",      "ÈIAMESNE", "T",         "T",         "q",      "1cfs",   
"DZIAMESNE",      "DÞIAMESNE", "D",         "D",         "q",      "1cfs",   
"IMESNE",      "IMESNE",      "",          "",          "q",      "1cfs",   
"OMESNE",      "OMESNE",      "",          "",          "q",      "1cfs",   

"AMESNES",     "AMESNËS",  "",          "",          "q",      "1cfV",   
"IAMESNES",    "IAMESNËS", "",          "",          "q",      "1cfV",   
"CIAMESNES",         "ÈIAMESNËS", "T",         "T",         "q",      "1cfV",   
"DZIAMESNES",         "DÞIAMESNËS", "D",         "D",         "q",      "1cfV",   
"IMESNES",     "IMESNËS",  "",          "",          "q",      "1cfV",   
"OMESNES",     "OMESNËS",  "",          "",          "q",      "1cfV",   

"AMESNIU",     "AMESNIØ", "",          "",          "q",      "1cfK",   
"IAMESNIU",     "IAMESNIØ", "",          "",          "q",      "1cfK",   
"CIAMESNIU",          "ÈIAMESNIØ", "T",         "T",         "q",      "1cfK",   
"DZIAMESNIU",          "DÞIAMESNIØ", "D",         "D",         "q",      "1cfK",   
"IMESNIU",     "IMESNIØ", "",          "",          "q",      "1cfK",   
"OMESNIU",     "OMESNIØ", "",          "",          "q",      "1cfK",   

"AMESNEM",     "AMESNËM",  "",          "",          "q",      "1cfN",   
"AMESNEMS",    "AMESNËMS", "",          "",          "q",      "1cfN",   
"IAMESNEM",    "IAMESNËM", "",          "",          "q",      "1cfN",   
"IAMESNEMS",    "IAMESNËMS", "",          "",          "q",      "1cfN",   
"CIAMESNEM",         "ÈIAMESNËM", "T",         "T",         "q",      "1cfN",   
"CIAMESNEMS",         "ÈIAMESNËMS", "T",         "T",         "q",      "1cfN",   
"DZIAMESNEM",         "DÞIAMESNËM", "D",         "D",         "q",      "1cfN",   
"DZIAMESNEMS",         "DÞIAMESNËMS", "D",         "D",         "q",      "1cfN",   
"IMESNEM",     "IMESNËM",  "",          "",          "q",      "1cfN",   
"IMESNEMS",    "IMESNËMS", "",          "",          "q",      "1cfN",   
"OMESNEM",     "OMESNËM",  "",          "",          "q",      "1cfN",   
"OMESNEMS",    "OMESNËMS", "",          "",          "q",      "1cfN",   

"AMESNES",     "AMESNES",     "",          "",          "q",      "1cfG",   
"IAMESNES",    "IAMESNES",    "",          "",          "q",      "1cfG",   
"CIAMESNES",      "ÈIAMESNES", "T",         "T",         "q",      "1cfG",   
"DZIAMESNES",      "DÞIAMESNES", "D",         "D",         "q",      "1cfG",   
"IMESNES",     "IMESNES",     "",          "",          "q",      "1cfG",   
"OMESNES",     "OMESNES",     "",          "",          "q",      "1cfG",   

"AMESNEM",     "AMESNEM",     "",          "",          "q",      "1cfI",   
"AMESNEMIS",   "AMESNEMIS",   "",          "",          "q",      "1cfI",   
"IAMESNEM",    "IAMESNEM",    "",          "",          "q",      "1cfI",   
"IAMESNEMIS",  "IAMESNEMIS",  "",          "",          "q",      "1cfI",   
"CIAMESNEM",      "ÈIAMESNEM", "T",         "T",         "q",      "1cfI",   
"CIAMESNEMIS",      "ÈIAMESNEMIS", "T",         "T",         "q",      "1cfI",   
"DZIAMESNEM",      "DÞIAMESNEM", "D",         "D",         "q",      "1cfI",   
"DZIAMESNEMIS",      "DÞIAMESNEMIS", "D",         "D",         "q",      "1cfI",   
"IMESNEM",     "IMESNEM",     "",          "",          "q",      "1cfI",   
"IMESNEMIS",   "IMESNEMIS",   "",          "",          "q",      "1cfI",   
"OMESNEM",     "OMESNEM",     "",          "",          "q",      "1cfI",   
"OMESNEMIS",   "OMESNEMIS",   "",          "",          "q",      "1cfI",   

"AMESNESE",    "AMESNËSE", "",          "",          "q",      "1cfW",   
"IAMESNESE",    "IAMESNËSE", "",          "",          "q",      "1cfW",   
"CIAMESNESE",         "ÈIAMESNËSE", "T",         "T",         "q",      "1cfW",   
"DZIAMESNESE",         "DÞIAMESNËSE", "D",         "D",         "q",      "1cfW",   
"IMESNESE",    "IMESNËSE", "",          "",          "q",      "1cfW",   
"OMESNESE",    "OMESNËSE", "",          "",          "q",      "1cfW",   


// ------- neveikiamasis esamojo laiko dalyvis, niek. gimine, aukstesnysis laipsnis
// suprantamiau

"AMIAU",       "AMIAU",       "",          "",          "q",      "co",   
"IAMIAU",      "IAMIAU",      "",          "",          "q",      "co",   
"CIAMIAU",      "ÈIAMIAU", "T",         "T",         "q",      "co",   
"DZIAMIAU",      "DÞIAMIAU", "D",         "D",         "q",      "co",   
"IMIAU",       "IMIAU",       "",          "",          "q",      "co",   
"OMIAU",       "OMIAU",       "",          "",          "q",      "co",   


// ------- neveikiamasis ivardziuotinis esamojo laiko dalyvis, vyr. gimine, aukstesnysis laipsnis
// suprantamesnysis - nevartojama


// ------- neveikiamasis ivardziuotinis esamojo laiko dalyvis, mot. gimine, aukstesnysis laipsnis
// suprantamesnioji - nevartojama


// ------- neveikiamasis esamojo laiko dalyvis, vyr. gimine, auksciausiasis laipsnis
// suprantamiausias

"AMIAUSIAS",   "AMIAUSIAS",   "",          "",          "q",      "2cmv",   
"IAMIAUSIAS",  "IAMIAUSIAS",  "",          "",          "q",      "2cmv",   
"CIAMIAUSIAS",      "ÈIAMIAUSIAS", "T",         "T",         "q",      "2cmv",   
"DZIAMIAUSIAS",      "DÞIAMIAUSIAS", "D",         "D",         "q",      "2cmv",   
"IMIAUSIAS",   "IMIAUSIAS",   "",          "",          "q",      "2cmv",   
"OMIAUSIAS",   "OMIAUSIAS",   "",          "",          "q",      "2cmv",   

"AMIAUSIO",    "AMIAUSIO",    "",          "",          "q",      "2cmk",   
"IAMIAUSIO",   "IAMIAUSIO",   "",          "",          "q",      "2cmk",   
"CIAMIAUSIO",      "ÈIAMIAUSIO", "T",         "T",         "q",      "2cmk",   
"DZIAMIAUSIO",      "DÞIAMIAUSIO", "D",         "D",         "q",      "2cmk",   
"IMIAUSIO",    "IMIAUSIO",    "",          "",          "q",      "2cmv",   
"OMIAUSIO",    "OMIAUSIO",    "",          "",          "q",      "2cmv",   


"AMIAUSIAM",   "AMIAUSIAM",   "",          "",          "q",      "2cmn",   
"IAMIAUSIAM",  "IAMIAUSIAM",  "",          "",          "q",      "2cmn",   
"CIAMIAUSIAM",      "ÈIAMIAUSIAM", "T",         "T",         "q",      "2cmn",   
"DZIAMIAUSIAM",      "DÞIAMIAUSIAM", "D",         "D",         "q",      "2cmn",   
"IMIAUSIAM",   "IMIAUSIAM",   "",          "",          "q",      "2cmn",   
"OMIAUSIAM",   "OMIAUSIAM",   "",          "",          "q",      "2cmn",   

"AMIAUSIA",     "AMIAUSIÀ", "",          "",          "q",      "2cmg",   
"IAMIAUSIA",     "IAMIAUSIÀ", "",          "",          "q",      "2cmg",   
"CIAMIAUSIA",          "ÈIAMIAUSIÀ", "T",         "T",         "q",      "2cmg",   
"DZIAMIAUSIA",          "DÞIAMIAUSIÀ", "D",         "D",         "q",      "2cmg",   
"IMIAUSIA",     "IMIAUSIÀ", "",          "",          "q",      "2cmg",   
"OMIAUSIA",     "OMIAUSIÀ", "",          "",          "q",      "2cmg",   

"AMIAUSIU",    "AMIAUSIU",    "",          "",          "q",      "2cmi",   
"IAMIAUSIU",   "IAMIAUSIU",   "",          "",          "q",      "2cmi",   
"CIAMIAUSIU",      "ÈIAMIAUSIU", "T",         "T",         "q",      "2cmi",   
"DZIAMIAUSIU",      "DÞIAMIAUSIU", "D",         "D",         "q",      "2cmi",   
"IMIAUSIU",    "IMIAUSIU",    "",          "",          "q",      "2cmi",   
"OMIAUSIU",    "OMIAUSIU",    "",          "",          "q",      "2cmi",   

"AMIAUSIAM",   "AMIAUSIAM",   "",          "",          "q",      "2cmw",   
"AMIAUSIAME",  "AMIAUSIAME",  "",          "",          "q",      "2cmw",   
"IAMIAUSIAM",  "IAMIAUSIAM",  "",          "",          "q",      "2cmw",   
"IAMIAUSIAME", "IAMIAUSIAME", "",          "",          "q",      "2cmw",   
"CIAMIAUSIAM",      "ÈIAMIAUSIAM", "T",         "T",         "q",      "2cmw",   
"CIAMIAUSIAME",      "ÈIAMIAUSIAME", "T",         "T",         "q",      "2cmw",   
"DZIAMIAUSIAM",      "DÞIAMIAUSIAM", "D",         "D",         "q",      "2cmw",   
"DZIAMIAUSIAME",      "DÞIAMIAUSIAME", "D",         "D",         "q",      "2cmw",   
"IMIAUSIAM",   "IMIAUSIAM",   "",          "",          "q",      "2cmw",   
"IMIAUSIAME",  "IMIAUSIAME",  "",          "",          "q",      "2cmw",   
"OMIAUSIAM",   "OMIAUSIAM",   "",          "",          "q",      "2cmw",   
"OMIAUSIAME",  "OMIAUSIAME",  "",          "",          "q",      "2cmw",   

"AMIAUSIAS",   "AMIAUSIAS",   "",          "",          "q",      "2cms",   
"IAMIAUSIAS",  "IAMIAUSIAS",  "",          "",          "q",      "2cms",   
"CIAMIAUSIAS",      "ÈIAMIAUSIAS", "T",         "T",         "q",      "2cms",   
"DZIAMIAUSIAS",      "DÞIAMIAUSIAS", "D",         "D",         "q",      "2cms",   
"IMIAUSIAS",   "IMIAUSIAS",   "",          "",          "q",      "2cms",   
"OMIAUSIAS",   "OMIAUSIAS",   "",          "",          "q",      "2cms",   

"AMIAUSI",     "AMIAUSI",     "",          "",          "q",      "2cmV",   
"IAMIAUSI",    "IAMIAUSI",    "",          "",          "q",      "2cmV",   
"CIAMIAUSI",      "ÈIAMIAUSI", "T",         "T",         "q",      "2cmV",   
"DZIAMIAUSI",      "DÞIAMIAUSI", "D",         "D",         "q",      "2cmV",   
"IMIAUSI",     "IMIAUSI",     "",          "",          "q",      "2cmV",   
"OMIAUSI",     "OMIAUSI",     "",          "",          "q",      "2cmV",   

"AMIAUSIU",     "AMIAUSIØ", "",          "",          "q",      "2cmK",   
"IAMIAUSIU",     "IAMIAUSIØ", "",          "",          "q",      "2cmK",   
"CIAMIAUSIU",          "ÈIAMIAUSIØ", "T",         "T",         "q",      "2cmK",   
"DZIAMIAUSIU",          "DÞIAMIAUSIØ", "D",         "D",         "q",      "2cmK",   
"IMIAUSIU",     "IMIAUSIØ", "",          "",          "q",      "2cmK",   
"OMIAUSIU",     "OMIAUSIØ", "",          "",          "q",      "2cmK",   

"AMIAUSIEM",   "AMIAUSIEM",   "",          "",          "q",      "2cmN",   
"AMIAUSIEMS",  "AMIAUSIEMS",  "",          "",          "q",      "2cmN",   
"IAMIAUSIEM",  "IAMIAUSIEM",  "",          "",          "q",      "2cmN",   
"IAMIAUSIEMS", "IAMIAUSIEMS", "",          "",          "q",      "2cmN",   
"CIAMIAUSIEM",      "ÈIAMIAUSIEM", "T",         "T",         "q",      "2cmN",   
"CIAMIAUSIEMS",      "ÈIAMIAUSIEMS", "T",         "T",         "q",      "2cmN",   
"DZIAMIAUSIEM",      "DÞIAMIAUSIEM", "D",         "D",         "q",      "2cmN",   
"DZIAMIAUSIEMS",      "DÞIAMIAUSIEMS", "D",         "D",         "q",      "2cmN",   
"IMIAUSIEM",   "IMIAUSIEM",   "",          "",          "q",      "2cmN",   
"IMIAUSIEMS",  "IMIAUSIEMS",  "",          "",          "q",      "2cmN",   
"OMIAUSIEM",   "OMIAUSIEM",   "",          "",          "q",      "2cmN",   
"OMIAUSIEMS",  "OMIAUSIEMS",  "",          "",          "q",      "2cmN",   

"AMIAUSIUS",   "AMIAUSIUS",   "",          "",          "q",      "2cmG",   
"IAMIAUSIUS",  "IAMIAUSIUS",  "",          "",          "q",      "2cmG",   
"CIAMIAUSIUS",      "ÈIAMIAUSIUS", "T",         "T",         "q",      "2cmG",   
"DZIAMIAUSIUS",      "DÞIAMIAUSIUS", "D",         "D",         "q",      "2cmG",   
"IMIAUSIUS",   "IMIAUSIUS",   "",          "",          "q",      "2cmG",   
"OMIAUSIUS",   "OMIAUSIUS",   "",          "",          "q",      "2cmG",   

"AMIAUSIAIS",  "AMIAUSIAIS",  "",          "",          "q",      "2cmI",   
"IAMIAUSIAIS", "IAMIAUSIAIS", "",          "",          "q",      "2cmI",   
"CIAMIAUSIAIS",      "ÈIAMIAUSIAIS", "T",         "T",         "q",      "2cmI",   
"DZIAMIAUSIAIS",      "DÞIAMIAUSIAIS", "D",         "D",         "q",      "2cmI",   
"IMIAUSIAIS",  "IMIAUSIAIS",  "",          "",          "q",      "2cmI",   
"OMIAUSIAIS",  "OMIAUSIAIS",  "",          "",          "q",      "2cmI",   

"AMIAUSIUOS",  "AMIAUSIUOS",  "",          "",          "q",      "2cmW",   
"AMIAUSIUOSE", "AMIAUSIUOSE", "",          "",          "q",      "2cmW",   
"IAMIAUSIUOS", "IAMIAUSIUOS", "",          "",          "q",      "2cmW",   
"IAMIAUSIUOSE", "IAMIAUSIUOSE", "",          "",          "q",      "2cmW",   
"CIAMIAUSIUOS",      "ÈIAMIAUSIUOS", "T",         "T",         "q",      "2cmW",   
"CIAMIAUSIUOSE",      "ÈIAMIAUSIUOSE", "T",         "T",         "q",      "2cmW",   
"DZIAMIAUSIUOS",      "DÞIAMIAUSIUOS", "D",         "D",         "q",      "2cmW",   
"DZIAMIAUSIUOSE",      "DÞIAMIAUSIUOSE", "D",         "D",         "q",      "2cmW",   
"IMIAUSIUOS",  "IMIAUSIUOS",  "",          "",          "q",      "2cmW",   
"IMIAUSIUOSE", "IMIAUSIUOSE", "",          "",          "q",      "2cmW",   
"OMIAUSIUOS",  "OMIAUSIUOS",  "",          "",          "q",      "2cmW",   
"OMIAUSIUOSE", "OMIAUSIUOSE", "",          "",          "q",      "2cmW",   


// ------- neveikiamasis esamojo laiko dalyvis, mot. gimine, auksciausiasis laipsnis
// suprantamiausia

"AMIAUSIA",    "AMIAUSIA",    "",          "",          "q",      "2cfv",   
"IAMIAUSIA",   "IAMIAUSIA",   "",          "",          "q",      "2cfv",   
"CIAMIAUSIA",      "ÈIAMIAUSIA", "T",         "T",         "q",      "2cfv",   
"DZIAMIAUSIA",      "DÞIAMIAUSIA", "D",         "D",         "q",      "2cfv",   
"IMIAUSIA",    "IMIAUSIA",    "",          "",          "q",      "2cfv",   
"OMIAUSIA",    "OMIAUSIA",    "",          "",          "q",      "2cfv",   

"AMIAUSIOS",   "AMIAUSIOS",   "",          "",          "q",      "2cfk",   
"IAMIAUSIOS",  "IAMIAUSIOS",  "",          "",          "q",      "2cfk",   
"CIAMIAUSIOS",      "ÈIAMIAUSIOS", "T",         "T",         "q",      "2cfk",   
"DZIAMIAUSIOS",      "DÞIAMIAUSIOS", "D",         "D",         "q",      "2cfk",   
"IMIAUSIOS",   "IMIAUSIOS",   "",          "",          "q",      "2cfk",   
"OMIAUSIOS",   "OMIAUSIOS",   "",          "",          "q",      "2cfk",   

"AMIAUSIAI",   "AMIAUSIAI",   "",          "",          "q",      "2cfn",   
"IAMIAUSIAI",  "IAMIAUSIAI",  "",          "",          "q",      "2cfn",   
"CIAMIAUSIAI",      "ÈIAMIAUSIAI", "T",         "T",         "q",      "2cfn",   
"DZIAMIAUSIAI",      "DÞIAMIAUSIAI", "D",         "D",         "q",      "2cfn",   
"IMIAUSIAI",   "IMIAUSIAI",   "",          "",          "q",      "2cfn",   
"OMIAUSIAI",   "OMIAUSIAI",   "",          "",          "q",      "2cfn",   

"AMIAUSIA",     "AMIAUSIÀ", "",          "",          "q",      "2cfg",   
"IAMIAUSIA",     "IAMIAUSIÀ", "",          "",          "q",      "2cfg",   
"CIAMIAUSIA",          "ÈIAMIAUSIÀ", "T",         "T",         "q",      "2cfg",   
"DZIAMIAUSIA",          "DÞIAMIAUSIÀ", "D",         "D",         "q",      "2cfg",   
"IMIAUSIA",     "IMIAUSIÀ", "",          "",          "q",      "2cfg",   
"OMIAUSIA",     "OMIAUSIÀ", "",          "",          "q",      "2cfg",   

"AMIAUSIA",    "AMIAUSIA",    "",          "",          "q",      "2cfi",   
"IAMIAUSIA",   "IAMIAUSIA",   "",          "",          "q",      "2cfi",   
"CIAMIAUSIA",      "ÈIAMIAUSIA", "T",         "T",         "q",      "2cfi",   
"DZIAMIAUSIA",      "DÞIAMIAUSIA", "D",         "D",         "q",      "2cfi",   
"IMIAUSIA",    "IMIAUSIA",    "",          "",          "q",      "2cfi",   
"OMIAUSIA",    "OMIAUSIA",    "",          "",          "q",      "2cfi",   

// "AMIAUSIO", "AMIAUSIO",    "",          "",          "q",      "2cfw",   // tarm.
"AMIAUSIOJ",   "AMIAUSIOJ",   "",          "",          "q",      "2cfw",   
"AMIAUSIOJE",  "AMIAUSIOJE",  "",          "",          "q",      "2cfw",   
// "IAMIAUSIO", "IAMIAUSIO",   "",          "",          "q",      "2cfw",   // tarm.
"IAMIAUSIOJ",  "IAMIAUSIOJ",  "",          "",          "q",      "2cfw",   
"IAMIAUSIOJE", "IAMIAUSIOJE", "",          "",          "q",      "2cfw",   
// "CIAMIAUSIO",      "ÈIAMIAUSIO", "T",         "T",         "q",      "2cfw",   // tarm.
"CIAMIAUSIOJ",      "ÈIAMIAUSIOJ", "T",         "T",         "q",      "2cfw",   
"CIAMIAUSIOJE",      "ÈIAMIAUSIOJE", "T",         "T",         "q",      "2cfw",   
// "DZIAMIAUSIO",      "DÞIAMIAUSIO", "D",         "D",         "q",      "2cfw",   // tarm.
"DZIAMIAUSIOJ",      "DÞIAMIAUSIOJ", "D",         "D",         "q",      "2cfw",   
"DZIAMIAUSIOJE",      "DÞIAMIAUSIOJE", "D",         "D",         "q",      "2cfw",   
// "IMIAUSIO", "IMIAUSIO",    "",          "",          "q",      "2cfw",   // tarm.
"IMIAUSIOJ",   "IMIAUSIOJ",   "",          "",          "q",      "2cfw",   
"IMIAUSIOJE",  "IMIAUSIOJE",  "",          "",          "q",      "2cfw",   
// "OMIAUSIO", "OMIAUSIO",    "",          "",          "q",      "2cfw",   // tarm.
"OMIAUSIOJ",   "OMIAUSIOJ",   "",          "",          "q",      "2cfw",   
"OMIAUSIOJE",  "OMIAUSIOJE",  "",          "",          "q",      "2cfw",   

"AMIAUSIA",    "AMIAUSIA",    "",          "",          "q",      "2cfs",   
"IAMIAUSIA",   "IAMIAUSIA",   "",          "",          "q",      "2cfs",   
"CIAMIAUSIA",      "ÈIAMIAUSIA", "T",         "T",         "q",      "2cfs",   
"DZIAMIAUSIA",      "DÞIAMIAUSIA", "D",         "D",         "q",      "2cfs",   
"IMIAUSIA",    "IMIAUSIA",    "",          "",          "q",      "2cfs",   
"OMIAUSIA",    "OMIAUSIA",    "",          "",          "q",      "2cfs",   

"AMIAUSIOS",   "AMIAUSIOS",   "",          "",          "q",      "2cfV",   
"IAMIAUSIOS",  "IAMIAUSIOS",  "",          "",          "q",      "2cfV",   
"CIAMIAUSIOS",      "ÈIAMIAUSIOS", "T",         "T",         "q",      "2cfV",   
"DZIAMIAUSIOS",      "DÞIAMIAUSIOS", "D",         "D",         "q",      "2cfV",   
"IMIAUSIOS",   "IMIAUSIOS",   "",          "",          "q",      "2cfV",   
"OMIAUSIOS",   "OMIAUSIOS",   "",          "",          "q",      "2cfV",   

"AMIAUSIU",     "AMIAUSIØ", "",          "",          "q",      "2cfK",   
"IAMIAUSIU",     "IAMIAUSIØ", "",          "",          "q",      "2cfK",   
"CIAMIAUSIU",          "ÈIAMIAUSIØ", "T",         "T",         "q",      "2cfK",   
"DZIAMIAUSIU",          "DÞIAMIAUSIØ", "D",         "D",         "q",      "2cfK",   
"IMIAUSIU",     "IMIAUSIØ", "",          "",          "q",      "2cfK",   
"OMIAUSIU",     "OMIAUSIØ", "",          "",          "q",      "2cfK",   

"AMIAUSIOM",   "AMIAUSIOM",   "",          "",          "q",      "2cfN",   
"AMIAUSIOMS",  "AMIAUSIOMS",  "",          "",          "q",      "2cfN",   
"IAMIAUSIOM",  "IAMIAUSIOM",  "",          "",          "q",      "2cfN",   
"IAMIAUSIOMS", "IAMIAUSIOMS", "",          "",          "q",      "2cfN",   
"CIAMIAUSIOM",      "ÈIAMIAUSIOM", "T",         "T",         "q",      "2cfN",   
"CIAMIAUSIOMS",      "ÈIAMIAUSIOMS", "T",         "T",         "q",      "2cfN",   
"DZIAMIAUSIOM",      "DÞIAMIAUSIOM", "D",         "D",         "q",      "2cfN",   
"DZIAMIAUSIOMS",      "DÞIAMIAUSIOMS", "D",         "D",         "q",      "2cfN",   
"IMIAUSIOM",   "IMIAUSIOM",   "",          "",          "q",      "2cfN",   
"IMIAUSIOMS",  "IMIAUSIOMS",  "",          "",          "q",      "2cfN",   
"OMIAUSIOM",   "OMIAUSIOM",   "",          "",          "q",      "2cfN",   
"OMIAUSIOMS",  "OMIAUSIOMS",  "",          "",          "q",      "2cfN",   

"AMIAUSIAS",   "AMIAUSIAS",   "",          "",          "q",      "2cfG",   
"IAMIAUSIAS",  "IAMIAUSIAS",  "",          "",          "q",      "2cfG",   
"CIAMIAUSIAS",      "ÈIAMIAUSIAS", "T",         "T",         "q",      "2cfG",   
"DZIAMIAUSIAS",      "DÞIAMIAUSIAS", "D",         "D",         "q",      "2cfG",   
"IMIAUSIAS",   "IMIAUSIAS",   "",          "",          "q",      "2cfG",   
"OMIAUSIAS",   "OMIAUSIAS",   "",          "",          "q",      "2cfG",   

"AMIAUSIOM",   "AMIAUSIOM",   "",          "",          "q",      "2cfI",   
"AMIAUSIOMIS", "AMIAUSIOMIS", "",          "",          "q",      "2cfI",   
"IAMIAUSIOM",  "IAMIAUSIOM",  "",          "",          "q",      "2cfI",   
"IAMIAUSIOMIS", "IAMIAUSIOMIS", "",          "",          "q",      "2cfI",   
"CIAMIAUSIOM",      "ÈIAMIAUSIOM", "T",         "T",         "q",      "2cfI",   
"CIAMIAUSIOMIS",      "ÈIAMIAUSIOMIS", "T",         "T",         "q",      "2cfI",   
"DZIAMIAUSIOM",      "DÞIAMIAUSIOM", "D",         "D",         "q",      "2cfI",   
"DZIAMIAUSIOMIS",      "DÞIAMIAUSIOMIS", "D",         "D",         "q",      "2cfI",   
"IMIAUSIOM",   "IMIAUSIOM",   "",          "",          "q",      "2cfI",   
"IMIAUSIOMIS", "IMIAUSIOMIS", "",          "",          "q",      "2cfI",   
"OMIAUSIOM",   "OMIAUSIOM",   "",          "",          "q",      "2cfI",   
"OMIAUSIOMIS", "OMIAUSIOMIS", "",          "",          "q",      "2cfI",   

"AMIAUSIOSE",  "AMIAUSIOSE",  "",          "",          "q",      "2cfW",   
"IAMIAUSIOSE", "IAMIAUSIOSE", "",          "",          "q",      "2cfW",   
"CIAMIAUSIOSE",      "ÈIAMIAUSIOSE", "T",         "T",         "q",      "2cfW",   
"DZIAMIAUSIOSE",      "DÞIAMIAUSIOSE", "D",         "D",         "q",      "2cfW",   
"IMIAUSIOSE",  "IMIAUSIOSE",  "",          "",          "q",      "2cfW",   
"OMIAUSIOSE",  "OMIAUSIOSE",  "",          "",          "q",      "2cfW",   


// ------- neveikiamasis esamojo laiko dalyvis, niek. gimine, auksciausiasis laipsnis
// suprantamiausia

"AMIAUSIA",    "AMIAUSIA",    "",          "",          "q",      "co",   
"IAMIAUSIA",   "IAMIAUSIA",   "",          "",          "q",      "co",   
"CIAMIAUSIA",      "ÈIAMIAUSIA", "T",         "T",         "q",      "co",   
"DZIAMIAUSIA",      "DÞIAMIAUSIA", "D",         "D",         "q",      "co",   
"IMIAUSIA",    "IMIAUSIA",    "",          "",          "q",      "co",   
"OMIAUSIA",    "OMIAUSIA",    "",          "",          "q",      "co",   


// ------- neveikiamasis ivardziuotinis esamojo laiko dalyvis, vyr. gimine, auksciausiasis laipsnis
// suprantamiausiasis - nevartojamas


// ------- neveikiamasis ivardziuotinis esamojo laiko dalyvis, mot. gimine, auksciausiasis laipsnis
// suprantamiausioji - nevartojamas


// ------- neveikiamasis butojo laiko dalyvis, vyr. gimine
// suprastas

"TAS",         "TAS",         "T",         "T",         "(",      "crmv",   

"TO",          "TO",          "T",         "T",         "(",      "crmk",   

"TAM",         "TAM",         "T",         "T",         "(",      "crmn",   

"TA",          "TÀ",      "T",         "T",         "(",      "crmg",   

"TU",          "TU",          "T",         "T",         "(",      "crmi",   

"TAM",         "TAM",         "T",         "T",         "(",      "crmw",   
"TAME",        "TAME",        "T",         "T",         "(",      "crmw",   

"TAS",         "TAS",         "T",         "T",         "(",      "crms",   

"TI",          "TI",          "T",         "T",         "(",      "crmV",   

"TU",          "TØ",      "T",         "T",         "(",      "crmK",   

"TIEM",        "TIEM",        "T",         "T",         "(",      "crmN",   
"TIEMS",       "TIEMS",       "T",         "T",         "(",      "crmN",   

"TUS",         "TUS",         "T",         "T",         "(",      "crmG",   

"TAIS",        "TAIS",        "T",         "T",         "(",      "crmI",   

"TUOS",        "TUOS",        "T",         "T",         "(",      "crmW",   
"TUOSE",       "TUOSE",       "T",         "T",         "(",      "crmW",   


// ------- neveikiamasis butojo laiko dalyvis, mot. gimine
// suprasta

"TA",          "TA",          "T",         "T",         "(",      "crfv",   

"TOS",         "TOS",         "T",         "T",         "(",      "crfk",   

"TAI",         "TAI",         "T",         "T",         "(",      "crfn",   

"TA",          "TÀ",      "T",         "T",         "(",      "crfg",   

"TA",          "TA",          "T",         "T",         "(",      "crfi",   

// "TO",       "TO",          "T",         "T",         "(",      "crfw",   // tarm.
"TOJ",         "TOJ",         "T",         "T",         "(",      "crfw",   
"TOJE",        "TOJE",        "T",         "T",         "(",      "crfw",   

"TA",          "TA",          "T",         "T",         "(",      "crfs",   

"TOS",         "TOS",         "T",         "T",         "(",      "crfV",   

"TU",          "TØ",      "T",         "T",         "(",      "crfK",   

"TOM",         "TOM",         "T",         "T",         "(",      "crfN",   
"TOMS",        "TOMS",        "T",         "T",         "(",      "crfN",   

"TAS",         "TAS",         "T",         "T",         "(",      "crfG",   

"TOM",         "TOM",         "T",         "T",         "(",      "crfI",   
"TOMIS",       "TOMIS",       "T",         "T",         "(",      "crfI",   

"TOSE",        "TOSE",        "T",         "T",         "(",      "crfW",   


// ------- neveikiamasis butojo laiko dalyvis, niek. gimine
// suprasta

"TA",          "TA",          "T",         "T",         "(",      "crov",   


// ------- neveikiamasis ivardziuotinis butojo laiko dalyvis, vyr. gimine
// suprastasis

"TASIS",       "TASIS",       "T",         "T",         "(",      "ecrmv",   

"TOJO",        "TOJO",        "T",         "T",         "(",      "ecrmk",   

"TAJAM",       "TAJAM",       "T",         "T",         "(",      "ecrmn",   

"TAJI",         "TÀJÁ", "T",         "T",         "(",      "ecrmg",   

"TUOJU",       "TUOJU",       "T",         "T",         "(",      "ecrmi",   

"TAJAM",       "TAJAM",       "T",         "T",         "(",      "ecrmw",   
"TAJAME",      "TAJAME",      "T",         "T",         "(",      "ecrmw",   

"TASIS",       "TASIS",       "T",         "T",         "(",      "ecrms",   

"TIEJI",       "TIEJI",       "T",         "T",         "(",      "ecrmV",   

"TUJU",         "TØJØ", "T",         "T",         "(",      "ecrmK",   

"TIESIEM",     "TIESIEM",     "T",         "T",         "(",      "ecrmN",   
"TIESIEMS",    "TIESIEMS",    "T",         "T",         "(",      "ecrmN",   

"TUOSIUS",     "TUOSIUS",     "T",         "T",         "(",      "ecrmG",   

"TAISIAIS",    "TAISIAIS",    "T",         "T",         "(",      "ecrmI",   

"TUOSIUOS",    "TUOSIUOS",    "T",         "T",         "(",      "ecrmW",   
"TUOSIUOSE",   "TUOSIUOSE",   "T",         "T",         "(",      "ecrmW",   


// ------- neveikiamasis ivardziuotinis butojo laiko dalyvis, mot. gimine
// suprastoji

"TOJI",        "TOJI",        "T",         "T",         "(",      "ecrfv",   

"TOSIOS",      "TOSIOS",      "T",         "T",         "(",      "ecrfk",   

"TAJAI",       "TAJAI",       "T",         "T",         "(",      "ecrfn",   

"TAJA",         "TÀJÀ", "T",         "T",         "(",      "ecrfg",   

"TAJA",        "TÀJA",    "T",         "T",         "(",      "ecrfi",   

"TOJO",        "TOJO",        "T",         "T",         "(",      "ecrfw",   
"TOJOJ",       "TOJOJ",       "T",         "T",         "(",      "ecrfw",   
"TOJOJE",      "TOJOJE",      "T",         "T",         "(",      "ecrfw",   

"TOJI",        "TOJI",        "T",         "T",         "(",      "ecrfs",   

"TOSIOS",      "TOSIOS",      "T",         "T",         "(",      "ecrfV",   

"TUJU",         "TØJØ", "T",         "T",         "(",      "ecrfK",   

"TOSIOM",      "TOSIOM",      "T",         "T",         "(",      "ecrfN",   
"TOSIOMS",     "TOSIOMS",     "T",         "T",         "(",      "ecrfN",   

"TASIAS",      "TÀSIAS",  "T",         "T",         "(",      "ecrfG",   

"TOSIOM",      "TOSIOM",      "T",         "T",         "(",      "ecrfI",   
"TOSIOMIS",    "TOSIOMIS",    "T",         "T",         "(",      "ecrfI",   

"TOSIOSE",     "TOSIOSE",     "T",         "T",         "(",      "ecrfW",   


// ------- neveikiamasis butojo laiko dalyvis, vyr. gimine, aukstesnysis laipsnis
// mokytesnis

"TESNIS",      "TESNIS",      "T",         "T",         "(",      "1crmv",   

"TESNIO",      "TESNIO",      "T",         "T",         "(",      "1crmk",   

"TESNIAM",     "TESNIAM",     "T",         "T",         "(",      "1crmn",   

"TESNI",       "TESNÁ",   "T",         "T",         "(",      "1crmg",   

"TESNIU",      "TESNIU",      "T",         "T",         "(",      "1crmi",   

"TESNIAM",     "TESNIAM",     "T",         "T",         "(",      "1crmw",   
"TESNIAME",    "TESNIAME",    "T",         "T",         "(",      "1crmw",   

"TESNIS",      "TESNIS",      "T",         "T",         "(",      "1crms",   

"TESNI",       "TESNI",       "T",         "T",         "(",      "1crmV",   

"TESNIU",      "TESNIØ",  "T",         "T",         "(",      "1crmK",   

"TESNIEM",     "TESNIEM",     "T",         "T",         "(",      "1crmN",   
"TESNIEMS",    "TESNIEMS",    "T",         "T",         "(",      "1crmN",   

"TESNIUS",     "TESNIUS",     "T",         "T",         "(",      "1crmG",   

"TESNIAIS",    "TESNIAIS",    "T",         "T",         "(",      "1crmI",   

"TESNIUOS",    "TESNIUOS",    "T",         "T",         "(",      "1crmW",   
"TESNIUOSE",   "TESNIUOSE",   "T",         "T",         "(",      "1crmW",   


// ------- neveikiamasis butojo laiko dalyvis, mot. gimine, aukstesnysis laipsnis
// mokytesne

"TESNE",       "TESNË",    "T",         "T",         "(",      "1crfv",   

"TESNES",      "TESNËS",   "T",         "T",         "(",      "1crfk",   

"TESNEI",      "TESNEI",      "T",         "T",         "(",      "1crfn",   

"TESNE",       "TESNÆ",   "T",         "T",         "(",      "1crfg",   

"TESNE",       "TESNE",       "T",         "T",         "(",      "1crfi",   

// "TESNE",    "TESNË",    "T",         "T",         "(",      "1crfw",   // tarm.
"TESNEJ",      "TESNËJ",   "T",         "T",         "(",      "1crfw",   
"TESNEJE",     "TESNËJE",  "T",         "T",         "(",      "1crfw",   

"TESNE",       "TESNE",       "T",         "T",         "(",      "1crfs",   

"TESNES",      "TESNËS",   "T",         "T",         "(",      "1crfV",   

"TESNIU",      "TESNIØ",  "T",         "T",         "(",      "1crfK",   

"TESNEM",      "TESNËM",   "T",         "T",         "(",      "1crfN",   
"TESNEMS",     "TESNËMS",  "T",         "T",         "(",      "1crfN",   

"TESNES",      "TESNES",      "T",         "T",         "(",      "1crfG",   

"TESNEM",      "TESNËM",   "T",         "T",         "(",      "1crfI",   
"TESNEMIS",    "TESNËMIS", "T",         "T",         "(",      "1crfI",   

"TESNESE",     "TESNËSE",  "T",         "T",         "(",      "1crfW",   


// ------- neveikiamasis butojo laiko dalyvis, niek. gimine
// mokyciau

"CIAU",        "ÈIAU",   "T",         "T",         "(",      "1crov",   


// ------- neveikiamasis ivardziuotinis butojo laiko dalyvis, vyr. gimine, aukstesnysis laipsnis
// suprastesnysis - nevartojamas


// ------- neveikiamasis ivardziuotinis butojo laiko dalyvis, mot. gimine, aukstesnysis laipsnis
// suprastesnioji - nevartojamas


// ------- neveikiamasis butojo laiko dalyvis, vyr. gimine, auksciausiasis laipsnis
// mokyciausias

"CIAUSIAS",      "ÈIAUSIAS", "T",         "T",         "(",      "2crmv",   

"CIAUSIO",      "ÈIAUSIO", "T",         "T",         "(",      "2crmk",   

"CIAUSIAM",      "ÈIAUSIAM", "T",         "T",         "(",      "2crmn",   

"CIAUSIA",          "ÈIAUSIÀ", "T",         "T",         "(",      "2crmg",   

"CIAUSIU",      "ÈIAUSIU", "T",         "T",         "(",      "2crmi",   

"CIAUSIAM",      "ÈIAUSIAM", "T",         "T",         "(",      "2crmw",   
"CIAUSIAME",      "ÈIAUSIAME", "T",         "T",         "(",      "2crmw",   

"CIAUSIAS",      "ÈIAUSIAS", "T",         "T",         "(",      "2crms",   

"CIAUSI",      "ÈIAUSI", "T",         "T",         "(",      "2crmV",   

"CIAUSIU",          "ÈIAUSIØ", "T",         "T",         "(",      "2crmK",   

"CIAUSIEM",      "ÈIAUSIEM", "T",         "T",         "(",      "2crmN",   
"CIAUSIEMS",      "ÈIAUSIEMS", "T",         "T",         "(",      "2crmN",   

"CIAUSIUS",      "ÈIAUSIUS", "T",         "T",         "(",      "2crmG",   

"CIAUSIAIS",      "ÈIAUSIAIS", "T",         "T",         "(",      "2crmI",   

"CIAUSIUOS",      "ÈIAUSIUOS", "T",         "T",         "(",      "2crmW",   
"CIAUSIUOSE",      "ÈIAUSIUOSE", "T",         "T",         "(",      "2crmW",   


// ------- neveikiamasis butojo laiko dalyvis, mot. gimine, auksciausiasis laipsnis
// mokyciausia

"CIAUSIA",      "ÈIAUSIA", "T",         "T",         "(",      "2crfv",   

"CIAUSIOS",      "ÈIAUSIOS", "T",         "T",         "(",      "2crfk",   

"CIAUSIAI",      "ÈIAUSIAI", "T",         "T",         "(",      "2crfn",   

"CIAUSIA",          "ÈIAUSIÀ", "T",         "T",         "(",      "2crfg",   

"CIAUSIA",      "ÈIAUSIA", "T",         "T",         "(",      "2crfi",   

// "CIAUSIO",      "ÈIAUSIO", "T",         "T",         "(",      "2crfw",   // tarm.
"CIAUSIOJ",      "ÈIAUSIOJ", "T",         "T",         "(",      "2crfw",   
"CIAUSIOJE",      "ÈIAUSIOJE", "T",         "T",         "(",      "2crfw",   

"CIAUSIA",      "ÈIAUSIA", "T",         "T",         "(",      "2crfs",   

"CIAUSIOS",      "ÈIAUSIOS", "T",         "T",         "(",      "2crfV",   

"CIAUSIU",          "ÈIAUSIØ", "T",         "T",         "(",      "2crfK",   

"CIAUSIOM",      "ÈIAUSIOM", "T",         "T",         "(",      "2crfN",   
"CIAUSIOMS",      "ÈIAUSIOMS", "T",         "T",         "(",      "2crfN",   

"CIAUSIAS",      "ÈIAUSIAS", "T",         "T",         "(",      "2crfG",   

"CIAUSIOM",      "ÈIAUSIOM", "T",         "T",         "(",      "2crfI",   
"CIAUSIOMIS",      "ÈIAUSIOMIS", "T",         "T",         "(",      "2crfI",   

"CIAUSIOSE",      "ÈIAUSIOSE", "T",         "T",         "(",      "2crfW",   


// ------- neveikiamasis butojo laiko dalyvis, niek. gimine, auksciausiasis laipsnis
// mokyciausia

"CIAUSIA",      "ÈIAUSIA", "T",         "T",         "(",      "2crov",   


// ------- neveikiamasis ivardziuotinis butojo laiko dalyvis, vyr. gimine, auksciausiasis laipsnis
// mokyciausiasis - nevartojama


// ------- neveikiamasis ivardziuotinis butojo laiko dalyvis, mot. gimine, auksciausiasis laipsnis
// mokyciausioji - nevartojama


// ------- neveikiamasis busimojo laiko dalyvis, vyr. gimine
// busimas
// -imas pjaunasi su jungimas, ejimas..., arimas, Rimas, ... !!!
// siaip busimas turetu buti keiciamas i bus, po to turetu suveikti nereguliarios formos

"BUSIMAS",     "BÛSIMAS", "BUT",          "BÛT",          "s",      "cmv",   
// "IMAS",     "IMAS",        "",          "",          "s",      "cmv",   

"BUSIMO",      "BÛSIMO",  "BUT",          "BÛT",          "s",      "cmk",   
// "IMO",      "IMO",         "",          "",          "s",      "cmk",   

"BUSIMAM",     "BÛSIMAM", "BUT",          "BÛT",          "s",      "cmn",   
// "IMAM",     "IMAM",        "",          "",          "s",      "cmn",   

"BUSIMA",         "BÛSIMÀ", "BUT",          "BÛT",          "s",      "cmg",   
// "IMA",      "IMÀ",     "",          "",          "s",      "cmg",   

"BUSIMU",      "BÛSIMU",  "BUT",          "BÛT",          "s",      "cmi",   
// "IMU",      "IMU",         "",          "",          "s",      "cmi",   

"BUSIMAM",     "BÛSIMAM", "BUT",          "BÛT",          "s",      "cmw",   
"BUSIMAME",     "BÛSIMAME", "BUT",          "BÛT",          "s",      "cmw",   
// "IMAM",     "IMAM",        "",          "",          "s",      "cmw",   
// "IMAME",    "IMAME",       "",          "",          "s",      "cmw",   

"BUSIMAS",     "BÛSIMAS", "BUT",          "BÛT",          "s",      "cms",   
// "IMAS",     "IMAS",        "",          "",          "s",      "cms",   

"BUSIMI",      "BÛSIMI",  "BUT",          "BÛT",          "s",      "cmV",   
// "IMI",      "IMI",         "",          "",          "s",      "cmV",   

"BUSIMU",         "BÛSIMØ", "BUT",          "BÛT",          "s",      "cmK",   
// "IMU",      "IMØ",     "",          "",          "s",      "cmK",   

"BUSIMIEM",     "BÛSIMIEM", "BUT",          "BÛT",          "s",      "cmN",   
"BUSIMIEMS",     "BÛSIMIEMS", "BUT",          "BÛT",          "s",      "cmN",   
// "IMIEM",    "IMIEM",       "",          "",          "s",      "cmN",   
// "IMIEMS",    "IMIEMS",       "",          "",          "s",      "cmN",   

"BUSIMUS",     "BÛSIMUS", "BUT",          "BÛT",          "s",      "cmG",   
// "IMUS",     "IMUS",        "",          "",          "s",      "cmG",   

"BUSIMAIS",     "BÛSIMAIS", "BUT",          "BÛT",          "s",      "cmI",   
// "IMAIS",    "IMAIS",       "",          "",          "s",      "cmI",   

"BUSIMUOS",     "BÛSIMUOS", "BUT",          "BÛT",          "s",      "cmW",   
"BUSIMUOSE",     "BÛSIMUOSE", "BUT",          "BÛT",          "s",      "cmW",   
// "IMUOS",    "IMUOS",       "",          "",          "s",      "cmW",   
// "IMUOSE",   "IMUOSE",      "",          "",          "s",      "cmW",   


// ------- neveikiamasis busimojo laiko dalyvis, mot. gimimine
// busima
// -imas pjaunasi su jungimas, ejimas..., arimas, Rimas, ... !!!

"BUSIMA",      "BÛSIMA",  "BUT",          "BÛT",          "s",      "cfv",   
// "IMA",      "IMA",         "",          "",          "s",      "cfv",   

"BUSIMOS",     "BÛSIMOS", "BUT",          "BÛT",          "s",      "cfk",   
// "IMOS",     "IMOS",        "",          "",          "s",      "cfk",   

"BUSIMAI",     "BÛSIMAI", "BUT",          "BÛT",          "s",      "cfn",   
// "IMAI",     "IMAI",        "",          "",          "s",      "cfn",   

"BUSIMA",         "BÛSIMÀ", "BUT",          "BÛT",          "s",      "cfg",   
// "IMA",      "IMÀ",     "",          "",          "s",      "cfg",   

"BUSIMA",      "BÛSIMA",  "BUT",          "BÛT",          "s",      "cfi",   
// "IMA",      "IMA",         "",          "",          "s",      "cfi",   

// "BUSIMO",     "BÛSIMO",  "BUT",          "BÛT",          "s",      "cfw",   // tarm.
"BUSIMOJ",     "BÛSIMOJ", "BUT",          "BÛT",          "s",      "cfw",   
"BUSIMOJE",     "BÛSIMOJE", "BUT",          "BÛT",          "s",      "cfw",   
// "IMO",      "IMO",         "",          "",          "s",      "cfw",   // tarm.
// "IMOJ",     "IMOJ",        "",          "",          "s",      "cfw",   
// "IMOJE",    "IMOJE",       "",          "",          "s",      "cfw",   

"BUSIMA",      "BÛSIMA",  "BUT",          "BÛT",          "s",      "cfs",   
// "IMA",      "IMA",         "",          "",          "s",      "cfs",   

"BUSIMOS",     "BÛSIMOS", "BUT",          "BÛT",          "s",      "cfV",   
// "IMOS",     "IMOS",        "",          "",          "s",      "cfV",   

"BUSIMU",         "BÛSIMØ", "BUT",          "BÛT",          "s",      "cfK",   
// "IMU",      "IMØ",     "",          "",          "s",      "cfK",   

"BUSIMOM",     "BÛSIMOM", "BUT",          "BÛT",          "s",      "cfN",   
"BUSIMOMS",     "BÛSIMOMS", "BUT",          "BÛT",          "s",      "cfN",   
// "IMOM",     "IMOM",        "",          "",          "s",      "cfN",   
// "IMOMS",    "IMOMS",       "",          "",          "s",      "cfN",   

"BUSIMAS",     "BÛSIMAS", "BUT",          "BÛT",          "s",      "cfG",   
// "IMAS",     "IMAS",        "",          "",          "s",      "cfG",   

"BUSIMOM",     "BÛSIMOM", "BUT",          "BÛT",          "s",      "cfI",   
"BUSIMOMIS",     "BÛSIMOMIS", "BUT",          "BÛT",          "s",      "cfI",   
// "IMOM",     "IMOM",        "",          "",          "s",      "cfI",   
// "IMOMIS",   "IMOMIS",      "",          "",          "s",      "cfI",   

"BUSIMOSE",     "BÛSIMOSE", "BUT",          "BÛT",          "s",      "cfW",   
// "IMOSE",    "IMOSE",       "",          "",          "s",      "cfW",   


// ------- neveikiamasis ivardziuotinis busimojo laiko dalyvis, vyr. gimine
// busimasis

"IMASIS",      "IMASIS",      "",          "",          "s",      "ecmv",   

"IMOJO",       "IMOJO",       "",          "",          "s",      "ecmk",   

"IMAJAM",      "IMAJAM",      "",          "",          "s",      "ecmn",   

"IMAJI",       "IMÀJÁ", "",          "",          "s",      "ecmg",   

"IMUOJU",      "IMUOJU",      "",          "",          "s",      "ecmi",   

"IMAJAM",      "IMAJAM",      "",          "",          "s",      "ecmw",   
"IMAJAME",     "IMAJAME",     "",          "",          "s",      "ecmw",   

"IMASIS",      "IMASIS",      "",          "",          "s",      "ecms",   

"IMIEJI",      "IMIEJI",      "",          "",          "s",      "ecmV",   

"IMUJU",         "IMØJØ", "",          "",          "s",      "ecmK",   

"IMIESIEM",    "IMIESIEM",    "",          "",          "s",      "ecmN",   
"IMIESIEMS",   "IMIESIEMS",   "",          "",          "s",      "ecmN",   

"IMUOSIUS",    "IMUOSIUS",    "",          "",          "s",      "ecmG",   

"IMAISIAIS",   "IMAISIAIS",   "",          "",          "s",      "ecmI",   

"IMUOSIUOS",   "IMUOSIUOS",   "",          "",          "s",      "ecmW",   
"IMUOSIUOSE",  "IMUOSIUOSE",  "",          "",          "s",      "ecmW",   


// ------- neveikiamasis ivardziuotinis busimojo laiko dalyvis, mot. gimimine
// busimoji

"IMOJI",       "IMOJI",       "",          "",          "s",      "ecfv",   

"IMOSIOS",     "IMOSIOS",     "",          "",          "s",      "ecfk",   

"IMAJAI",      "IMAJAI",      "",          "",          "s",      "ecfn",   

"IMAJA",         "IMÀJÀ", "",          "",          "s",      "ecfg",   

"IMAJA",       "IMÀJA",   "",          "",          "s",      "ecfi",   

// "IMOJO",    "IMOJO",       "",          "",          "s",      "ecfw",   // tarm.
"IMOJOJ",      "IMOJOJ",      "",          "",          "s",      "ecfw",   
"IMOJOJE",     "IMOJOJE",     "",          "",          "s",      "ecfw",   

"IMOJI",       "IMOJI",       "",          "",          "s",      "ecfs",   

"IMOSIOS",     "IMOSIOS",     "",          "",          "s",      "ecfV",   

"IMUJU",         "IMØJØ", "",          "",          "s",      "ecfK",   

"IMOSIOM",     "IMOSIOM",     "",          "",          "s",      "ecfN",   
"IMOSIOMS",    "IMOSIOMS",    "",          "",          "s",      "ecfN",   

"IMASIAS",     "IMÀSIAS", "",          "",          "s",      "ecfG",   

"IMOSIOM",     "IMOSIOM",     "",          "",          "s",      "ecfI",   
"IMOSIOMIS",   "IMOSIOMIS",   "",          "",          "s",      "ecfI",   

"IMOSIOSE",    "IMOSIOSE",    "",          "",          "s",      "ecfW",   


// ------- neveikiamasis busimojo laiko dalyvis, vyr. gimine, aukstesnysis laipsnis
// busimesnis - nevartojamas


// ------- neveikiamasis busimojo laiko dalyvis, mot. gimimine, aukstesnysis laipsnis
// busimesne - nevartojamas


// ------- neveikiamasis ivardziuotinis busimojo laiko dalyvis, vyr. gimine, aukstesnysis laipsnis
// busimesnysis - nevartojamas


// ------- neveikiamasis ivardziuotinis busimojo laiko dalyvis, mot. gimimine, aukstesnysis laipsnis
// busimesnioji - nevartojamas


// ------- reikiamybes dalyvis, vyr. gimine
// butinas
"INAS",     "INAS", "",          "",          "s",      "cmv",   
"INO",      "INO",         "",          "",          "s",      "cmk",   
"INAM",     "INAM",        "",          "",          "s",      "cmn",   
"INA",      "INÀ",     "",          "",          "s",      "cmg",   
"INU",      "INU",         "",          "",          "s",      "cmi",   
"INAM",     "INAM",        "",          "",          "s",      "cmw",   
"INAME",    "INAME",       "",          "",          "s",      "cmw",   
"INAS",     "INAS",        "",          "",          "s",      "cms",   
"INI",      "INI",         "",          "",          "s",      "cmV",   
"INU",      "INØ",     "",          "",          "s",      "cmK",   
"INIEM",    "INIEM",       "",          "",          "s",      "cmN",   
"INIEMS",   "INIEMS",       "",          "",          "s",      "cmN",   
"INUS",     "INUS",        "",          "",          "s",      "cmG",   
"INAIS",    "INAIS",       "",          "",          "s",      "cmI",   
"INUOS",    "INUOS",       "",          "",          "s",      "cmW",   
"INUOSE",   "INUOSE",      "",          "",          "s",      "cmW",   

// ------- reikiamybes dalyvis, mot. gimine
// butina

"INA",      "INA", "",          "",          "s",      "cmv",   
"INOS",     "INOS",         "",          "",          "s",      "cmk",   
"INAI",     "INAI",        "",          "",          "s",      "cmn",   
"INA",      "INÀ",     "",          "",          "s",      "cmg",   
"INA",      "INA",         "",          "",          "s",      "cmi",   
"INOJ",     "INOJ",        "",          "",          "s",      "cmw",   
"INOJE",    "INOJE",       "",          "",          "s",      "cmw",   
"INA",      "INA",        "",          "",          "s",      "cms",   
"INOS",     "INOS",         "",          "",          "s",      "cmV",   
"INU",      "INØ",     "",          "",          "s",      "cmK",   
"INOM",     "INOM",       "",          "",          "s",      "cmN",   
"INOMS",    "INOMS",       "",          "",          "s",      "cmN",   
"INAS",     "INAS",        "",          "",          "s",      "cmG",   
"INOMIS",   "INOMIS",       "",          "",          "s",      "cmI",   
"INOSE",    "INOSE",      "",          "",          "s",      "cmW",   

// ------- reikiamybes dalyvis, vyr. gimine, aukstesnysis laipsnis
// butinesnis

"INESNIS",     "INESNIS", "",          "",          "s",      "cmv",   
"INESNIO",     "INESNIO",         "",          "",          "s",      "cmk",   
"INESNIAM",    "INESNIAM",        "",          "",          "s",      "cmn",   
"INESNI",      "INESNIÁ",     "",          "",          "s",      "cmg",   
"INESNIU",     "INESNIU",         "",          "",          "s",      "cmi",   
"INESNIAM",    "INESNIAM",        "",          "",          "s",      "cmw",   
"INESNIAME",   "INESNIAME",       "",          "",          "s",      "cmw",   
"INESNIS",     "INESNIS",        "",          "",          "s",      "cms",   
"INESNI",      "INESNI",         "",          "",          "s",      "cmV",   
"INESNIU",     "INESNIØ",     "",          "",          "s",      "cmK",   
"INESNIEM",    "INESNIEM",       "",          "",          "s",      "cmN",   
"INESNIEMS",   "INESNIEMS",       "",          "",          "s",      "cmN",   
"INESNIUS",    "INESNIUS",        "",          "",          "s",      "cmG",   
"INESNIAIS",   "INESNIAIS",       "",          "",          "s",      "cmI",   
"INESNIUOS",   "INESNIUOS",       "",          "",          "s",      "cmW",   
"INESNIUOSE",  "INESNIUOSE",      "",          "",          "s",      "cmW",   

// ------- reikiamybes dalyvis, mot. gimine, aukstesnysis laipsnis
// butinesne
"INESNE",      "INESNË", "",          "",          "s",      "cmv",   
"INESNES",     "INESNËS",         "",          "",          "s",      "cmk",   
"INESNEI",     "INESNEI",        "",          "",          "s",      "cmn",   
"INESNE",      "INESNÆ",     "",          "",          "s",      "cmg",   
"INESNE",      "INESNE",         "",          "",          "s",      "cmi",   
"INESNEJ",     "INESNËJ",        "",          "",          "s",      "cmw",   
"INESNEJE",    "INESNËJE",       "",          "",          "s",      "cmw",   
"INESNE",      "INESNE",        "",          "",          "s",      "cms",   
"INESNES",     "INESNËS",         "",          "",          "s",      "cmV",   
"INESNIU",     "INESNIØ",     "",          "",          "s",      "cmK",   
"INESNEM",     "INESNËM",       "",          "",          "s",      "cmN",   
"INESNEMS",    "INESNËMS",       "",          "",          "s",      "cmN",   
"INESNES",     "INESNES",        "",          "",          "s",      "cmG",   
"INESNEMIS",   "INESNËMIS",       "",          "",          "s",      "cmI",   
"INESNESE",    "INESNËSE",      "",          "",          "s",      "cmW",   

// ------- reikiamybes dalyvis, vyr. gimine, auksciausias laipsnis
// butiniausias
"INIAUSIAS",    "INIAUSIAS", "",          "",          "s",      "cmv",   
"INIAUSIO",     "INIAUSIO",         "",          "",          "s",      "cmk",   
"INIAUSIAM",    "INIAUSIAM",        "",          "",          "s",      "cmn",   
"INIAUSIA",     "INIAUSIÀ",     "",          "",          "s",      "cmg",   
"INIAUSIU",     "INIAUSIU",         "",          "",          "s",      "cmi",   
"INIAUSIAM",    "INIAUSIAM",        "",          "",          "s",      "cmw",   
"INIAUSIAME",   "INIAUSIAME",       "",          "",          "s",      "cmw",   
"INIAUSIAS",    "INIAUSIAS",        "",          "",          "s",      "cms",   
"INIAUSI",      "INIAUSI",         "",          "",          "s",      "cmV",   
"INIAUSIU",     "INIAUSIØ",     "",          "",          "s",      "cmK",   
"INIAUSIEM",    "INIAUSIEM",       "",          "",          "s",      "cmN",   
"INIAUSIEMS",   "INIAUSIEMS",       "",          "",          "s",      "cmN",   
"INIAUSIUS",    "INIAUSIUS",        "",          "",          "s",      "cmG",   
"INIAUSIAIS",   "INIAUSIAIS",       "",          "",          "s",      "cmI",   
"INIAUSIUOS",   "INIAUSIUOS",       "",          "",          "s",      "cmW",   
"INIAUSIUOSE",  "INIAUSIUOSE",      "",          "",          "s",      "cmW",   

// ------- reikiamybes dalyvis, mot. gimine, auksciausias laipsnis
// butiniausia

"INIAUSIA",      "INIAUSIA", "",          "",          "s",      "cmv",   
"INIAUSIOS",     "INIAUSIOS",         "",          "",          "s",      "cmk",   
"INIAUSIAI",     "INIAUSIAI",        "",          "",          "s",      "cmn",   
"INIAUSIA",      "INIAUSIÀ",     "",          "",          "s",      "cmg",   
"INIAUSIA",      "INIAUSIA",         "",          "",          "s",      "cmi",   
"INIAUSIOJ",     "INIAUSIOJ",        "",          "",          "s",      "cmw",   
"INIAUSIOJE",    "INIAUSIOJE",       "",          "",          "s",      "cmw",   
"INIAUSIA",      "INIAUSIA",        "",          "",          "s",      "cms",   
"INIAUSIOS",     "INIAUSIOS",         "",          "",          "s",      "cmV",   
"INIAUSIU",      "INIAUSIØ",     "",          "",          "s",      "cmK",   
"INIAUSIOM",     "INIAUSIOM",       "",          "",          "s",      "cmN",   
"INIAUSIOMS",    "INIAUSIOMS",       "",          "",          "s",      "cmN",   
"INIAUSIAS",     "INIAUSIAS",        "",          "",          "s",      "cmG",   
"INIAUSIOMIS",   "INIAUSIOMIS",       "",          "",          "s",      "cmI",   
"INIAUSIOSE",    "INIAUSIOSE",      "",          "",          "s",      "cmW",   

// ------- reikiamybes dalyvis, vyr. gimine, ivardziuotine forma
// butinasis
"INASIS",     "INASIS", "",          "",          "s",      "cmv",   
"INOJO",      "INOJO",         "",          "",          "s",      "cmk",   
"INAJAM",     "INAJAM",        "",          "",          "s",      "cmn",   
"INAJI",      "INÀJÁ",     "",          "",          "s",      "cmg",   
"INUOJU",      "INUOJU",         "",          "",          "s",      "cmi",   
"INAJAM",     "INAJAM",        "",          "",          "s",      "cmw",   
"INAJAME",    "INAJAME",       "",          "",          "s",      "cmw",   
"INASIS",     "INASIS",        "",          "",          "s",      "cms",   
"INIEJI",      "INIEJI",         "",          "",          "s",      "cmV",   
"INUJU",      "INØJØ",     "",          "",          "s",      "cmK",   
"INIESIEM",    "INIESIEM",       "",          "",          "s",      "cmN",   
"INIESIEMS",   "INIESIEMS",       "",          "",          "s",      "cmN",   
"INUOSIUS",     "INUOSIUS",        "",          "",          "s",      "cmG",   
"INAISIAIS",    "INAISIAIS",       "",          "",          "s",      "cmI",   
"INUOSIUOS",    "INUOSIUOS",       "",          "",          "s",      "cmW",   
"INUOSIUOSE",   "INUOSIUOSE",      "",          "",          "s",      "cmW",   

// ------- reikiamybes dalyvis, mot. gimine, ivardziuotine forma
// butinoji
"INOJI",      "INOJI", "",          "",          "s",      "cmv",   
"INOSIOS",    "INOSIOS",         "",          "",          "s",      "cmk",   
"INAJAI",     "INAJAI",        "",          "",          "s",      "cmn",   
"INAJA",      "INÀJÀ",     "",          "",          "s",      "cmg",   
"INAJA",      "INÀJA",         "",          "",          "s",      "cmi",   
"INOJOJ",     "INOJOJ",        "",          "",          "s",      "cmw",   
"INOJOJE",    "INOJOJE",       "",          "",          "s",      "cmw",   
"INOJI",      "INOJI",        "",          "",          "s",      "cms",   
"INOSIOS",    "INOSIOS",         "",          "",          "s",      "cmV",   
"INUJU",      "INØJØ",     "",          "",          "s",      "cmK",   
"INOSIOM",    "INOSIOM",       "",          "",          "s",      "cmN",   
"INISIOMS",   "INOSIOMS",       "",          "",          "s",      "cmN",   
"INASIAS",    "INÀSIAS",        "",          "",          "s",      "cmG",   
"INOSIOMIS",  "INOSIOMIS",       "",          "",          "s",      "cmI",   
"INOSIOSE",   "INOSIOSE",      "",          "",          "s",      "cmW",   

// ------- reikiamybes dalyvis, vyr. gimine, ivardziuotine forma, aukstesnysis laipsnis
// butinesnysis
"INESNYSIS",     "INESNYSIS", "",          "",          "s",      "cmv",   
"INESNIOJO",      "INESNIOJO",         "",          "",          "s",      "cmk",   
"INESNIAJAM",     "INESNIAJAM",        "",          "",          "s",      "cmn",   
"INESNIJI",      "INESNÁJÁ",     "",          "",          "s",      "cmg",   
"INESNIUOJU",      "INESNIUOJU",         "",          "",          "s",      "cmi",   
"INESNIAJAM",     "INESNIAJAM",        "",          "",          "s",      "cmw",   
"INESNIAJAME",    "INESNIAJAME",       "",          "",          "s",      "cmw",   
"INESNYSIS",     "INESNYSIS",        "",          "",          "s",      "cms",   
"INESNIEJI",      "INESNIEJI",         "",          "",          "s",      "cmV",   
"INESNIUJU",      "INESNIØJØ",     "",          "",          "s",      "cmK",   
"INESNIESIEM",    "INESNIESIEM",       "",          "",          "s",      "cmN",   
"INESNIESIEMS",   "INESNIESIEMS",       "",          "",          "s",      "cmN",   
"INESNIUOSIUS",     "INESNIUOSIUS",        "",          "",          "s",      "cmG",   
"INESNIAISIAIS",    "INESNIAISIAIS",       "",          "",          "s",      "cmI",   
"INESNIUOSIUOS",    "INESNIUOSIUOS",       "",          "",          "s",      "cmW",   
"INESNIUOSIUOSE",   "INESNIUOSIUOSE",      "",          "",          "s",      "cmW",   

// ------- reikiamybes dalyvis, mot. gimine, ivardziuotine forma, aukstesnysis laipsnis
// butinoji
"INESNIOJI",      "INESNIOJI", "",          "",          "s",      "cmv",   
"INESNIOSIOS",    "INESNIOSIOS",         "",          "",          "s",      "cmk",   
"INESNIAJAI",     "INESNIAJAI",        "",          "",          "s",      "cmn",   
"INESNIAJA",      "INESNIÀJÀ",     "",          "",          "s",      "cmg",   
"INESNIAJA",      "INESNIÀJA",         "",          "",          "s",      "cmi",   
"INESNIOJOJ",     "INESNIOJOJ",        "",          "",          "s",      "cmw",   
"INESNIOJOJE",    "INESNIOJOJE",       "",          "",          "s",      "cmw",   
"INESNIOJI",      "INESNIOJI",        "",          "",          "s",      "cms",   
"INESNIOSIOS",    "INESNIOSIOS",         "",          "",          "s",      "cmV",   
"INESNIUJU",      "INESNIØJØ",     "",          "",          "s",      "cmK",   
"INESNIOSIOM",    "INESNIOSIOM",       "",          "",          "s",      "cmN",   
"INESNIOSIOMS",   "INESNIOSIOMS",       "",          "",          "s",      "cmN",   
"INESNIASIAS",    "INESNIÀSIAS",        "",          "",          "s",      "cmG",   
"INESNIOSIOMIS",  "INESNIOSIOMIS",       "",          "",          "s",      "cmI",   
"INESNIOSIOSE",   "INESNIOSIOSE",      "",          "",          "s",      "cmW",   

// ------- reikiamybes dalyvis, vyr. gimine, ivardziuotine forma, auksciausias laipsnis
// butinasis
"INIAUSIASIS",     "INIAUSIASIS", "",          "",          "s",      "cmv",   
"INIAUSIOJO",      "INIAUSIOJO",         "",          "",          "s",      "cmk",   
"INIAUSIAJAM",     "INIAUSIAJAM",        "",          "",          "s",      "cmn",   
"INIAUSIAJI",      "INIAUSIÀJÁ",     "",          "",          "s",      "cmg",   
"INIAUSIUOJU",      "INIAUSIUOJU",         "",          "",          "s",      "cmi",   
"INIAUSIAJAM",     "INIAUSIAJAM",        "",          "",          "s",      "cmw",   
"INIAUSIAJAME",    "INIAUSIAJAME",       "",          "",          "s",      "cmw",   
"INIAUSIASIS",     "INIAUSIASIS",        "",          "",          "s",      "cms",   
"INIAUSIEJI",      "INIAUSIEJI",         "",          "",          "s",      "cmV",   
"INIAUSIUJU",      "INIAUSIØJØ",     "",          "",          "s",      "cmK",   
"INIAUSIESIEM",    "INIAUSIESIEM",       "",          "",          "s",      "cmN",   
"INIAUSIESIEMS",   "INIAUSIESIEMS",       "",          "",          "s",      "cmN",   
"INIAUSIUOSIUS",     "INIAUSIUOSIUS",        "",          "",          "s",      "cmG",   
"INIAUSIAISIAIS",    "INIAUSIAISIAIS",       "",          "",          "s",      "cmI",   
"INIAUSIUOSIUOS",    "INIAUSIUOSIUOS",       "",          "",          "s",      "cmW",   
"INIAUSIUOSIUOSE",   "INIAUSIUOSIUOSE",      "",          "",          "s",      "cmW",   

// ------- reikiamybes dalyvis, mot. gimine, ivardziuotine forma, auksciausias laipsnis
// butinoji
"INIAUSIOJI",      "INIAUSIOJI", "",          "",          "s",      "cmv",   
"INIAUSIOSIOS",    "INIAUSIOSIOS",         "",          "",          "s",      "cmk",   
"INIAUSIAJAI",     "INIAUSIAJAI",        "",          "",          "s",      "cmn",   
"INIAUSIAJA",      "INIAUSIÀJÀ",     "",          "",          "s",      "cmg",   
"INIAUSIAJA",      "INIAUSIÀJA",         "",          "",          "s",      "cmi",   
"INIAUSIOJOJ",     "INIAUSIOJOJ",        "",          "",          "s",      "cmw",   
"INIAUSIOJOJE",    "INIAUSIOJOJE",       "",          "",          "s",      "cmw",   
"INIAUSIOJI",      "INIAUSIOJI",        "",          "",          "s",      "cms",   
"INIAUSIOSIOS",    "INIAUSIOSIOS",         "",          "",          "s",      "cmV",   
"INIAUSIUJU",      "INIAUSIØJØ",     "",          "",          "s",      "cmK",   
"INIAUSIOSIOM",    "INIAUSIOSIOM",       "",          "",          "s",      "cmN",   
"INIAUSIISIOMS",   "INIAUSIOSIOMS",       "",          "",          "s",      "cmN",   
"INIAUSIASIAS",    "INIAUSIÀSIAS",        "",          "",          "s",      "cmG",   
"INIAUSIOSIOMIS",  "INIAUSIOSIOMIS",       "",          "",          "s",      "cmI",   
"INIAUSIOSIOSE",   "INIAUSIOSIOSE",      "",          "",          "s",      "cmW",   

// ------- pusdalyvis, vyr. gimine
// budamas

".ADAMAS",     ".ADAMAS",     "ADAM",      "ADAM",      "a",      "mv",   
"DAMAS",       "DAMAS",       "T",         "T",         "(",      "ymv",   

"DAMI",        "DAMI",        "T",         "T",         "(",      "ymV",   


// ------- pusdalyvis, mot. gimimine
// busima

"DAMA",        "DAMA",        "T",         "T",         "(",      "yfv",   

"DAMOS",       "DAMOS",       "T",         "T",         "(",      "yfV",   


// ------- padalyvis, esamasis laikas
// bunant, tupiant, puciant, snaudziant

"ANT",         "ANT",      "",          "",          "q",      "q",   
"IANT",        "IANT",     "",          "",          "q",      "q",   
"CIANT",       "ÈIANT",    "T",         "T",         "q",      "q",   
"DZANT",       "DÞANT",    "D",         "D",         "q",      "q",   


// ------- padalyvis, esamasis laikas, sangrazine forma
// tesiantis

"ANTIS",       "ANTIS",       "",          "",          "q",      "qx",   
"IANTIS",      "IANTIS",      "",          "",          "q",      "qx",   
"CANTIS",      "ÈANTIS", "T",         "T",         "q",      "qx",   
"DZANTIS",      "DÞANTIS", "D",         "D",         "q",      "qx",   


// ------- padalyvis, butasis k. laikas
// buvus

"US",          "US",          "",          "",          "r",      "q",   


// ------- padalyvis, butasis k. laikas, sangrazine forma
// praususis

"USIS",        "USIS",        "",          "",          "r",      "qx",   


// ------- padalyvis, butasis d. laikas
// budavus

"DAVUS",       "DAVUS",       "T",         "T",         "(",      "qb",   


// ------- padalyvis, butasis d. laikas
// prausdavusis

"DAVUSIS",     "DAVUSIS",     "T",         "T",         "(",      "qbx",   


// ------- padalyvis, busimasis laikas
// busiant

"IANT",        "IANT",        "",          "",          "s",      "q",   

NULL,          NULL,          NULL,        NULL,        NULL,     NULL
};


// ===================================================
// isimtys, kamieno kaita
// zodziu, neturinciu pagrindines reiksmes, grazinimas i isvestine reiksme (dometis)
//  pirma kolonele nurodo pagr. zodzio forma ir galima pagr. formos pasikeitima
//
//  antra/trecia koloneles - zodzio forma, automatiskai atmetus galunes
//
//  ketvirta/penkta koloneles - i ka reikia atstatyti (sugadinta sakni)
//
//  antra ir ketvirta koloneles - trecios ir penktos koloneles variantai be diakritu
//

char *plpszaUnRegForms_l[] =
{

   "LO",       "PASK",       "PASK",       "PASKUTIN",  "PASKUTIN",   // paskesnis - paskutinis (keitimas is 
                                                                     //  aukstesniojo laipsnio i nelyginamaji)

// kelintiniai skaitvardziai - kiekiniai skaitvardziai
   "]1",       "PIRM",       "PIRM",        "VIEN",        "VIEN",    
   "]2",       "ANTR",       "ANTR",        "DU",          "DU",    
   "]3",       "TRET",       "TRET",        "TR",          "TR",    
   "]4",       "KETVIRT",    "KETVIRT",     "KETUR",       "KETUR",    
   "]4",       "SEPTINT",    "SEPTINT",     "SEPTYN",      "SEPTYN",    
   "]4",       "ASTUNT",     "AÐTUNT", "ASTUON",      "AÐTUON",    
   "]4",       "DEVINT",     "DEVINT",      "DEVYN",       "DEVYN",    
// "]4",       "T",          "T",           "",            "",   // penktas, sestas, bet desimtas !!!, be to gram. formos dar ne iki galo realizuotos
// "]0",       "T",          "T",           "",            "",   // vienuoliktas, dvyliktas, ..., bet desimtas !!!, be to gram. formos dar ne iki galo realizuotos
// "*[",       "IN",         "IN",          "",            "",   // simtinis, tukstantinis, milijoninis, ..., gram. formos dar ne iki galo realizuotos !!!
   "]@",       "",           "",            "",            "",   // -desimtas 
   "][",       "",           "",            "",            "",   // simtasis, tukstantasis 

// sangraziniai veiksmazodziai be reiksmes paprastos bendraties formoje

//   "))",       ".DOMET",        ".DOMËT",     "DOMETIS"/*"DOMETIS."*/,                 "DOMËTIS"/*"DOMËTIS."*/,
//   "))",       ".DZIAUGT",      ".DÞIAUGT", "DZIAUGTIS"/*"DZIAUGTIS."*/,             "DÞIAUGTIS"/*"DÞIAUGTIS."*/,
//   "))",       ".JUOKT",        ".JUOKT",        "JUOKTIS"/*"JUOKTIS."*/,                 "JUOKTIS"/*"JUOKTIS."*/,
//   "))",       ".NIAUKT",       ".NIAUKT",       "NIAUKTIS"/*"NIAUKTIS."*/,               "NIAUKTIS"/*"NIAUKTIS."*/,
// "))",         ".GERET",        ".GËRËT",  "GERETIS"/*"GERETIS."*/,                 "GËRËTIS"/*"GËRËTIS."*/,
//// "))",       ".STEBET",       ".STEBËT",    "STEBETIS"/*"STEBETIS."*/,               "STEBËTIS"/*"STEBËTIS."*/,
// "))",         ".STEBET",       ".STEBËT",    "STEBE",                                 "STEBË",   // stebeti 
// "))",         ".SYPSOT",       ".ÐYPSOT",  "SYPSOTIS"/*"SYPSOTIS."*/,               "ÐYPSOTIS"/*"ÐYPSOTIS."*/,
//// "))",       ".LAUKT",        ".LAUKT",        "LAUKTIS"/*"LAUKTIS."*/,                 "LAUKTIS"/*"LAUKTIS."*/,
//// "))",       ".LAUKT",        ".LAUKT",        "LAUK",                                  "LAUK",   // laukti 
//// "))",       ".TIKET",        ".TIKËT",     "TIKETIS"/*"TIKETIS."*/,                 "TIKËTIS"/*"TIKËTIS."*/,
//// "))",       ".TIKET",        ".TIKËT",     "TIKE",                                  "TIKË",   // tiketi 
//// "))",       "MUISTYT",       "MUISTYT",       "MUISTYTIS"/*"MUISTYTIS."*/,             "MUISTYTIS"/*"MUISTYTIS."*/,
//// "))",       "MUISTYT",       "MUISTYT",       "MUISTY",                                "MUISTY",   // pasimuistyti 

// painiava tarp neveikiamuju dalyviu ir daiktavardziu - "-tas", "-tus", -amas, ...


// ")A",       ".NAM",            ".NAM",            "NAM",           "NAM",           // namas - suveikia "amas"
   ")A",       "KNAT",            "KNAT",            "KNAT",          "KNAT",          // knatas - suveikia "tas", pjaunasi su rasti
   ")A",       "KNUT",            "KNUT",            "KNUT",          "KNUT",          // knutas - suveikia "tas", pjaunasi su rasti
   ")A",       ".RAT",            ".RAT",            "RAT",           "RAT",           // ratas - suveikia "tas", pjaunasi su rasti
   ")A",       "PIRAT",           "PIRAT",           "PIRAT",         "PIRAT",         // piratas - suveikia "tas", pjaunasi su rasti
   ")A",       "KVADRAT",         "KVADRAT",         "KVADRAT",       "KVADRAT",       // kvadratas - suveikia "tas", pjaunasi su rasti
   ")A",       "RAST",            "RAST",            "RAST",          "RAST",          // rastas - suveikia "tas", pjaunasi su rasti
   ")A",       "RAST",            "RAÐT",       "RAST",          "RAÐT",   // rastas - suveikia "tas" 
   ")A",       "MIEST",           "MIEST",           "MIEST",         "MIEST",   // miestas - suveikia "tas" 
   "))",       "UIST",            "UIST",            "UIS",           "UIS",   // sukuistas 
   "))",       "AIST",            "AIST",            "AIS",           "AIS",   // uzkaistas, suzaistas 
   "))",       "EIST",            "EIST",            "EIS",           "EIS",   // atleistas, pakeistas, geistas - pjaunasi su keistas - o kur pats "keistas" ??? !!! 
   ")A",       "UTOPIST",         "UTOPIST",         "UTOPIST",       "UTOPIST",   // utopistas 
   "))",       "PIST",            "PIST",            "PIS",           "PIS",   // nacionalistas, masinistas, socialistas, fasistas, komunistas, ateistas, baptistas, metodistas, budistas, 
   ")A",       "IST",             "IST",             "IST",           "IST",   // nacionalistas, masinistas, socialistas, fasistas, komunistas, ateistas, baptistas, metodistas, budistas, 
   ")A",       "ADVOKAT",         "ADVOKAT",         "ADVOKAT",       "ADVOKAT",   // advokatas - suveikia "tas" 
   ")A",       "ARIAT",           "ARIAT",           "ARIAT",         "ARIAT",   // proletariatas, sariatas, notariatas - suveikia "tas" 
   ")A",       "AGENT",           "AGENT",           "AGENT",         "AGENT",   // (re)agentas - suveikia "tas" 
   ")A",       "SPURT",           "SPURT",           "SPURT",         "SPURT",   // spurtas - suveikia "tas" 
   ")A",       "SPORT",           "SPORT",           "SPORT",         "SPORT",   // sportas - suveikia "tas" 
   ")A",       "TORT",            "TORT",            "TORT",          "TORT",   // tortas - suveikia "tas" 
   ")A",       "REKTORAT",        "REKTORAT",        "REKTORAT",      "REKTORAT",   // (di)rektoratas - suveikia "tas" 
   ")A",       "DOKTORAT",        "DOKTORAT",        "DOKTORAT",      "DOKTORAT",   // doktoratas - suveikia "tas" 
   ")A",       "DEKANAT",         "DEKANAT",         "DEKANAT",       "DEKANAT",   // dekanatas - suveikia "tas" 
   ")A",       "REZULTAT",        "REZULTAT",        "REZULTAT",      "REZULTAT",   // rezultatas - suveikia "tas" 
   ")A",       "JEKT",            "JEKT",            "JEKT",          "JEKT",   // projektas, objektas - suveikia "tas" 
   ")A",       "STIUART",         "STIUART",         "STIUART",       "STIUART",   // stiuartas - suveikia "tas" 
   ")A",       "NORBERT",         "NORBERT",         "NORBERT",       "NORBERT",   // norbertas - suveikia "tas" 
   ")A",       "HERBERT",         "HERBERT",         "HERBERT",       "HERBERT",   // herbertas - suveikia "tas" 
   ")A",       "ALBERT",          "ALBERT",          "ALBERT",        "ALBERT",   // albertas - suveikia "tas" 
   ")A",       "ROBERT",          "ROBERT",          "ROBERT",        "ROBERT",   // robertas - suveikia "tas" 
   ")A",       "LANKST",          "LANKST",          "LANKST",        "LANKST",   // lankstas - suveikia "tas" 
   ")A",       "TAIMAUT",         "TAIMAUT",         "TAIMAUT",       "TAIMAUT",   // taimautas - suveikia "tas" 
   ")A",       "LOKAUT",          "LOKAUT",          "LOKAUT",        "LOKAUT",   // lokautas - suveikia "tas" 
   ")A",       ".AUT",            ".AUT",            "AUT",           "AUT",   // autas - suveikia "tas" - pjaunasi su (ap)auti 
   ")A",       "SPAST",           "SPÀST",       "SPAST",         "SPÀST",   // spastai - suveikia "tai" 
   ")A",       ".KALT",           ".KALT",           "KALT",          "KALT",   // kaltas - suveikia "tas" - pjaunasi su (i)kaltas 
   ")A",       "PALT",            "PALT",            "PALT",          "PALT",   // paltas - suveikia "tas" 
   ")A",       ".RYT",            ".RYT",            "RYT",           "RYT",   // rytas - suveikia "tas" - pjaunasi su (pra)rytas 
   ")A",       "TREST",           "TREST",           "TREST",         "TREST",   // trestas - suveikia "tas" 
   ")A",       "LIAT",            "LIAT",            "LIAT",          "LIAT",   // jubiliatas - suveikia "tas" 
   ")A",       "LAUREAT",         "LAUREAT",         "LAUREAT",       "LAUREAT",   // surogatas - suveikia "tas" 
   ")A",       "SUROGAT",         "SUROGAT",         "SUROGAT",       "SUROGAT",   // surogatas - suveikia "tas" 
   ")A",       "FABRIKAT",        "FABRIKAT",        "FABRIKAT",      "FABRIKAT",   // fabrikatas - suveikia "tas" 
   ")A",       ".GEST",           ".GEST",           "GEST",          "GEST",   // gestas - suveikia "tas" - pjaunasi su gesti 
   ")A",       "MANIFEST",        "MANIFEST",        "MANIFEST",      "MANIFEST",   // manifestas - suveikia "tas" 
   ")A",       "PROTEST",         "PROTEST",         "PROTEST",       "PROTEST",   // protestas - suveikia "tas" 
   ")A",       "VAIST",           "VAIST",           "VAIST",         "VAIST",   // vaistas - suveikia "tas" 
   ")A",       "MAIST",           "MAIST",           "MAIST",         "MAIST",   // maistas - suveikia "tas" 
   ")A",       "REGENT",          "REGENT",          "REGENT",        "REGENT",   // regentas - suveikia "tas" 
   ")A",       "PREZIDENT",       "PREZIDENT",       "PREZIDENT",     "PREZIDENT",   // prezidentas - suveikia "tas" 
   ")A",       "ZENT",            "ZENT",            "ZENT",          "ZENT",   // brezentas, prezentas - suveikia "tas" 
   ")A",       "TENT",            "TENT",            "TENT",          "TENT",   // tentas, patentas - suveikia "tas" 
   ")A",       "STANDART",        "STANDART",        "STANDART",      "STANDART",   // standartas - suveikia "tas" 
   ")A",       "ETAT",            "ETAT",            "ETAT",          "ETAT",   // etatas - suveikia "tas" 
   ")A",       "GIGANT",          "GIGANT",          "GIGANT",        "GIGANT",   // gigantas - suveikia "tas" 
   ")A",       "TORANT",          "TORANT",          "TORANT",        "TORANT",   // doktorantas - suveikia "tas" 
   ")A",       "TRANT",           "TRANT",           "TRANT",         "TRANT",   // magistrantas - suveikia "tas" 
   ")A",       "LVENT",           "LVENT",           "LVENT",         "LVENT",   // absolventas - suveikia "tas" 
   ")A",       "ABITURIENT",      "ABITURIENT",      "ABITURIENT",    "ABITURIENT",   // abiturientas - suveikia "tas" 
   ")A",       "RBENT",           "RBENT",           "RBENT",         "RBENT",   // sorbentas, absorbentas, serbentas - suveikia "tas" 
   ")A",       "PATRIANT",        "PATRIANT",        "PATRIANT",      "PATRIANT",   // ekspatriantas, repatriantas - suveikia "tas" 
   ")A",       "UNIVERSITET",     "UNIVERSITET",     "UNIVERSITET",   "UNIVERSITET",   // universitetas - suveikia "tas" 
   ")A",       "INSTITUT",        "INSTITUT",        "INSTITUT",      "INSTITUT",   // institutas - suveikia "tas" 
   ")A",       "MENT",            "MENT",            "MENT",          "MENT",   // departamentas, mentas, alimentas, suplementas, ekskrementas, argumentas - suveikia "tas" 
   ")A",       "DISKONT",         "DISKONT",         "DISKONT",       "DISKONT",   // diskontas - suveikia "tas" 
   ")A",       "DISKANT",         "DISKANT",         "DISKANT",       "DISKANT",   // diskantas - suveikia "tas" 
   ")A",       "DIKTANT",         "DIKTANT",         "DIKTANT",       "DIKTANT",   // diktantas - suveikia "tas" 
   ")A",       "DISKRIMINANT",    "DISKRIMINANT",    "DISKRIMINANT",  "DISKRIMINANT",   // diskriminantas - suveikia "tas" 
   ")A",       "DETERMINANT",     "DETERMINANT",     "DETERMINANT",   "DETERMINANT",   // determinantas - suveikia "tas" 
   ")A",       "JUNKT",           "JUNKT",           "JUNKT",         "JUNKT",   // adjunktas - suveikia "tas" 
   ")A",       "MANT",            "MANT",            "MANT",          "MANT",   // mantas - suveikia "tas" 
   ")A",       "KRANT",           "KRANT",           "KRANT",         "KRANT",   // krantas - suveikia "tas" 
   ")A",       "GRANT",           "GRANT",           "GRANT",         "GRANT",   // grantas - suveikia "tas" 
   ")A",       "LIMIT",           "LIMIT",           "LIMIT",         "LIMIT",   // srautas - suveikia "tas" 
   ")A",       "SRAUT",           "SRAUT",           "SRAUT",         "SRAUT",   // srautas - suveikia "tas" 
   ")A",       ".AUT",            ".AUT",            "AUT",           "AUT",   // autas - suveikia "tas" - pjaunasi su (ap)autas 
// ")A",       "PLAUT",           "PLAUT",           "PLAUT",         "PLAUT",   // plautas - suveikia "tas" - pjaunasi su plautas 
   ")A",       "PAUT",            "PAUT",            "PAUT",          "PAUT",   // pautas - suveikia "tas" 
   ")A",       "AUKST",           "AUKÐT",      "AUKST",         "AUKÐT",   // aukstas, saukstas - suveikia "tas" 
   ")A",       "SVERT",           "SVERT",           "SVERT",         "SVERT",   // svertas - suveikia "tas" 
   ")A",       "DEFICIT",         "DEFICIT",         "DEFICIT",       "DEFICIT",   // deficitas - suveikia "tas" 
   ")A",       "HOT",             "HOT",             "HOT",           "HOT",   // bedzhotas - suveikia "tas" 
   ")A",       "ASFALT",          "ASFALT",          "ASFALT",        "ASFALT",   // asfaltas - suveikia "tas" 
   ")A",       "KOBALT",          "KOBALT",          "KOBALT",        "KOBALT",   // kobaltas - suveikia "tas" 
   ")A",       "PASAT",           "PASAT",           "PASAT",         "PASAT",   // pasatas - suveikia "tas" 
   ")A",       "PRODUKT",         "PRODUKT",         "PRODUKT",       "PRODUKT",   // produktas - suveikia "tas" 
   ")A",       "BANKNOT",         "BANKNOT",         "BANKNOT",       "BANKNOT",   // banknotas - suveikia "tas" 
   ")A",       "BANKROT",         "BANKROT",         "BANKROT",       "BANKROT",   // bankrotas - suveikia "tas" 
   ")A",       "FEKT",            "FEKT",            "FEKT",          "FEKT",   // efektas, afektas - suveikia "tas" 
   ")A",       "PORT",            "PORT",            "PORT",          "PORT",   // importas, exportas - suveikia "tas" 
   ")A",       "PUNKT",           "PUNKT",           "PUNKT",         "PUNKT",   // punktas - suveikia "tas" 
   ")A",       "PROT",            "PROT",            "PROT",          "PROT",   // protas - suveikia "tas" 
   ")A",       "IENT",            "IENT",            "IENT",          "IENT",   // koeficientas, gradientas - suveikia "tas" 
   ")A",       "TURT",            "TURT",            "TURT",          "TURT",   // turtas - suveikia "tas" 
   ")A",       ".KURT",           ".KURT",           "KURT",          "KURT",   // kurtas - suveikia "tas" 
   ")A",       ".PAT",            ".PAT",            "PAT",           "PAT",   // patas - suveikia "tas" 
   ")A",       "MUIT",            "MUIT",            "MUIT",          "MUIT",   // muitas - suveikia "tas" 
   ")A",       "MAST",            "MAST",            "MAST",          "MAST",   // mastas - suveikia "tas" 
   ")A",       "MAT",             "MAT",             "MAT",           "MAT",   // matas, kompromatas - suveikia "tas" 
   ")A",       "BAT",             "BAT",             "BAT",           "BAT",   // batas - suveikia "tas" 
   ")A",       "RAT",             "RAT",             "RAT",           "RAT",   // ratas - suveikia "tas" 
   ")A",       "AKT",             "AKT",             "AKT",           "AKT",   // raktas, aktas - suveikia "tas" 
   ")A",       "LAKST",           "LAKÐT",      "LAKST",         "LAKÐT",   // lakstas - suveikia "tas" 
   ")A",       "KAST",            "KAÐT",       "KAST",          "KAÐT",   // kastai - suveikia "tu" 
   ")A",       "STAKIET",         "ÐTAKIET",    "STAKIET",       "ÐTAKIET",   // stakietas - suveikia "tas" 
   ")A",       "MIET",            "MIET",            "MIET",          "MIET",   // mietas - suveikia "tas" 
   ")A",       "ARST",            "ARST",            "ARST",          "ARST",   // karstas, varstas - suveikia "tas" 
   ")A",       "BUCST",           "BÛCST",       "BUCST",         "BÛCST",   // bustas - suveikia "tas" 
   ")A",       ".RIET",           ".RIET",           "RIET",          "RIET",   // rietas - suveikia "tas" 
   ")A",       ".UOT",            ".UOT",            "UOT",           "UOT",   // uotas - suveikia "tas" 
   ")A",       ".KOT",            ".KOT",            "KOT",           "KOT",   // kotas - suveikia "tas" 
   ")A",       ".MOT",            ".MOT",            "MOT",           "MOT",   // motais - suveikia "tais" 
   ")A",       "ABSOLIUT",        "ABSOLIUT",        "ABSOLIUT",      "ABSOLIUT",   // absoliutas - suveikia "tas" 
   ")A",       "ANKST",           "ANKST",           "ANKST",         "ANKST",   // (is) anksto - suveikia "to" 
   ")A",       ".KART",           ".KART",           "KART",          "KART",   // kartas - suveikia "tas" - pjaunasi su (pa)karti 
   ")C",       ".KART",           ".KART",           "KART",          "KART",   // karta - suveikia "ta" - pjaunasi su (pa)karti 
   ")C",       "SPART",           "SPART",           "SPART",         "SPART",   // sparta - suveikia "ta" 
   ")C",       "TAUT",            "TAUT",            "TAUT",          "TAUT",   // tauta - suveikia "ta" 
   ")C",       "BRAST",           "BRAST",           "BRAST",         "BRAST",   // brasta - suveikia "ta" 
   ")C",       "SKAT",            "SKAT",            "SKAT",          "SKAT",   // paskata - suveikia "ta" 
   "))",       "PJAUT",           "PJAUT",           "PJAU",          "PJAU",   // pjauti, spjauti 
   ")C",       "JAUT",            "JAUT",            "JAUT",          "JAUT",   // savijauta, atjauta - suveikia "ta" 
   ")C",       "PRAVAIKST",       "PRAVAIKÐT",  "PRAVAIKST",     "PRAVAIKÐT",   // pravaiksta - suveikia "ta" 
   ")C",       "SKAIT",           "SKAIT",           "SKAIT",         "SKAIT",   // paskaita, saskaita, iskaita  - suveikia "ta" 
   ")C",       "RENT",            "RENT",            "RENT",          "RENT",   // renta  - suveikia "ta" 
   ")C",       "VIST",            "VIÐT",       "VIST",          "VIÐT",   // vista - suveikia "ta" 
// ")C",       "ATKIRT",          "ATKIRT",          "ATKIRT",        "ATKIRT",   // atkirta - suveikia "ta" 
   ")C",       "LENT",            "LENT",            "LENT",          "LENT",   // lenta - suveikia "ta" 
   ")C",       "PLYT",            "PLYT",            "PLYT",          "PLYT",   // plyta - suveikia "ta" 
   ")C",       "STAT",            "STAT",            "STAT",          "STAT",   // nuostata, akistata - suveikia "ta" 
   ")C",       "MANT",            "MANT",            "MANT",          "MANT",   // manta - suveikia "ta" 
   ")C",       "VALIUT",          "VALIUT",          "VALIUT",        "VALIUT",   // valiuta - suveikia "ta" 
   ")C",       "NAST",            "NAÐT",       "NAST",          "NAÐT",   // nasta - suveikia "ta" 
   ")C",       "GUZT",            "GÛÞT",   "GUZT",          "GÛÞT",   // guzta - suveikia "ta" 
   ")C",       "GAMT",            "GAMT",            "GAMT",          "GAMT",   // gamta - suveikia "ta" 
// ")C",       "BLET",            "BLËT",         "BLET",          "BLËT",   // bleta - suveikia "ta" 
   ")C",       "KVOT",            "KVOT",            "KVOT",          "KVOT",   // kvota - suveikia "ta" 
   ")C",       "PUOT",            "PUOT",            "PUOT",          "PUOT",   // puota - suveikia "ta" 
   ")C",       ".SLUOT",          ".ÐLUOT",     "SLUOT",         "ÐLUOT",   // sluota - suveikia "ta" - pjaunasi su sluota, sluoti(s) 
   ")C",       "NAFT",            "NAFT",            "NAFT",          "NAFT",   // nafta - suveikia "ta" 
   ")C",       "DAT",             "DAT",             "DAT",           "DAT",   // data - suveikia "ta" 
   ")C",       "NAT",             "NAT",             "NAT",           "NAT",   // nata - suveikia "ta" 
   ")C",       "KET",             "KET",             "KET",           "KET",   // keta - suveikia "ta" 
   ")H",       "KET",             "KET",             "KET",           "KET",   // ketus - suveikia "tus" 
   ")L",       "KIET",            "KIET",            "KIET",          "KIET",   // kietas(-a) - suveikia "tas" 
   ")L",       "GREIT",           "GREIT",           "GREIT",         "GREIT",   // greitas(-a) - suveikia "tas" 
   ")L",       "GRIEZT",          "GRIEÞT",     "GRIEZT",        "GRIEÞT",   // grieztas(-a) - suveikia "tas" - pjaunasi su griezti 
   ")L",       ".KALT",           ".KALT",           "KALT",          "KALT",   // kaltas - suveikia "tas" - pjaunasi su (i)kaltas 
   ")L",       "BALT",            "BALT",            "BALT",          "BALT",   // baltas(-a) - suveikia "tas" 
   ")L",       "PRAST",           "PRAST",           "PRAST",         "PRAST",   // (pa)prastas(-a)(-ai) - suveikia "tas" 
   ")L",       "AUKST",           "AUKÐT",      "AUKST",         "AUKÐT",   // aukstas - suveikia "tas" 

   ")L",       "LEST",            "LËÐT",    "LEST",          "LËÐT",   // lekstas - suveikia "tas" 
   ")L",       "BLET",            "BLËT",         "BLET",          "BLËT",   // gruobletas - suveikia "tas" 
   ")L",       "PLET",            "PLËT",         "PLET",          "PLËT",   // raupletas - suveikia "tas" 
   ")L",       "RASTUOT",         "RAÐTUOT",    "RASTUOT",       "RAÐTUOT",   // rastuotas - suveikia "tas" 
   ")L",       "GUOT",            "GUOT",            "GUOT",          "GUOT",   // languotas, raguotas - suveikia "tas" 
   ")L",       "KEIST",           "KEIST",           "KEIST",         "KEIST",   // keistas - suveikia "tas" - pjaunasi su (pa)keistas 
   ")L",       "MINKST",          "MINKÐT",     "MINKST",        "MINKÐT",   // minkstas - suveikia "tas" - pjaunasi su (pa)keistas 
   ")L",       "AKYT",            "AKYT",            "AKYT",          "AKYT",   // akytas - suveikia "tas" 
   ")L",       "TVIRT",           "TVIRT",           "TVIRT",         "TVIRT",   // tvirtas - suveikia "tas" 
   ")L",       "KARST",           "KARÐT",      "KARST",         "KARÐT",   // karstas - suveikia "tas" 
   ")L",       "SALT",            "ÐALT",       "SALT",          "ÐALT",   // saltas - suveikia "tas" 
   ")L",       "RET",             "RET",             "RET",           "RET",   // retas - suveikia "tas" 
   "),",       ".KIT",            ".KIT",       ".KIT",          ".KIT",   // kitas(-a), sitas(-a) - suveikia "tas" 
   "),",       ".T",              ".T",              ".T",            ".T",   // tas(-a) - suveikia "tas" 
   ")]",       "KETVIRT",         "KETVIRT",         "KETVIRT",       "KETVIRT",   // ketvirtas(-a) - suveikia "tas" 
   ")]",       "PENKT",           "PENKT",           "PENKT",         "PENKT",   // penktas(-a) - suveikia "tas" 
   ")]",       "SEST",            "ÐEÐT",  "SEST",          "ÐEÐT",   // sestas(-a) - suveikia "tas" 
   ")]",       "SEPTINT",         "SEPTINT",         "SEPTINT",       "SEPTINT",   // septintas(-a) - suveikia "tas" 
   ")]",       "ASTUNT",          "AÐTUNT",     "ASTUNT",        "AÐTUNT",   // astuntas(-a) - suveikia "tas" 
   ")]",       "DEVINT",          "DEVINT",          "DEVINT",        "DEVINT",   // devintas(-a) - suveikia "tas" 
   ")]",       "DESIMT",          "DEÐIMT",     "DESIMT",        "DEÐIMT",   // desimtas(-a) - suveikia "tas" 
   ")]",       "OLIKT",           "OLIKT",           "OLIKT",         "OLIKT",   // vienuoliktas(-a), keturioliktas, ... - suveikia "tas" 
   ")]",       "YLIKT",           "YLIKT",           "YLIKT",         "YLIKT",   // dvyliktas(-a), tryliktas - suveikia "tas" 

   ")N",       "PLAT",            "PLAT",            "PLAT",          "PLAT",   // platus - suveikia "tesnis" 
   ")N",       "GRAKST",          "GRAKÐT",     "GRAKST",        "GRAKÐT",   // grakstus - suveikia "tesnis" 

   ")E",       ".Z",              ".Þ",         "ZEM",           "ÞEM", // zemes - suveikia "emes" !!! neveikia
   ")P",       "POKYT",           "POKYT",           "POKYT",         "POKYT",   // pokytis - suveikia "tis" 
   ")P",       "SLENKST",         "SLENKST",         "SLENKST",       "SLENKST",   // slenkstis - suveikia "tis" 
   ")P",       ".JAUT",           ".JAUT",           "JAUT",          "JAUT",   // jautis - suveikia "tis" 
   ")P",       "FABRIKAT",        "FABRIKAT",        "FABRIKAT",      "FABRIKAT",   // pusfabrikatis - suveikia "tis" 
   ")P",       "LIKUT",           "LIKUT",           "LIKUT",         "LIKUT",   // likutis - suveikia "tis" 
   ")P",       "KEST",            "KEST",            "KEST",          "KEST",   // mokestis - suveikia "tis" 
   ")P",       "LEST",            "LEST",            "LEST",          "LEST",   // gailestis - suveikia "tis" 
   ")P",       "VALKT",           "VALKT",           "VALKT",         "VALKT",   // valktis - suveikia "tis" 
   "))",       ".LIET",           ".LIET",           "LIE",           "LIE",   // lietis 
   ")P",       "IET",             "IET",             "IET",           "IET",   // kietis, akvinietis, grietinietis - suveikia "tis" 
   ")P",       "KIRT",            "KIRT",            "KIRT",          "KIRT",   // kirtis - suveikia "tis" 
   ")P",       "KIRT",            "KIRT",            "KIRT",          "KIRT",   // kirtis - suveikia "tis" 
   ")P",       "VART",            "VART",            "VART",          "VART",   // ivartis - suveikia "tis" 
   ")P",       "KRYT",            "KRYT",            "KRYT",          "KRYT",   // nuokrytis - suveikia "tis" 
   ")G",       "VALT",            "VALT",            "VALT",          "VALT",   // valtis - suveikia "tis" 
   ")G",       "PALT",            "PALT",            "PALT",          "PALT",   // paltis - suveikia "tis" 
   ")G",       "PANT",            "PANT",            "PANT",          "PANT",   // paltis - suveikia "tis" 
   ")G",       ".ANT",            ".ANT",            "ANT",           "ANT",           // antis - suveikia "tis", "antis"
   ")G",       ".AN",             ".AN",             "ANT",           "ANT",           // antis - suveikia "ciai", "anciai"
   ")G",       "SUTART",          "SUTART",          "SUTART",        "SUTART",   // sutartis - suveikia "tis" 
   ")G",       "LYGT",            "LYGT",            "LYGT",          "LYGT",   // lygtis - suveikia "tis" - pjaunasi su lygtis (susilygti) 
   ")G",       "ZAST",            "ÞAST",       "ZAST",          "ÞAST",   // priezastis - suveikia "tis" 
   ")G",       "NAKT",            "NAKT",            "NAKT",          "NAKT",   // naktis - suveikia "tis" 
   ")G",       "KLIUT",           "KLIÛT",       "KLIUT",         "KLIÛT",   // kliutis - suveikia "tis" 
   ")G",       "PIRT",            "PIRT",            "PIRT",          "PIRT",   // pirtis, paspirtis - suveikia "tis" 
   ")G",       "MIRT",            "MIRT",            "MIRT",          "MIRT",   // mirtis - suveikia "tis" 
   ")G",       "VILT",            "VILT",            "VILT",          "VILT",   // viltis - suveikia "tis" 
   ")G",       "PASKIRT",         "PASKIRT",         "PASKIRT",       "PASKIRT",   // paskirtis - suveikia "tis" - pjaunasi su paskirti 
   ")G",       "VIENAT",          "VIENAT",          "VIENAT",        "VIENAT",   // vienatis - suveikia "tis" 
   ")G",       "BENDRAT",         "BENDRAT",         "BENDRAT",       "BENDRAT",   // bendratis - suveikia "tis" 
   ")G",       "MAISAT",          "MAIÐAT",     "MAISAT",        "MAIÐAT",   // maisatis - suveikia "tis" 
   ")G",       "UZDUOT",          "UÞDUOT",     "UZDUOT",        "UÞDUOT",   // maisatis - suveikia "tis" 
   ")G",       "NETEKT",          "NETEKT",          "NETEKT",        "NETEKT",   // netektis - suveikia "tis" - pjaunasi su netekti 
   ")G",       "BENDRAT",         "BENDRAT",         "BENDRAT",       "BENDRAT",   // bendratis - suveikia "tis" 
   ")G",       ".IMT",            ".IMT",            "IMT",           "IMT",   // imtis - suveikia "tis" - pjaunasi su imti 
   ")G",       "APIMT",           "APIMT",           "APIMT",         "APIMT",   // apimtis - suveikia "tis" - pjaunasi su apimti 
   ")G",       "PADET",           "PADËT",        "PADET",         "PADËT",   // padetis - suveikia "tis" - pjaunasi su padeti 
   ")G",       "SUDET",           "SUDËT",        "SUDET",         "SUDËT",   // sudetis - suveikia "tis" - pjaunasi su sudeti 
   ")G",       "ATIMT",           "ATIMT",           "ATIMT",         "ATIMT",   // atimtis - suveikia "tis" - pjaunasi su atimti 

   ")N",       "ABSOLIUT",        "ABSOLIUT",        "ABSOLIUT",      "ABSOLIUT",   // absoliutus - suveikia "tus" 

   ") ",       "SANKT",           "SANKT",           "SANKT",         "SANKT",   // sankt - suveikia "t" 

// "))",       "T",               "T",               "",              "",   // bendraties formos sutrumpintos tik iki -t, "T" minksteja i "È" - pjaunasi su budvardziais ("2m...") !!!, gram. formos dar ne iki galo realizuotos !!!

// veiksmazodziu esamojo ir butojo k. laiku vertimas i bendrati

   "Q)",       "SAL",         "ÐÀL",         "SALT",         "ÐALT",   // sala - salti 
   "Q)",       "BAL",         "BÀL",         "BALT",         "BALT",   // bala - balti 
   "Q)",       "SAL",         "SÀL",         "SALT",         "SALT",   // sala - salti 
   "Q)",       "TEZT",        "TÆÞT",        "TEZT",         "TEÞT",   // tezta - tezti 
   "Q)",       "GLEZT",       "GLÆÞT",       "GLEZT",        "GLEÞT",   // glezta - glezti 
   "Q)",       "SAST",        "ÐÀÐT",        "SAST",         "ÐAÐT",   // sasta - sasti 
   "Q)",       "MAZT",        "MÀÞT",        "MAZT",         "MAÞT",   // mazta - mazti 
   "Q)",       "TREST",       "TRÆÐT",       "TREST",        "TREÐT",   // tresta - tresti 
   "Q)",       "GEST",        "GÆST",        "GEST",         "GEST",   // gesta - gesti 

   "Q)",       "KAIST",       "KAIST",       "KAIST",        "KAIST",   // kaista - kaisti 
      "R)",    "PRIKAIT",     "PRIKAIT",     "PRIKAIST",     "PRIKAIST",   // prikaito, prikaite - prikaisti 
      "R)",    "UZKAIT",      "UÞKAIT",      "UZKAIST",      "UÞKAIST",   // uzkaito, uzkaite - uzkaisti 
      "R)",    "PAKAIT",      "PAKAIT",      "PAKAIST",      "PAKAIST",   // pakaite - pakaisti 
      "R)",    "NUKAIT",      "NUKAIT",      "NUKAIST",      "NUKAIST",   // nukaito - nukaisti 
//    "R)",    "IKAIT",       "ÁKAIT",       "IKAIST",       "ÁKAIST",   // ikaito - ikaisti - pjaunasi su ikaitas 
      "R)",    ".KAIT",       ".KAIT",       "KAIST",        "KAIST",   // kaito - kaisti 
//    "R)",    "AIT",         "AIT",         "AIST",         "AIST",   // kaito - kaisti - pjaunasi su -aite 
   "Q)",       "JAUT",        "JAUT",        "JAUST",        "JAUST",   // jaucia - jausti 
      "R)",    "JAUT",        "JAUT",        "JAUST",        "JAUST",   // jaute - jausti 
   "Q)",       "SNAUD",       "SNAUD",       "SNAUST",       "SNAUST",   // snaudzia - snausti 
      "QC",    "NAUD",        "NAUD",        "NAUD",         "NAUD",   // nauda - suveikia "AUD" 
      "Q)",    "AUD",         "AUD",         "AUST",         "AUST",   // baudzia - bausti, audzia 
//    "R)",    "UD",          "UD",          "UST",          "UST",   // baude - bausti, dar: budo - busti - zr. toliau 
   "Q)",       "KEIT",        "KEIT",        "KEIST",        "KEIST",   // keicia - keisti 
      "R)",    "KEIT",        "KEIT",        "KEIST",        "KEIST",   // keite - keisti 
   "Q)",       "EID",         "EID",         "EIST",         "EIST",   // leidzia - leisti 
      "R)",    "EID",         "EID",         "EIST",         "EIST",   // leido - leisti 
   "QC",       "PIET",        "PIET",        "PIET",        "PIET",   // pieta 
      "Q)",    "KVIET",       "KVIET",       "KVIEST",       "KVIEST",   // kviecia - kviesti 
      "QC",    "VIET",        "VIET",        "VIET",        "VIET",   // vieta 
      "QC",    "DIET",        "DIET",        "DIET",        "DIET",   // dieta 
      "QC",    "HENRIET",     "HENRIET",     "HENRIET",     "HENRIET",   // henrieta 
      "Q)",    "IET",         "IET",         "IEST",         "IEST",   // sviecia, spiecia, liecia 
      "RC",    "HENRIET",     "HENRIET",     "HENRIET",     "HENRIET",   // henriete 
      "R)",    "IET",         "IET",         "IEST",         "IEST",   // kviete - kviesti, liete 
   "Q)",       "TRIED",       "TRIED",       "TRIEST",       "TRIEST",   // triedzia 
      "Q)",    "RIED",        "RIED",        "RIEDE",       "RIEDËT",   // rieda 
      "Q)",    "IED",         "IED",         "IEST",         "IEST",   // skiedzia 
      "R)",    "IED",         "IED",         "IEST",         "IEST",   // triede, skiede 
// "Q)",       "UOT",         "UOT",         "UOST",         "UOST",   // nera 
//    "R)",    "UOT",         "UOT",         "UOST",         "UOST",   // nera 
   "QL",       "JUOD",        "JUOD",        "JUOD",        "JUOD",   // juoda 
      "Q)",    "DUOD",        "DUOD",        "DUOT",         "DUOT",   // duoda - duoti 
      "Q)",    "UOD",         "UOD",         "UOST",         "UOST",   // guodzia - guosti, skuodzia 
      "RE",    ".UOD",        ".UOD",        "UOD",         "UOD",   // uode, pjaunasi su uosti
      "R)",    "UOD",         "UOD",         "UOST",         "UOST",   // guode - guosti 

   "Q)",       "AMB",         "AMB",         "AMBET",        "AMBËT",   // skamba - skambeti 
   "Q)",       "KAND",        "KAND",        "KAST",         "KÀST",   // kanda - kasti 
      "R)",    "KAND",        "KAND",        "KAST",         "KÀST",   // kando - kasti 
   "Q)",       "PRANT",       "PRANT",       "PRAST",        "PRAST",   // supranta - suprasti, pripranta 
      "R)",    "AT",          "AT",          "ATYT",         "ATYT",   // mate - matyti, krate - kratyti 
      "RM",    "NMAT",        "NMAT",        "NMAT",        "NMAT",   // vienmate - suveikia "at" 
      "RM",    "IMAT",        "IMAT",        "IMAT",        "IMAT",   // dvimate, trimate - suveikia "at" 
//    "RM",    "RMAT",        "RMAT",        "RMAT",        "RMAT",   // keturmate - suveikia "at" 
//    "RM",    "TMAT",        "TMAT",        "TMAT",        "TMAT",   // desimtmate - suveikia "at" 
//    "RM",    "KAMAT",       "KAMAT",       "KAMAT",       "KAMAT",   // vienuolikamate - suveikia "at" 
      "RM",    "IAMAT",       "IAMAT",       "IAMAT",       "IAMAT",   // daugiamate - suveikia "at" 
      "RE",    "INAT",        "INAT",        "INAT",        "INAT",   // koordinate - suveikia "at" 
      "RE",    "KAT",         "KAT",         "KAT",         "KAT",   // kate - suveikia "at" 
      "R)",    "PRAT",        "PRAT",        "PRAST",        "PRAST",   // suprato - suprasti 
      "R)",    "ADEKVAT",     "ADEKVAT",     "ADEKVAT",      "ADEKVAT",   // adekvatus
      "R)",    "ADRESAT",     "ADRESAT",     "ADRESAT",      "ADRESAT",   // adresatas
      "R)",    "AGREGAT",     "AGREGAT",     "AGREGAT",      "AGREGAT",   // agregatas
      "R)",    "KOMBINAT",    "KOMBINAT",    "KOMBINAT",     "KOMBINAT",  // kombinatas
      "R)",    "AD",          "AD",          "ADYT",         "ADYT",   // ade - adyti, bade badyti
   "QC",       "RANK",        "RANK",        "RANK",        "RANK",   // ranka, atranka, patranka - suveikia "ANK" 
   "Q)",       "ANK",         "ANK",         "AKT",          "AKT",   // anka - akti 
   "RE",       "PASAKEL",     "PASAKËL",     "PASAKEL",     "PASAKËL",   // pasakele 
   "R)",       "KEL",         "KËL",         "KELT",         "KELT",   // kele - kelti 
   "RE",       "BORUZEL",     "BORUÞËL",     "BORUZEL",     "BORUÞËL",   // boruzele 
   "R)",       "ZEL",         "ÞËL",         "ZELT",         "ÞELT",   // zele 
   "R)",       "GEL",         "GËL",         "GEL",         "GEL",   // gele - pjaunasi su daiktavardziu gele 
   "Q)",       "EMB",         "EMB",         "EBT",          "EBT",   // klemba - klebti 
// "Q)",       "EMP",         "EMP",         "EP",          "EP",   // nera 
   "Q)",       "SMENG",       "SMENG",       "SMEGT",        "SMEGT",   // smenga - smegti 
   "Q)",       "ENG",         "ENG",         "ENGT",         "ENGT",   // rengia - rengti, vengia - vengti 
   "Q)",       "SLENK",       "SLENK",       "SLINKT",       "SLINKT",   // slenka - slinkti 
   "Q)",       "SENK",        "SENK",        "SEKT",         "SEKT",   // senka - sekti 
// "Q)",       "EST",         "ÆST",         "EST",          "ÆST",   // skesta - skesti 
      "RE",    "SKLEND",      "SKLEND",      "SKLEST",      "SKLÆST",   // sklende 
      "RA",    "TREND",       "TREND",       "TREND",       "TREND",   // trendas 
      "RA",    "DEND",        "DEND",        "DEND",        "DEND",   // dividendas 
      "R)",    "END",         "END",         "EST",          "ÆST",   // skendo - skesti 
   "Q)",       "KRENT",       "KRENT",       "KRIST",        "KRIST",   // krenta - kristi 
//    "QE",    "MENT",        "MENT",        "MENT",         "MENT",   // mente 
      "Q)",    "KENT",        "KENT",        "KEST",         "KÆST",   // kencia - kesti (dar: kenteti) 
//    "Q)",    "ENT",         "ENT",         "EST",          "ÆST",   // kencia - kesti (dar: kenteti) 
      "R)",    "KENT",        "KENT",        "KEST",         "KÆST",   // kente - kesti 
//    "R)",    "ENT",         "ENT",         "EST",          "ÆST",   // kente - kesti - kertasi su tento, absolvento, brezento, absorbento 
//    "))",    "GABENT",      "GABENT",      "GABENT",       "GABENT", // gabenti - suveikia "ENT" - kencia - kesti (dar: kenteti) 
//    "))",    "KALENT",      "KALENT",      "KALENT",       "KALENT", // gabenti - suveikia "ENT" - kencia - kesti (dar: kenteti) 
//    "))",    "TENT",        "TENT",        "TENT",         "TENT", // tirtenti, letenti - suveikia "ENT" - kencia - kesti (dar: kenteti) 
   "Q)",       "EN",          "EN",          "ENT",          "ENT",   // gabena, stusena
      "QA",    "IEN",         "IEN",         "IEN",          "IEN",   // vienas, sienas, iena
      "QA",    ".BEN",        ".BEN",        "BEN",          "BEN",   // benas
      "QA",    "BDEN",        "BDEN",        "BDEN",         "BDEN",   // molibdenas
      "QA",    "FEN",         "FEN",         "FEN",          "FEN",   // fenas, alofenas
      "QA",    "GEN",         "GEN",         "GEN",          "GEN",   // genas, autogenas
      "QA",    "JEN",         "JEN",         "JEN",          "JEN",   // jena
      "QA",    ".LEN",        ".LEN",        "LEN",          "LEN",   // lena
      "QA",    "ELEN",        "ELEN",        "ELEN",         "ELEN",   // elena
      "QA",    "GLEN",        "GLEN",        "GLEN",         "GLEN",   // glenas
      "QA",    ".MEN",        ".MEN",        "MEN",          "MEN",   // menas, mene
      "QA",    "IEMEN",       "IEMEN",       "IEMEN",        "IEMEN",  // piemene
      "QA",    "IEMEN",       "IEMEN",       "IEMEN",        "IEMEN",  // piemene
      "QA",    "PEN",         "PEN",         "PEN",          "PEN",  // penas
      "QA",    ".SEN",        ".SEN",        "SEN",          "SEN",  // senas
      "QA",    ".TEN",        ".TEN",        "TEN",          "TEN",  // tenas
      "QA",    ".VEN",        ".VEN",        "VEN",          "VEN",  // vena
   "Q)",       "SPREND",      "SPREND",      "SPREST",       "SPRÆST",   // sprendzia 
   "Q)",       "BREND",       "BREND",       "BRIST",        "BRIST",   // brenda - bristi 
   "QC",       "BLEND",       "BLEND",       "BLEND",       "BLEND",   // blenda 
   "Q)",       "LEND",        "LEND",        "LIST",         "LÁST",   // lenda - listi 
      "R)",    "MIND",        "MIND",        "MINDYT",       "MINDYT",   // minde 
      "RA",    ".PAGRIND",    ".PAGRIND",    "PAGRIND",     "PAGRIND",   // pagrindas - pjaunasi su pagrinde - pagristi !!! 
      "R)",    "IND",         "IND",         "IST",          "ÁST",   // lindo - listi - pjaunasi su inde - daiktav. 
   "Q)",       "END",         "END",         "IST",          "IST",   // skrenda - skristi 
      "R)",    "RID",         "RID",         "RIST",         "RIST",   // skrido - skristi, brido 
      "R)",    "LID",         "LID",         "LIST",         "LIST",   // sklido 
// "Q)",       "ERT",         "ERT",         "ERST",         "ERST",         // vercia - versti - !!! pjaunasi su "vertë", "vertæ" - daiktavardis
//    "R)",    "ERT",         "ERT",         "ERST",         "ERST",         // verte - versti - !!! pjaunasi su "vertë", "vertæ" - daiktavardis
   "Q)",       "ERD",         "ERD",         "ERST",         "ERST",   // perdzia - persti 
      "R)",    "ERD",         "ERD",         "ERST",         "ERST",   // perde - persti 
   "Q)",       "ERK",         "ERK",         "IRKT",         "IRKT",   // perka - pirkti 
   "R)",       "ER",          "ËR",          "ERT",          "ERT",   // bere, pere, svere - pjaunasi su svere - (zole) 
   "QC",       "BRYL",        "BRYL",        "BRYL",        "BRYL",   // zubryla 
      "QC",    ".YL",         ".YL",         "YL",          "YL",   // yla 
      "Q)",    "YL",          "YL",          "ILT",          "ILT",   // kyla - kilti, dyla,  skyla, svyla 
   "Q)",       "IMB",         "IMB",         "IBT",          "IBT",   // drimba - dribti 
   "Q)",       "MING",        "MING",        "MIGT",         "MIGT",   // sminga - smigti, minga 
   "QC",       "APLINK",      "APLINK",      "APLINK",      "APLINK",      // aplinka - suveikia "ink", "plink"
   "QC",       "RINK",        "RINK",        "RINK",        "RINK",   // rinka, trinka - suveikia "ink" 
   "Q)",       "MINK",        "MINK",        "MINKYT",       "MINKYT",   // minko 
   "Q)",       "PLINK",       "PLINK",       "PLIKT",        "PLIKT",   // plinka - plikti 
   "Q)",       "INK",         "INK",         "IKT",          "IKT",   // plinka - plikti 
   "Q)",       "IMP",         "IMP",         "IPT",          "IPT",   // limpa - lipti 
   "QC",       ".INT",        ".INT",        "INT",         "INT",   // inta 
      "Q)",    "KRINT",       "KRINT",       "KRIST",        "KRIST",   // krinta - kristi, svinta - svisti 
      "Q)",    "SVINT",       "ÐVINT",       "SVIST",        "ÐVIST",   // krinta - kristi, svinta - svisti 
//    "Q)",    "INT",         "INT",         "IST",          "IST",   // krinta - kristi, svinta - svisti 
//    "))",    "MINT",        "MINT",        "MINT",         "MINT",   // gaminti - suveikia "INT" - krinta
      "Q)",    ".MINT",       ".MINT",       "MIST",         "MIST",   // minta - suveikia "MINT" - gaminti
//     "))",    "BINT",        "BINT",        "BINT",         "BINT",   // apkabinti, bintas - suveikai "INT" - krinta
//    "))",    "DINT",        "DINT",        "DINT",         "DINT",   // sprogdinti - suveikai "INT" - krinta
      "R)",    "KRIT",        "KRIT",        "KRIST",        "KRIST",   // krito - kristi 
      "R)",    "SVIT",        "ÐVIT",        "SVIST",        "ÐVIST",   // svito - svisti 
      "R)",    "MIT",         "MIT",         "MIST",         "MIST",   // mito 
   "Q)",       "PAZIST",      "PAÞÁST",      "PAZINT",       "PAÞINT",   // pazista - pazinti
   "Q)",       "PAZ",         "PAÞ",         "PAZINT",       "PAÞINT",   // pazinti - suveikia -inti
      "R)",    "PAZIN",       "PAÞIN",       "PAZINT",       "PAÞINT",   // pazino
   "Q)",       "PAZINT",      "PAÞINT",      "PAZINT",       "PAÞINT",   // pazinti - suveikia -int-a (krinta)
   "R)",       "KUL",         "KÛL",         "KULT",         "KULT",   // kule - kulti 
   "Q)",       "UMP",         "UMP",         "UPT",          "UPT",   // klumpa - klupti 
   "Q)",       "BUMB",        "BUMB",        "BUMBET",       "BUMBËT",   // bumba - bumbeti 
      "Q)",    "UMB",         "UMB",         "UBT",          "UBT",   // dumba - dubti 
   "Q)",       "SKRUND",      "SKRUND",      "SKRUST",       "SKRUST",   // skrunda 
      "Q)",    "SKUND",       "SKUND",       "SKUST",        "SKØST",   // skundzia - skusti 
      "R)",    "UND",         "UND",         "UST",          "ØST",   // skunde - skusti 
   "Q)",       "UND",         "UND",         "UST",          "UST",   // bunda - busti, 
//    "R)",    "UD",          "UD",          "UST",          "UST",   // budo - busti, baude - zr. toliau 
   "Q)",       "JUNG",        "JUNG",        "JUNGT",        "JUNGT",   // jungia - jungti 
   "Q)",       "UNG",         "UNG",         "UGT",          "UGT",   // zlunga - zlugti 
   "Q)",       "SUNK",        "SUNK",        "SUNKT",        "SUNKT",   // sunkia - sunkti 
   "Q)",       "UNK",         "UNK",         "UKT",          "UKT",   // smunka - smukti, tunka 
   "Q)",       "SIUNT",       "SIUNT",       "SIUST",        "SIØST",   // siuncia - siusti - pjaunasi su siunta 
      "R)",    "SIUNT",       "SIUNT",       "SIUST",        "SIØST",   // siunte - siusti 
      "Q)",    "UNT",         "UNT",         "UST",          "UST",   // siunta - siusti, punta 
      "R)",    "SIUT",        "SIUT",        "SIUST",        "SIUST",   // siuto - siusti 
      "R)",    ".KUT",        ".KUT",        "KUST",         "KUST",   // kuto - kusti 
      "R)",    ".PRAKUT",     ".PRAKUT",     "PRAKUST",      "PRAKUST",   // prakuto - prakusti 
      "R)",    ".PUT",        ".PUT",        "PUST",         "PUST",   // puto - pusti 
      "R)",    ".ISPUT",      ".IÐPUT",      "ISPUST",       "IÐPUST",   // isputo - ispusti 
      "R)",    ".SUT",        ".ÐUT",        "SUST",         "ÐUST",   // suto - susti 
      "R)",    ".NUSUT",      ".NUÐUT",      "NUSUST",       "NUÐUST",   // nusuto - nususti 
      "R)",    ".APSUT",      ".APÐUT",      "APSUST",       "APÐUST",   // apsuto - apsusti 
      "R)",    ".ISSUT",      ".IÐÐUT",      "ISSUST",       "IÐÐUST",   // issuto - issusti 
      "R)",    ".PRISUT",     ".PRIÐUT",     "PRISUST",      "PRIÐUST",   // prisuto - prisusti 
      "R)",    ".PASUT",      ".PAÐUT",      "PASUST",       "PAÐUST",   // pasuto - pasusti 
      "R)",    "KRUT",        "KRUT",        "KRUTET",       "KRUTËT",   // kruta 
//    "R)",    "UT",          "UT",          "UST",          "UST",   // siuto - siusti - pjaunasi su eilute, ... 

   "Q)",       "VAG",         "VAG",         "VOGT",         "VOGT",   // vagia - vogti 
   "R)",       "DAV",         "DAV",         "DUOT",         "DUOT",   // dave - duoti 
      "RL",    "NUOSAV",      "NUOSAV",      "NUOSAV",      "NUOSAV",   // nuosavas 
//    "R)",    "AV",          "AV",          "AUT",          "AUT",   // ave - auti 
   "Q)",       "SREB",        "SREB",        "SREBT",        "SRËBT",   // srebia - srebti 
      "Q)",    "SUGEB",       "SUGEB",       "SUGEBET",      "SUGEBËT",   // sugeba 
      "QC",    "GEB",         "GEB",         "GEB",         "GEB",   // geba 
      "Q)",    "EB",          "EB",          "EBET",         "EBËT",   // kleba - klebeti 
   "Q)",       "SLEG",        "SLEG",        "SLEGT",        "SLËGT",   // slegia - slegti 
      "Q)",    "KLEG",        "KLEG",        "KLEGET",       "KLEGËT",   // klega - klegeti 
//    "Q)",    "EG",          "EG",          "EGET",         "EGËT",   // klega - klegeti 
   "QC",       "AUSVYR",      "AUSVYR",      "AUSVYR",      "AUSVYR",   // pusiausvyra 
      "Q)",    "YR",          "YR",          "IRT",          "IRT",   // byra - birti, svyra 
   "Q)",       "IN",          "IN",          "INT",          "INT",   // derina - derinti, pina - pinti 
// "Q)",       "IN",          "IN",          "YT",           "YT",   // pina - pyti - tarm. 
      "RE",    "AIN",         "AIN",         "AIN",          "AIN",   // svetaine, cukraine
//    "RE",    "BIN",         "BIN",         "BIN",          "BIN",   // kabina - pjaunasi su kabinti
      "RE",    "CIN",         "CIN",         "CIN",          "CIN",   // ricina
      "RE",    "REGIN",       "REGIN",       "REGIN",        "REGIN",   // regina
      "RE",    "ANGIN",       "ANGIN",       "ANGIN",        "ANGIN",   // angina, banginis
      "RE",    "LIN",         "LIN",         "LIN",          "LIN",   // abecelinis
      "RE",    "ALIN",        "ALIN",        "ALINT",        "ALINT",  // balina, salina
      "RE",   "JIN",         "JIN",          "JIN",          "JIN",   // kojine
      "RE",   ".KIN",        ".KIN",         "KIN",          "KIN",   // kinas
      "RE",   ".LIN",        ".LIN",         "LIN",          "LIN",   // linas
      "RE",   "IGNALIN",     "IGNALIN",      "IGNALIN",      "IGNALIN",   // ignalina
//    "RE",   ".KALIN",      ".KALIN",       "KALIN",        "KALIN",   // kalinys, pjaunasi su kalino
      "RE",   ".GALIN",      ".GALIN",       "GALIN",        "GALIN",   // galinis
      "RE",   "PAKULIN",     "PAKULIN",      "PAKULIN",      "PAKULIN",   // pakulinis
      "RE",   "BURBULIN",    "BURBULIN",     "BURBULIN",     "BURBULIN",   // burbulinis
      "RE",   ".MIN",        ".MIN",         "MIN",          "MIN",   // mina
      "RE",   ".KAMIN",      ".KAMIN",       "KAMIN",        "KAMIN",   // kaminas
      "RE",   "NIN",         "NIN",          "NIN",          "NIN",   // nina, leninas
      "RE",   "PALAPIN",     "PALAPIN",      "PALAPIN",      "PALAPIN", // palapine
      "RE",   "KAPIN",       "KAPIN",        "KAPIN",        "KAPIN", // kapines
      "RE",   "KARIN",       "KARIN",        "KARIN",        "KARIN", // karina
//    "RE",   "GARIN",       "GARIN",        "GARIN",        "GARIN", // garinis, pjaunasi su garinti
      "RE",   "APELSIN",     "APELSIN",      "APELSIN",      "APELSIN", // apelsinas
      "RE",   ".KATIN",      ".KATIN",       "KATIN",        "KATIN", // katinas
      "RE",   "PATIN",       "PATIN",        "PATIN",        "PATIN", // patinas, apatinis
// "Q)",      "EIN",          "EIN",         "EIT",          "EIT",   // eina - eiti, pjaunasi su derina - derinti, pina - pinti 
      "RE",    "UIN",         "UIN",         "UIN",         "UIN",   // kuinas
      "RE",    "KAVIN",       "KAVIN",       "KAVIN",       "KAVIN",   // kavine
      "RE",    ".VIN",        ".VIN",        ".VIN",        ".VIN",   // vinis
      "RE",    "ZIN",         "ZIN",         "ZIN",         "ZIN",   // kazino
      "RE",    ".ÞIN",        ".ÞIN",        "ÞIN",         "ÞIN",   // zinia
      "RE",    "ABSOLIUTIN",  "ABSOLIUTIN",  "ABSOLIUTIN",  "ABSOLIUTIN",  // absoliutinis
      "RE",    "ADATIN",  "ADATIN",  "ADATIN",  "ADATIN",  // adatine
      "RE",    ".ADIN",  ".ADIN",  "ADIN",  "ADIN",  // adinys
      "RE",    "AGRARIN",  "AGRARIN",  "AGRARIN",  "AGRARIN",  // agrarinis
//!!!    "RE",    ".NEÞIN",        ".NEÞIN",        "NEÞIN",         "NEÞIN",   // nezinia
      "RE",    "MELYN",       "MËLYN",       "MELYN",       "MËLYN",   // melyne 
      "RE",    "SUPYN",       "SÛPYN",       "SUPYN",       "SÛPYN",   // supyne 
      "R)",    "YN",          "YN",          "INT",          "INT",   // gyne - ginti, pyne - pinti 
//    "R)",    "YN",          "YN",          "YT",           "YT",   // pyne - pyti - tarm. 
    "Q)",      "IEJ",         "IEJ",         "IET",          "IET",   // sieja - sieti, skrieja - skrieti 
      "R)",    "IEJ",         "IEJ",         "IET",          "IET",   // siejo - sieti, skriejo - skrieti 
    "Q)",      "EJ",          "EJ",          "YT",           "YT",   // veja - vyti, pjaunasi su veja (pieva) 
      "Q)",    "BEJ",         "BEJ",         "BEJ",          "BEJ",   // abeji
      "Q)",    "YJ",          "YJ",          "YT",           "YT",   // gyja - gyti 
      "R)",    "IJ",          "IJ",          "YT",           "YT",   // gijo - gyti, vijo - vyti, lijo - lyti 
      "RH",    "IMPRESARIJ",  "IMPRESARIJ",  "IMPRESARIJ",  "IMPRESARIJ",   // impresarijus - suveikia "IJ" 
      "RH",    "SCENARIJ",    "SCENARIJ",    "SCENARIJ",    "SCENARIJ",   // scenarijus - suveikia "IJ" 
      "RH",    ".ARIJ",       ".ARIJ",       "ARIJ",        "ARIJ",   // arijus - suveikia "IJ" 
      "RH",    "KRITERIJ",    "KRITERIJ",    "KRITERIJ",    "KRITERIJ",   // kriterijus - suveikia "IJ" 
      "RH",    "TOKIJ",       "TOKIJ",       "TOKIJ",       "TOKIJ",   // tokijas - suveikia "IJ" 
      "RH",    "ENIJ",        "ENIJ",        "ENIJ",        "ENIJ",   // genijus, eugenijus - suveikia "IJ" 
      "RH",    "PIJ",         "PIJ",         "PIJ",         "PIJ",   // pijus - suveikia "IJ" 
      "RH",    "CIJ",         "CIJ",         "CIJ",         "CIJ",   // patricijus - suveikia "IJ" 
      "RH",    "GONIJ",       "GONIJ",       "GONIJ",       "GONIJ",  // agonija, begonija, patagonija
      "RH",    "RESIJ",       "RESIJ",       "RESIJ",       "RESIJ",  // agresija, represija
      "RH",    "NOMIJ",       "NOMIJ",       "NOMIJ",       "NOMIJ",  // agronomija, astronomija
   "Q)",       "ZUD",         "ÞUD",         "ZUDYT",        "ÞUDYT",   // zudo - zudyti 
      "QC",    "RAUD",        "RAUD",        "RAUD",        "RAUD",   // rauda 
      "QC",    "BAUD",        "BAUD",        "BAUD",        "BAUD",   // bauda 
      "QC",    "NAUD",        "NAUD",        "NAUD",        "NAUD",   // nauda 
         "Q)", "AUD",         "AUD",         "AUST",         "AUST",   // audzia - austi, snaudzia, maudzia 
         "Q)", "JUD",         "JUD",         "JUDET",        "JUDËT",   // juda 
//       "QL", "RUD",         "RUD",         "RUD",         "RUD",   // ruda 
//       "Q)", "UD",          "UD",          "UST",          "UST",   // audzia - austi, snaudzia, maudzia 
      "RE",    "AMPLITUD",    "AMPLITUD",    "AMPLITUD",    "AMPLITUD",   // amplitude - suveikia "UD" 
      "RE",    "LUD",         "LUD",         "LUD",         "LUD",   // pelude, alude - suveikia "UD" 
      "R)",    "PRABUD",      "PRABUD",      "PRABUST",      "PRABUST",   // prabudo - prabusti 
      "R)",    "PABUD",       "PABUD",       "PABUST",       "PABUST",   // pabudo - pabusti 
      "RE",    "ABUD",        "ABUD",        "ABUD",        "ABUD",   // kreivabude - suveikia "UD" 
//    "RE",    ".BUD",        ".BUD",        "BUD",         "BUD",         // bude - suveikia "UD", pjaunasi su budo - busti
      "RE",    ".ABUD",       ".ABUD",       "ABUDU",       "ABUDU",   // abudu
      "R)",    "ZUD",         "ÞUD",         "ZUDYT",        "ÞUDYT",   // zude - zudyti 
      "R)",    "UD",          "UD",          "UST",          "UST",   // aude - austi, budo - busti, baude 
   "Q)",       "UV",          "ÛV",          "UT",           "ÛT",   // buva - buti, puva - puti, zuva - zuti 
      "QC",    "KARUN",       "KARÛN",       "KARUN",       "KARÛN",   // karuna 
      "Q)",    "UN",          "ÛN",          "UT",           "ÛT",   // buna - buti, puna - puti 
      "RE",    "TUV",         "TUV",         "TUV",         "TUV",   // plautuve, parduotuve 
      "R)",    "UV",          "UV",          "UT",           "ÛT",   // buvo - buti, puvo - puti, zuvo - zuti 
      "Q)",    "KAUP",        "KAUP",        "KAUPT",        "KAUPT",   // kaupia - kaupti 
      "Q)",    "AUP",         "AUP",         "AUPYT",        "AUPYT",   // taupo - taupyti 
      "Q)",    "TUP",         "TUP",         "TUPET",        "TUPËT",   // tupi - tupeti 
      "QC",    "PUP",         "PUP",         "PUP",         "PUP",   // pupa 
//    "Q)",    "TUP",         "TUP",         "TUPET",        "TUPËT",   // tupi - pjaunasi su tupti 
      "Q)",    "TUP",         "TUP",         "TUPT",         "TÛPT",   // tupia - tupti - pjaunasi su "tupi" 
      "Q)",    "KLUP",        "KLÛP",        "KLUPOT",       "KLÛPOT",   // klupo 
// "R)",       "TUR",         "TÛR",         "TUR",          "TÛR",   // nomenklatura, diktatura 
      "R)",    "KUR",         "KÛR",         "KURT",         "KURT",   // kure - kurti 
//    "R)",    "BUR",         "BÛR",         "BURT",         "BURT",   // bure - burti, bet burys
      "R)",    "DUR",         "DÛR",         "DURT",         "DURT",   // dure - durti 
//    "AA",    "ZUR",         "ÞÛR",         "ZUR",          "ÞUR",   // abaþûras
   "Q)",       "PUT",         "PUT",         "PUST",         "PÛST",   // pucia - pusti - pjaunasi su puta 
      "R)",    "PUT",         "PÛT",         "PUST",         "PÛST",   // pute - pusti 

   "Q)",       "AUN",         "AUN",         "AUT",          "AUT",   // auna, plauna 
      "R)",    "OV",          "OV",          "AUT",          "AUT",   // plove, move, kove, rove 
      "R)",    ".ISIAV",      ".ÁSIAV",      "ISIAUT",       "ÁSIAUT",   // isiave 
      "R)",    ".UZSIAV",     ".UÞSIAV",     "UZSIAUT",      "UÞSIAUT",   // uzsiave 
      "R)",    ".NUSIAV",     ".NUSIAV",     "NUSIAUT",      "NUSIAUT",   // nusiave 
      "R)",    ".APSIAV",     ".APSIAV",     "APSIAUT",      "APSIAUT",   // apsiave 
      "R)",    ".PRISIAV",    ".PRISIAV",    "PRISIAUT",     "PRISIAUT",   // apsiave 
      "R)",    ".IAV",        ".ÁAV",        "IAUT",         "ÁAUT",   // iave 
      "R)",    ".UZAV",       ".UÞAV",       "UZAUT",        "UÞAUT",   // uzave 
      "R)",    ".NUAV",       ".NUAV",       "NUAUT",        "NUAUT",   // nuave 
      "R)",    ".APAV",       ".APAV",       "APAUT",        "APAUT",   // apave 
//    "R)",    ".PRIAV",      ".PRIAV",      "PRIAUT",       "PRIAUT",   // apave 
      "R)",    ".AV",         ".AV",         "AUT",          "AUT",   // ave 
   "Q)",       "AUJ",         "AUJ",         "AUT",          "AUT",   // dalyvauja, skanauja, grybauja 
   "Q)",       "KRAUJ",       "KRAUJ",       "KRAUJ",        "KRAUJ",  // kraujas, suveikia krauja - krauti
      "R)",    "VAV",         "VAV",         "VAUT",         "VAUT",   // dalyvavo 
      "R)",    "SKANAV",      "SKANAV",      "SKANAUT",      "SKANAUT",   // skanavo 
      "R)",    "GRYBAV",      "GRYBAV",      "GRYBAUT",      "GRYBAUT",   // grybavo 
      "R)",    "UOGAV",       "UOGAV",       "UOGAUT",       "UOGAUT",   // uogavo 
      "R)",    "RIESUTAV",    "RIEÐUTAV",    "RIESUTAUT",    "RIEÐUTAUT",   // riesutavo 
      "R)",    "ZUVAV",       "ÞUVAV",       "ZUVAUT",       "ÞUVAUT",   // zuvavo 
      "R)",    "AV",          "AV",          "UOT",          "UOT",   // dainavo - dainuoti, ... 
      "R)",    "ADVOKATAV",   "ADVOKATAV",   "ADVOKATAUT",   "ADVOKATAUT",   // advokatavo
      "R)",    "GRYBAV",      "GRYBAV",      "GRYBAUT",      "GRYBAUT",   // grybavo
      "R)",    ".AGAV",       ".AGAV",       "AGAV",        "AGAV",   // agava
      "R)",    "VELNIAV",     "VELNIAV",     "VELNIAV",     "VELNIAV",   // velniava
   "Q)",       "GIED",        "GIED",        "GIEDOT",       "GIEDOT",   // gieda - giËi 
      "QC",    "TOJ",         "TOJ",         "TOJ",         "TOJ",   // skolintoja - suveikia "OJ" 
      "Q)",    "OJ",          "OJ",          "OT",           "OT",   // joja - joti, vartoja - vartoti, dainuoja - dainuoti 
      "RH",    "RYTOJ",       "RYTOJ",       "RYTOJ",       "RYTOJ",   // rytojus - suveikia "oj" 
      "RH",    ".ROJ",        ".ROJ",        "ROJ",         "ROJ",   // rojus - suveikia "oj" 
      "RH",    ".GOJ",        ".GOJ",        "GOJ",         "GOJ",   // gojus - suveikia "oj" 
      "RH",    ".KOJ",        ".KOJ",        "KOJ",         "KOJ",   // koja - suveikia "oj" 
      "RH",    "SILOJ",       "ÐILOJ",       "SILOJ",       "ÐILOJ",   // silojus - suveikia "oj" 
      "RH",    "HANOJ",       "HANOJ",       "HANOJ",       "HANOJ",   // hanojus - suveikia "oj" 
//    "RH",    "VASAROJ",     "VASAROJ",     "VASAROJ",     "VASAROJ",   // vasarojus - suveikia "oj" - !!! pjaunasi su vasarojo - vasaroti 
      "RH",    "KARVOJ",      "KARVOJ",      "KARVOJ",      "KARVOJ",   // karvojus - suveikia "oj" 
      "R)",    "VARTOJ",      "VARTOJ",      "VARTOT",       "VARTOT",   // vartojo - vartoti 
      "RA",    "TOJ",         "TOJ",         "TOJ",         "TOJ",   // rytoj, artojus, artojai - suveikia "oj" 
      "RA",    "ABUOJ",       "ABUOJ",       "ABUOJ",       "ABUOJ",   // abuojas - suveikia "oj" 
      "RA",    ".KUOJ",       ".KUOJ",       "KUOJ",       "KUOJ",   // kuoja - suveikia "oj" 
      "R)",    "OJ",          "OJ",          "OT",           "OT",   // jojo - joti, vartojo - vartoti 
   "Q)",       "LAS",         "LAÐ",         "LASET",        "LAÐËT",   // lasa 
      "Q)",    "RAS",         "RAÐ",         "RASYT",        "RAÐYT",   // praso, raso 
      "Q)",    "TAS",         "TAÐ",         "TASYT",        "TAÐYT",   // taso - pjaunasi su taso (tasas) 
      "R)",    "RAS",         "RAÐ",         "RASYT",        "RAÐYT",   // prase, rase 
      "R)",    "TAS",         "TAÐ",         "TASYT",        "TAÐYT",   // tase 
// "Q)",       "KAS",         "KAS",         "KASYT",        "KASYT",   // kaso - kasyti - pjaunasi su kasa (kasos), kasa - kasti 
//    "RA",    "LUKAS",       "LUKAS",       "LUKAS",       "LUKAS",   // lukasas 
//    "RE",    "GAKAS",       "GAKAS",       "GAKAS",       "GAKAS",   // ilgakase 
//    "R)",    "KAS",         "KAS",         "KASYT",        "KASYT",   // kase - kasyti - pjaunasi su kase - kasti 
   "Q)",       "AIS",         "AIÐ",         "AISYT",        "AIÐYT",   // (ap)kaiso 
      "R)",    "AIS",         "AIÐ",         "AISYT",        "AIÐYT",   // (ap)kaise 
   "QA",       "PRAIS",       "PRAIS",       "PRAIS",       "PRAIS",   // praisas 
      "Q)",    "AIS",         "AIS",         "AISYT",        "AISYT",   // taiso 
      "R)",    "AIS",         "AIS",         "AISYT",        "AISYT",   // taise 

   "Q)",       "EIN",         "EIN",         "EIT",          "EIT",   // eina - eiti 
//    "R)",    "ATEJ",        "ATËJ",        "ATEIT",        "ATEIT",   // atejo 
//    "R)",    "APEJ",        "APËJ",        "APEIT",        "APEIT",   // apejo 
//    "R)",    "UZEJ",        "UÞËJ",        "UZEIT",        "UÞEIT",   // uzejo 
//    "R)",    "IEJ",         "ÁËJ",         "IEIT",         "ÁEIT",   // iejo 
//    "R)",    "ISEJ",        "IÐËJ",        "ISEIT",        "IÐEIT",   // isejo 
//    "R)",    "NUEJ",        "NUËJ",        "NUEIT",        "NUEIT",   // nuejo 
//    "R)",    "PAEJ",        "PAËJ",        "PAEIT",        "PAEIT",   // paejo 
//    "R)",    "PAREJ",       "PARËJ",       "PAREIT",       "PAREIT",   // parejo 
//    "R)",    "PRAEJ",       "PRAËJ",       "PRAEIT",       "PRAEIT",   // praejo 
//    "R)",    "PRIEJ",       "PRIËJ",       "PRIEIT",       "PRIEIT",   // praejo 
//    "R)",    "SUEJ",        "SUËJ",        "SUEIT",        "SUEIT",   // suejo 
//    "R)",    ".NEJ",        ".NËJ",        "NEIT",         "NEIT",   // nejo 
//    "R)",    ".EJ",         ".ËJ",         "EIT",          "EIT",   // ejo - eiti 
      "R)",    "EJ",          "ËJ",          "EIT",          "EIT",   // ejo - eiti 
      "RC",    ".ALEJ",       ".ALËJ",       "ALEJ",         "ALËJ",   // aleja - suveikia ejo
      "RC",    "BAKALEJ",     "BAKALËJ",     "BAKALEJ",      "BAKALËJ",   // bakaleja - suveikia ejo
      "R)",    "GEJ",         "GËJ",         "GEJ",          "GËJ",   // gejus, apogejus - suveikia ejo
      "R)",    "MEJ",         "MËJ",         "MEJ",          "MËJ",   // salomeja - suveikia ejo
      "R)",    "JOJ",         "JOJ",         "JOT",          "JOT",   // jojo, abejojo, skrajojo
      "RA",    "GAVEJ",       "GAVËJ",       "GAVEJ",       "GAVËJ",   // gavejas, rinkejas, losejas, siuvejas, audejas, ... !!! gal keist su veiksmazodziais? 
      "RA",    "SKALBEJ",     "SKALBËJ",     "SKALBEJ",     "SKALBËJ",   // skalbejas 
      "R)",    "KALBEJ",      "KALBËJ",      "KALBET",       "KALBËT",   // kalbejo - kalbeti 
      "R)",    "TUPEJ",       "TUPËJ",       "TUPET",        "TUPËT",   // tupejo 
      "R)",    "LASEJ",       "LAÐËJ",       "LASET",        "LAÐËT",   // lasejo 
      "R)",    "BARSKEJ",     "BARÐKËJ",     "BARSKET",      "BARÐKËT",   // barskejo 
      "R)",    "BEZDEJ",      "BEZDËJ",      "BEZDET",       "BEZDËT",   // bezdejo 
      "R)",    "DARDEJ",      "DARDËJ",      "DARDET",       "DARDËT",   // dardejo 
      "R)",    "LIULEJ",      "LIULËJ",      "LIULET",       "LIULËT",   // liulejo 
      "R)",    "GULEJ",       "GULËJ",       "GULET",        "GULËT",   // gulejo 
      "R)",    "SEDEJ",       "SËDËJ",       "SEDET",        "SËDËT",   // sedejo 
      "R)",    "ZIUREJ",      "ÞIÛRËJ",      "ZIURET",       "ÞIÛRËT",   // ziurejo 
      "R)",    "STOVEJ",      "STOVËJ",      "STOVET",       "STOVËT",   // stovejo 
      "R)",    "MURMEJ",      "MURMËJ",      "MURMET",       "MURMËT",   // murmejo 
      "R)",    "BURBEJ",      "BURBËJ",      "BURBET",       "BURBËT",   // burbejo 
      "R)",    "SNEKEJ",      "ÐNEKËJ",      "SNEKET",       "ÐNEKËT",   // snekejo 
      "R)",    "CIULBEJ",     "ÈIULBËJ",     "CIULBET",      "ÈIULBËT",   // ciulbejo, ... !!! 
      "R)",    "LAIMEJ",      "LAIMËJ",      "LAIMET",       "LAIMËT",   // laimejo, ... !!! 
//    "R)",    "EJ",          "ËJ",          "ET",           "ËT",   // ciulbejo, ... 
   "QC",       "NUOZIUR",     "NUOÞIÛR",     "NUOZIUR",     "NUOÞIÛR",   // nuoziura 
      "Q)",    "ZIUR",        "ÞIÛR",        "ZIURET",       "ÞIÛRËT",   // ziuri - ziureti 
      "Q)",    "GUL",         "GUL",         "GULET",        "GULËT",   // guli 
      "Q)",    "SED",         "SËD",         "SEDET",        "SËDËT",   // sedi 
      "Q)",    "STOV",        "STOV",        "STOVET",       "STOVËT",   // stovi 

// "Q)",       "T",           "T",           "T",            "T",   // blesta - blesti 
      "Q)",    "BLEST",       "BLËST",       "BLEST",        "BLËST",   // blesta - blesti 
//    "Q)",    "ZT",          "ÞT",          "ZT",           "ÞT",   // gryzta - gryzti 
      "Q)",    "KENT",        "KENT",        "KENTET",       "KENTËT",   // kenteti (dar: kesti) 
      "Q)",    "KLEST",       "KLEST",       "KLESTET",      "KLESTËT",   // klesti - klesteti 
      "Q)",    "KENT",        "KENT",        "KEST",         "KÆST",   // kencia - kenteti (dar: kesti) 
//    "RE",    "KAT",         "KAT",         "KAT",         "KAT",         // "katë", "katæ" - suveikia "VERT", "ERT"
//    "RE",    "ASIMPTOT",    "ASIMPTOT",    "ASIMPTOT",    "ASIMPTOT",    // "asimptotë", "asimptotæ" - suveikia "VERT", "ERT"
//    "RE",    "VERT",        "VERT",        "VERT",        "VERT",        // "vertë", "vertæ" - "vertë" - suveikia "VERT", "ERT"
//    "R)",    "VERT",        "VERT",        "VERST",        "VERST",        // verte - versti - suveikia "T" - !!! pjaunasi su "vertë", "vertæ"
      "RE",    "APGAVYST",    "APGAVYST",    "APGAVYST",    "APGAVYST",   // apgavyste 
      "R)",    "VYST",        "VYST",        "VYSTYT",       "VYSTYT",   // vyste - vystyti 
      "Q)",    "YST",         "YST",         "YST",          "YST",   // tysta - tysti, slysta 
      "Q)",    "PST",         "PST",         "PT",           "PT",   // ispampsta - ispampti 
      "Q)",    "RST",         "RÐT",         "RT",           "RT",   // mirsta - mire 
      "Q)",    "ISMAT",       "IÐMAT",       "ISMAT",       "IÐMAT",   // ismata 
      "Q)",    "ATMAT",       "ATMAT",       "ATMAT",       "ATMAT",   // atmata 
      "Q)",    "MAT",         "MAT",         "MATYT",        "MATYT",   // mato - matyti 
      "Q)",    ".KAIT",       ".KAIT",       "KAIT",        "KAIT",   // kaita 
      "Q)",    "AIT",         "AIT",         "AITYT",        "AITYT",   // skaito, raito 
      "Q)",    "VYST",        "VYST",        "VYSTYT",       "VYSTYT",   // vysto - vystyti - !!! pjaunasi su vysta - vysti 

   "Q)",       "DED",         "DED",         "DET",          "DËT",   // deda - deti 
      "Q)",    "BEZD",        "BEZD",        "BEZDET",       "BEZDËT",   // bezda - bezdeti 
      "QC",    "PAROD",       "PAROD",       "PAROD",       "PAROD",   // paroda - pjaunasi su parodyti, parodomasis !!! 
      "Q)",    "ROD",         "ROD",         "RODYT",        "RODYT",   // rodo - rodyti 
      "Q)",    "PILD",        "PILD",        "PILDYT",       "PILDYT",   // pildo - pildyti 
      "R)",    "ROD",         "ROD",         "RODYT",        "RODYT",   // rode - rodyti 
      "RN",    "TOLYD",       "TOLYD",       "TOLYD",       "TOLYD",   // tolydus 
      "R)",    "LYD",         "LYD",         "LYDYT",        "LYDYT",   // lyde - lydyti 
      "Q)",    "BED",         "BED",         "BEST",         "BEST",   // beda - besti 
      "R)",    "BED",         "BED",         "BEST",         "BEST",   // bede - besti 
      "Q)",    "DUOD",        "DUOD",        "DUOT",         "DUOT",   // duoda - duoti 

// "Q)",       "",            "",            "T",            "T",   // nesa - nesti !!!
//    "R)",    "",            "",            "T",            "T",   // tupe - tupti !!!

   "Q)",       "VAR",         "VAR",         "VARYT",        "VARYT",   // varo - varyti 
      "R)",    "VAR",         "VAR",         "VARYT",        "VARYT",   // vare - varyti 
      "QC",    "ODAR",        "ODAR",        "ODAR",        "ODAR",   // kainodara, rinkodara, ... 
      "Q)",    "DAR",         "DAR",         "DARYT",        "DARYT",   // daro - daryti 
      "R)",    "DAR",         "DAR",         "DARYT",        "DARYT",   // dare - daryti 
//    "Q)",    "KAR",         "KAR",         "KAROT",        "KAROT",   // karo - karoti - pjaunasi su karo (karas) 

   "Q)",       ".YR",         ".YR",         "BUT",          "BÛT",   // yra - buti 
      "Q)",    ".ES",         ".ES",         "BUT",          "BÛT",   // esu, esantis - buti 
      "Q)",    ".NER",        ".NËR",        "NEBUT",        "NEBÛT",   // nera - nebuti 
      "Q)",    ".NES",        ".NES",        "NEBUT",        "NEBÛT",   // nesu, nesantis - nebuti 

// veiksmazodziu busimojo laiko vertimas i bendrati

   "SP",       "FRENS",       "FRENS",       "FRENS",       "FRENS",   // frensis 
   "S)",       "EGS",         "EGS",         "EGZT",         "EGZT",   // megs, regs 
   "S)",       "ZYS",         "ZYS",         "ZYZT",         "ZYZT",   // zys - zyzti 
   "S)",       "BRIGS",       "BRIGS",       "BRIGZT",       "BRIGZT",   // brigs - brigzti 
   "S)",       "GRES",        "GRÆÐ",        "GREZT",        "GRÆÞT",   // gres - grezti 
   "S)",       "LUS",         "LUÐ",         "LUZT",         "LÛÞT",   // lus - luzti 
   "S)",       "LAUS",        "LAUÐ",        "LAUZT",        "LAUÞT",   // laus - lauzti 
   "S)",       "BRES",        "BRËÐ",        "BREZT",        "BRËÞT",   // bres - brezti 
   "S)",       "MYS",         "MYÐ",         "MYZT",         "MYÞT",   // mys - myzti 
   "S)",       "MES",         "MES",         "MEST",         "MEST",   // mes - mesti 
   "S)",       "RAS",         "RAS",         "RAST",         "RAST",   // ras - rasti 
   "S)",       "RES",         "RÆS",         "REST",         "RÆST",   // res - resti 
   "S)",       "GUOS",        "GUOS",        "GUOST",        "GUOST",   // guos 
   "S)",       "JUOS",        "JUOS",        "JUOST",        "JUOST",   // juos 
   "S)",       "PUS",         "PÛS",         "PUST",         "PÛST",   // pu/s - pu/sti 
   "S)",       "DUS",         "DUS",         "DUST",         "DUST",   // atsiduso - atsidusti, suveikia grius, bus, ...
   "S)",       "BLES",        "BLËS",        "BLEST",        "BLËST",   // bles 
   "S)",       "PIS",         "PIS",         "PIST",         "PIST",   // pis 
   "S)",       "US",          "ÛS",          "UT",           "ÛT",   // pusiu, busiu, busimas - buti, pjaunasi su pabus - pabusti 
   "S)",       "US",          "US",          "UT",           "ÛT",   // grius - griuti, pus - puti, bus - buti 
   "S)",       "S",           "Ð",           "ST",           "ÐT",   // nes - nesti, kis - kisti, ruos - ruosti, puos 
   "S)",       "AFIS",        "AFIÐ",        "AFIS",         "AFIÐ",  // afisa
   "S)",       "S",           "S",           "T",            "T",   // kels - kelti 
   "S)",       "ABRIKOS",     "ABRIKOS",     "ABRIKOS",      "ABRIKOS",   // abrikosas
   "S)",       "KOKOS",       "KOKOS",       "KOKOS",       "KOKOS",   // kokosas
   "S)",       "ABSCES",       "ABSCES",       "ABSCES",       "ABSCES",   // abscesas
   "S)",       "ABSCIS",       "ABSCIS",       "ABSCIS",       "ABSCIS",   // abscise
   "S)",       "PAKS",        "PAKS",       "PAKS",       "PAKS",   // paksas
   "S)",       "ADRES",       "ADRES",      "ADRES",      "ADRES",   // adresas

// veiksmazodziu liepiamosios nuosakos vertimas i bendrati !!!

   "Z ",       ".IK",         ".IK",         "IKI", "IKI",   // iki - suveikia "K" ir "I" 
   "Z)",       "NSK",         "NSK",   "NSK", "NSK",   // rybcinski(-is) 
   "Z)",       "CK",          "CK",    "CK",  "CK",   // kalecki, sluckis 
   "Z)",       "ÐK",          "ÐK",    "T",    "T",   // nesk - nesti, kentek - kenteti 
   "Z)",       "K",           "K",     "KT",   "KT",   // lauk - laukti 
   "Z)",       "NUOTRAUK",    "NUOTRAUK",    "NUOTRAUK", "NUOTRAUK",   // nuotrauka
   "Z)",       "TECHNIK",     "TECHNIK",     "TECHNIK",  "TECHNIK",     // technika
   "Z)",       "ONIK",        "ONIK",  "ONIK", "ONIK",     // elektronika, ...
   "Z)",       "BËK",         "BËK",   "GT",   "GT",   // bek - begti 
   "Z)",       "ISK",         "IÐK",   "ISK",  "IÐK",  // abeceliskas, visiskas, absurdiskas
// "Z)",       "KISK",        "KIÐK",  "KIST", "KIÐT",  // kisk - kisti, bet kiskis
// "Z)",       "UKISK",       "ÛKIÐK", "UKISK", "ÛKIÐK",  // ukiskas

// ---------------------
   "RM",       "ABIP",        "ABIP",  "ABIPUS",  "ABIPUS",   // abipusis - suveikia galunes -usio, ... 
   "MM",       "DID",         "DID",   "DIDEL",   "DIDEL",   // didysis (didis) - didelis 
// "QA",       ".AD",         ".AD",   "ADOM",    "ADOM",   // Adomas - suveikia galunes -omas, ... 
   "QA",       ".AERODR",     ".AERODR","AERODROM","AERODROM",   // Aerodromas - suveikia galunes -omas, -oma, ... 
   "QA",       ".KOSMODR",    ".KOSMODR","KOSMODROM","KOSMODROM",   // Kosmodromas - suveikia galunes -omas, -oma, ... 
   "QA",       ".R",          ".R",    "ROM",     "ROM",   // Romas - suveikia galunes -omas, ... 
   "QC",       ".R",          ".R",    "ROM",     "ROM",   // Roma - suveikia galunes -oma, ... 
   "QC",       "AKSI",        "AKSI",  "AKSIOM",  "AKSIOM",   // aksioma - suveikia galune -oma, ... 
// "QA",       ".R",          ".R",    "RIM",     "RIM",   // Rimas - suveikia galunes -imas, ... 
// "SA",       ".R",          ".R",    "RIM",     "RIM",   // Rimas - suveikia galunes -imas, ... 
// "QC",       ".R",          ".R",    "RIM",     "RIM",   // Rima - suveikia galunes -ima, ... 
// "SC",       ".R",          ".R",    "RIM",     "RIM",   // Rima - suveikia galunes -ima, ... 
   "QC",       ".DIAGR",      ".DIAGR","DIAGRAM", "DIAGRAM",   // Diagrama - suveikia galunes -ama, ... 
   "QC",       ".PANOR",      ".PANOR","PANORAM", "PANORAM",   // Panorama - suveikia galunes -ama, ... 
   "1I",       ".POPI",       ".POPI", "POPIER",  "POPIER",   // Popierius - suveikia galunes -eriais, -eriØ, ... 
   "4I",       ".POPI",       ".POPI", "POPIER",  "POPIER",   // Popierius - suveikia galunes -eriais, -eriØ, ... 
   "KI",       ".POPI",       ".POPI", "POPIER",  "POPIER",   // Popierius - suveikia galunes -eriai 
   "1P",       ".VALT",       ".VALT", "VALTER",  "VALTER",   // Valteris - suveikia galunes -eris, ... 
   "4P",       ".VALT",       ".VALT", "VALTER",  "VALTER",   // Valteris - suveikia galunes -eris, ... 
   "KP",       ".VALT",       ".VALT", "VALTER",  "VALTER",   // Valteris - suveikia galunes -eris, ... 

   "1A",       "PAK",         "PAK",   "PAKET",   "PAKET",   // paketas - suveikia galunes -etas, ... 
   "4A",       "PAK",         "PAK",   "PAKET",   "PAKET",   // paketas - suveikia galunes -etas, ... 
   "1A",       "MON",         "MON",   "MONET",   "MONET",   // moneta - suveikia galunes -etas, ... 
   "4A",       "MON",         "MON",   "MONET",   "MONET",   // moneta - suveikia galunes -etas, ... 
   "1A",       "FURS",        "FURÐ", "FURSET",      "FURÐET",   // fursetas - suveikia galunes -etas, ... 
   "4A",       "FURS",        "FURÐ", "FURSET",      "FURÐET",   // fursetas - suveikia galunes -etas, ... 
// "1A",       "BANK",        "BANK",  "BANKET",  "BANKET",    // banketas - suveikia galunes -etas, ... - bet "bankas" !!!
// "4A",       "BANK",        "BANK",  "BANKET",  "BANKET",    // banketas - suveikia galunes -etas, ... - bet "bankas" !!!
// "1A",       "LANG",        "LANG",  "LANGET",  "LANGET",    // langetas - suveikia galunes -etas, ... - bet "langas" !!!
// "4A",       "LANG",        "LANG",  "LANGET",  "LANGET",    // langetas - suveikia galunes -etas, ...  - bet "langas" !!!
   "1A",       "OML",         "OML",   "OMLET",   "OMLET",     // omletas - suveikia galunes -etas, ... 
   "4A",       "OML",         "OML",   "OMLET",   "OMLET",     // omletas - suveikia galunes -etas, ... 
   "1A",       "LAF",         "LAF",   "LAFET",   "LAFET",     // lafetas - suveikia galunes -etas, ... 
   "4A",       "LAF",         "LAF",   "LAFET",   "LAFET",     // lafetas - suveikia galunes -etas, ... 
// "1A",       "BAL",         "BAL",   "BALET",   "BALET",     // baletas - suveikia galunes -etas, ... - bet "bala" !!!
// "4A",       "BAL",         "BAL",   "BALET",   "BALET",     // baletas - suveikia galunes -etas, ... - bet "bala" !!!
   "1A",       "KORN",        "KORN",  "KORNET",  "KORNET",    // kornetas - suveikia galunes -etas, ... 
   "4A",       "KORN",  "KORN",  "KORNET",  "KORNET",    // kornetas - suveikia galunes -etas, ... 
   "1A",       "ORS",   "ORS",   "ORSET",   "ORSET",     // korsetas - suveikia galunes -etas, ... 
   "4A",       "ORS",   "ORS",   "ORSET",   "ORSET",     // korsetas - suveikia galunes -etas, ... 
// "1A",       "DU",    "DU",    "DUET",    "DUET",      // duetas - suveikia galunes -etas, tur but, pjaunasi su dvejetas - bet "du" !!!
// "4A",       "DU",    "DU",    "DUET",    "DUET",      // duetas - suveikia galunes -etas, tur but, pjaunasi su dvejetas - bet "du" !!!
// "1A",       "KVART", "KVART", "KVARTET", "KVARTET",   // kvartetas - suveikia galunes -etas - bet "kvarta" !!!
// "4A",       "KVART", "KVART", "KVARTET", "KVARTET",   // kvartetas - suveikia galunes -etas - bet "kvarta" !!! 
// "1A",       "KVINT", "KVINT", "KVINTET", "KVINTET",   // kvintetas - suveikia galunes -etas - bet "kvinta" !!!
// "4A",       "KVINT", "KVINT", "KVINTET", "KVINTET",   // kvintetas - suveikia galunes -etas - bet "kvinta" !!!
// "1A",       "SEKST", "SEKST", "SEKSTET", "SEKSTET",   // sekstetas - suveikia galunes -etas - bet "seksta" !!!
// "4A",       "SEKST", "SEKST", "SEKSTET", "SEKSTET",   // sekstetas - suveikia galunes -etas - bet "seksta" !!! 
   "1A",       "OKT",   "OKT",   "OKTET",   "OKTET",     // oktetas - suveikia galunes -etas 
   "4A",       "OKT",   "OKT",   "OKTET",   "OKTET",     // oktetas - suveikia galunes -etas 

   NULL,       NULL,    NULL,    NULL,      NULL
};
