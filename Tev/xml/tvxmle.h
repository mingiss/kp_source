// ==============================================
// tvxmle.h
// endings and suffixes skipper for searching in flex. languages
// other grammatical things
// definitions

#ifndef tvxmle_included
#define tvxmle_included


// ----------------------------------------------
#define TV_XE_COMP_ENTRY_SIZ 3   // number of pointers in one line of plpszaEndSkipTableCompact_x

#define TV_MAX_FORMS 10          // max. length of third column of plpszaEndSkipTable_l or plpszaEndSkipTableCompact_l

#define TV_XE_CTBL   71          // internal code table of endings skipper

// ----------------------------------------------
extern unsigned char *plpszaToGrForm_l[];
extern unsigned char lpszToMainForm_l[];
extern unsigned char lpszForms_l[];
extern char *plpszaPrefixes_l[];
extern unsigned char *plpszauPrefixes_l[];
extern char *plpszaEndSkipTable_l[];
extern unsigned char *plpszaEndSkipTableCompact_l[];
extern char *plpszaUnRegForms_l[];
extern unsigned char *plpszauUnRegForms_l[];

extern unsigned char *plpszaToGrForm_e[];
extern unsigned char lpszToMainForm_e[];
extern unsigned char lpszForms_e[];
extern char *plpszaPrefixes_e[];
extern unsigned char *plpszauPrefixes_e[];
extern char *plpszaEndSkipTable_e[];
extern unsigned char *plpszaEndSkipTableCompact_e[];
extern char *plpszaUnRegForms_e[];
extern unsigned char *plpszauUnRegForms_e[];

extern unsigned char *plpszaToGrForm_v[]; // former plpszaToGrForm_g
extern unsigned char lpszToMainForm_v[]; // former lpszToMainForm_g
extern unsigned char lpszForms_v[]; // former lpszForms_g
extern char *plpszaPrefixes_v[]; // former plpszaPrefixes_g
extern unsigned char *plpszauPrefixes_v[]; // former plpszauPrefixes_g
extern char *plpszaEndSkipTable_v[]; // former plpszaEndSkipTable_g
extern unsigned char *plpszaEndSkipTableCompact_v[]; // former plpszaEndSkipTableCompact_g
extern char *plpszaUnRegForms_v[]; // former plpszaUnRegForms_g
extern unsigned char *plpszauUnRegForms_v[]; // former plpszauUnRegForms_g

extern unsigned char *plpszaToGrForm_f[];
extern unsigned char lpszToMainForm_f[];
extern unsigned char lpszForms_f[];
extern char *plpszaPrefixes_f[];
extern unsigned char *plpszauPrefixes_f[];
extern char *plpszaEndSkipTable_f[];
extern unsigned char *plpszaEndSkipTableCompact_f[];
extern char *plpszaUnRegForms_f[];
extern unsigned char *plpszauUnRegForms_f[];

extern unsigned char *plpszaToGrForm_r[];
extern unsigned char lpszToMainForm_r[];
extern unsigned char lpszForms_r[];
extern char *plpszaPrefixes_r[];
extern unsigned char *plpszauPrefixes_r[];
extern char *plpszaEndSkipTable_r[];
extern unsigned char *plpszaEndSkipTableCompact_r[];
extern char *plpszaUnRegForms_r[];
extern unsigned char *plpszauUnRegForms_r[];


// ----------------------------------------------
class TvXmlEsClass // former TvXmlEs_tag
{
   HRESULT lhOpenResult;
   int iEndSkipTableSize_l;
   int iEndSkipTableSize_e;
   int iEndSkipTableSize_v; // former iEndSkipTableSize_g
   int iEndSkipTableSize_f;
   int iEndSkipTableSize_r;

   HRESULT Replace
   (
      unsigned char **plpszTblPtr,
      unsigned char **ppucPntDest,
      unsigned char *lpszDest,
      bool *pbReplaced
   );                               // replace ending *plpszTblPtr with *(plpszTblPtr+1)
                                    // pucPntDest must point to the end of the word
                                    // lpszDest - pointer to the start of the string
                                    //    pointed by pucPntDest
                                    // *pbReplaced is returned as TRUE, if the ending
                                    //    was successfully replaced

   HRESULT IdToMainForm(unsigned char *FormsToChange, unsigned char *FormTable);
                                    // converts gram. forms string to string of
                                    //    corresponding main forms

public:

   TvXmlEsClass(void);

   HRESULT GetOpenResult(void);     // Returns value of OpenResult -
                                    //    object creation error code

   HRESULT CutEndings(unsigned char *lpszDest, const unsigned char *lpszSrc, unsigned char ucLanguage, EC_Types iEcType, bool bProcessIrr);
                                    // cuts endings, depending on language
                                    // must be implemented testing of dest. buffer overflow !!!
                                    // bProcessIrr - process using table of irregular forms
                                    // bProcessIrr==False by generation of the table itself
   HRESULT CutEndingsDelCjts(KpChar *iazDest, KpChar *iazSrc, unsigned char ucLanguage, EC_Types iEcType, bool bDelCjtsFl);
};

extern class TvXmlEsClass TvXmlEs;

extern HRESULT EndCmp
(
   const unsigned char *pucEndPtr,
   const unsigned char *pucLowLomit,
   int iNumOfBytes,
   const unsigned char *lpszTableEntry,
   int *iCmpRes,
   unsigned char ucLanguage,
   EC_Types iEcType
);                               // Compares word ending with endigs table entry
                                 // returns iCmpRes: -1, 0, 1 - like strcmp()
                                 // pucLowLomit - start of word buffer, wich must
                                 //    not be exceeded by stepping down to word start
                                 // iNumOfBytes - how many bytes from the end of
                                 //    the word to compare (-1 - whole ending)

//------------------------------------------------
#define TV_GRAMF_CTBL 71 // char. table of grammatical forms

extern const unsigned char *lpszaGramForms_v[]; // german, former lpszaGramForms_g
extern const unsigned char *lpszaGramForms_l[]; // lithuanian

#endif
