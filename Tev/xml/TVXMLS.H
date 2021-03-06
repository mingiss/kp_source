// ==================================================
// tvxmls.h
// XML sort and search definitions


#ifndef tvxmls_included
#define tvxmls_included


#define EXACT_ENTRY_CHR C_Numb   // '#' - exact search entries terminator
                                 // kad nesuveiktu galuniu numetiklis
#define WORD_START_CHR C_Point   // '.' - full word entries in endings skipping table

#define DOUBLE_ENTRIES_KPCHAR       C_Bpoint // bullet - full word entries in endings skipping table // former DOUBLE_ENTRIES_CHR16
#define DOUBLE_ENTRIES_CHR          C_Ast    // '*' - homonimu ir kt. galo pazymejimui, vietoj C_Bpoint
#define DOUBLE_ENTRIES_LZDSH_KPCHAR C_NBSP   // dvigub� antra��i� simbolis LZDSH listuose - kad nesimatyt�
#define DOUBLE_ENTRIES_LZDSH_CHR    0xA0     // C_NBSP lenteleje 71 // former DOUBLE_ENTRIES_LZDSH

#define TECH_DELIM_KPCHAR     C_hyph   // atskyr�jas HistList'e �odyno pavadinimui prie kiekvieno �ra�o // former LZDSH_TECH_DELIM
#define TECH_DELIM_CHR        0xAD     // TECH_DELIM_KPCHAR (C_hyph) 71-oje ir 73-je lentel�se 
#define TECH_DELIM_STR        ("\xAD") // eilut� i� TECH_DELIM_CHR // former LZDSH_TECH_DELIM_STR 


// =================================================== free fields and functions
// --------------------------------------------------
extern unsigned char *plpszaEndSkipTableLit[];  // lithuanian endings skipping table
                                                //  pairs of substitution pointers
                                                //    must be searched from end to
                                                //    beginning, because longer
                                                //    endings are entered further.
                                                // Table end - two NULL pointers

// --------------------------------------------------
extern HRESULT TvXmlSortTextIndexes(const unsigned char *lpszFname);
                                          // sorts text index files
            
extern int *TvCleanIxSpchI(int *iazStr);
            
#endif
