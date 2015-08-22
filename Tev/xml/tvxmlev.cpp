// ==================================================
// tvxmleg.cpp
// endings and suffixes skipper for searching in flex. languages
// german endings
//


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


// -------------------------------------------------
char *plpszaPrefixes_v[] =
{
   ".GE",       ".GE",       "",         "",         ")",  "",

// -----------------------------------------
// ge-
//   
   ".GEB",      ".GEB",     "GEB",         "GEB",         ")",  "",         // geben - suveikia ge-
   
   ".GEDEIH",   ".GEDEIH",  "GEDEIH",      "GEDEIH",  ")",  "",    // gedeihen - suveikia ge-
   ".GEDIEH",   ".GEDIEH",  "GEDEIH",      "GEDEIH",  ")",  "",       
                                                            
   ".GEH",      ".GEH",     "GEH",         "GEH",     ")",  "",    // gehen - suveikia ge-     
   
   ".GEHOL",    ".GEHOL",   "HOL",         "HOL",     ")",  "",    // geholfen - suveikia gehen
                                                            
   ".GELT",     ".GELT",    "GELT",        "GELT",    ")",  "",    // gelten - suveikia ge-
                                                            
   ".GELING",   ".GELING",  "GELING",      "GELING",  ")",  "",    // gelingen - suveikia ge-
   ".GELANG",   ".GELANG",  "GELING",      "GELING",  ")",  "",       
   ".GELANG",   ".GELÄNG",  "GELING",      "GELING",  ")",  "",       
   ".GELUNG",   ".GELUNG",  "GELING",      "GELING",  ")",  "",       
                                                    
   ".GENES",    ".GENES",   "GENES",       "GENES",   ")",  "",    // genesen - suveikia ge-
   ".GENA",     ".GENA",    "GENES",       "GENES",   ")",  "",       
   ".GENAS",    ".GENÄS",   "GENES",       "GENES",   ")",  "",       
                                                    
   ".GENIES",   ".GENIEß",  "GENIES",      "GENIEß",  ")",  "",    // geniessen - suveikia ge-
   ".GENOS",    ".GENOS",   "GENIES",      "GENIEß",  ")",  "",       
   ".GENOSS",   ".GENÖSS",  "GENIES",      "GENIEß",  ")",  "",       
   ".GENOSS",   ".GENOSS",  "GENIES",      "GENIEß",  ")",  "",       
                                                    
   ".GESCHEH",  ".GESCHEH", "GESCHEH",     "GESCHEH", ")",  "",    // geschehen - suveikia ge-
   ".GESCHIEH", ".GESCHIEH","GESCHEH",     "GESCHEH", ")",  "",      
   ".GESCHAH",  ".GESCHAH", "GESCHEH",     "GESCHEH", ")",  "",       
   ".GESCHAH",  ".GESCHÄH", "GESCHEH",     "GESCHEH", ")",  "",       
                                                    
   ".GEWINN",   ".GEWINN",  "GEWINN",      "GEWINN",  ")",  "",    // gewinnen - suveikia ge-
   ".GEWANN",   ".GEWANN",  "GEWINN",      "GEWINN",  ")",  "",       
   ".GEWANN",   ".GEWÄNN",  "GEWINN",      "GEWINN",  ")",  "",       
   ".GEWONN",   ".GEWÖNN",  "GEWINN",      "GEWINN",  ")",  "",       
   ".GEWONN",   ".GEWONN",  "GEWINN",      "GEWINN",  ")",  "",       

   ".GEWOHN",   ".GEWÖHN",  ".GEWOHN",     ".GEWÖHN", ")",  "",   // gewohnlich

//------------
   ".ABGE",     ".ABGE",     "AB",       "AB",       ")",  "",
   ".ABGEH",    ".ABGEH",    "ABGEH",    "ABGEH",    ")",  "", // abgehen
   ".ABGEB",    ".ABGEB",    "ABGEB",    "ABGEB",    ")",  "", // abgeben
   
   ".ANGE",     ".ANGE",     "AN",       "AN",       ")",  "",
   ".AUFGE",    ".AUFGE",    "AUF",      "AUF",      ")",  "",
   ".AUSGE",    ".AUSGE",    "AUS",      "AUS",      ")",  "",
   ".BEIGE",    ".BEIGE",    "BEI",      "BEI",      ")",  "",
   ".DURCHGE",  ".DURCHGE",  "DURCH",    "DURCH",    ")",  "",
   ".EINGE",    ".EINGE",    "EIN",      "EIN",      ")",  "",
   ".ENGEGENGE", ".ENGEGENGE", "ENGEGEN", "ENGEGEN", ")",  "",
   ".FORTGE",   ".FORTGE",   "FORT",     "FORT",     ")",  "",
   ".HERGE",    ".HERGE",    "HER",      "HER",      ")",  "",
   ".HERABGE",  ".HERABGE",  "HERAB",    "HERAB",    ")",  "",
   ".HERANGE",  ".HERANGE",  "HERAN",    "HERAN",    ")",  "",
   ".HERAUFGE", ".HERAUFGE", "HERAUF",   "HERAUF",   ")",  "",
   ".HERAUSGE", ".HERAUSGE", "HERAUS",   "HERAUS",   ")",  "",
   ".HERBEIGE", ".HERBEIGE", "HERBEI",   "HERBEI",   ")",  "",
   ".HEREINGE", ".HEREINGE", "HEREIN",   "HEREIN",   ")",  "",
   ".HERUBERGE",".HERÜBERGE","HERUBER",  "HERÜBER",  ")",  "",
   ".HERUMGE",  ".HERUMGE",  "HERUM",    "HERUM",    ")",  "",
   ".HERUNTERGE",".HERUNTERGE","HERUNTER","HERUNTER",")",  "",
   ".HERVORGE", ".HERVORGE", "HERVOR",   "HERVOR",   ")",  "",
   ".HERZUGE",  ".HERZUGE",  "HERZU",    "HERZU",    ")",  "",
   ".HINGE",    ".HINGE",    "HIN",      "HIN",      ")",  "",
   ".HINABGE",  ".HINABGE",  "HINAB",    "HINAB",    ")",  "",
   ".HINANGE",  ".HINANGE",  "HINAN",    "HINAN",    ")",  "",
   ".HINAUFGE", ".HINAUFGE", "HINAUF",   "HINAUF",   ")",  "",
   ".HINAUSGE", ".HINAUSGE", "HINAUS",   "HINAUS",   ")",  "",
   ".HINDURCHGE",".HINDURCHGE","HINDURCH","HINDURCH",")",  "",
   ".HINEINGE", ".HINEINGE", "HINEIN",   "HINEIN",   ")",  "",
   ".HINUBERGE",".HINÜBERGE","HINUBER",  "HINÜBER",  ")",  "",
   ".HINUNTERGE",".HINUNTERGE","HINUNTER","HINUNTER",")",  "",
   ".HINWEGGE", ".HINWEGGE", "HINWEG",   "HINWEG",   ")",  "",
   ".HINZUGE",  ".HINZUGE",  "HINZU",    "HINZU",    ")",  "",
   ".LOSGE",    ".LOSGE",    "LOS",      "LOS",      ")",  "",
   ".MISSGE",   ".MISSGE",   "MISS",     "MISS",     ")",  "",
   ".MITGE",    ".MITGE",    "MIT",      "MIT",      ")",  "",
   ".NACHGE",   ".NACHGE",   "NACH",     "NACH",     ")",  "",
   ".UBERGE",   ".ÜBERGE",   "UBER",     "ÜBER",     ")",  "",
   ".UMGE",     ".UMGE",     "UM",       "UM",       ")",  "",
// ".UNGE",     ".UNGE",     "UN",       "UN",       ")",  "", // neatsk.
   ".UNTERGE",  ".UNTERGE",  "UNTER",    "UNTER",    ")",  "",
// ".URGE",     ".URGE",     "UR",       "UR",       ")",  "", // budv.
// ".VERGE",    ".VERGE",    "VER",      "VER",      ")",  "", // neatsk.
   ".VOLLGE",   ".VOLLGE",   "VOLL",     "VOLL",     ")",  "",
   ".VORGE",    ".VORGE",    "VOR",      "VOR",      ")",  "",
   ".VORANGE",  ".VORANGE",  "VORAN",    "VORAN",    ")",  "",
   ".VORAUSGE", ".VORAUSGE", "VORAUS",   "VORAUS",   ")",  "",
   ".VORBEIGE", ".VORBEIGE", "VORBEI",   "VORBEI",   ")",  "",
   ".VORHERGE", ".VORHERGE", "VORHER",   "VORHER",   ")",  "",
   ".VORUBERGE",".VORÜBERGE","VORUBER",  "VORÜBER",  ")",  "",
// ".ZERGE",    ".ZERGE",    "ZER",      "ZER",      ")",  "", // neatsk.
   ".ZUGE",     ".ZUGE",     "ZU",       "ZU",       ")",  "",
   ".ZURUCKGE", ".ZURÜCKGE", "ZURUCK",   "ZURÜCK",   ")",  "",
   ".ZUSAMMENGE",".ZUSAMMENGE","ZUSAMMEN","ZUSAMMEN",")",  "",
   
   NULL,       NULL,       NULL,       NULL,       NULL, NULL
};


// ---------------------------------------
// "T" ir "E" metam ir nuo saknu - maziau isimciu
//
char *plpszaEndSkipTable_v[] = {
   "EST",      "EST",      "",         "",         "q",  "t",
   
   "ST",       "ST",       "",         "",         "q",  "t",
   "LUST",     "LUST",     "LUST",     "LUST",     "A",  "",
   
   "ET",       "ET",       "",         "",         "q",  "j",

   "T",        "T",        "",         "",         "q",  "J",
// ".ABART",   ".ABART",   "ABART",    "ABART",    "X",  "v",
// "ZEIT",     "ZEIT",     "ZEIT",     "ZEIT",     "A",  "v",
// "RIENT",    "RIENT",    "RIENT",    "RIENT",    "A",  "v",     // abiturient
// "MENT",     "MENT",     "MENT",     "MENT",     "A",  "v",     // abonement
// "ABONNENT", "ABONNENT", "ABONNENT", "ABONNENT", "A",  "v",
// "ABSOLUT",  "ABSOLUT",  "ABSOLUT",  "ABSOLUT",  "A",  "v",
// "ENT",      "ENT",      "ENT",      "ENT",      "A",  "v",     // absolvent, advent
// "ABSTRAKT", "ABSTRAKT", "ABSTRAKT", "ABSTRAKT", "A",  "v",
// "TAT",      "TÄT",      "TAT",      "TÄT",      "A",  "v",     // absurdität
// "ACHT",     "ACHT",     "ACHT",     "ACHT",     "6",  "v",
// "ADAQUAT",  "ADÄQUAT",  "ADAQUAT",  "ADÄQUAT",  "L",  "v",
// "TANT",     "TANT",     "TANT",     "TANT",     "A",  "v", // adjutant

   "ENS",      "ENS",      "",         "",         "a",  "k",

   "END",      "END",      "",         "",         "Q",  "v",
   "ABEND",    "ABEND",    "ABEND",    "ABEND",    "A",  "v",
   "GEGEND",   "GEGEND",   "GEGEND",   "GEGEND",   "A",  "v",
   "ELEND",    "ELEND",    "ELEND",    "ELEND",    "A",  "v",
   
   "ER",       "ER",       "",         "",         "l",  "1",
   "TER",      "TER",      "",         "",         "q",  "v",
   "LER",      "LER",      "",         "",         "A",  "v",
   "TEUER",    "TEUER",    "TEUER",    "TEUER",    "L",  "",
   "TEURER",   "TEURER",   "TEUER",    "TEUER",    "l",  "1",
// "ACKER",    "ACKER",    "ACKER",    "ACKER",    "A",  "",
// "PTER",     "PTER",     "PTER",     "PTER",     "A",  "", // adapter
   
   "E",        "E",        "",         "",         "a",  "V",
   "TE",       "TE",       "",         "",         "a",  "V",

   "ES",       "ES",       "",         "",         "a",  "k",
   "TES",      "TES",      "",         "",         "q",  "v",
// "ABSOLUTES","ABSOLUTES","ABSOLUT",  "ABSOLUT",  "a",  "k",

   "EM",       "EM",       "",         "",         "a",  "k",
   "TEM",      "TEM",      "",         "",         "q",  "v",
   
   "EN",       "EN",       "",         "",         "a",  "g",
   "TEN",      "TEN",      "",         "",         "q",  "g",

   "RN",       "RN",       "R",        "R",        ")",  "",
   "LN",       "LN",       "L",        "L",        ")",  "",
   "ND",       "ND",       "",         "",         "l",  "v",
   "ENE",      "ENE",      "",         "",         "q",  "v",
   
   "S",        "S",        "",         "",         "a",  "k",
   "SS",       "SS",       "SS",       "SS",       "A",  "v",    // ablass, abscess
   "EIS",      "EIS",      "EIS",      "EIS",      "A",  "v",    // preis eis
   "OS",       "OS",       "OS",       "OS",       "A",  "v",    // los, adonisros

   NULL,       NULL,       NULL,       NULL,       NULL, NULL
};


// -------------------------------------------------
char *plpszaUnRegForms_v[] =
{
// "",   ".ABART",      ".ABART",   "ABART",       "ABART",       // suveikia gebaren
   
// -------------------------------------------------
// automatizuotai sugeneruota is vlz04vl.tex (vlz04vl.cpp)   
//
   "Q)", "BACK",        "BÄCK",        "BACK",        "BACK",        
   "Q)", "BACK",        "BÄCK",        "BACK",        "BACK",        
   "R)", "BUK",         "BUK",         "BACK",        "BACK",        
   "R)", "BACKT",       "BACKT",       "BACK",        "BACK",        
   "R)", "BUK",         "BÜK",         "BACK",        "BACK",        
                                                                     
   "R)", "BEDANG",      "BEDANG",      "BEDING",      "BEDING",      
   "R)", "BEDINGT",     "BEDINGT",     "BEDING",      "BEDING",      
   "R)", "BEDANG",      "BEDÄNG",      "BEDING",      "BEDING",      
   "R)", "BEDINGT",     "BEDINGT",     "BEDING",      "BEDING",      
   "R)", "BEDUNG",      "BEDUNG",      "BEDING",      "BEDING",      
                                                                     
   "Q)", "BEFIEHL",     "BEFIEHL",     "BEFEHL",      "BEFEHL",      
   "Q)", "BEFIEHL",     "BEFIEHL",     "BEFEHL",      "BEFEHL",      
   "R)", "BEFAHL",      "BEFAHL",      "BEFEHL",      "BEFEHL",      
   "R)", "BEFOHL",      "BEFÖHL",      "BEFEHL",      "BEFEHL",      
   "R)", "BEFAHL",      "BEFÄHL",      "BEFEHL",      "BEFEHL",      
   "Z)", "BEFIEHL",     "BEFIEHL",     "BEFEHL",      "BEFEHL",      
   "R)", "BEFOHL",      "BEFOHL",      "BEFEHL",      "BEFEHL",      
                                                                     
   "R)", "BEFLIS",      "BEFLIS",      "BEFLEIS",     "BEFLEIß",     
   "R)", "BEFLISS",     "BEFLISS",     "BEFLEIS",     "BEFLEIß",     
   "R)", "BEFLISS",     "BEFLISS",     "BEFLEIS",     "BEFLEIß",     
   "R)", "BEFLISS",     "BEFLISS",     "BEFLEIS",     "BEFLEIß",     
                                                                     
   "R)", "BEGANN",      "BEGANN",      "BEGINN",      "BEGINN",      
   "R)", "BEGONN",      "BEGÖNN",      "BEGINN",      "BEGINN",      
   "R)", "BEGANN",      "BEGÄNN",      "BEGINN",      "BEGINN",      
   "R)", "BEGONN",      "BEGONN",      "BEGINN",      "BEGINN",      
                                                                     
   "R)", "BIS",         "BIS",         "BEIS",        "BEIß",        
   "R)", "BISS",        "BISS",        "BEIS",        "BEIß",        
   "R)", "BISS",        "BISS",        "BEIS",        "BEIß",        
   "R)", "BISS",        "BISS",        "BEIS",        "BEIß",        
                                                                     
   "Q)", "BIRG",        "BIRG",        "BERG",        "BERG",        
   "Q)", "BIRG",        "BIRG",        "BERG",        "BERG",        
   "R)", "BARG",        "BARG",        "BERG",        "BERG",        
   "R)", "BARG",        "BÄRG",        "BERG",        "BERG",        
   "Z)", "BIRG",        "BIRG",        "BERG",        "BERG",        
   "R)", "BORG",        "BORG",        "BERG",        "BERG",        
                                                                     
   "Q)", "BIR",         "BIR",         "BERST",       "BERST",       
   "Q)", "BIR",         "BIR",         "BERST",       "BERST",       
   "Q)", "BERST",       "BERST",       "BERST",       "BERST",       
   "R)", "BAR",         "BAR",         "BERST",       "BERST",       
   "R)", "BOR",         "BOR",         "BERST",       "BERST",       
   "R)", "BERSTET",     "BERSTET",     "BERST",       "BERST",       
   "R)", "BARST",       "BÄRST",       "BERST",       "BERST",       
   "Z)", "BIR",         "BIR",         "BERST",       "BERST",       
   "R)", "BORST",       "BORST",       "BERST",       "BERST",       
                                                                     
   "R)", "BEWOG",       "BEWOG",       "BEWEG",       "BEWEG",       
   "R)", "BEWOG",       "BEWÖG",       "BEWEG",       "BEWEG",       
   "R)", "BEWOG",       "BEWOG",       "BEWEG",       "BEWEG",       
                                                                     
   "R)", "BOG",         "BOG",         "BIEG",        "BIEG",        
   "R)", "BOG",         "BÖG",         "BIEG",        "BIEG",        
   "R)", "BOG",         "BOG",         "BIEG",        "BIEG",        
                                                                     
   "R)", "BO",          "BO",          "BIET",        "BIET",        
   "R)", "BOT",         "BÖT",         "BIET",        "BIET",        
   "R)", "BOT",         "BOT",         "BIET",        "BIET",        
                                                                     
   "R)", "BAND",        "BAND",        "BIND",        "BIND",        
   "R)", "BAND",        "BÄND",        "BIND",        "BIND",        
   "R)", "BUND",        "BUND",        "BIND",        "BIND",        
                                                                     
   "R)", ".BA",         ".BA",         "BITT",        "BITT",        
   "R)", "BAT",         "BÄT",         "BITT",        "BITT",        
   "R)", "BET",         "BET",         "BITT",        "BITT",        
                                                                     
   "Q)", "BLA",         "BLÄ",         "BLAS",        "BLAS",        
   "Q)", "BLA",         "BLÄ",         "BLAS",        "BLAS",        
   "R)", "BLI",         "BLI",         "BLAS",        "BLAS",        
   "R)", "BLIES",       "BLIES",       "BLAS",        "BLAS",        
                                                                     
   "R)", "BLIEB",       "BLIEB",       "BLEIB",       "BLEIB",       
   "R)", "BLIEB",       "BLIEB",       "BLEIB",       "BLEIB",       
   "R)", "BLIEB",       "BLIEB",       "BLEIB",       "BLEIB",       
                                                                     
   "R)", "BLICH",       "BLICH",       "BLEICH",      "BLEICH",      
   "R)", "BLICH",       "BLICH",       "BLEICH",      "BLEICH",      
   "R)", "BLICH",       "BLICH",       "BLEICH",      "BLEICH",      
                                                                     
   "Q)", "BRAT",        "BRÄT",        "BRAT",        "BRAT",        
   "Q)", "BRA",         "BRÄ",         "BRAT",        "BRAT",        
   "R)", "BRI",         "BRI",         "BRAT",        "BRAT",        
   "R)", "BRIET",       "BRIET",       "BRAT",        "BRAT",        
                                                                     
   "Q)", "BRICH",       "BRICH",       "BRECH",       "BRECH",       
   "Q)", "BRICH",       "BRICH",       "BRECH",       "BRECH",       
   "R)", "BRACH",       "BRACH",       "BRECH",       "BRECH",       
   "R)", "BRACH",       "BRÄCH",       "BRECH",       "BRECH",       
   "Z)", "BRICH",       "BRICH",       "BRECH",       "BRECH",       
   "R)", "BROCH",       "BROCH",       "BRECH",       "BRECH",       
                                                                     
   "R)", "BRANNT",      "BRANNT",      "BRENN",       "BRENN",       
   "R)", "BRENNT",      "BRENNT",      "BRENN",       "BRENN",       
   "R)", "BRANN",       "BRANN",       "BRENN",       "BRENN",       
                                                                     
   "R)", "BRACHT",      "BRACHT",      "BRING",       "BRING",       
   "R)", "BRACHT",      "BRÄCHT",      "BRING",       "BRING",       
   "R)", "BRACH",       "BRACH",       "BRING",       "BRING",       
                                                                     
   "R)", "DACHT",       "DACHT",       "DENK",        "DENK",        
   "R)", "DACHT",       "DÄCHT",       "DENK",        "DENK",        
   "R)", "DACH",        "DACH",        "DENK",        "DENK",        
                                                                     
   "R)", "DANG",        "DANG",        "DING",        "DING",        
   "R)", "DINGT",       "DINGT",       "DING",        "DING",        
   "R)", "DINGET",      "DINGET",      "DING",        "DING",        
   "R)", "DUNG",        "DÜNG",        "DING",        "DING",        
   "R)", "DANG",        "DÄNG",        "DING",        "DING",        
   "R)", "DUNG",        "DUNG",        "DING",        "DING",        
                                                                     
   "Q)", "DRISCH",      "DRISCH",      "DRESCH",      "DRESCH",      
   "Q)", "DRISCH",      "DRISCH",      "DRESCH",      "DRESCH",      
   "R)", "DROSCH",      "DROSCH",      "DRESCH",      "DRESCH",      
   "R)", "DRASCH",      "DRASCH",      "DRESCH",      "DRESCH",      
   "R)", "DROSCH",      "DRÖSCH",      "DRESCH",      "DRESCH",      
   "Z)", "DRISCH",      "DRISCH",      "DRESCH",      "DRESCH",      
   "R)", "DROSCH",      "DROSCH",      "DRESCH",      "DRESCH",      
                                                                     
   "R)", "DRANG",       "DRANG",       "DRING",       "DRING",       
   "R)", "DRANG",       "DRÄNG",       "DRING",       "DRING",       
   "R)", "DRUNG",       "DRUNG",       "DRING",       "DRING",       
                                                                     
   "Q)", "DEUCH",       "DEUCH",       "DUNK",        "DÜNK",        
   "R)", "DUNKT",       "DÜNKT",       "DUNK",        "DÜNK",        
   "R)", "DEUCHT",      "DEUCHT",      "DUNK",        "DÜNK",        
   "R)", "DEUCH",       "DEUCH",       "DUNK",        "DÜNK",        
                                                                     
   "Q)", "DARF",        "DARF",        "DURF",        "DÜRF",        
   "R)", "DURFT",       "DURFT",       "DURF",        "DÜRF",        
   "R)", "DURFT",       "DÜRFT",       "DURF",        "DÜRF",        
   "R)", "DURF",        "DURF",        "DURF",        "DÜRF",        
                                                                     
   "Q)", "EMPFIEHL",    "EMPFIEHL",    "EMPFEHL",     "EMPFEHL",     
   "Q)", "EMPFIEHL",    "EMPFIEHL",    "EMPFEHL",     "EMPFEHL",     
   "R)", "EMPFAHL",     "EMPFAHL",     "EMPFEHL",     "EMPFEHL",     
   "R)", "EMPFOHL",     "EMPFÖHL",     "EMPFEHL",     "EMPFEHL",     
   "Z)", "EMPFIEHL",    "EMPFIEHL",    "EMPFEHL",     "EMPFEHL",     
   "R)", "EMPFOHL",     "EMPFOHL",     "EMPFEHL",     "EMPFEHL",     
                                                                     
   "R)", "ERBLEICHT",   "ERBLEICHT",   "ERBLEICH",    "ERBLEICH",    
   "R)", "ERBLICH",     "ERBLICH",     "ERBLEICH",    "ERBLEICH",    
   "R)", "ERBLEICHT",   "ERBLEICHT",   "ERBLEICH",    "ERBLEICH",    
   "R)", "ERBLICH",     "ERBLICH",     "ERBLEICH",    "ERBLEICH",    
   "R)", "ERBLICH",     "ERBLICH",     "ERBLEICH",    "ERBLEICH",    
                                                                     
   "R)", "ERKOR",       "ERKOR",       "ERKIES",      "ERKIES",      
   "R)", "ERKOR",       "ERKÖR",       "ERKIES",      "ERKIES",      
   "R)", "ERKOR",       "ERKOR",       "ERKIES",      "ERKIES",      
                                                                     
   "Q)", "ERLISCH",     "ERLISCH",     "ERLOSCH",     "ERLÖSCH",     
   "Q)", "ERLISCH",     "ERLISCH",     "ERLOSCH",     "ERLÖSCH",     
   "R)", "ERLOSCH",     "ERLOSCH",     "ERLOSCH",     "ERLÖSCH",     
   "Z)", "ERLISCH",     "ERLISCH",     "ERLOSCH",     "ERLÖSCH",     
   "R)", "ERLOSCH",     "ERLOSCH",     "ERLOSCH",     "ERLÖSCH",     
                                                                     
   "Q)", "ERSCHRICK",   "ERSCHRICK",   "ERSCHRECK",   "ERSCHRECK",   
   "Q)", "ERSCHRICK",   "ERSCHRICK",   "ERSCHRECK",   "ERSCHRECK",   
   "R)", "ERSCHRAK",    "ERSCHRAK",    "ERSCHRECK",   "ERSCHRECK",   
   "R)", "ERSCHRAK",    "ERSCHRÄK",    "ERSCHRECK",   "ERSCHRECK",   
   "Z)", "ERSCHRICK",   "ERSCHRICK",   "ERSCHRECK",   "ERSCHRECK",   
   "R)", "ERSCHROCK",   "ERSCHROCK",   "ERSCHRECK",   "ERSCHRECK",   
                                                                     
   "R)", "ERWOG",       "ERWOG",       "ERWAG",       "ERWÄG",       
   "R)", "ERWOG",       "ERWÖG",       "ERWAG",       "ERWÄG",       
   "R)", "ERWOG",       "ERWOG",       "ERWAG",       "ERWÄG",       
                                                                     
   "Q)", ".IS",         ".IS",         "ESS",         "ESS",         
   "Q)", "ISS",         "ISS",         "ESS",         "ESS",         
   "Q)", ".IS",         ".IS",         "ESS",         "ESS",         
   "R)", ".AS",         ".Aß",         "ESS",         "ESS",         
   "R)", ".AS",         ".Äß",         "ESS",         "ESS",         
   "Z)", ".IS",         ".IS",         "ESS",         "ESS",         
   "R)", "GESS",        "GESS",        "ESS",         "ESS",         
                                                                     
   "Q)", "FAHR",        "FÄHR",        "FAHR",        "FAHR",        
   "Q)", "FAHR",        "FÄHR",        "FAHR",        "FAHR",        
   "R)", "FUHR",        "FUHR",        "FAHR",        "FAHR",        
   "R)", "FUHR",        "FÜHR",        "FAHR",        "FAHR",        
                                                                     
   "Q)", "FALL",        "FÄLL",        "FALL",        "FALL",        
   "Q)", "FALL",        "FÄLL",        "FALL",        "FALL",        
   "R)", "FIEL",        "FIEL",        "FALL",        "FALL",        
   "R)", "FIEL",        "FIEL",        "FALL",        "FALL",        
                                                                     
   "Q)", "FANG",        "FÄNG",        "FANG",        "FANG",        
   "Q)", "FANG",        "FÄNG",        "FANG",        "FANG",        
   "R)", "FING",        "FING",        "FANG",        "FANG",        
   "R)", "FING",        "FING",        "FANG",        "FANG",        
                                                                     
   "Q)", "FICHT",       "FICHT",       "FECHT",       "FECHT",       
   "Q)", "FICH",        "FICH",        "FECHT",       "FECHT",       
   "R)", "FOCH",        "FOCH",        "FECHT",       "FECHT",       
   "R)", "FOCHT",       "FÖCHT",       "FECHT",       "FECHT",       
   "Z)", "FICH",        "FICH",        "FECHT",       "FECHT",       
   "R)", "FOCHT",       "FOCHT",       "FECHT",       "FECHT",       
                                                                     
   "R)", "FAND",        "FAND",        "FIND",        "FIND",        
   "R)", "FAND",        "FÄND",        "FIND",        "FIND",        
   "R)", "FUND",        "FUND",        "FIND",        "FIND",        
                                                                     
   "Q)", "FLICHT",      "FLICHT",      "FLECHT",      "FLECHT",      
   "Q)", "FLICH",       "FLICH",       "FLECHT",      "FLECHT",      
   "Q)", "FLECHT",      "FLECHT",      "FLECHT",      "FLECHT",      
   "R)", "FLOCH",       "FLOCH",       "FLECHT",      "FLECHT",      
   "R)", "FLOCHT",      "FLÖCHT",      "FLECHT",      "FLECHT",      
   "Z)", "FLICH",       "FLICH",       "FLECHT",      "FLECHT",      
   "R)", "FLOCHT",      "FLOCHT",      "FLECHT",      "FLECHT",      
                                                                     
   "R)", "FLOG",        "FLOG",        "FLIEG",       "FLIEG",       
   "R)", "FLOG",        "FLÖG",        "FLIEG",       "FLIEG",       
   "R)", "FLOG",        "FLOG",        "FLIEG",       "FLIEG",       
                                                                     
   "R)", "FLOH",        "FLOH",        "FLIEH",       "FLIEH",       
   "R)", "FLOH",        "FLÖH",        "FLIEH",       "FLIEH",       
   "R)", "FLOH",        "FLOH",        "FLIEH",       "FLIEH",       
                                                                     
   "R)", "FLOS",        "FLOS",        "FLIES",       "FLIEß",       
   "R)", "FLOSS",       "FLOSS",       "FLIES",       "FLIEß",       
   "R)", "FLOSS",       "FLÖSS",       "FLIES",       "FLIEß",       
   "R)", "FLOSS",       "FLOSS",       "FLIES",       "FLIEß",       
                                                                     
   "Q)", "FRIS",        "FRIS",        "FRESS",       "FRESS",       
   "Q)", "FRIS",        "FRIß",        "FRESS",       "FRESS",       
   "R)", "FRAS",        "FRAß",        "FRESS",       "FRESS",       
   "R)", "FRAS",        "FRÄß",        "FRESS",       "FRESS",       
   "Z)", "FRIS",        "FRIß",        "FRESS",       "FRESS",       
                                                                     
   "R)", "FROR",        "FROR",        "FRIER",       "FRIER",       
   "R)", "FROR",        "FRÖR",        "FRIER",       "FRIER",       
   "R)", "FROR",        "FROR",        "FRIER",       "FRIER",       
                                                                     
   "R)", "GART",        "GÄRT",        "GAR",         "GÄR",         
   "R)", "GOR",         "GOR",         "GAR",         "GÄR",         
   "R)", "GART",        "GÄRT",        "GAR",         "GÄR",         
   "R)", "GOR",         "GÖR",         "GAR",         "GÄR",         
   "R)", "GOR",         "GOR",         "GAR",         "GÄR",         

   "Q)", "GEBIER",      "GEBIER",      "GEBAR",       "GEBÄR",         
   "Q)", "GEBAR",       "GEBÄR",       "GEBAR",       "GEBÄR",         
   "Q)", "GEBIER",      "GEBIER",      "GEBAR",       "GEBÄR",         
   "R)", "GEBAR",       "GEBAR",       "GEBAR",       "GEBÄR",         
   "Z)", "GEBI",        "GEBI",        "GEBAR",       "GEBÄR",         
   "R)", "GEBOR",       "GEBOR",       "GEBAR",       "GEBÄR",         
                                                                     
   "Q)", "GEGIB",       "GEGIB",       "GEB",         "GEB",           
   "Q)", "GEGIB",       "GEGIB",       "GEB",         "GEB",           
   "R)", "GEGAB",       "GEGAB",       "GEB",         "GEB",           
   "R)", "GEGAB",       "GEGÄB",       "GEB",         "GEB",           
   "Z)", "GEGIB",       "GEGIB",       "GEB",         "GEB",           
   "R)", "GEGEB",       "GEGEB",       "GEB",         "GEB",           
                                                                     
   "R)", "GEDIEH",      "GEDIEH",      "GEDEIH",      "GEDEIH",        
   "R)", "GEDIEH",      "GEDIEH",      "GEDEIH",      "GEDEIH",        
   "R)", "GEDIEH",      "GEDIEH",      "GEDEIH",      "GEDEIH",        
                                                                     
   "R)", "GING",        "GING",        "GEH",         "GEH",           
   "R)", "GING",        "GING",        "GEH",         "GEH",           
   "R)", "GANG",        "GANG",        "GEH",         "GEH",           
                                                                     
   "R)", "GELANG",      "GELANG",      "GELING",      "GELING",        
   "R)", "GELANG",      "GELÄNG",      "GELING",      "GELING",        
   "R)", "GELUNG",      "GELUNG",      "GELING",      "GELING",        
                                                                     
   "Q)", "GILT",        "GILT",        "GELT",        "GELT",           
   "Q)", "GIL",         "GIL",         "GELT",        "GELT",           
   "R)", "GAL",         "GAL",         "GELT",        "GELT",           
   "R)", "GALT",        "GÄLT",        "GELT",        "GELT",           
   "R)", "GOLT",        "GÖLT",        "GELT",        "GELT",           
   "Z)", "GIL",         "GIL",         "GELT",        "GELT",           
   "R)", "GOLT",        "GOLT",        "GELT",        "GELT",           
                                                            
   "R)", "GENA",        "GENA",        "GENES",       "GENES",         
   "R)", "GENAS",       "GENÄS",       "GENES",       "GENES",         
                                                                     
   "R)", "GENOS",       "GENOS",       "GENIES",      "GENIEß",        
   "R)", "GENOSS",      "GENÖSS",      "GENIES",      "GENIEß",        
   "R)", "GENOSS",      "GENOSS",      "GENIES",      "GENIEß",        
                                                                     
   "Q)", "GESCHIEH",    "GESCHIEH",    "GESCHEH",     "GESCHEH",       
   "R)", "GESCHAH",     "GESCHAH",     "GESCHEH",     "GESCHEH",       
   "R)", "GESCHAH",     "GESCHÄH",     "GESCHEH",     "GESCHEH",       
                                                                     
   "R)", "GEWANN",      "GEWANN",      "GEWINN",      "GEWINN",        
   "R)", "GEWANN",      "GEWÄNN",      "GEWINN",      "GEWINN",        
   "R)", "GEWONN",      "GEWÖNN",      "GEWINN",      "GEWINN",        
   "R)", "GEWONN",      "GEWONN",      "GEWINN",      "GEWINN",        
                                                                     
   "R)", "GOS",         "GOS",         "GIES",        "GIEß",        
   "R)", "GOSS",        "GOSS",        "GIES",        "GIEß",        
   "R)", "GOSS",        "GÖSS",        "GIES",        "GIEß",        
   "R)", "GOSS",        "GOSS",        "GIES",        "GIEß",        
                                                                     
   "R)", "GLICH",       "GLICH",       "GLEICH",      "GLEICH",      
   "R)", "GLICH",       "GLICH",       "GLEICH",      "GLEICH",      
   "R)", "GLICH",       "GLICH",       "GLEICH",      "GLEICH",      
                                                                     
   "R)", "GLEIST",      "GLEIßT",      "GLEIS",       "GLEIß",       
   "R)", "GLIS",        "GLIS",        "GLEIS",       "GLEIß",       
   "R)", "GLISS",       "GLISS",       "GLEIS",       "GLEIß",       
   "R)", "GLISS",       "GLISS",       "GLEIS",       "GLEIß",       
   "R)", "GLISS",       "GLISS",       "GLEIS",       "GLEIß",       
                                                                     
   "R)", "GLIT",        "GLIT",        "GLEIT",       "GLEIT",       
   "R)", "GLITT",       "GLITT",       "GLEIT",       "GLEIT",       
   "R)", "GLITT",       "GLITT",       "GLEIT",       "GLEIT",       
                                                                     
   "R)", "GLIMMT",      "GLIMMT",      "GLIMM",       "GLIMM",       
   "R)", "GLOMM",       "GLOMM",       "GLIMM",       "GLIMM",       
   "R)", "GLOMM",       "GLÖMM",       "GLIMM",       "GLIMM",       
   "R)", "GLOMM",       "GLOMM",       "GLIMM",       "GLIMM",       
                                                                     
   "Q)", "GRAB",        "GRÄB",        "GRAB",        "GRAB",        
   "Q)", "GRAB",        "GRÄB",        "GRAB",        "GRAB",        
   "R)", "GRUB",        "GRUB",        "GRAB",        "GRAB",        
   "R)", "GRUB",        "GRÜB",        "GRAB",        "GRAB",        
                                                                     
   "R)", "GRIFF",       "GRIFF",       "GREIF",       "GREIF",       
   "R)", "GRIFF",       "GRIFF",       "GREIF",       "GREIF",       
   "R)", "GRIFF",       "GRIFF",       "GREIF",       "GREIF",       
                                                                     
   "Q)", ".HA",         ".HA",         "HAB",         "HAB",         
   "Q)", ".HA",         ".HA",         "HAB",         "HAB",         
   "R)", "HATT",        "HATT",        "HAB",         "HAB",         
   "R)", "HATT",        "HÄTT",        "HAB",         "HAB",         
                                                                     
   "Q)", "HALT",        "HÄLT",        "HALT",        "HALT",        
   "Q)", "HAL",         "HÄL",         "HALT",        "HALT",        
   "R)", "HIEL",        "HIEL",        "HALT",        "HALT",        
   "R)", "HIELT",       "HIELT",       "HALT",        "HALT",        
                                                                     
   "Q)", "HANG",        "HÄNG",        "HANG",        "HÄNG",        
   "Q)", "HANG",        "HANG",        "HANG",        "HÄNG",        
   "Q)", "HANG",        "HÄNG",        "HANG",        "HÄNG",        
   "Q)", "HANG",        "HÄNG",        "HANG",        "HÄNG",        
   "R)", "HING",        "HING",        "HANG",        "HÄNG",        
   "R)", "HING",        "HING",        "HANG",        "HÄNG",        
   "Z)", "HANG",        "HÄNG",        "HANG",        "HÄNG",        
   "R)", "HANG",        "HANG",        "HANG",        "HÄNG",        
                                                                     
   "Q)", "HANG",        "HÄNG",        "HANG",        "HANG",        
   "Q)", "HANG",        "HANG",        "HANG",        "HANG",        
   "Q)", "HANG",        "HÄNG",        "HANG",        "HANG",        
   "Q)", "HANG",        "HÄNG",        "HANG",        "HANG",        
   "R)", "HING",        "HING",        "HANG",        "HANG",        
   "R)", "HING",        "HING",        "HANG",        "HANG",        
   "Z)", "HANG",        "HÄNG",        "HANG",        "HANG",        
   "R)", "HANG",        "HANG",        "HANG",        "HANG",        
                                                                     
   "R)", "HAUT",        "HAUT",        "HAU",         "HAU",         
   "R)", "HIEB",        "HIEB",        "HAU",         "HAU",         
   "R)", "HIEB",        "HIEB",        "HAU",         "HAU",         
   "R)", "HAUT",        "HAUT",        "HAU",         "HAU",         
                                                                     
   "R)", "HOB",         "HOB",         "HEB",         "HEB",         
   "R)", "HUB",         "HUB",         "HEB",         "HEB",         
   "R)", "HOB",         "HÖB",         "HEB",         "HEB",         
   "R)", "HUB",         "HÜB",         "HEB",         "HEB",         
   "R)", "HOB",         "HOB",         "HEB",         "HEB",         
                                                                     
   "R)", "HIES",        "HIEß",        "HEIS",        "HEIß",        
   "R)", "HIES",        "HIEß",        "HEIS",        "HEIß",        
                                                                     
   "Q)", "HILF",        "HILF",        "HELF",        "HELF",        
   "Q)", "HILF",        "HILF",        "HELF",        "HELF",        
   "R)", "HALF",        "HALF",        "HELF",        "HELF",        
   "R)", "HULF",        "HÜLF",        "HELF",        "HELF",        
   "Z)", "HILF",        "HILF",        "HELF",        "HELF",        
   "R)", "HOLF",        "HOLF",        "HELF",        "HELF",        
                                                                     
   "R)", "KANNT",       "KANNT",       "KENN",        "KENN",        
   "R)", "KENNT",       "KENNT",       "KENN",        "KENN",        
   "R)", "KANN",        "KANN",        "KENN",        "KENN",        
                                                                     
   "R)", "KLIMMT",      "KLIMMT",      "KLIMM",       "KLIMM",       
   "R)", "KLOMM",       "KLOMM",       "KLIMM",       "KLIMM",       
   "R)", "KLOMM",       "KLÖMM",       "KLIMM",       "KLIMM",       
   "R)", "KLOMM",       "KLOMM",       "KLIMM",       "KLIMM",       
                                                                     
   "R)", "KLANG",       "KLANG",       "KLING",       "KLING",       
   "R)", "KLANG",       "KLÄNG",       "KLING",       "KLING",       
   "R)", "KLUNG",       "KLUNG",       "KLING",       "KLING",       
                                                                     
   "R)", "KNIFF",       "KNIFF",       "KNEIF",       "KNEIF",       
   "R)", "KNIFF",       "KNIFF",       "KNEIF",       "KNEIF",       
   "R)", "KNIFF",       "KNIFF",       "KNEIF",       "KNEIF",       
                                                                     
   "R)", "KAM",         "KAM",         "KOMM",        "KOMM",        
   "R)", "KAM",         "KÄM",         "KOMM",        "KOMM",        
                                                                     
   "Q)", "KANN",        "KANN",        "KONN",        "KÖNN",        
   "R)", "KONNT",       "KONNT",       "KONN",        "KÖNN",        
   "R)", "KONNT",       "KÖNNT",       "KONN",        "KÖNN",        
   "R)", "KONN",        "KONN",        "KONN",        "KÖNN",        
                                                                     
   "R)", "KROCH",       "KROCH",       "KRIECH",      "KRIECH",      
   "R)", "KROCH",       "KRÖCH",       "KRIECH",      "KRIECH",      
   "R)", "KROCH",       "KROCH",       "KRIECH",      "KRIECH",      
                                                                     
   "Q)", "LAD",         "LAD",         "LAD",         "LAD",         
   "Q)", "LAD",         "LÄD",         "LAD",         "LAD",         
   "Q)", "LAD",         "LÄD",         "LAD",         "LAD",         
   "R)", "LUD",         "LUD",         "LAD",         "LAD",         
   "R)", "LUD",         "LÜD",         "LAD",         "LAD",         
   "Z)", "LAD",         "LAD",         "LAD",         "LAD",         
   "R)", "LAD",         "LAD",         "LAD",         "LAD",         
                                                                     
   "Q)", "LAD",         "LAD",         "LAD",         "LAD",         
   "Q)", "LAD",         "LÄD",         "LAD",         "LAD",         
   "Q)", "LAD",         "LÄD",         "LAD",         "LAD",         
   "Q)", "LAD",         "LAD",         "LAD",         "LAD",         
   "Q)", "LAD",         "LAD",         "LAD",         "LAD",         
   "R)", "LUD",         "LUD",         "LAD",         "LAD",         
   "R)", "LADET",       "LADET",       "LAD",         "LAD",         
   "R)", "LUD",         "LÜD",         "LAD",         "LAD",         
   "R)", "LADET",       "LADET",       "LAD",         "LAD",         
   "Z)", "LAD",         "LAD",         "LAD",         "LAD",         
   "R)", "LAD",         "LAD",         "LAD",         "LAD",         
                                                                     
   "Q)", "LAS",         "LÄS",         "LASS",        "LASS",        
   "Q)", "LAS",         "LÄS",         "LASS",        "LASS",        
   "R)", "LIES",        "LIEß",        "LASS",        "LASS",        
   "R)", "LIES",        "LIEß",        "LASS",        "LASS",        
   "Z)", "LAS",         "LAß",         "LASS",        "LASS",        
                                                                     
   "Q)", "LAUF",        "LÄUF",        "LAUF",        "LAUF",        
   "Q)", "LAUF",        "LÄUF",        "LAUF",        "LAUF",        
   "R)", "LIEF",        "LIEF",        "LAUF",        "LAUF",        
   "R)", "LIEF",        "LIEF",        "LAUF",        "LAUF",        
                                                                     
   "R)", "LIT",         "LIT",         "LEID",        "LEID",        
   "R)", "LITT",        "LITT",        "LEID",        "LEID",        
   "R)", "LITT",        "LITT",        "LEID",        "LEID",        
                                                                     
   "R)", "LIEH",        "LIEH",        "LEIH",        "LEIH",        
   "R)", "LIEH",        "LIEH",        "LEIH",        "LEIH",        
   "R)", "LIEH",        "LIEH",        "LEIH",        "LEIH",        
                                                                     
   "Q)", ".LI",         ".LI",         "LES",         "LES",         
   "Q)", ".LI",         ".LI",         "LES",         "LES",         
   "R)", ".LA",         ".LA",         "LES",         "LES",         
   "R)", "LAS",         "LÄS",         "LES",         "LES",         
   "Z)", ".LI",         ".LI",         "LES",         "LES",         
                                                                     
   "R)", "LAG",         "LAG",         "LIEG",        "LIEG",        
   "R)", "LAG",         "LÄG",         "LIEG",        "LIEG",        
   "R)", "LEG",         "LEG",         "LIEG",        "LIEG",        
   "R)", "SCHLAG",      "SCHLAG",      "SCHLAG",      "SCHLAG",        
                                                                     
   "R)", "LOG",         "LOG",         "LUG",         "LÜG",         
   "R)", "LOG",         "LÖG",         "LUG",         "LÜG",         
   "R)", "LOG",         "LOG",         "LUG",         "LÜG",         
                                                                     
   "R)", "MAHLT",       "MAHLT",       "MAHL",        "MAHL",        
   "R)", "MAHLT",       "MAHLT",       "MAHL",        "MAHL",        
                                                                     
   "R)", "MIED",        "MIED",        "MEID",        "MEID",        
   "R)", "MIED",        "MIED",        "MEID",        "MEID",        
   "R)", "MIED",        "MIED",        "MEID",        "MEID",        
                                                                     
   "Q)", "MILK",        "MILK",        "MELK",        "MELK",        
   "Q)", "MILK",        "MILK",        "MELK",        "MELK",        
   "R)", "MELKT",       "MELKT",       "MELK",        "MELK",        
   "R)", "MOLK",        "MOLK",        "MELK",        "MELK",        
   "R)", "MOLK",        "MÖLK",        "MELK",        "MELK",        
   "R)", "MOLK",        "MOLK",        "MELK",        "MELK",        
                                                                     
   "Q)", "MIS",         "MIS",         "MESS",        "MESS",        
   "Q)", "MIS",         "MIß",         "MESS",        "MESS",        
   "R)", "MAS",         "MAß",         "MESS",        "MESS",        
   "R)", "MAS",         "MÄß",         "MESS",        "MESS",        
   "Z)", "MIS",         "MIS",         "MESS",        "MESS",        
                                                                     
   "R)", "MISLANG",     "MIßLANG",     "MISLING",     "MIßLING",     
   "R)", "MISLANG",     "MIßLÄNG",     "MISLING",     "MIßLING",     
   "R)", "MISLUNG",     "MIßLUNG",     "MISLING",     "MIßLING",     
                                                                     
   "Q)", "MAG",         "MAG",         "MOG",         "MÖG",         
   "R)", "MOCHT",       "MOCHT",       "MOG",         "MÖG",         
   "R)", "MOCHT",       "MÖCHT",       "MOG",         "MÖG",         
   "R)", "MOCH",        "MOCH",        "MOG",         "MÖG",         
                                                                     
   "Q)", "MUS",         "MUS",         "MUSS",        "MÜSS",        
   "R)", "MUST",        "MUßT",        "MUSS",        "MÜSS",        
   "R)", "MUST",        "MÜßT",        "MUSS",        "MÜSS",        
   "R)", "MUS",         "MUS",         "MUSS",        "MÜSS",        
                                                                     
   "Q)", "NIMM",        "NIMM",        "NEHM",        "NEHM",        
   "Q)", "NIMM",        "NIMM",        "NEHM",        "NEHM",        
   "R)", "NAHM",        "NAHM",        "NEHM",        "NEHM",        
   "R)", "NAHM",        "NÄHM",        "NEHM",        "NEHM",        
   "Z)", "NIMM",        "NIMM",        "NEHM",        "NEHM",        
   "R)", "NOMM",        "NOMM",        "NEHM",        "NEHM",        
                                                                     
   "R)", "NANNT",       "NANNT",       "NENN",        "NENN",        
   "R)", "NENNT",       "NENNT",       "NENN",        "NENN",        
   "R)", "NANN",        "NANN",        "NENN",        "NENN",        
                                                                     
   "R)", "PFIFF",       "PFIFF",       "PFEIF",       "PFEIF",       
   "R)", "PFIFF",       "PFIFF",       "PFEIF",       "PFEIF",       
   "R)", "PFIFF",       "PFIFF",       "PFEIF",       "PFEIF",       
                                                                     
   "R)", "PFLEGT",      "PFLEGT",      "PFLEG",       "PFLEG",       
   "R)", "PFLOG",       "PFLOG",       "PFLEG",       "PFLEG",       
   "R)", "PFLOG",       "PFLOG",       "PFLEG",       "PFLEG",       
   "R)", "PFLEGT",      "PFLEGT",      "PFLEG",       "PFLEG",       
   "R)", "PFLOG",       "PFLÖG",       "PFLEG",       "PFLEG",       
   "R)", "PFLOG",       "PFLOG",       "PFLEG",       "PFLEG",       
                                                                     
   "R)", "PRI",         "PRI",         "PREIS",       "PREIS",       
   "R)", "PRIES",       "PRIES",       "PREIS",       "PREIS",       
   "R)", "PRIES",       "PRIES",       "PREIS",       "PREIS",       
                                                                     
   "Q)", "QUILL",       "QUILL",       "QUELL",       "QUELL",       
   "Q)", "QUILL",       "QUILL",       "QUELL",       "QUELL",       
   "Q)", "QUELL",       "QUELL",       "QUELL",       "QUELL",       
   "R)", "QUOLL",       "QUOLL",       "QUELL",       "QUELL",       
   "R)", "QUELLT",      "QUELLT",      "QUELL",       "QUELL",       
   "R)", "QUOLL",       "QUÖLL",       "QUELL",       "QUELL",       
   "Z)", "QUILL",       "QUILL",       "QUELL",       "QUELL",       
   "R)", "QUOLL",       "QUOLL",       "QUELL",       "QUELL",       
                                                                     
   "Q)", "RAT",         "RÄT",         "RAT",         "RAT",         
   "Q)", ".RA",         ".RÄ",         "RAT",         "RAT",         
   "R)", ".RI",         ".RI",         "RAT",         "RAT",         
   "R)", "RIET",        "RIET",        "RAT",         "RAT",         
                                                                     
   "R)", "RIEB",        "RIEB",        "REIB",        "REIB",        
   "R)", "RIEB",        "RIEB",        "REIB",        "REIB",        
   "R)", "RIEB",        "RIEB",        "REIB",        "REIB",        
                                                                     
   "R)", "RIS",         "RIS",         "REIS",        "REIß",        
   "R)", "RISS",        "RISS",        "REIS",        "REIß",        
   "R)", "RISS",        "RISS",        "REIS",        "REIß",        
   "R)", "RISS",        "RISS",        "REIS",        "REIß",        
                                                                     
   "R)", "RIT",         "RIT",         "REIT",        "REIT",        
   "R)", "RITT",        "RITT",        "REIT",        "REIT",        
   "R)", "RITT",        "RITT",        "REIT",        "REIT",        
                                                                     
   "R)", "RANNT",       "RANNT",       "RENN",        "RENN",        
   "R)", "RENNT",       "RENNT",       "RENN",        "RENN",        
   "R)", "RANN",        "RANN",        "RENN",        "RENN",        
                                                                     
   "R)", "ROCH",        "ROCH",        "RIECH",       "RIECH",       
   "R)", "ROCH",        "RÖCH",        "RIECH",       "RIECH",       
   "R)", "ROCH",        "ROCH",        "RIECH",       "RIECH",       
                                                                     
   "R)", "RANG",        "RANG",        "RING",        "RING",        
   "R)", "RANG",        "RÄNG",        "RING",        "RING",        
   "R)", "RUNG",        "RUNG",        "RING",        "RING",        
                                                                     
   "R)", "RANN",        "RANN",        "RINN",        "RINN",        
   "R)", "RANN",        "RÄNN",        "RINN",        "RINN",        
   "R)", "RONN",        "RÖNN",        "RINN",        "RINN",        
   "R)", "RONN",        "RONN",        "RINN",        "RINN",        
                                                                     
   "R)", "RIEF",        "RIEF",        "RUF",         "RUF",         
   "R)", "RIEF",        "RIEF",        "RUF",         "RUF",         
                                                                     
   "R)", "SALZT",       "SALZT",       "SALZ",        "SALZ",        
   "R)", "SALZT",       "SALZT",       "SALZ",        "SALZ",        
                                                                     
   "Q)", "SAUF",        "SÄUF",        "SAUF",        "SAUF",        
   "Q)", "SAUF",        "SÄUF",        "SAUF",        "SAUF",        
   "R)", "SOFF",        "SOFF",        "SAUF",        "SAUF",        
   "R)", "SOFF",        "SÖFF",        "SAUF",        "SAUF",        
   "R)", "SOFF",        "SOFF",        "SAUF",        "SAUF",        
                                                                     
   "R)", "SOG",         "SOG",         "SAUG",        "SAUG",        
   "R)", "SAUGT",       "SAUGT",       "SAUG",        "SAUG",        
   "R)", "SOG",         "SÖG",         "SAUG",        "SAUG",        
   "R)", "SOG",         "SOG",         "SAUG",        "SAUG",        
                                                                     
   "R)", "SCHUF",       "SCHUF",       "SCHAFF",      "SCHAFF",      
   "R)", "SCHUF",       "SCHÜF",       "SCHAFF",      "SCHAFF",      
                                                                     
   "R)", "SCHALLT",     "SCHALLT",     "SCHALL",      "SCHALL",      
   "R)", "SCHOLL",      "SCHOLL",      "SCHALL",      "SCHALL",      
   "R)", "SCHALLET",    "SCHALLET",    "SCHALL",      "SCHALL",      
   "R)", "SCHOLL",      "SCHÖLL",      "SCHALL",      "SCHALL",      
                                                                     
   "R)", "SCHIED",      "SCHIED",      "SCHEID",      "SCHEID",      
   "R)", "SCHIED",      "SCHIED",      "SCHEID",      "SCHEID",      
   "R)", "SCHIED",      "SCHIED",      "SCHEID",      "SCHEID",      
                                                                     
   "R)", "SCHI",        "SCHI",        "SCHEIN",      "SCHEIN",      
   "R)", "SCHIEN",      "SCHIEN",      "SCHEIN",      "SCHEIN",      
   "R)", "SCHIEN",      "SCHIEN",      "SCHEIN",      "SCHEIN",      
                                                                     
   "R)", "SCHIS",       "SCHIß",       "SCHEIS",      "SCHEIß",      
   "R)", "SCHISS",      "SCHISS",      "SCHEIS",      "SCHEIß",      
   "R)", "SCHISS",      "SCHISS",      "SCHEIS",      "SCHEIß",      
   "R)", "SCHISS",      "SCHISS",      "SCHEIS",      "SCHEIß",      
                                                                     
   "Q)", "SCHILT",      "SCHILT",      "SCHELT",      "SCHELT",      
   "Q)", "SCHIL",       "SCHIL",       "SCHELT",      "SCHELT",      
   "R)", "SCHAL",       "SCHAL",       "SCHELT",      "SCHELT",      
   "R)", "SCHOLT",      "SCHÖLT",      "SCHELT",      "SCHELT",      
   "Z)", "SCHIL",       "SCHIL",       "SCHELT",      "SCHELT",      
   "R)", "SCHOLT",      "SCHOLT",      "SCHELT",      "SCHELT",      
                                                                     
   "Q)", "SCHER",       "SCHER",       "SCHER",       "SCHER",       
   "R)", "SCHERT",      "SCHERT",      "SCHER",       "SCHER",       
   "R)", "SCHOR",       "SCHOR",       "SCHER",       "SCHER",       
   "R)", "SCHOR",       "SCHÖR",       "SCHER",       "SCHER",       
   "Z)", "SCHI",        "SCHI",        "SCHER",       "SCHER",       
   "Z)", "SCHER",       "SCHER",       "SCHER",       "SCHER",       
   "R)", "SCHOR",       "SCHOR",       "SCHER",       "SCHER",       
                                                                     
   "Q)", "SCHER",       "SCHER",       "SCHER",       "SCHER",       
   "Q)", "SCHIER",      "SCHIER",      "SCHER",       "SCHER",       
   "Q)", "SCHER",       "SCHER",       "SCHER",       "SCHER",       
   "Q)", "SCHIER",      "SCHIER",      "SCHER",       "SCHER",       
   "Q)", "SCHER",       "SCHER",       "SCHER",       "SCHER",       
   "R)", "SCHERT",      "SCHERT",      "SCHER",       "SCHER",       
   "R)", "SCHERT",      "SCHERT",      "SCHER",       "SCHER",       
   "Z)", "SCHER",       "SCHER",       "SCHER",       "SCHER",       
   "R)", "SCHOR",       "SCHOR",       "SCHER",       "SCHER",       
                                                                     
   "R)", "SCHOB",       "SCHOB",       "SCHIEB",      "SCHIEB",      
   "R)", "SCHOB",       "SCHÖB",       "SCHIEB",      "SCHIEB",      
   "R)", "SCHOB",       "SCHOB",       "SCHIEB",      "SCHIEB",      
                                                                     
   "R)", "SCHOS",       "SCHOS",       "SCHIES",      "SCHIEß",      
   "R)", "SCHOSS",      "SCHOSS",      "SCHIES",      "SCHIEß",      
   "R)", "SCHOSS",      "SCHÖSS",      "SCHIES",      "SCHIEß",      
   "R)", "SCHOSS",      "SCHOSS",      "SCHIES",      "SCHIEß",      
                                                                     
   "R)", "SCHUND",      "SCHUND",      "SCHIND",      "SCHIND",      
   "R)", "SCHUND",      "SCHÜND",      "SCHIND",      "SCHIND",      
   "R)", "SCHUND",      "SCHUND",      "SCHIND",      "SCHIND",      
                                                                     
   "Q)", "SCHLAF",      "SCHLÄF",      "SCHLAF",      "SCHLAF",      
   "Q)", "SCHLAF",      "SCHLÄF",      "SCHLAF",      "SCHLAF",      
   "R)", "SCHLIEF",     "SCHLIEF",     "SCHLAF",      "SCHLAF",      
   "R)", "SCHLIEF",     "SCHLIEF",     "SCHLAF",      "SCHLAF",      
                                                                     
   "Q)", "SCHLAG",      "SCHLÄG",      "SCHLAG",      "SCHLAG",      
   "Q)", "SCHLAG",      "SCHLÄG",      "SCHLAG",      "SCHLAG",      
   "R)", "SCHLUG",      "SCHLUG",      "SCHLAG",      "SCHLAG",      
   "R)", "SCHLUG",      "SCHLÜG",      "SCHLAG",      "SCHLAG",      
                                                                     
   "R)", "SCHLICH",     "SCHLICH",     "SCHLEICH",    "SCHLEICH",    
   "R)", "SCHLICH",     "SCHLICH",     "SCHLEICH",    "SCHLEICH",    
   "R)", "SCHLICH",     "SCHLICH",     "SCHLEICH",    "SCHLEICH",    
                                                                     
   "R)", "SCHLIFF",     "SCHLIFF",     "SCHLEIF",     "SCHLEIF",     
   "R)", "SCHLIFF",     "SCHLIFF",     "SCHLEIF",     "SCHLEIF",     
   "R)", "SCHLIFF",     "SCHLIFF",     "SCHLEIF",     "SCHLEIF",     
                                                                     
   "R)", "SCHLEIST",    "SCHLEIßT",    "SCHLEIS",     "SCHLEIß",     
   "R)", "SCHLIS",      "SCHLIS",      "SCHLEIS",     "SCHLEIß",     
   "R)", "SCHLISS",     "SCHLISS",     "SCHLEIS",     "SCHLEIß",     
   "R)", "SCHLISS",     "SCHLISS",     "SCHLEIS",     "SCHLEIß",     
   "R)", "SCHLEIST",    "SCHLEIßT",    "SCHLEIS",     "SCHLEIß",     
   "R)", "SCHLISS",     "SCHLISS",     "SCHLEIS",     "SCHLEIß",     
                                                                     
   "R)", "SCHLOS",      "SCHLOS",      "SCHLIES",     "SCHLIEß",     
   "R)", "SCHLOSS",     "SCHLOSS",     "SCHLIES",     "SCHLIEß",     
   "R)", "SCHLOSS",     "SCHLÖSS",     "SCHLIES",     "SCHLIEß",     
   "R)", "SCHLOSS",     "SCHLOSS",     "SCHLIES",     "SCHLIEß",     
                                                                     
   "R)", "SCHLANG",     "SCHLANG",     "SCHLING",     "SCHLING",     
   "R)", "SCHLANG",     "SCHLÄNG",     "SCHLING",     "SCHLING",     
   "R)", "SCHLUNG",     "SCHLUNG",     "SCHLING",     "SCHLING",     
                                                                     
   "R)", "SCHMIS",      "SCHMIS",      "SCHMEIS",     "SCHMEIß",     
   "R)", "SCHMISS",     "SCHMISS",     "SCHMEIS",     "SCHMEIß",     
   "R)", "SCHMISS",     "SCHMISS",     "SCHMEIS",     "SCHMEIß",     
                                                                     
   "Q)", "SCHMELZ",     "SCHMELZ",     "SCHMELZ",     "SCHMELZ",     
   "Q)", "SCHMILZ",     "SCHMILZ",     "SCHMELZ",     "SCHMELZ",     
   "Q)", "SCHMILZ",     "SCHMILZ",     "SCHMELZ",     "SCHMELZ",     
   "R)", "SCHMOLZ",     "SCHMOLZ",     "SCHMELZ",     "SCHMELZ",     
   "R)", "SCHMOLZ",     "SCHMÖLZ",     "SCHMELZ",     "SCHMELZ",     
   "Z)", "SCHMILZ",     "SCHMILZ",     "SCHMELZ",     "SCHMELZ",     
   "R)", "SCHMOLZ",     "SCHMOLZ",     "SCHMELZ",     "SCHMELZ",     
                                                                     
   "Q)", "SCHMELZ",     "SCHMELZ",     "SCHMELZ",     "SCHMELZ",     
   "Q)", "SCHMILZ",     "SCHMILZ",     "SCHMELZ",     "SCHMELZ",     
   "Q)", "SCHMILZ",     "SCHMILZ",     "SCHMELZ",     "SCHMELZ",     
   "R)", "SCHMOLZ",     "SCHMOLZ",     "SCHMELZ",     "SCHMELZ",     
   "R)", "SCHMELZT",    "SCHMELZT",    "SCHMELZ",     "SCHMELZ",     
   "R)", "SCHMOLZ",     "SCHMÖLZ",     "SCHMELZ",     "SCHMELZ",     
   "R)", "SCHMELZT",    "SCHMELZT",    "SCHMELZ",     "SCHMELZ",     
   "Z)", "SCHMELZ",     "SCHMELZ",     "SCHMELZ",     "SCHMELZ",     
   "Z)", "SCHMILZ",     "SCHMILZ",     "SCHMELZ",     "SCHMELZ",     
   "R)", "SCHMOLZ",     "SCHMOLZ",     "SCHMELZ",     "SCHMELZ",     
   "R)", "SCHMELZ",     "SCHMELZ",     "SCHMELZ",     "SCHMELZ",     
                                                                     
   "R)", "SCHNIT",      "SCHNIT",      "SCHNEID",     "SCHNEID",     
   "R)", "SCHNITT",     "SCHNITT",     "SCHNEID",     "SCHNEID",     
   "R)", "SCHNITT",     "SCHNITT",     "SCHNEID",     "SCHNEID",     
                                                                     
   "Q)", "SCHRICK",     "SCHRICK",     "SCHRECK",     "SCHRECK",     
   "Q)", "SCHRICK",     "SCHRICK",     "SCHRECK",     "SCHRECK",     
   "Q)", "SCHRECK",     "SCHRECK",     "SCHRECK",     "SCHRECK",     
   "Q)", "SCHRECK",     "SCHRECK",     "SCHRECK",     "SCHRECK",     
   "R)", "SCHRAK",      "SCHRAK",      "SCHRECK",     "SCHRECK",     
   "R)", "SCHRAK",      "SCHRÄK",      "SCHRECK",     "SCHRECK",     
   "R)", "SCHRECKT",    "SCHRECKT",    "SCHRECK",     "SCHRECK",     
   "R)", "SCHRECKT",    "SCHRECKT",    "SCHRECK",     "SCHRECK",     
// "R)", "ERSCHRECK",   "ERSCHRECK",   "SCHRECK",     "SCHRECK",     
   "Z)", "SCHRICK",     "SCHRICK",     "SCHRECK",     "SCHRECK",     
// "R)", "ERSCHROCK",   "ERSCHROCK",   "SCHRECK",     "SCHRECK",     
                                                                     
   "R)", "SCHRIEB",     "SCHRIEB",     "SCHREIB",     "SCHREIB",     
   "R)", "SCHRIEB",     "SCHRIEB",     "SCHREIB",     "SCHREIB",     
   "R)", "SCHRIEB",     "SCHRIEB",     "SCHREIB",     "SCHREIB",     
                                                                     
   "R)", "SCHRI",       "SCHRI",       "SCHREI",      "SCHREI",      
   "R)", "SCHRIE",      "SCHRIE",      "SCHREI",      "SCHREI",      
   "R)", "SCHRIE",      "SCHRIE",      "SCHREI",      "SCHREI",      
                                                                     
   "R)", "SCHRIT",      "SCHRIT",      "SCHREIT",     "SCHREIT",     
   "R)", "SCHRITT",     "SCHRITT",     "SCHREIT",     "SCHREIT",     
   "R)", "SCHRITT",     "SCHRITT",     "SCHREIT",     "SCHREIT",     
                                                                     
   "R)", "SCHWIEG",     "SCHWIEG",     "SCHWEIG",     "SCHWEIG",     
   "R)", "SCHWIEG",     "SCHWIEG",     "SCHWEIG",     "SCHWEIG",     
   "R)", "SCHWIEG",     "SCHWIEG",     "SCHWEIG",     "SCHWEIG",     
                                                                     
   "Q)", "SCHWILL",     "SCHWILL",     "SCHWELL",     "SCHWELL",     
   "Q)", "SCHWELN",     "SCHWELN",     "SCHWELL",     "SCHWELL",     
   "Q)", "SCHWILL",     "SCHWILL",     "SCHWELL",     "SCHWELL",     
   "Q)", "SCHWELL",     "SCHWELL",     "SCHWELL",     "SCHWELL",     
   "R)", "SCHWOLL",     "SCHWOLL",     "SCHWELL",     "SCHWELL",     
   "R)", "SCHWELLT",    "SCHWELLT",    "SCHWELL",     "SCHWELL",     
   "R)", "SCHWOLL",     "SCHWÖLL",     "SCHWELL",     "SCHWELL",     
   "R)", "SCHWELLT",    "SCHWELLT",    "SCHWELL",     "SCHWELL",     
   "R)", "SCHWEL",      "SCHWEL",      "SCHWELL",     "SCHWELL",     
   "Z)", "SCHWILL",     "SCHWILL",     "SCHWELL",     "SCHWELL",     
   "R)", "SCHWOLL",     "SCHWOLL",     "SCHWELL",     "SCHWELL",     
                                                                     
   "R)", "SCHWAMM",     "SCHWAMM",     "SCHWIMM",     "SCHWIMM",     
   "R)", "SCHWOMM",     "SCHWÖMM",     "SCHWIMM",     "SCHWIMM",     
   "R)", "SCHWAMM",     "SCHWÄMM",     "SCHWIMM",     "SCHWIMM",     
   "R)", "SCHWOMM",     "SCHWOMM",     "SCHWIMM",     "SCHWIMM",     
                                                                     
   "R)", "SCHWAND",     "SCHWAND",     "SCHWIND",     "SCHWIND",     
   "R)", "SCHWAND",     "SCHWÄND",     "SCHWIND",     "SCHWIND",     
   "R)", "SCHWUND",     "SCHWUND",     "SCHWIND",     "SCHWIND",     
                                                                     
   "R)", "SCHWANG",     "SCHWANG",     "SCHWING",     "SCHWING",     
   "R)", "SCHWANG",     "SCHWÄNG",     "SCHWING",     "SCHWING",     
   "R)", "SCHWUNG",     "SCHWUNG",     "SCHWING",     "SCHWING",     
                                                                     
   "R)", "SCHWOR",      "SCHWOR",      "SCHWOR",      "SCHWÖR",      
   "R)", "SCHWUR",      "SCHWUR",      "SCHWOR",      "SCHWÖR",      
   "R)", "SCHWUR",      "SCHWÜR",      "SCHWOR",      "SCHWÖR",      
   "R)", "SCHWOR",      "SCHWOR",      "SCHWOR",      "SCHWÖR",      
                                                                     
   "Q)", "SIEH",        "SIEH",        "SEH",         "SEH",         
   "Q)", "SIEH",        "SIEH",        "SEH",         "SEH",         
   "R)", "SAH",         "SAH",         "SEH",         "SEH",         
   "R)", "SAH",         "SÄH",         "SEH",         "SEH",         
   "Z)", "SIEH",        "SIEH",        "SEH",         "SEH",         
                                                                     
   "Q)", "BIN",         "BIN",         "SEIN",        "SEIN",        
   "Q)", ".BI",         ".BI",         "SEIN",        "SEIN",        
   "Q)", ".I",          ".I",          "SEIN",        "SEIN",        
   "Q)", "SIND",        "SIND",        "SEIN",        "SEIN",        
   "Q)", "SEID",        "SEID",        "SEIN",        "SEIN",        
   "Q)", "SIND",        "SIND",        "SEIN",        "SEIN",        
   "R)", "WAR",         "WAR",         "SEIN",        "SEIN",        
   "R)", "WAR",         "WAR",         "SEIN",        "SEIN",        
   "R)", "WAR",         "WÄR",         "SEIN",        "SEIN",        
   "R)", "SEI",         "SEI",         "SEIN",        "SEIN",        
   "R)", "SEI",         "SEI",         "SEIN",        "SEIN",        
   "R)", "SEI",         "SEI",         "SEIN",        "SEIN",        
   "R)", "SEI",         "SEI",         "SEIN",        "SEIN",        
   "R)", "SEI",         "SEI",         "SEIN",        "SEIN",        
   "R)", "SEI",         "SEI",         "SEIN",        "SEIN",        
   "Z)", "SEI",         "SEI",         "SEIN",        "SEIN",        
   "Z)", "SEID",        "SEID",        "SEIN",        "SEIN",        
   "R)", "WES",         "WES",         "SEIN",        "SEIN",        
                                                                     
   "R)", "SANDT",       "SANDT",       "SEND",        "SEND",        
   "R)", "SENDET",      "SENDET",      "SEND",        "SEND",        
   "R)", "SANDT",       "SANDT",       "SEND",        "SEND",        
   "R)", "SENDET",      "SENDET",      "SEND",        "SEND",        
   "R)", "SAND",        "SAND",        "SEND",        "SEND",        
                                                                     
   "R)", "SIEDET",      "SIEDET",      "SIED",        "SIED",        
   "R)", "SOT",         "SOT",         "SIED",        "SIED",        
   "R)", "SIEDET",      "SIEDET",      "SIED",        "SIED",        
   "R)", "SOTT",        "SÖTT",        "SIED",        "SIED",        
   "R)", "SOTT",        "SOTT",        "SIED",        "SIED",        
                                                                     
   "R)", "SANG",        "SANG",        "SING",        "SING",        
   "R)", "SANG",        "SÄNG",        "SING",        "SING",        
   "R)", "SUNG",        "SUNG",        "SING",        "SING",        
                                                                     
   "R)", "SANK",        "SANK",        "SINK",        "SINK",        
   "R)", "SANK",        "SÄNK",        "SINK",        "SINK",        
   "R)", "SUNK",        "SUNK",        "SINK",        "SINK",        
                                                                     
   "R)", "SANN",        "SANN",        "SINN",        "SINN",        
   "R)", "SANN",        "SÄNN",        "SINN",        "SINN",        
   "R)", "SONN",        "SÖNN",        "SINN",        "SINN",        
   "R)", "SONN",        "SONN",        "SINN",        "SINN",        
                                                                     
   "R)", "SAS",         "SAß",         "SITZ",        "SITZ",        
   "R)", "SAS",         "SÄß",         "SITZ",        "SITZ",        
   "R)", "SESS",        "SESS",        "SITZ",        "SITZ",        
                                                                     
   "R)", "SOLLT",       "SOLLT",       "SOLL",        "SOLL",        
   "R)", "SOLLT",       "SOLLT",       "SOLL",        "SOLL",        
                                                                     
   "R)", "SPALTET",     "SPALTET",     "SPALT",       "SPALT",       
   "R)", "SPALTET",     "SPALTET",     "SPALT",       "SPALT",       
                                                                     
   "R)", "SPI",         "SPI",         "SPEI",        "SPEI",        
   "R)", "SPIE",        "SPIE",        "SPEI",        "SPEI",        
   "R)", "SPIE",        "SPIE",        "SPEI",        "SPEI",        
                                                                     
   "R)", "SPANN",       "SPANN",       "SPINN",       "SPINN",       
   "R)", "SPONN",       "SPÖNN",       "SPINN",       "SPINN",       
   "R)", "SPANN",       "SPÄNN",       "SPINN",       "SPINN",       
   "R)", "SPONN",       "SPONN",       "SPINN",       "SPINN",       
                                                                     
   "Q)", "SPRICH",      "SPRICH",      "SPRECH",      "SPRECH",      
   "Q)", "SPRICH",      "SPRICH",      "SPRECH",      "SPRECH",      
   "R)", "SPRACH",      "SPRACH",      "SPRECH",      "SPRECH",      
   "R)", "SPRACH",      "SPRÄCH",      "SPRECH",      "SPRECH",      
   "Z)", "SPRICH",      "SPRICH",      "SPRECH",      "SPRECH",      
   "R)", "SPROCH",      "SPROCH",      "SPRECH",      "SPRECH",      
                                                                     
   "R)", "SPROS",       "SPROS",       "SPRIES",      "SPRIEß",      
   "R)", "SPROSS",      "SPROSS",      "SPRIES",      "SPRIEß",      
   "R)", "SPROSS",      "SPRÖSS",      "SPRIES",      "SPRIEß",      
   "R)", "SPROSS",      "SPROSS",      "SPRIES",      "SPRIEß",      
                                                                     
   "R)", "SPRANG",      "SPRANG",      "SPRING",      "SPRING",      
   "R)", "SPRANG",      "SPRÄNG",      "SPRING",      "SPRING",      
   "R)", "SPRUNG",      "SPRUNG",      "SPRING",      "SPRING",      
                                                                     
   "Q)", "STICH",       "STICH",       "STECH",       "STECH",       
   "Q)", "STICH",       "STICH",       "STECH",       "STECH",       
   "R)", "STACH",       "STACH",       "STECH",       "STECH",       
   "R)", "STACH",       "STÄCH",       "STECH",       "STECH",       
   "Z)", "STICH",       "STICH",       "STECH",       "STECH",       
   "R)", "STOCH",       "STOCH",       "STECH",       "STECH",       
                                                                     
   "R)", "STAK",        "STAK",        "STECK",       "STECK",       
   "R)", "STAK",        "STÄK",        "STECK",       "STECK",       
                                                                     
   "R)", "STAND",       "STAND",       "STEH",        "STEH",        
   "R)", "STAND",       "STÄND",       "STEH",        "STEH",        
   "R)", "STUND",       "STÜND",       "STEH",        "STEH",        
   "R)", "STAND",       "STAND",       "STEH",        "STEH",        
                                                                     
   "Q)", "STIEHL",      "STIEHL",      "STEHL",       "STEHL",       
   "Q)", "STIEHL",      "STIEHL",      "STEHL",       "STEHL",       
   "R)", "STAHL",       "STAHL",       "STEHL",       "STEHL",       
   "R)", "STOHL",       "STÖHL",       "STEHL",       "STEHL",       
   "R)", "STAHL",       "STÄHL",       "STEHL",       "STEHL",       
   "Z)", "STIEHL",      "STIEHL",      "STEHL",       "STEHL",       
   "R)", "STOHL",       "STOHL",       "STEHL",       "STEHL",       
                                                                     
   "R)", "STIEG",       "STIEG",       "STEIG",       "STEIG",       
   "R)", "STIEG",       "STIEG",       "STEIG",       "STEIG",       
   "R)", "STIEG",       "STIEG",       "STEIG",       "STEIG",       
                                                                     
   "Q)", "STIRB",       "STIRB",       "STERB",       "STERB",       
   "Q)", "STIRB",       "STIRB",       "STERB",       "STERB",       
   "R)", "STARB",       "STARB",       "STERB",       "STERB",       
   "R)", "STURB",       "STÜRB",       "STERB",       "STERB",       
   "Z)", "STIRB",       "STIRB",       "STERB",       "STERB",       
   "R)", "STORB",       "STORB",       "STERB",       "STERB",       
                                                                     
   "R)", "STOB",        "STOB",        "STIEB",       "STIEB",       
   "R)", "STIEBT",      "STIEBT",      "STIEB",       "STIEB",       
   "R)", "STOB",        "STÖB",        "STIEB",       "STIEB",       
   "R)", "STIEBT",      "STIEBT",      "STIEB",       "STIEB",       
   "R)", "STOB",        "STOB",        "STIEB",       "STIEB",       
                                                                     
   "R)", "STANK",       "STANK",       "STINK",       "STINK",       
   "R)", "STANK",       "STÄNK",       "STINK",       "STINK",       
   "R)", "STUNK",       "STUNK",       "STINK",       "STINK",       
                                                                     
   "Q)", "STOS",        "STÖß",        "STOS",        "STOß",        
   "Q)", "STOS",        "STÖß",        "STOS",        "STOß",        
   "R)", "STIES",       "STIEß",       "STOS",        "STOß",        
   "R)", "STIES",       "STIEß",       "STOS",        "STOß",        
                                                                     
   "R)", "STRICH",      "STRICH",      "STREICH",     "STREICH",     
   "R)", "STRICH",      "STRICH",      "STREICH",     "STREICH",     
   "R)", "STRICH",      "STRICH",      "STREICH",     "STREICH",     
                                                                     
   "R)", "STRIT",       "STRIT",       "STREIT",      "STREIT",      
   "R)", "STRITT",      "STRITT",      "STREIT",      "STREIT",      
   "R)", "STRITT",      "STRITT",      "STREIT",      "STREIT",      
                                                                     
   "Q)", "TRAG",        "TRÄG",        "TRAG",        "TRAG",        
   "Q)", "TRAG",        "TRÄG",        "TRAG",        "TRAG",        
   "R)", "TRUG",        "TRUG",        "TRAG",        "TRAG",        
   "R)", "TRUG",        "TRÜG",        "TRAG",        "TRAG",        
                                                                     
   "Q)", "TRIFF",       "TRIFF",       "TREFF",       "TREFF",       
   "Q)", "TRIFF",       "TRIFF",       "TREFF",       "TREFF",       
   "R)", "TRAF",        "TRAF",        "TREFF",       "TREFF",       
   "R)", "TRAF",        "TRÄF",        "TREFF",       "TREFF",       
   "Z)", "TRIFF",       "TRIFF",       "TREFF",       "TREFF",       
   "R)", "TROFF",       "TROFF",       "TREFF",       "TREFF",       
                                                                     
   "R)", "TRIEB",       "TRIEB",       "TREIB",       "TREIB",       
   "R)", "TRIEB",       "TRIEB",       "TREIB",       "TREIB",       
   "R)", "TRIEB",       "TRIEB",       "TREIB",       "TREIB",       
                                                                     
   "Q)", "TRITT",       "TRITT",       "TRET",        "TRET",        
   "Q)", "TRIT",        "TRIT",        "TRET",        "TRET",        
   "R)", "TRA",         "TRA",         "TRET",        "TRET",        
   "R)", "TRAT",        "TRÄT",        "TRET",        "TRET",        
   "Z)", "TRIT",        "TRIT",        "TRET",        "TRET",        
                                                                     
   "R)", "TROFF",       "TROFF",       "TRIEF",       "TRIEF",       
   "R)", "TRIEFT",      "TRIEFT",      "TRIEF",       "TRIEF",       
   "R)", "TROFF",       "TRÖFF",       "TRIEF",       "TRIEF",       
   "R)", "TRIEFT",      "TRIEFT",      "TRIEF",       "TRIEF",       
   "R)", "TROFF",       "TROFF",       "TRIEF",       "TRIEF",       
                                                                     
   "R)", "TRANK",       "TRANK",       "TRINK",       "TRINK",       
   "R)", "TRANK",       "TRÄNK",       "TRINK",       "TRINK",       
   "R)", "TRUNK",       "TRUNK",       "TRINK",       "TRINK",       
                                                                     
   "R)", "TROG",        "TROG",        "TRUG",        "TRÜG",        
   "R)", "TROG",        "TRÖG",        "TRUG",        "TRÜG",        
   "R)", "TROG",        "TROG",        "TRUG",        "TRÜG",        
                                                                     
   "Q)", ".TU",         ".TU",         "TUN",         "TUN",         
   "Q)", ".TU",         ".TU",         "TUN",         "TUN",         
   "Q)", ".TU",         ".TU",         "TUN",         "TUN",         
   "R)", ".TA",         ".TA",         "TUN",         "TUN",         
   "R)", "TAT",         "TÄT",         "TUN",         "TUN",         
   "Z)", ".TU",         ".TU",         "TUN",         "TUN",         
   "R)", "TAN",         "TAN",         "TUN",         "TUN",         
                                                                     
   "Q)", "VERDIRB",     "VERDIRB",     "VERDERB",     "VERDERB",     
   "Q)", "VERDIRB",     "VERDIRB",     "VERDERB",     "VERDERB",     
   "R)", "VERDARB",     "VERDARB",     "VERDERB",     "VERDERB",     
   "R)", "VERDURB",     "VERDÜRB",     "VERDERB",     "VERDERB",     
   "Z)", "VERDIRB",     "VERDIRB",     "VERDERB",     "VERDERB",     
   "R)", "VERDORB",     "VERDORB",     "VERDERB",     "VERDERB",     
                                                                     
   "R)", "VERDROS",     "VERDROS",     "VERDRIES",    "VERDRIEß",    
   "R)", "VERDROSS",    "VERDROSS",    "VERDRIES",    "VERDRIEß",    
   "R)", "VERDROSS",    "VERDRÖSS",    "VERDRIES",    "VERDRIEß",    
   "R)", "VERDROSS",    "VERDROSS",    "VERDRIES",    "VERDRIEß",    
                                                                     
   "Q)", "VERGIS",      "VERGIS",      "VERGESS",     "VERGESS",     
   "Q)", "VERGISS",     "VERGISS",     "VERGESS",     "VERGESS",     
   "Q)", "VERGIS",      "VERGIS",      "VERGESS",     "VERGESS",     
   "R)", "VERGAS",      "VERGAß",      "VERGESS",     "VERGESS",     
   "R)", "VERGAS",      "VERGÄß",      "VERGESS",     "VERGESS",     
   "Z)", "VERGIS",      "VERGIS",      "VERGESS",     "VERGESS",     
                                                                     
   "R)", "VERLOR",      "VERLOR",      "VERLIER",     "VERLIER",     
   "R)", "VERLOR",      "VERLÖR",      "VERLIER",     "VERLIER",     
   "R)", "VERLOR",      "VERLOR",      "VERLIER",     "VERLIER",     
                                                                     
   "R)", "VERZIEH",     "VERZIEH",     "VERZEIH",     "VERZEIH",     
   "R)", "VERZIEH",     "VERZIEH",     "VERZEIH",     "VERZEIH",     
   "R)", "VERZIEH",     "VERZIEH",     "VERZEIH",     "VERZEIH",     
                                                                     
   "Q)", "WACH",        "WÄCH",        "WACHS",       "WACHS",       
   "Q)", "WACH",        "WÄCH",        "WACHS",       "WACHS",       
   "R)", "WUCH",        "WUCH",        "WACHS",       "WACHS",       
   "R)", "WUCHS",       "WÜCHS",       "WACHS",       "WACHS",       
                                                                     
   "R)", "WOG",         "WOG",         "WAG",         "WÄG",         
   "R)", "WAGT",        "WÄGT",        "WAG",         "WÄG",         
   "R)", "WOG",         "WÖG",         "WAG",         "WÄG",         
   "R)", "WAGT",        "WÄGT",        "WAG",         "WÄG",         
   "R)", "WOG",         "WOG",         "WAG",         "WÄG",         
                                                                     
   "Q)", "WASCH",       "WÄSCH",       "WASCH",       "WASCH",       
   "Q)", "WASCH",       "WÄSCH",       "WASCH",       "WASCH",       
   "R)", "WUSCH",       "WUSCH",       "WASCH",       "WASCH",       
   "R)", "WUSCH",       "WÜSCH",       "WASCH",       "WASCH",       
                                                                     
   "R)", "WEBT",        "WEBT",        "WEB",         "WEB",         
   "R)", "WOB",         "WOB",         "WEB",         "WEB",         
   "R)", "WOB",         "WOB",         "WEB",         "WEB",         
   "R)", "WEBT",        "WEBT",        "WEB",         "WEB",         
   "R)", "WOB",         "WÖB",         "WEB",         "WEB",         
   "R)", "WOB",         "WOB",         "WEB",         "WEB",         
                                                                     
   "R)", "WICH",        "WICH",        "WEICH",       "WEICH",       
   "R)", "WICH",        "WICH",        "WEICH",       "WEICH",       
   "R)", "WICH",        "WICH",        "WEICH",       "WEICH",       
                                                                     
   "R)", "WI",          "WI",          "WEIS",        "WEIS",        
   "R)", "WIES",        "WIES",        "WEIS",        "WEIS",        
   "R)", "WIES",        "WIES",        "WEIS",        "WEIS",        
                                                                     
   "R)", "WANDT",       "WANDT",       "WEND",        "WEND",        
   "R)", "WENDET",      "WENDET",      "WEND",        "WEND",        
   "R)", "WENDET",      "WENDET",      "WEND",        "WEND",        
   "R)", "WAND",        "WAND",        "WEND",        "WEND",        
                                                                     
   "Q)", "WIRB",        "WIRB",        "WERB",        "WERB",        
   "Q)", "WIRB",        "WIRB",        "WERB",        "WERB",        
   "R)", "WARB",        "WARB",        "WERB",        "WERB",        
   "R)", "WURB",        "WÜRB",        "WERB",        "WERB",        
   "Z)", "WIRB",        "WIRB",        "WERB",        "WERB",        
   "R)", "WORB",        "WORB",        "WERB",        "WERB",        
                                                                     
   "Q)", "WIR",         "WIR",         "WERD",        "WERD",        
   "Q)", "WIRD",        "WIRD",        "WERD",        "WERD",        
   "R)", "WURD",        "WURD",        "WERD",        "WERD",        
   "R)", "WARD",        "WARD",        "WERD",        "WERD",        
   "R)", "WURD",        "WÜRD",        "WERD",        "WERD",        
   "R)", "WORD",        "WORD",        "WERD",        "WERD",        
   "R)", "WORD",        "WORD",        "WERD",        "WERD",        
                                                                     
   "Q)", "WIRF",        "WIRF",        "WERF",        "WERF",        
   "Q)", "WIRF",        "WIRF",        "WERF",        "WERF",        
   "R)", "WARF",        "WARF",        "WERF",        "WERF",        
   "R)", "WURF",        "WÜRF",        "WERF",        "WERF",        
   "Z)", "WIRF",        "WIRF",        "WERF",        "WERF",        
   "R)", "WORF",        "WORF",        "WERF",        "WERF",        
                                                                     
   "R)", "WOG",         "WOG",         "WIEG",        "WIEG",        
   "R)", "WOG",         "WÖG",         "WIEG",        "WIEG",        
   "R)", "WOG",         "WOG",         "WIEG",        "WIEG",        
                                                                     
   "R)", "WAND",        "WAND",        "WIND",        "WIND",        
   "R)", "WAND",        "WÄND",        "WIND",        "WIND",        
   "R)", "WUND",        "WUND",        "WIND",        "WIND",        
                                                                     
   "Q)", "WEIS",        "WEIß",        "WISS",        "WISS",        
   "Q)", "WIS",         "WIS",         "WISS",        "WISS",        
   "R)", "WUST",        "WUßT",        "WISS",        "WISS",        
   "R)", "WUST",        "WÜßT",        "WISS",        "WISS",        
   "R)", "WUS",         "WUS",         "WISS",        "WISS",        
                                                                     
   "Q)", "WILL",        "WILL",        "WOLL",        "WOLL",        
   "R)", "WOLLT",       "WOLLT",       "WOLL",        "WOLL",        
   "R)", "WOLLT",       "WOLLT",       "WOLL",        "WOLL",        
                                                                     
   "R)", "WRANG",       "WRANG",       "WRING",       "WRING",       
   "R)", "WRANG",       "WRÄNG",       "WRING",       "WRING",       
   "R)", "WRUNG",       "WRUNG",       "WRING",       "WRING",       

#if FALSE // ziehen                                                                     
   "R)", "ZIEH",        "ZIEH",        "ZEIH",        "ZEIH",        
   "R)", "ZEIHT",       "ZEIHT",       "ZEIH",        "ZEIH",        
   "R)", "ZIEH",        "ZIEH",        "ZEIH",        "ZEIH",        
   "R)", "ZIEH",        "ZIEH",        "ZEIH",        "ZEIH",        
#endif
                                                                     
   "R)", "ZOG",         "ZOG",         "ZIEH",        "ZIEH",        
   "R)", "ZOG",         "ZÖG",         "ZIEH",        "ZIEH",        
   "R)", "ZOG",         "ZOG",         "ZIEH",        "ZIEH",        
                                                                     
   "R)", "ZWANG",       "ZWANG",       "ZWING",       "ZWING",       
   "R)", "ZWANG",       "ZWÄNG",       "ZWING",       "ZWING",       
   "R)", "ZWUNG",       "ZWUNG",       "ZWING",       "ZWING",       
                                                                     
   NULL, NULL,          NULL,          NULL,          NULL          
};

