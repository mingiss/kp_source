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
   ".GELANG",   ".GEL�NG",  "GELING",      "GELING",  ")",  "",       
   ".GELUNG",   ".GELUNG",  "GELING",      "GELING",  ")",  "",       
                                                    
   ".GENES",    ".GENES",   "GENES",       "GENES",   ")",  "",    // genesen - suveikia ge-
   ".GENA",     ".GENA",    "GENES",       "GENES",   ")",  "",       
   ".GENAS",    ".GEN�S",   "GENES",       "GENES",   ")",  "",       
                                                    
   ".GENIES",   ".GENIE�",  "GENIES",      "GENIE�",  ")",  "",    // geniessen - suveikia ge-
   ".GENOS",    ".GENOS",   "GENIES",      "GENIE�",  ")",  "",       
   ".GENOSS",   ".GEN�SS",  "GENIES",      "GENIE�",  ")",  "",       
   ".GENOSS",   ".GENOSS",  "GENIES",      "GENIE�",  ")",  "",       
                                                    
   ".GESCHEH",  ".GESCHEH", "GESCHEH",     "GESCHEH", ")",  "",    // geschehen - suveikia ge-
   ".GESCHIEH", ".GESCHIEH","GESCHEH",     "GESCHEH", ")",  "",      
   ".GESCHAH",  ".GESCHAH", "GESCHEH",     "GESCHEH", ")",  "",       
   ".GESCHAH",  ".GESCH�H", "GESCHEH",     "GESCHEH", ")",  "",       
                                                    
   ".GEWINN",   ".GEWINN",  "GEWINN",      "GEWINN",  ")",  "",    // gewinnen - suveikia ge-
   ".GEWANN",   ".GEWANN",  "GEWINN",      "GEWINN",  ")",  "",       
   ".GEWANN",   ".GEW�NN",  "GEWINN",      "GEWINN",  ")",  "",       
   ".GEWONN",   ".GEW�NN",  "GEWINN",      "GEWINN",  ")",  "",       
   ".GEWONN",   ".GEWONN",  "GEWINN",      "GEWINN",  ")",  "",       

   ".GEWOHN",   ".GEW�HN",  ".GEWOHN",     ".GEW�HN", ")",  "",   // gewohnlich

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
   ".HERUBERGE",".HER�BERGE","HERUBER",  "HER�BER",  ")",  "",
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
   ".HINUBERGE",".HIN�BERGE","HINUBER",  "HIN�BER",  ")",  "",
   ".HINUNTERGE",".HINUNTERGE","HINUNTER","HINUNTER",")",  "",
   ".HINWEGGE", ".HINWEGGE", "HINWEG",   "HINWEG",   ")",  "",
   ".HINZUGE",  ".HINZUGE",  "HINZU",    "HINZU",    ")",  "",
   ".LOSGE",    ".LOSGE",    "LOS",      "LOS",      ")",  "",
   ".MISSGE",   ".MISSGE",   "MISS",     "MISS",     ")",  "",
   ".MITGE",    ".MITGE",    "MIT",      "MIT",      ")",  "",
   ".NACHGE",   ".NACHGE",   "NACH",     "NACH",     ")",  "",
   ".UBERGE",   ".�BERGE",   "UBER",     "�BER",     ")",  "",
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
   ".VORUBERGE",".VOR�BERGE","VORUBER",  "VOR�BER",  ")",  "",
// ".ZERGE",    ".ZERGE",    "ZER",      "ZER",      ")",  "", // neatsk.
   ".ZUGE",     ".ZUGE",     "ZU",       "ZU",       ")",  "",
   ".ZURUCKGE", ".ZUR�CKGE", "ZURUCK",   "ZUR�CK",   ")",  "",
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
// "TAT",      "T�T",      "TAT",      "T�T",      "A",  "v",     // absurdit�t
// "ACHT",     "ACHT",     "ACHT",     "ACHT",     "6",  "v",
// "ADAQUAT",  "AD�QUAT",  "ADAQUAT",  "AD�QUAT",  "L",  "v",
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
   "Q)", "BACK",        "B�CK",        "BACK",        "BACK",        
   "Q)", "BACK",        "B�CK",        "BACK",        "BACK",        
   "R)", "BUK",         "BUK",         "BACK",        "BACK",        
   "R)", "BACKT",       "BACKT",       "BACK",        "BACK",        
   "R)", "BUK",         "B�K",         "BACK",        "BACK",        
                                                                     
   "R)", "BEDANG",      "BEDANG",      "BEDING",      "BEDING",      
   "R)", "BEDINGT",     "BEDINGT",     "BEDING",      "BEDING",      
   "R)", "BEDANG",      "BED�NG",      "BEDING",      "BEDING",      
   "R)", "BEDINGT",     "BEDINGT",     "BEDING",      "BEDING",      
   "R)", "BEDUNG",      "BEDUNG",      "BEDING",      "BEDING",      
                                                                     
   "Q)", "BEFIEHL",     "BEFIEHL",     "BEFEHL",      "BEFEHL",      
   "Q)", "BEFIEHL",     "BEFIEHL",     "BEFEHL",      "BEFEHL",      
   "R)", "BEFAHL",      "BEFAHL",      "BEFEHL",      "BEFEHL",      
   "R)", "BEFOHL",      "BEF�HL",      "BEFEHL",      "BEFEHL",      
   "R)", "BEFAHL",      "BEF�HL",      "BEFEHL",      "BEFEHL",      
   "Z)", "BEFIEHL",     "BEFIEHL",     "BEFEHL",      "BEFEHL",      
   "R)", "BEFOHL",      "BEFOHL",      "BEFEHL",      "BEFEHL",      
                                                                     
   "R)", "BEFLIS",      "BEFLIS",      "BEFLEIS",     "BEFLEI�",     
   "R)", "BEFLISS",     "BEFLISS",     "BEFLEIS",     "BEFLEI�",     
   "R)", "BEFLISS",     "BEFLISS",     "BEFLEIS",     "BEFLEI�",     
   "R)", "BEFLISS",     "BEFLISS",     "BEFLEIS",     "BEFLEI�",     
                                                                     
   "R)", "BEGANN",      "BEGANN",      "BEGINN",      "BEGINN",      
   "R)", "BEGONN",      "BEG�NN",      "BEGINN",      "BEGINN",      
   "R)", "BEGANN",      "BEG�NN",      "BEGINN",      "BEGINN",      
   "R)", "BEGONN",      "BEGONN",      "BEGINN",      "BEGINN",      
                                                                     
   "R)", "BIS",         "BIS",         "BEIS",        "BEI�",        
   "R)", "BISS",        "BISS",        "BEIS",        "BEI�",        
   "R)", "BISS",        "BISS",        "BEIS",        "BEI�",        
   "R)", "BISS",        "BISS",        "BEIS",        "BEI�",        
                                                                     
   "Q)", "BIRG",        "BIRG",        "BERG",        "BERG",        
   "Q)", "BIRG",        "BIRG",        "BERG",        "BERG",        
   "R)", "BARG",        "BARG",        "BERG",        "BERG",        
   "R)", "BARG",        "B�RG",        "BERG",        "BERG",        
   "Z)", "BIRG",        "BIRG",        "BERG",        "BERG",        
   "R)", "BORG",        "BORG",        "BERG",        "BERG",        
                                                                     
   "Q)", "BIR",         "BIR",         "BERST",       "BERST",       
   "Q)", "BIR",         "BIR",         "BERST",       "BERST",       
   "Q)", "BERST",       "BERST",       "BERST",       "BERST",       
   "R)", "BAR",         "BAR",         "BERST",       "BERST",       
   "R)", "BOR",         "BOR",         "BERST",       "BERST",       
   "R)", "BERSTET",     "BERSTET",     "BERST",       "BERST",       
   "R)", "BARST",       "B�RST",       "BERST",       "BERST",       
   "Z)", "BIR",         "BIR",         "BERST",       "BERST",       
   "R)", "BORST",       "BORST",       "BERST",       "BERST",       
                                                                     
   "R)", "BEWOG",       "BEWOG",       "BEWEG",       "BEWEG",       
   "R)", "BEWOG",       "BEW�G",       "BEWEG",       "BEWEG",       
   "R)", "BEWOG",       "BEWOG",       "BEWEG",       "BEWEG",       
                                                                     
   "R)", "BOG",         "BOG",         "BIEG",        "BIEG",        
   "R)", "BOG",         "B�G",         "BIEG",        "BIEG",        
   "R)", "BOG",         "BOG",         "BIEG",        "BIEG",        
                                                                     
   "R)", "BO",          "BO",          "BIET",        "BIET",        
   "R)", "BOT",         "B�T",         "BIET",        "BIET",        
   "R)", "BOT",         "BOT",         "BIET",        "BIET",        
                                                                     
   "R)", "BAND",        "BAND",        "BIND",        "BIND",        
   "R)", "BAND",        "B�ND",        "BIND",        "BIND",        
   "R)", "BUND",        "BUND",        "BIND",        "BIND",        
                                                                     
   "R)", ".BA",         ".BA",         "BITT",        "BITT",        
   "R)", "BAT",         "B�T",         "BITT",        "BITT",        
   "R)", "BET",         "BET",         "BITT",        "BITT",        
                                                                     
   "Q)", "BLA",         "BL�",         "BLAS",        "BLAS",        
   "Q)", "BLA",         "BL�",         "BLAS",        "BLAS",        
   "R)", "BLI",         "BLI",         "BLAS",        "BLAS",        
   "R)", "BLIES",       "BLIES",       "BLAS",        "BLAS",        
                                                                     
   "R)", "BLIEB",       "BLIEB",       "BLEIB",       "BLEIB",       
   "R)", "BLIEB",       "BLIEB",       "BLEIB",       "BLEIB",       
   "R)", "BLIEB",       "BLIEB",       "BLEIB",       "BLEIB",       
                                                                     
   "R)", "BLICH",       "BLICH",       "BLEICH",      "BLEICH",      
   "R)", "BLICH",       "BLICH",       "BLEICH",      "BLEICH",      
   "R)", "BLICH",       "BLICH",       "BLEICH",      "BLEICH",      
                                                                     
   "Q)", "BRAT",        "BR�T",        "BRAT",        "BRAT",        
   "Q)", "BRA",         "BR�",         "BRAT",        "BRAT",        
   "R)", "BRI",         "BRI",         "BRAT",        "BRAT",        
   "R)", "BRIET",       "BRIET",       "BRAT",        "BRAT",        
                                                                     
   "Q)", "BRICH",       "BRICH",       "BRECH",       "BRECH",       
   "Q)", "BRICH",       "BRICH",       "BRECH",       "BRECH",       
   "R)", "BRACH",       "BRACH",       "BRECH",       "BRECH",       
   "R)", "BRACH",       "BR�CH",       "BRECH",       "BRECH",       
   "Z)", "BRICH",       "BRICH",       "BRECH",       "BRECH",       
   "R)", "BROCH",       "BROCH",       "BRECH",       "BRECH",       
                                                                     
   "R)", "BRANNT",      "BRANNT",      "BRENN",       "BRENN",       
   "R)", "BRENNT",      "BRENNT",      "BRENN",       "BRENN",       
   "R)", "BRANN",       "BRANN",       "BRENN",       "BRENN",       
                                                                     
   "R)", "BRACHT",      "BRACHT",      "BRING",       "BRING",       
   "R)", "BRACHT",      "BR�CHT",      "BRING",       "BRING",       
   "R)", "BRACH",       "BRACH",       "BRING",       "BRING",       
                                                                     
   "R)", "DACHT",       "DACHT",       "DENK",        "DENK",        
   "R)", "DACHT",       "D�CHT",       "DENK",        "DENK",        
   "R)", "DACH",        "DACH",        "DENK",        "DENK",        
                                                                     
   "R)", "DANG",        "DANG",        "DING",        "DING",        
   "R)", "DINGT",       "DINGT",       "DING",        "DING",        
   "R)", "DINGET",      "DINGET",      "DING",        "DING",        
   "R)", "DUNG",        "D�NG",        "DING",        "DING",        
   "R)", "DANG",        "D�NG",        "DING",        "DING",        
   "R)", "DUNG",        "DUNG",        "DING",        "DING",        
                                                                     
   "Q)", "DRISCH",      "DRISCH",      "DRESCH",      "DRESCH",      
   "Q)", "DRISCH",      "DRISCH",      "DRESCH",      "DRESCH",      
   "R)", "DROSCH",      "DROSCH",      "DRESCH",      "DRESCH",      
   "R)", "DRASCH",      "DRASCH",      "DRESCH",      "DRESCH",      
   "R)", "DROSCH",      "DR�SCH",      "DRESCH",      "DRESCH",      
   "Z)", "DRISCH",      "DRISCH",      "DRESCH",      "DRESCH",      
   "R)", "DROSCH",      "DROSCH",      "DRESCH",      "DRESCH",      
                                                                     
   "R)", "DRANG",       "DRANG",       "DRING",       "DRING",       
   "R)", "DRANG",       "DR�NG",       "DRING",       "DRING",       
   "R)", "DRUNG",       "DRUNG",       "DRING",       "DRING",       
                                                                     
   "Q)", "DEUCH",       "DEUCH",       "DUNK",        "D�NK",        
   "R)", "DUNKT",       "D�NKT",       "DUNK",        "D�NK",        
   "R)", "DEUCHT",      "DEUCHT",      "DUNK",        "D�NK",        
   "R)", "DEUCH",       "DEUCH",       "DUNK",        "D�NK",        
                                                                     
   "Q)", "DARF",        "DARF",        "DURF",        "D�RF",        
   "R)", "DURFT",       "DURFT",       "DURF",        "D�RF",        
   "R)", "DURFT",       "D�RFT",       "DURF",        "D�RF",        
   "R)", "DURF",        "DURF",        "DURF",        "D�RF",        
                                                                     
   "Q)", "EMPFIEHL",    "EMPFIEHL",    "EMPFEHL",     "EMPFEHL",     
   "Q)", "EMPFIEHL",    "EMPFIEHL",    "EMPFEHL",     "EMPFEHL",     
   "R)", "EMPFAHL",     "EMPFAHL",     "EMPFEHL",     "EMPFEHL",     
   "R)", "EMPFOHL",     "EMPF�HL",     "EMPFEHL",     "EMPFEHL",     
   "Z)", "EMPFIEHL",    "EMPFIEHL",    "EMPFEHL",     "EMPFEHL",     
   "R)", "EMPFOHL",     "EMPFOHL",     "EMPFEHL",     "EMPFEHL",     
                                                                     
   "R)", "ERBLEICHT",   "ERBLEICHT",   "ERBLEICH",    "ERBLEICH",    
   "R)", "ERBLICH",     "ERBLICH",     "ERBLEICH",    "ERBLEICH",    
   "R)", "ERBLEICHT",   "ERBLEICHT",   "ERBLEICH",    "ERBLEICH",    
   "R)", "ERBLICH",     "ERBLICH",     "ERBLEICH",    "ERBLEICH",    
   "R)", "ERBLICH",     "ERBLICH",     "ERBLEICH",    "ERBLEICH",    
                                                                     
   "R)", "ERKOR",       "ERKOR",       "ERKIES",      "ERKIES",      
   "R)", "ERKOR",       "ERK�R",       "ERKIES",      "ERKIES",      
   "R)", "ERKOR",       "ERKOR",       "ERKIES",      "ERKIES",      
                                                                     
   "Q)", "ERLISCH",     "ERLISCH",     "ERLOSCH",     "ERL�SCH",     
   "Q)", "ERLISCH",     "ERLISCH",     "ERLOSCH",     "ERL�SCH",     
   "R)", "ERLOSCH",     "ERLOSCH",     "ERLOSCH",     "ERL�SCH",     
   "Z)", "ERLISCH",     "ERLISCH",     "ERLOSCH",     "ERL�SCH",     
   "R)", "ERLOSCH",     "ERLOSCH",     "ERLOSCH",     "ERL�SCH",     
                                                                     
   "Q)", "ERSCHRICK",   "ERSCHRICK",   "ERSCHRECK",   "ERSCHRECK",   
   "Q)", "ERSCHRICK",   "ERSCHRICK",   "ERSCHRECK",   "ERSCHRECK",   
   "R)", "ERSCHRAK",    "ERSCHRAK",    "ERSCHRECK",   "ERSCHRECK",   
   "R)", "ERSCHRAK",    "ERSCHR�K",    "ERSCHRECK",   "ERSCHRECK",   
   "Z)", "ERSCHRICK",   "ERSCHRICK",   "ERSCHRECK",   "ERSCHRECK",   
   "R)", "ERSCHROCK",   "ERSCHROCK",   "ERSCHRECK",   "ERSCHRECK",   
                                                                     
   "R)", "ERWOG",       "ERWOG",       "ERWAG",       "ERW�G",       
   "R)", "ERWOG",       "ERW�G",       "ERWAG",       "ERW�G",       
   "R)", "ERWOG",       "ERWOG",       "ERWAG",       "ERW�G",       
                                                                     
   "Q)", ".IS",         ".IS",         "ESS",         "ESS",         
   "Q)", "ISS",         "ISS",         "ESS",         "ESS",         
   "Q)", ".IS",         ".IS",         "ESS",         "ESS",         
   "R)", ".AS",         ".A�",         "ESS",         "ESS",         
   "R)", ".AS",         ".��",         "ESS",         "ESS",         
   "Z)", ".IS",         ".IS",         "ESS",         "ESS",         
   "R)", "GESS",        "GESS",        "ESS",         "ESS",         
                                                                     
   "Q)", "FAHR",        "F�HR",        "FAHR",        "FAHR",        
   "Q)", "FAHR",        "F�HR",        "FAHR",        "FAHR",        
   "R)", "FUHR",        "FUHR",        "FAHR",        "FAHR",        
   "R)", "FUHR",        "F�HR",        "FAHR",        "FAHR",        
                                                                     
   "Q)", "FALL",        "F�LL",        "FALL",        "FALL",        
   "Q)", "FALL",        "F�LL",        "FALL",        "FALL",        
   "R)", "FIEL",        "FIEL",        "FALL",        "FALL",        
   "R)", "FIEL",        "FIEL",        "FALL",        "FALL",        
                                                                     
   "Q)", "FANG",        "F�NG",        "FANG",        "FANG",        
   "Q)", "FANG",        "F�NG",        "FANG",        "FANG",        
   "R)", "FING",        "FING",        "FANG",        "FANG",        
   "R)", "FING",        "FING",        "FANG",        "FANG",        
                                                                     
   "Q)", "FICHT",       "FICHT",       "FECHT",       "FECHT",       
   "Q)", "FICH",        "FICH",        "FECHT",       "FECHT",       
   "R)", "FOCH",        "FOCH",        "FECHT",       "FECHT",       
   "R)", "FOCHT",       "F�CHT",       "FECHT",       "FECHT",       
   "Z)", "FICH",        "FICH",        "FECHT",       "FECHT",       
   "R)", "FOCHT",       "FOCHT",       "FECHT",       "FECHT",       
                                                                     
   "R)", "FAND",        "FAND",        "FIND",        "FIND",        
   "R)", "FAND",        "F�ND",        "FIND",        "FIND",        
   "R)", "FUND",        "FUND",        "FIND",        "FIND",        
                                                                     
   "Q)", "FLICHT",      "FLICHT",      "FLECHT",      "FLECHT",      
   "Q)", "FLICH",       "FLICH",       "FLECHT",      "FLECHT",      
   "Q)", "FLECHT",      "FLECHT",      "FLECHT",      "FLECHT",      
   "R)", "FLOCH",       "FLOCH",       "FLECHT",      "FLECHT",      
   "R)", "FLOCHT",      "FL�CHT",      "FLECHT",      "FLECHT",      
   "Z)", "FLICH",       "FLICH",       "FLECHT",      "FLECHT",      
   "R)", "FLOCHT",      "FLOCHT",      "FLECHT",      "FLECHT",      
                                                                     
   "R)", "FLOG",        "FLOG",        "FLIEG",       "FLIEG",       
   "R)", "FLOG",        "FL�G",        "FLIEG",       "FLIEG",       
   "R)", "FLOG",        "FLOG",        "FLIEG",       "FLIEG",       
                                                                     
   "R)", "FLOH",        "FLOH",        "FLIEH",       "FLIEH",       
   "R)", "FLOH",        "FL�H",        "FLIEH",       "FLIEH",       
   "R)", "FLOH",        "FLOH",        "FLIEH",       "FLIEH",       
                                                                     
   "R)", "FLOS",        "FLOS",        "FLIES",       "FLIE�",       
   "R)", "FLOSS",       "FLOSS",       "FLIES",       "FLIE�",       
   "R)", "FLOSS",       "FL�SS",       "FLIES",       "FLIE�",       
   "R)", "FLOSS",       "FLOSS",       "FLIES",       "FLIE�",       
                                                                     
   "Q)", "FRIS",        "FRIS",        "FRESS",       "FRESS",       
   "Q)", "FRIS",        "FRI�",        "FRESS",       "FRESS",       
   "R)", "FRAS",        "FRA�",        "FRESS",       "FRESS",       
   "R)", "FRAS",        "FR��",        "FRESS",       "FRESS",       
   "Z)", "FRIS",        "FRI�",        "FRESS",       "FRESS",       
                                                                     
   "R)", "FROR",        "FROR",        "FRIER",       "FRIER",       
   "R)", "FROR",        "FR�R",        "FRIER",       "FRIER",       
   "R)", "FROR",        "FROR",        "FRIER",       "FRIER",       
                                                                     
   "R)", "GART",        "G�RT",        "GAR",         "G�R",         
   "R)", "GOR",         "GOR",         "GAR",         "G�R",         
   "R)", "GART",        "G�RT",        "GAR",         "G�R",         
   "R)", "GOR",         "G�R",         "GAR",         "G�R",         
   "R)", "GOR",         "GOR",         "GAR",         "G�R",         

   "Q)", "GEBIER",      "GEBIER",      "GEBAR",       "GEB�R",         
   "Q)", "GEBAR",       "GEB�R",       "GEBAR",       "GEB�R",         
   "Q)", "GEBIER",      "GEBIER",      "GEBAR",       "GEB�R",         
   "R)", "GEBAR",       "GEBAR",       "GEBAR",       "GEB�R",         
   "Z)", "GEBI",        "GEBI",        "GEBAR",       "GEB�R",         
   "R)", "GEBOR",       "GEBOR",       "GEBAR",       "GEB�R",         
                                                                     
   "Q)", "GEGIB",       "GEGIB",       "GEB",         "GEB",           
   "Q)", "GEGIB",       "GEGIB",       "GEB",         "GEB",           
   "R)", "GEGAB",       "GEGAB",       "GEB",         "GEB",           
   "R)", "GEGAB",       "GEG�B",       "GEB",         "GEB",           
   "Z)", "GEGIB",       "GEGIB",       "GEB",         "GEB",           
   "R)", "GEGEB",       "GEGEB",       "GEB",         "GEB",           
                                                                     
   "R)", "GEDIEH",      "GEDIEH",      "GEDEIH",      "GEDEIH",        
   "R)", "GEDIEH",      "GEDIEH",      "GEDEIH",      "GEDEIH",        
   "R)", "GEDIEH",      "GEDIEH",      "GEDEIH",      "GEDEIH",        
                                                                     
   "R)", "GING",        "GING",        "GEH",         "GEH",           
   "R)", "GING",        "GING",        "GEH",         "GEH",           
   "R)", "GANG",        "GANG",        "GEH",         "GEH",           
                                                                     
   "R)", "GELANG",      "GELANG",      "GELING",      "GELING",        
   "R)", "GELANG",      "GEL�NG",      "GELING",      "GELING",        
   "R)", "GELUNG",      "GELUNG",      "GELING",      "GELING",        
                                                                     
   "Q)", "GILT",        "GILT",        "GELT",        "GELT",           
   "Q)", "GIL",         "GIL",         "GELT",        "GELT",           
   "R)", "GAL",         "GAL",         "GELT",        "GELT",           
   "R)", "GALT",        "G�LT",        "GELT",        "GELT",           
   "R)", "GOLT",        "G�LT",        "GELT",        "GELT",           
   "Z)", "GIL",         "GIL",         "GELT",        "GELT",           
   "R)", "GOLT",        "GOLT",        "GELT",        "GELT",           
                                                            
   "R)", "GENA",        "GENA",        "GENES",       "GENES",         
   "R)", "GENAS",       "GEN�S",       "GENES",       "GENES",         
                                                                     
   "R)", "GENOS",       "GENOS",       "GENIES",      "GENIE�",        
   "R)", "GENOSS",      "GEN�SS",      "GENIES",      "GENIE�",        
   "R)", "GENOSS",      "GENOSS",      "GENIES",      "GENIE�",        
                                                                     
   "Q)", "GESCHIEH",    "GESCHIEH",    "GESCHEH",     "GESCHEH",       
   "R)", "GESCHAH",     "GESCHAH",     "GESCHEH",     "GESCHEH",       
   "R)", "GESCHAH",     "GESCH�H",     "GESCHEH",     "GESCHEH",       
                                                                     
   "R)", "GEWANN",      "GEWANN",      "GEWINN",      "GEWINN",        
   "R)", "GEWANN",      "GEW�NN",      "GEWINN",      "GEWINN",        
   "R)", "GEWONN",      "GEW�NN",      "GEWINN",      "GEWINN",        
   "R)", "GEWONN",      "GEWONN",      "GEWINN",      "GEWINN",        
                                                                     
   "R)", "GOS",         "GOS",         "GIES",        "GIE�",        
   "R)", "GOSS",        "GOSS",        "GIES",        "GIE�",        
   "R)", "GOSS",        "G�SS",        "GIES",        "GIE�",        
   "R)", "GOSS",        "GOSS",        "GIES",        "GIE�",        
                                                                     
   "R)", "GLICH",       "GLICH",       "GLEICH",      "GLEICH",      
   "R)", "GLICH",       "GLICH",       "GLEICH",      "GLEICH",      
   "R)", "GLICH",       "GLICH",       "GLEICH",      "GLEICH",      
                                                                     
   "R)", "GLEIST",      "GLEI�T",      "GLEIS",       "GLEI�",       
   "R)", "GLIS",        "GLIS",        "GLEIS",       "GLEI�",       
   "R)", "GLISS",       "GLISS",       "GLEIS",       "GLEI�",       
   "R)", "GLISS",       "GLISS",       "GLEIS",       "GLEI�",       
   "R)", "GLISS",       "GLISS",       "GLEIS",       "GLEI�",       
                                                                     
   "R)", "GLIT",        "GLIT",        "GLEIT",       "GLEIT",       
   "R)", "GLITT",       "GLITT",       "GLEIT",       "GLEIT",       
   "R)", "GLITT",       "GLITT",       "GLEIT",       "GLEIT",       
                                                                     
   "R)", "GLIMMT",      "GLIMMT",      "GLIMM",       "GLIMM",       
   "R)", "GLOMM",       "GLOMM",       "GLIMM",       "GLIMM",       
   "R)", "GLOMM",       "GL�MM",       "GLIMM",       "GLIMM",       
   "R)", "GLOMM",       "GLOMM",       "GLIMM",       "GLIMM",       
                                                                     
   "Q)", "GRAB",        "GR�B",        "GRAB",        "GRAB",        
   "Q)", "GRAB",        "GR�B",        "GRAB",        "GRAB",        
   "R)", "GRUB",        "GRUB",        "GRAB",        "GRAB",        
   "R)", "GRUB",        "GR�B",        "GRAB",        "GRAB",        
                                                                     
   "R)", "GRIFF",       "GRIFF",       "GREIF",       "GREIF",       
   "R)", "GRIFF",       "GRIFF",       "GREIF",       "GREIF",       
   "R)", "GRIFF",       "GRIFF",       "GREIF",       "GREIF",       
                                                                     
   "Q)", ".HA",         ".HA",         "HAB",         "HAB",         
   "Q)", ".HA",         ".HA",         "HAB",         "HAB",         
   "R)", "HATT",        "HATT",        "HAB",         "HAB",         
   "R)", "HATT",        "H�TT",        "HAB",         "HAB",         
                                                                     
   "Q)", "HALT",        "H�LT",        "HALT",        "HALT",        
   "Q)", "HAL",         "H�L",         "HALT",        "HALT",        
   "R)", "HIEL",        "HIEL",        "HALT",        "HALT",        
   "R)", "HIELT",       "HIELT",       "HALT",        "HALT",        
                                                                     
   "Q)", "HANG",        "H�NG",        "HANG",        "H�NG",        
   "Q)", "HANG",        "HANG",        "HANG",        "H�NG",        
   "Q)", "HANG",        "H�NG",        "HANG",        "H�NG",        
   "Q)", "HANG",        "H�NG",        "HANG",        "H�NG",        
   "R)", "HING",        "HING",        "HANG",        "H�NG",        
   "R)", "HING",        "HING",        "HANG",        "H�NG",        
   "Z)", "HANG",        "H�NG",        "HANG",        "H�NG",        
   "R)", "HANG",        "HANG",        "HANG",        "H�NG",        
                                                                     
   "Q)", "HANG",        "H�NG",        "HANG",        "HANG",        
   "Q)", "HANG",        "HANG",        "HANG",        "HANG",        
   "Q)", "HANG",        "H�NG",        "HANG",        "HANG",        
   "Q)", "HANG",        "H�NG",        "HANG",        "HANG",        
   "R)", "HING",        "HING",        "HANG",        "HANG",        
   "R)", "HING",        "HING",        "HANG",        "HANG",        
   "Z)", "HANG",        "H�NG",        "HANG",        "HANG",        
   "R)", "HANG",        "HANG",        "HANG",        "HANG",        
                                                                     
   "R)", "HAUT",        "HAUT",        "HAU",         "HAU",         
   "R)", "HIEB",        "HIEB",        "HAU",         "HAU",         
   "R)", "HIEB",        "HIEB",        "HAU",         "HAU",         
   "R)", "HAUT",        "HAUT",        "HAU",         "HAU",         
                                                                     
   "R)", "HOB",         "HOB",         "HEB",         "HEB",         
   "R)", "HUB",         "HUB",         "HEB",         "HEB",         
   "R)", "HOB",         "H�B",         "HEB",         "HEB",         
   "R)", "HUB",         "H�B",         "HEB",         "HEB",         
   "R)", "HOB",         "HOB",         "HEB",         "HEB",         
                                                                     
   "R)", "HIES",        "HIE�",        "HEIS",        "HEI�",        
   "R)", "HIES",        "HIE�",        "HEIS",        "HEI�",        
                                                                     
   "Q)", "HILF",        "HILF",        "HELF",        "HELF",        
   "Q)", "HILF",        "HILF",        "HELF",        "HELF",        
   "R)", "HALF",        "HALF",        "HELF",        "HELF",        
   "R)", "HULF",        "H�LF",        "HELF",        "HELF",        
   "Z)", "HILF",        "HILF",        "HELF",        "HELF",        
   "R)", "HOLF",        "HOLF",        "HELF",        "HELF",        
                                                                     
   "R)", "KANNT",       "KANNT",       "KENN",        "KENN",        
   "R)", "KENNT",       "KENNT",       "KENN",        "KENN",        
   "R)", "KANN",        "KANN",        "KENN",        "KENN",        
                                                                     
   "R)", "KLIMMT",      "KLIMMT",      "KLIMM",       "KLIMM",       
   "R)", "KLOMM",       "KLOMM",       "KLIMM",       "KLIMM",       
   "R)", "KLOMM",       "KL�MM",       "KLIMM",       "KLIMM",       
   "R)", "KLOMM",       "KLOMM",       "KLIMM",       "KLIMM",       
                                                                     
   "R)", "KLANG",       "KLANG",       "KLING",       "KLING",       
   "R)", "KLANG",       "KL�NG",       "KLING",       "KLING",       
   "R)", "KLUNG",       "KLUNG",       "KLING",       "KLING",       
                                                                     
   "R)", "KNIFF",       "KNIFF",       "KNEIF",       "KNEIF",       
   "R)", "KNIFF",       "KNIFF",       "KNEIF",       "KNEIF",       
   "R)", "KNIFF",       "KNIFF",       "KNEIF",       "KNEIF",       
                                                                     
   "R)", "KAM",         "KAM",         "KOMM",        "KOMM",        
   "R)", "KAM",         "K�M",         "KOMM",        "KOMM",        
                                                                     
   "Q)", "KANN",        "KANN",        "KONN",        "K�NN",        
   "R)", "KONNT",       "KONNT",       "KONN",        "K�NN",        
   "R)", "KONNT",       "K�NNT",       "KONN",        "K�NN",        
   "R)", "KONN",        "KONN",        "KONN",        "K�NN",        
                                                                     
   "R)", "KROCH",       "KROCH",       "KRIECH",      "KRIECH",      
   "R)", "KROCH",       "KR�CH",       "KRIECH",      "KRIECH",      
   "R)", "KROCH",       "KROCH",       "KRIECH",      "KRIECH",      
                                                                     
   "Q)", "LAD",         "LAD",         "LAD",         "LAD",         
   "Q)", "LAD",         "L�D",         "LAD",         "LAD",         
   "Q)", "LAD",         "L�D",         "LAD",         "LAD",         
   "R)", "LUD",         "LUD",         "LAD",         "LAD",         
   "R)", "LUD",         "L�D",         "LAD",         "LAD",         
   "Z)", "LAD",         "LAD",         "LAD",         "LAD",         
   "R)", "LAD",         "LAD",         "LAD",         "LAD",         
                                                                     
   "Q)", "LAD",         "LAD",         "LAD",         "LAD",         
   "Q)", "LAD",         "L�D",         "LAD",         "LAD",         
   "Q)", "LAD",         "L�D",         "LAD",         "LAD",         
   "Q)", "LAD",         "LAD",         "LAD",         "LAD",         
   "Q)", "LAD",         "LAD",         "LAD",         "LAD",         
   "R)", "LUD",         "LUD",         "LAD",         "LAD",         
   "R)", "LADET",       "LADET",       "LAD",         "LAD",         
   "R)", "LUD",         "L�D",         "LAD",         "LAD",         
   "R)", "LADET",       "LADET",       "LAD",         "LAD",         
   "Z)", "LAD",         "LAD",         "LAD",         "LAD",         
   "R)", "LAD",         "LAD",         "LAD",         "LAD",         
                                                                     
   "Q)", "LAS",         "L�S",         "LASS",        "LASS",        
   "Q)", "LAS",         "L�S",         "LASS",        "LASS",        
   "R)", "LIES",        "LIE�",        "LASS",        "LASS",        
   "R)", "LIES",        "LIE�",        "LASS",        "LASS",        
   "Z)", "LAS",         "LA�",         "LASS",        "LASS",        
                                                                     
   "Q)", "LAUF",        "L�UF",        "LAUF",        "LAUF",        
   "Q)", "LAUF",        "L�UF",        "LAUF",        "LAUF",        
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
   "R)", "LAS",         "L�S",         "LES",         "LES",         
   "Z)", ".LI",         ".LI",         "LES",         "LES",         
                                                                     
   "R)", "LAG",         "LAG",         "LIEG",        "LIEG",        
   "R)", "LAG",         "L�G",         "LIEG",        "LIEG",        
   "R)", "LEG",         "LEG",         "LIEG",        "LIEG",        
   "R)", "SCHLAG",      "SCHLAG",      "SCHLAG",      "SCHLAG",        
                                                                     
   "R)", "LOG",         "LOG",         "LUG",         "L�G",         
   "R)", "LOG",         "L�G",         "LUG",         "L�G",         
   "R)", "LOG",         "LOG",         "LUG",         "L�G",         
                                                                     
   "R)", "MAHLT",       "MAHLT",       "MAHL",        "MAHL",        
   "R)", "MAHLT",       "MAHLT",       "MAHL",        "MAHL",        
                                                                     
   "R)", "MIED",        "MIED",        "MEID",        "MEID",        
   "R)", "MIED",        "MIED",        "MEID",        "MEID",        
   "R)", "MIED",        "MIED",        "MEID",        "MEID",        
                                                                     
   "Q)", "MILK",        "MILK",        "MELK",        "MELK",        
   "Q)", "MILK",        "MILK",        "MELK",        "MELK",        
   "R)", "MELKT",       "MELKT",       "MELK",        "MELK",        
   "R)", "MOLK",        "MOLK",        "MELK",        "MELK",        
   "R)", "MOLK",        "M�LK",        "MELK",        "MELK",        
   "R)", "MOLK",        "MOLK",        "MELK",        "MELK",        
                                                                     
   "Q)", "MIS",         "MIS",         "MESS",        "MESS",        
   "Q)", "MIS",         "MI�",         "MESS",        "MESS",        
   "R)", "MAS",         "MA�",         "MESS",        "MESS",        
   "R)", "MAS",         "M��",         "MESS",        "MESS",        
   "Z)", "MIS",         "MIS",         "MESS",        "MESS",        
                                                                     
   "R)", "MISLANG",     "MI�LANG",     "MISLING",     "MI�LING",     
   "R)", "MISLANG",     "MI�L�NG",     "MISLING",     "MI�LING",     
   "R)", "MISLUNG",     "MI�LUNG",     "MISLING",     "MI�LING",     
                                                                     
   "Q)", "MAG",         "MAG",         "MOG",         "M�G",         
   "R)", "MOCHT",       "MOCHT",       "MOG",         "M�G",         
   "R)", "MOCHT",       "M�CHT",       "MOG",         "M�G",         
   "R)", "MOCH",        "MOCH",        "MOG",         "M�G",         
                                                                     
   "Q)", "MUS",         "MUS",         "MUSS",        "M�SS",        
   "R)", "MUST",        "MU�T",        "MUSS",        "M�SS",        
   "R)", "MUST",        "M��T",        "MUSS",        "M�SS",        
   "R)", "MUS",         "MUS",         "MUSS",        "M�SS",        
                                                                     
   "Q)", "NIMM",        "NIMM",        "NEHM",        "NEHM",        
   "Q)", "NIMM",        "NIMM",        "NEHM",        "NEHM",        
   "R)", "NAHM",        "NAHM",        "NEHM",        "NEHM",        
   "R)", "NAHM",        "N�HM",        "NEHM",        "NEHM",        
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
   "R)", "PFLOG",       "PFL�G",       "PFLEG",       "PFLEG",       
   "R)", "PFLOG",       "PFLOG",       "PFLEG",       "PFLEG",       
                                                                     
   "R)", "PRI",         "PRI",         "PREIS",       "PREIS",       
   "R)", "PRIES",       "PRIES",       "PREIS",       "PREIS",       
   "R)", "PRIES",       "PRIES",       "PREIS",       "PREIS",       
                                                                     
   "Q)", "QUILL",       "QUILL",       "QUELL",       "QUELL",       
   "Q)", "QUILL",       "QUILL",       "QUELL",       "QUELL",       
   "Q)", "QUELL",       "QUELL",       "QUELL",       "QUELL",       
   "R)", "QUOLL",       "QUOLL",       "QUELL",       "QUELL",       
   "R)", "QUELLT",      "QUELLT",      "QUELL",       "QUELL",       
   "R)", "QUOLL",       "QU�LL",       "QUELL",       "QUELL",       
   "Z)", "QUILL",       "QUILL",       "QUELL",       "QUELL",       
   "R)", "QUOLL",       "QUOLL",       "QUELL",       "QUELL",       
                                                                     
   "Q)", "RAT",         "R�T",         "RAT",         "RAT",         
   "Q)", ".RA",         ".R�",         "RAT",         "RAT",         
   "R)", ".RI",         ".RI",         "RAT",         "RAT",         
   "R)", "RIET",        "RIET",        "RAT",         "RAT",         
                                                                     
   "R)", "RIEB",        "RIEB",        "REIB",        "REIB",        
   "R)", "RIEB",        "RIEB",        "REIB",        "REIB",        
   "R)", "RIEB",        "RIEB",        "REIB",        "REIB",        
                                                                     
   "R)", "RIS",         "RIS",         "REIS",        "REI�",        
   "R)", "RISS",        "RISS",        "REIS",        "REI�",        
   "R)", "RISS",        "RISS",        "REIS",        "REI�",        
   "R)", "RISS",        "RISS",        "REIS",        "REI�",        
                                                                     
   "R)", "RIT",         "RIT",         "REIT",        "REIT",        
   "R)", "RITT",        "RITT",        "REIT",        "REIT",        
   "R)", "RITT",        "RITT",        "REIT",        "REIT",        
                                                                     
   "R)", "RANNT",       "RANNT",       "RENN",        "RENN",        
   "R)", "RENNT",       "RENNT",       "RENN",        "RENN",        
   "R)", "RANN",        "RANN",        "RENN",        "RENN",        
                                                                     
   "R)", "ROCH",        "ROCH",        "RIECH",       "RIECH",       
   "R)", "ROCH",        "R�CH",        "RIECH",       "RIECH",       
   "R)", "ROCH",        "ROCH",        "RIECH",       "RIECH",       
                                                                     
   "R)", "RANG",        "RANG",        "RING",        "RING",        
   "R)", "RANG",        "R�NG",        "RING",        "RING",        
   "R)", "RUNG",        "RUNG",        "RING",        "RING",        
                                                                     
   "R)", "RANN",        "RANN",        "RINN",        "RINN",        
   "R)", "RANN",        "R�NN",        "RINN",        "RINN",        
   "R)", "RONN",        "R�NN",        "RINN",        "RINN",        
   "R)", "RONN",        "RONN",        "RINN",        "RINN",        
                                                                     
   "R)", "RIEF",        "RIEF",        "RUF",         "RUF",         
   "R)", "RIEF",        "RIEF",        "RUF",         "RUF",         
                                                                     
   "R)", "SALZT",       "SALZT",       "SALZ",        "SALZ",        
   "R)", "SALZT",       "SALZT",       "SALZ",        "SALZ",        
                                                                     
   "Q)", "SAUF",        "S�UF",        "SAUF",        "SAUF",        
   "Q)", "SAUF",        "S�UF",        "SAUF",        "SAUF",        
   "R)", "SOFF",        "SOFF",        "SAUF",        "SAUF",        
   "R)", "SOFF",        "S�FF",        "SAUF",        "SAUF",        
   "R)", "SOFF",        "SOFF",        "SAUF",        "SAUF",        
                                                                     
   "R)", "SOG",         "SOG",         "SAUG",        "SAUG",        
   "R)", "SAUGT",       "SAUGT",       "SAUG",        "SAUG",        
   "R)", "SOG",         "S�G",         "SAUG",        "SAUG",        
   "R)", "SOG",         "SOG",         "SAUG",        "SAUG",        
                                                                     
   "R)", "SCHUF",       "SCHUF",       "SCHAFF",      "SCHAFF",      
   "R)", "SCHUF",       "SCH�F",       "SCHAFF",      "SCHAFF",      
                                                                     
   "R)", "SCHALLT",     "SCHALLT",     "SCHALL",      "SCHALL",      
   "R)", "SCHOLL",      "SCHOLL",      "SCHALL",      "SCHALL",      
   "R)", "SCHALLET",    "SCHALLET",    "SCHALL",      "SCHALL",      
   "R)", "SCHOLL",      "SCH�LL",      "SCHALL",      "SCHALL",      
                                                                     
   "R)", "SCHIED",      "SCHIED",      "SCHEID",      "SCHEID",      
   "R)", "SCHIED",      "SCHIED",      "SCHEID",      "SCHEID",      
   "R)", "SCHIED",      "SCHIED",      "SCHEID",      "SCHEID",      
                                                                     
   "R)", "SCHI",        "SCHI",        "SCHEIN",      "SCHEIN",      
   "R)", "SCHIEN",      "SCHIEN",      "SCHEIN",      "SCHEIN",      
   "R)", "SCHIEN",      "SCHIEN",      "SCHEIN",      "SCHEIN",      
                                                                     
   "R)", "SCHIS",       "SCHI�",       "SCHEIS",      "SCHEI�",      
   "R)", "SCHISS",      "SCHISS",      "SCHEIS",      "SCHEI�",      
   "R)", "SCHISS",      "SCHISS",      "SCHEIS",      "SCHEI�",      
   "R)", "SCHISS",      "SCHISS",      "SCHEIS",      "SCHEI�",      
                                                                     
   "Q)", "SCHILT",      "SCHILT",      "SCHELT",      "SCHELT",      
   "Q)", "SCHIL",       "SCHIL",       "SCHELT",      "SCHELT",      
   "R)", "SCHAL",       "SCHAL",       "SCHELT",      "SCHELT",      
   "R)", "SCHOLT",      "SCH�LT",      "SCHELT",      "SCHELT",      
   "Z)", "SCHIL",       "SCHIL",       "SCHELT",      "SCHELT",      
   "R)", "SCHOLT",      "SCHOLT",      "SCHELT",      "SCHELT",      
                                                                     
   "Q)", "SCHER",       "SCHER",       "SCHER",       "SCHER",       
   "R)", "SCHERT",      "SCHERT",      "SCHER",       "SCHER",       
   "R)", "SCHOR",       "SCHOR",       "SCHER",       "SCHER",       
   "R)", "SCHOR",       "SCH�R",       "SCHER",       "SCHER",       
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
   "R)", "SCHOB",       "SCH�B",       "SCHIEB",      "SCHIEB",      
   "R)", "SCHOB",       "SCHOB",       "SCHIEB",      "SCHIEB",      
                                                                     
   "R)", "SCHOS",       "SCHOS",       "SCHIES",      "SCHIE�",      
   "R)", "SCHOSS",      "SCHOSS",      "SCHIES",      "SCHIE�",      
   "R)", "SCHOSS",      "SCH�SS",      "SCHIES",      "SCHIE�",      
   "R)", "SCHOSS",      "SCHOSS",      "SCHIES",      "SCHIE�",      
                                                                     
   "R)", "SCHUND",      "SCHUND",      "SCHIND",      "SCHIND",      
   "R)", "SCHUND",      "SCH�ND",      "SCHIND",      "SCHIND",      
   "R)", "SCHUND",      "SCHUND",      "SCHIND",      "SCHIND",      
                                                                     
   "Q)", "SCHLAF",      "SCHL�F",      "SCHLAF",      "SCHLAF",      
   "Q)", "SCHLAF",      "SCHL�F",      "SCHLAF",      "SCHLAF",      
   "R)", "SCHLIEF",     "SCHLIEF",     "SCHLAF",      "SCHLAF",      
   "R)", "SCHLIEF",     "SCHLIEF",     "SCHLAF",      "SCHLAF",      
                                                                     
   "Q)", "SCHLAG",      "SCHL�G",      "SCHLAG",      "SCHLAG",      
   "Q)", "SCHLAG",      "SCHL�G",      "SCHLAG",      "SCHLAG",      
   "R)", "SCHLUG",      "SCHLUG",      "SCHLAG",      "SCHLAG",      
   "R)", "SCHLUG",      "SCHL�G",      "SCHLAG",      "SCHLAG",      
                                                                     
   "R)", "SCHLICH",     "SCHLICH",     "SCHLEICH",    "SCHLEICH",    
   "R)", "SCHLICH",     "SCHLICH",     "SCHLEICH",    "SCHLEICH",    
   "R)", "SCHLICH",     "SCHLICH",     "SCHLEICH",    "SCHLEICH",    
                                                                     
   "R)", "SCHLIFF",     "SCHLIFF",     "SCHLEIF",     "SCHLEIF",     
   "R)", "SCHLIFF",     "SCHLIFF",     "SCHLEIF",     "SCHLEIF",     
   "R)", "SCHLIFF",     "SCHLIFF",     "SCHLEIF",     "SCHLEIF",     
                                                                     
   "R)", "SCHLEIST",    "SCHLEI�T",    "SCHLEIS",     "SCHLEI�",     
   "R)", "SCHLIS",      "SCHLIS",      "SCHLEIS",     "SCHLEI�",     
   "R)", "SCHLISS",     "SCHLISS",     "SCHLEIS",     "SCHLEI�",     
   "R)", "SCHLISS",     "SCHLISS",     "SCHLEIS",     "SCHLEI�",     
   "R)", "SCHLEIST",    "SCHLEI�T",    "SCHLEIS",     "SCHLEI�",     
   "R)", "SCHLISS",     "SCHLISS",     "SCHLEIS",     "SCHLEI�",     
                                                                     
   "R)", "SCHLOS",      "SCHLOS",      "SCHLIES",     "SCHLIE�",     
   "R)", "SCHLOSS",     "SCHLOSS",     "SCHLIES",     "SCHLIE�",     
   "R)", "SCHLOSS",     "SCHL�SS",     "SCHLIES",     "SCHLIE�",     
   "R)", "SCHLOSS",     "SCHLOSS",     "SCHLIES",     "SCHLIE�",     
                                                                     
   "R)", "SCHLANG",     "SCHLANG",     "SCHLING",     "SCHLING",     
   "R)", "SCHLANG",     "SCHL�NG",     "SCHLING",     "SCHLING",     
   "R)", "SCHLUNG",     "SCHLUNG",     "SCHLING",     "SCHLING",     
                                                                     
   "R)", "SCHMIS",      "SCHMIS",      "SCHMEIS",     "SCHMEI�",     
   "R)", "SCHMISS",     "SCHMISS",     "SCHMEIS",     "SCHMEI�",     
   "R)", "SCHMISS",     "SCHMISS",     "SCHMEIS",     "SCHMEI�",     
                                                                     
   "Q)", "SCHMELZ",     "SCHMELZ",     "SCHMELZ",     "SCHMELZ",     
   "Q)", "SCHMILZ",     "SCHMILZ",     "SCHMELZ",     "SCHMELZ",     
   "Q)", "SCHMILZ",     "SCHMILZ",     "SCHMELZ",     "SCHMELZ",     
   "R)", "SCHMOLZ",     "SCHMOLZ",     "SCHMELZ",     "SCHMELZ",     
   "R)", "SCHMOLZ",     "SCHM�LZ",     "SCHMELZ",     "SCHMELZ",     
   "Z)", "SCHMILZ",     "SCHMILZ",     "SCHMELZ",     "SCHMELZ",     
   "R)", "SCHMOLZ",     "SCHMOLZ",     "SCHMELZ",     "SCHMELZ",     
                                                                     
   "Q)", "SCHMELZ",     "SCHMELZ",     "SCHMELZ",     "SCHMELZ",     
   "Q)", "SCHMILZ",     "SCHMILZ",     "SCHMELZ",     "SCHMELZ",     
   "Q)", "SCHMILZ",     "SCHMILZ",     "SCHMELZ",     "SCHMELZ",     
   "R)", "SCHMOLZ",     "SCHMOLZ",     "SCHMELZ",     "SCHMELZ",     
   "R)", "SCHMELZT",    "SCHMELZT",    "SCHMELZ",     "SCHMELZ",     
   "R)", "SCHMOLZ",     "SCHM�LZ",     "SCHMELZ",     "SCHMELZ",     
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
   "R)", "SCHRAK",      "SCHR�K",      "SCHRECK",     "SCHRECK",     
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
   "R)", "SCHWOLL",     "SCHW�LL",     "SCHWELL",     "SCHWELL",     
   "R)", "SCHWELLT",    "SCHWELLT",    "SCHWELL",     "SCHWELL",     
   "R)", "SCHWEL",      "SCHWEL",      "SCHWELL",     "SCHWELL",     
   "Z)", "SCHWILL",     "SCHWILL",     "SCHWELL",     "SCHWELL",     
   "R)", "SCHWOLL",     "SCHWOLL",     "SCHWELL",     "SCHWELL",     
                                                                     
   "R)", "SCHWAMM",     "SCHWAMM",     "SCHWIMM",     "SCHWIMM",     
   "R)", "SCHWOMM",     "SCHW�MM",     "SCHWIMM",     "SCHWIMM",     
   "R)", "SCHWAMM",     "SCHW�MM",     "SCHWIMM",     "SCHWIMM",     
   "R)", "SCHWOMM",     "SCHWOMM",     "SCHWIMM",     "SCHWIMM",     
                                                                     
   "R)", "SCHWAND",     "SCHWAND",     "SCHWIND",     "SCHWIND",     
   "R)", "SCHWAND",     "SCHW�ND",     "SCHWIND",     "SCHWIND",     
   "R)", "SCHWUND",     "SCHWUND",     "SCHWIND",     "SCHWIND",     
                                                                     
   "R)", "SCHWANG",     "SCHWANG",     "SCHWING",     "SCHWING",     
   "R)", "SCHWANG",     "SCHW�NG",     "SCHWING",     "SCHWING",     
   "R)", "SCHWUNG",     "SCHWUNG",     "SCHWING",     "SCHWING",     
                                                                     
   "R)", "SCHWOR",      "SCHWOR",      "SCHWOR",      "SCHW�R",      
   "R)", "SCHWUR",      "SCHWUR",      "SCHWOR",      "SCHW�R",      
   "R)", "SCHWUR",      "SCHW�R",      "SCHWOR",      "SCHW�R",      
   "R)", "SCHWOR",      "SCHWOR",      "SCHWOR",      "SCHW�R",      
                                                                     
   "Q)", "SIEH",        "SIEH",        "SEH",         "SEH",         
   "Q)", "SIEH",        "SIEH",        "SEH",         "SEH",         
   "R)", "SAH",         "SAH",         "SEH",         "SEH",         
   "R)", "SAH",         "S�H",         "SEH",         "SEH",         
   "Z)", "SIEH",        "SIEH",        "SEH",         "SEH",         
                                                                     
   "Q)", "BIN",         "BIN",         "SEIN",        "SEIN",        
   "Q)", ".BI",         ".BI",         "SEIN",        "SEIN",        
   "Q)", ".I",          ".I",          "SEIN",        "SEIN",        
   "Q)", "SIND",        "SIND",        "SEIN",        "SEIN",        
   "Q)", "SEID",        "SEID",        "SEIN",        "SEIN",        
   "Q)", "SIND",        "SIND",        "SEIN",        "SEIN",        
   "R)", "WAR",         "WAR",         "SEIN",        "SEIN",        
   "R)", "WAR",         "WAR",         "SEIN",        "SEIN",        
   "R)", "WAR",         "W�R",         "SEIN",        "SEIN",        
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
   "R)", "SOTT",        "S�TT",        "SIED",        "SIED",        
   "R)", "SOTT",        "SOTT",        "SIED",        "SIED",        
                                                                     
   "R)", "SANG",        "SANG",        "SING",        "SING",        
   "R)", "SANG",        "S�NG",        "SING",        "SING",        
   "R)", "SUNG",        "SUNG",        "SING",        "SING",        
                                                                     
   "R)", "SANK",        "SANK",        "SINK",        "SINK",        
   "R)", "SANK",        "S�NK",        "SINK",        "SINK",        
   "R)", "SUNK",        "SUNK",        "SINK",        "SINK",        
                                                                     
   "R)", "SANN",        "SANN",        "SINN",        "SINN",        
   "R)", "SANN",        "S�NN",        "SINN",        "SINN",        
   "R)", "SONN",        "S�NN",        "SINN",        "SINN",        
   "R)", "SONN",        "SONN",        "SINN",        "SINN",        
                                                                     
   "R)", "SAS",         "SA�",         "SITZ",        "SITZ",        
   "R)", "SAS",         "S��",         "SITZ",        "SITZ",        
   "R)", "SESS",        "SESS",        "SITZ",        "SITZ",        
                                                                     
   "R)", "SOLLT",       "SOLLT",       "SOLL",        "SOLL",        
   "R)", "SOLLT",       "SOLLT",       "SOLL",        "SOLL",        
                                                                     
   "R)", "SPALTET",     "SPALTET",     "SPALT",       "SPALT",       
   "R)", "SPALTET",     "SPALTET",     "SPALT",       "SPALT",       
                                                                     
   "R)", "SPI",         "SPI",         "SPEI",        "SPEI",        
   "R)", "SPIE",        "SPIE",        "SPEI",        "SPEI",        
   "R)", "SPIE",        "SPIE",        "SPEI",        "SPEI",        
                                                                     
   "R)", "SPANN",       "SPANN",       "SPINN",       "SPINN",       
   "R)", "SPONN",       "SP�NN",       "SPINN",       "SPINN",       
   "R)", "SPANN",       "SP�NN",       "SPINN",       "SPINN",       
   "R)", "SPONN",       "SPONN",       "SPINN",       "SPINN",       
                                                                     
   "Q)", "SPRICH",      "SPRICH",      "SPRECH",      "SPRECH",      
   "Q)", "SPRICH",      "SPRICH",      "SPRECH",      "SPRECH",      
   "R)", "SPRACH",      "SPRACH",      "SPRECH",      "SPRECH",      
   "R)", "SPRACH",      "SPR�CH",      "SPRECH",      "SPRECH",      
   "Z)", "SPRICH",      "SPRICH",      "SPRECH",      "SPRECH",      
   "R)", "SPROCH",      "SPROCH",      "SPRECH",      "SPRECH",      
                                                                     
   "R)", "SPROS",       "SPROS",       "SPRIES",      "SPRIE�",      
   "R)", "SPROSS",      "SPROSS",      "SPRIES",      "SPRIE�",      
   "R)", "SPROSS",      "SPR�SS",      "SPRIES",      "SPRIE�",      
   "R)", "SPROSS",      "SPROSS",      "SPRIES",      "SPRIE�",      
                                                                     
   "R)", "SPRANG",      "SPRANG",      "SPRING",      "SPRING",      
   "R)", "SPRANG",      "SPR�NG",      "SPRING",      "SPRING",      
   "R)", "SPRUNG",      "SPRUNG",      "SPRING",      "SPRING",      
                                                                     
   "Q)", "STICH",       "STICH",       "STECH",       "STECH",       
   "Q)", "STICH",       "STICH",       "STECH",       "STECH",       
   "R)", "STACH",       "STACH",       "STECH",       "STECH",       
   "R)", "STACH",       "ST�CH",       "STECH",       "STECH",       
   "Z)", "STICH",       "STICH",       "STECH",       "STECH",       
   "R)", "STOCH",       "STOCH",       "STECH",       "STECH",       
                                                                     
   "R)", "STAK",        "STAK",        "STECK",       "STECK",       
   "R)", "STAK",        "ST�K",        "STECK",       "STECK",       
                                                                     
   "R)", "STAND",       "STAND",       "STEH",        "STEH",        
   "R)", "STAND",       "ST�ND",       "STEH",        "STEH",        
   "R)", "STUND",       "ST�ND",       "STEH",        "STEH",        
   "R)", "STAND",       "STAND",       "STEH",        "STEH",        
                                                                     
   "Q)", "STIEHL",      "STIEHL",      "STEHL",       "STEHL",       
   "Q)", "STIEHL",      "STIEHL",      "STEHL",       "STEHL",       
   "R)", "STAHL",       "STAHL",       "STEHL",       "STEHL",       
   "R)", "STOHL",       "ST�HL",       "STEHL",       "STEHL",       
   "R)", "STAHL",       "ST�HL",       "STEHL",       "STEHL",       
   "Z)", "STIEHL",      "STIEHL",      "STEHL",       "STEHL",       
   "R)", "STOHL",       "STOHL",       "STEHL",       "STEHL",       
                                                                     
   "R)", "STIEG",       "STIEG",       "STEIG",       "STEIG",       
   "R)", "STIEG",       "STIEG",       "STEIG",       "STEIG",       
   "R)", "STIEG",       "STIEG",       "STEIG",       "STEIG",       
                                                                     
   "Q)", "STIRB",       "STIRB",       "STERB",       "STERB",       
   "Q)", "STIRB",       "STIRB",       "STERB",       "STERB",       
   "R)", "STARB",       "STARB",       "STERB",       "STERB",       
   "R)", "STURB",       "ST�RB",       "STERB",       "STERB",       
   "Z)", "STIRB",       "STIRB",       "STERB",       "STERB",       
   "R)", "STORB",       "STORB",       "STERB",       "STERB",       
                                                                     
   "R)", "STOB",        "STOB",        "STIEB",       "STIEB",       
   "R)", "STIEBT",      "STIEBT",      "STIEB",       "STIEB",       
   "R)", "STOB",        "ST�B",        "STIEB",       "STIEB",       
   "R)", "STIEBT",      "STIEBT",      "STIEB",       "STIEB",       
   "R)", "STOB",        "STOB",        "STIEB",       "STIEB",       
                                                                     
   "R)", "STANK",       "STANK",       "STINK",       "STINK",       
   "R)", "STANK",       "ST�NK",       "STINK",       "STINK",       
   "R)", "STUNK",       "STUNK",       "STINK",       "STINK",       
                                                                     
   "Q)", "STOS",        "ST��",        "STOS",        "STO�",        
   "Q)", "STOS",        "ST��",        "STOS",        "STO�",        
   "R)", "STIES",       "STIE�",       "STOS",        "STO�",        
   "R)", "STIES",       "STIE�",       "STOS",        "STO�",        
                                                                     
   "R)", "STRICH",      "STRICH",      "STREICH",     "STREICH",     
   "R)", "STRICH",      "STRICH",      "STREICH",     "STREICH",     
   "R)", "STRICH",      "STRICH",      "STREICH",     "STREICH",     
                                                                     
   "R)", "STRIT",       "STRIT",       "STREIT",      "STREIT",      
   "R)", "STRITT",      "STRITT",      "STREIT",      "STREIT",      
   "R)", "STRITT",      "STRITT",      "STREIT",      "STREIT",      
                                                                     
   "Q)", "TRAG",        "TR�G",        "TRAG",        "TRAG",        
   "Q)", "TRAG",        "TR�G",        "TRAG",        "TRAG",        
   "R)", "TRUG",        "TRUG",        "TRAG",        "TRAG",        
   "R)", "TRUG",        "TR�G",        "TRAG",        "TRAG",        
                                                                     
   "Q)", "TRIFF",       "TRIFF",       "TREFF",       "TREFF",       
   "Q)", "TRIFF",       "TRIFF",       "TREFF",       "TREFF",       
   "R)", "TRAF",        "TRAF",        "TREFF",       "TREFF",       
   "R)", "TRAF",        "TR�F",        "TREFF",       "TREFF",       
   "Z)", "TRIFF",       "TRIFF",       "TREFF",       "TREFF",       
   "R)", "TROFF",       "TROFF",       "TREFF",       "TREFF",       
                                                                     
   "R)", "TRIEB",       "TRIEB",       "TREIB",       "TREIB",       
   "R)", "TRIEB",       "TRIEB",       "TREIB",       "TREIB",       
   "R)", "TRIEB",       "TRIEB",       "TREIB",       "TREIB",       
                                                                     
   "Q)", "TRITT",       "TRITT",       "TRET",        "TRET",        
   "Q)", "TRIT",        "TRIT",        "TRET",        "TRET",        
   "R)", "TRA",         "TRA",         "TRET",        "TRET",        
   "R)", "TRAT",        "TR�T",        "TRET",        "TRET",        
   "Z)", "TRIT",        "TRIT",        "TRET",        "TRET",        
                                                                     
   "R)", "TROFF",       "TROFF",       "TRIEF",       "TRIEF",       
   "R)", "TRIEFT",      "TRIEFT",      "TRIEF",       "TRIEF",       
   "R)", "TROFF",       "TR�FF",       "TRIEF",       "TRIEF",       
   "R)", "TRIEFT",      "TRIEFT",      "TRIEF",       "TRIEF",       
   "R)", "TROFF",       "TROFF",       "TRIEF",       "TRIEF",       
                                                                     
   "R)", "TRANK",       "TRANK",       "TRINK",       "TRINK",       
   "R)", "TRANK",       "TR�NK",       "TRINK",       "TRINK",       
   "R)", "TRUNK",       "TRUNK",       "TRINK",       "TRINK",       
                                                                     
   "R)", "TROG",        "TROG",        "TRUG",        "TR�G",        
   "R)", "TROG",        "TR�G",        "TRUG",        "TR�G",        
   "R)", "TROG",        "TROG",        "TRUG",        "TR�G",        
                                                                     
   "Q)", ".TU",         ".TU",         "TUN",         "TUN",         
   "Q)", ".TU",         ".TU",         "TUN",         "TUN",         
   "Q)", ".TU",         ".TU",         "TUN",         "TUN",         
   "R)", ".TA",         ".TA",         "TUN",         "TUN",         
   "R)", "TAT",         "T�T",         "TUN",         "TUN",         
   "Z)", ".TU",         ".TU",         "TUN",         "TUN",         
   "R)", "TAN",         "TAN",         "TUN",         "TUN",         
                                                                     
   "Q)", "VERDIRB",     "VERDIRB",     "VERDERB",     "VERDERB",     
   "Q)", "VERDIRB",     "VERDIRB",     "VERDERB",     "VERDERB",     
   "R)", "VERDARB",     "VERDARB",     "VERDERB",     "VERDERB",     
   "R)", "VERDURB",     "VERD�RB",     "VERDERB",     "VERDERB",     
   "Z)", "VERDIRB",     "VERDIRB",     "VERDERB",     "VERDERB",     
   "R)", "VERDORB",     "VERDORB",     "VERDERB",     "VERDERB",     
                                                                     
   "R)", "VERDROS",     "VERDROS",     "VERDRIES",    "VERDRIE�",    
   "R)", "VERDROSS",    "VERDROSS",    "VERDRIES",    "VERDRIE�",    
   "R)", "VERDROSS",    "VERDR�SS",    "VERDRIES",    "VERDRIE�",    
   "R)", "VERDROSS",    "VERDROSS",    "VERDRIES",    "VERDRIE�",    
                                                                     
   "Q)", "VERGIS",      "VERGIS",      "VERGESS",     "VERGESS",     
   "Q)", "VERGISS",     "VERGISS",     "VERGESS",     "VERGESS",     
   "Q)", "VERGIS",      "VERGIS",      "VERGESS",     "VERGESS",     
   "R)", "VERGAS",      "VERGA�",      "VERGESS",     "VERGESS",     
   "R)", "VERGAS",      "VERG��",      "VERGESS",     "VERGESS",     
   "Z)", "VERGIS",      "VERGIS",      "VERGESS",     "VERGESS",     
                                                                     
   "R)", "VERLOR",      "VERLOR",      "VERLIER",     "VERLIER",     
   "R)", "VERLOR",      "VERL�R",      "VERLIER",     "VERLIER",     
   "R)", "VERLOR",      "VERLOR",      "VERLIER",     "VERLIER",     
                                                                     
   "R)", "VERZIEH",     "VERZIEH",     "VERZEIH",     "VERZEIH",     
   "R)", "VERZIEH",     "VERZIEH",     "VERZEIH",     "VERZEIH",     
   "R)", "VERZIEH",     "VERZIEH",     "VERZEIH",     "VERZEIH",     
                                                                     
   "Q)", "WACH",        "W�CH",        "WACHS",       "WACHS",       
   "Q)", "WACH",        "W�CH",        "WACHS",       "WACHS",       
   "R)", "WUCH",        "WUCH",        "WACHS",       "WACHS",       
   "R)", "WUCHS",       "W�CHS",       "WACHS",       "WACHS",       
                                                                     
   "R)", "WOG",         "WOG",         "WAG",         "W�G",         
   "R)", "WAGT",        "W�GT",        "WAG",         "W�G",         
   "R)", "WOG",         "W�G",         "WAG",         "W�G",         
   "R)", "WAGT",        "W�GT",        "WAG",         "W�G",         
   "R)", "WOG",         "WOG",         "WAG",         "W�G",         
                                                                     
   "Q)", "WASCH",       "W�SCH",       "WASCH",       "WASCH",       
   "Q)", "WASCH",       "W�SCH",       "WASCH",       "WASCH",       
   "R)", "WUSCH",       "WUSCH",       "WASCH",       "WASCH",       
   "R)", "WUSCH",       "W�SCH",       "WASCH",       "WASCH",       
                                                                     
   "R)", "WEBT",        "WEBT",        "WEB",         "WEB",         
   "R)", "WOB",         "WOB",         "WEB",         "WEB",         
   "R)", "WOB",         "WOB",         "WEB",         "WEB",         
   "R)", "WEBT",        "WEBT",        "WEB",         "WEB",         
   "R)", "WOB",         "W�B",         "WEB",         "WEB",         
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
   "R)", "WURB",        "W�RB",        "WERB",        "WERB",        
   "Z)", "WIRB",        "WIRB",        "WERB",        "WERB",        
   "R)", "WORB",        "WORB",        "WERB",        "WERB",        
                                                                     
   "Q)", "WIR",         "WIR",         "WERD",        "WERD",        
   "Q)", "WIRD",        "WIRD",        "WERD",        "WERD",        
   "R)", "WURD",        "WURD",        "WERD",        "WERD",        
   "R)", "WARD",        "WARD",        "WERD",        "WERD",        
   "R)", "WURD",        "W�RD",        "WERD",        "WERD",        
   "R)", "WORD",        "WORD",        "WERD",        "WERD",        
   "R)", "WORD",        "WORD",        "WERD",        "WERD",        
                                                                     
   "Q)", "WIRF",        "WIRF",        "WERF",        "WERF",        
   "Q)", "WIRF",        "WIRF",        "WERF",        "WERF",        
   "R)", "WARF",        "WARF",        "WERF",        "WERF",        
   "R)", "WURF",        "W�RF",        "WERF",        "WERF",        
   "Z)", "WIRF",        "WIRF",        "WERF",        "WERF",        
   "R)", "WORF",        "WORF",        "WERF",        "WERF",        
                                                                     
   "R)", "WOG",         "WOG",         "WIEG",        "WIEG",        
   "R)", "WOG",         "W�G",         "WIEG",        "WIEG",        
   "R)", "WOG",         "WOG",         "WIEG",        "WIEG",        
                                                                     
   "R)", "WAND",        "WAND",        "WIND",        "WIND",        
   "R)", "WAND",        "W�ND",        "WIND",        "WIND",        
   "R)", "WUND",        "WUND",        "WIND",        "WIND",        
                                                                     
   "Q)", "WEIS",        "WEI�",        "WISS",        "WISS",        
   "Q)", "WIS",         "WIS",         "WISS",        "WISS",        
   "R)", "WUST",        "WU�T",        "WISS",        "WISS",        
   "R)", "WUST",        "W��T",        "WISS",        "WISS",        
   "R)", "WUS",         "WUS",         "WISS",        "WISS",        
                                                                     
   "Q)", "WILL",        "WILL",        "WOLL",        "WOLL",        
   "R)", "WOLLT",       "WOLLT",       "WOLL",        "WOLL",        
   "R)", "WOLLT",       "WOLLT",       "WOLL",        "WOLL",        
                                                                     
   "R)", "WRANG",       "WRANG",       "WRING",       "WRING",       
   "R)", "WRANG",       "WR�NG",       "WRING",       "WRING",       
   "R)", "WRUNG",       "WRUNG",       "WRING",       "WRING",       

#if FALSE // ziehen                                                                     
   "R)", "ZIEH",        "ZIEH",        "ZEIH",        "ZEIH",        
   "R)", "ZEIHT",       "ZEIHT",       "ZEIH",        "ZEIH",        
   "R)", "ZIEH",        "ZIEH",        "ZEIH",        "ZEIH",        
   "R)", "ZIEH",        "ZIEH",        "ZEIH",        "ZEIH",        
#endif
                                                                     
   "R)", "ZOG",         "ZOG",         "ZIEH",        "ZIEH",        
   "R)", "ZOG",         "Z�G",         "ZIEH",        "ZIEH",        
   "R)", "ZOG",         "ZOG",         "ZIEH",        "ZIEH",        
                                                                     
   "R)", "ZWANG",       "ZWANG",       "ZWING",       "ZWING",       
   "R)", "ZWANG",       "ZW�NG",       "ZWING",       "ZWING",       
   "R)", "ZWUNG",       "ZWUNG",       "ZWING",       "ZWING",       
                                                                     
   NULL, NULL,          NULL,          NULL,          NULL          
};

