// ==================================================
// kpsort.h
// sort/search capabilities
//

#ifndef kpsort_included
#define kpsort_included


// ================================================== definitions
#define TV_TG_NoKey  (-1)

#define KP_MAX_NUM_OF_WORDS 20

// ================================================== static fields for sorting
extern int iCharWeigths[C_CharSize0];        // sort order definition
                                             // third digit will be ignored for for TvStrCmp()
                                             // use RoundChWgt(iCharWeigths[ii]) for it
#define KpCharWgtElem(chr, dig2, dig3, dig4) (chr * 10000 + dig2 * 1000 + dig3 * 100 + dig4) 
                                             // former ChWgt()
                                             // dig2 - skirtingu abeceles poziuriu diakritiniu raidziu eil. nr. (C, È, S, Ð, etc.) eil. nr.
                                             // dig3 - didziosios raides pozymis
                                             // dig4 (former dig3) - abeceliskai to paties svorio diakritiniu raidziu eil. nr.
#define ToLowWgt(ii)   (ii-ii%1000+ii%100)   // numeta didziosios raides pozymi dig3
#define RoundChWgt(ii) (ii-ii%100)           // numeta diakrito eiles nr dig4

extern int SortMode; // must be defined locally in main application file

// ================================================== keyword search
extern int TvStrStrArr(const unsigned char *lpszTestStr, const unsigned char **plpszStrArr);
                           // tests whether lpszTestStr is equal to one of lpszStrArr
                           //    strings.  End of lpszStrArr array is marked by NULL
                           //    entry.  lpszStrArr array index is returned in
                           //    case of matching, -1 otherwise
                           // Uses GetKwrdIndex()

extern HRESULT GetKwrdIndex
(
int *piIndex,
const unsigned char *lpszKeywrd,
const unsigned char * const *plpszKeytable,
const int iTabSize,
bool bCaseSens,
bool bWholeWords
);                               // Calculates keyword index in keyword table.
                                 //    returns TV_TG_NoKey (-1) if not found and return code KP_E_KWD_NOT_FOUND
                                 // Input:
                                 //    lpszKeywrd;
                                 //    plpszKeytable - array of pointers to all
                                 //       keywords - null terminated strings;
                                 //    if iTabSize <0, then end of keyword table
                                 //       is marked by NULL pointer,
                                 //    if iTabSize >=0, then all iTabSize records
                                 //       will be tested, regardless if they are NULL
                                 //       or not.
                                 //    bCaseSens - case sensitivity flag
                                 //    bWholeWords - search for lpszKeywrd as whole word,
                                 //       otherwise - only starting characters up to checking keyword length
                                 // Output:
                                 //    piIndex

HRESULT GetKwrdIndexSkipSpc
(
   int *piIndex,
   const unsigned char *lpszKeywrd,
   const unsigned char **plpszKeytable,
   const int iTabSize,
   bool bCaseSens,
   bool bWholeWords
);                               // like GetKwrdIndex(); ignores spaces in keywords

HRESULT GetKwrdIntIndex
(
   int *piIndex,
   KpChar *iazKeywrd,
   KpChar **piazKeytable,
   const int iTabSize,
   bool bWholeWords
);                               // GetKwrdIndex() variant for int strings


// ================================================== sort tools

extern HRESULT SortTextFile(const unsigned char *lpszFname, bool bReverse, bool bSkipSpc);
                                          // sorts text file
                                          // bReverse - set for reverse sorting
                                          // bSkipSpc - ignore all spaces by comparing

extern unsigned char *TvKpStrToSort(unsigned char *lpszOutStr, const KpChar *piazInStr, bool bStrictFl); 
// konvertuoja Kpt eilutæ á lovercase lotyniðkø raidþiø eilutæ be tarpø
// è, ð, þ keièia á cz, sz ir zz (failø rikiavimui, pvz., AKLZ)
// if bStrictFl == False - palieka tarpus (keièia á minusus), didþiasias raides ir Y, y 

#endif // #ifndef kpsort_included

