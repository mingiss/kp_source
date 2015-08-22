// ==================================================
// xmlis.h
// XML file index splitter/inverter definitions, textual mode
// XmlIs_IndexRecord - help class for Mcmr2xm_tag::TransferField()


#ifndef xmlis_included
#define xmlis_included


// --------------------------------------------------
#define MC_LeftBracket     ('[')
#define MC_RightBracket    (']')
#define MC_InvertDelimiter (',')
#define MC_CombDelimiter   ('/')
#define MC_LeftParenthese  ('(')
#define MC_RightParenthese (')')
#define MC_IndEntrDelimiter (';')

#define TV_MC_MAX_COMBINED 3

#define TV_X_MAX_ABBR_LENGTH 10

// --------------------------------------------------
class XmlIs_IndexRecord
{
   XmlO1 *lpXmlFilObj;
   int /* XL_Indexes */ uiIxFIdx;
   long lMainKeyVal;
   int m_iMinEntryLength;

   KpChar uiLastChar;
   int iParLev;
   bool m_bAfterApost; // skip text after apostrophe to the word end

   int iValIdx;
   KpChar auiValue[TV_XL_MAX_IX_LEN+1];

   bool bTestInverted;
   bool bTestCombinedLeft;
   bool bTestCombinedRight;
   bool m_bProcessSubkeys;   // switches off all subkey processing if False

   unsigned char m_ucIxLang;              // negali buti paimamas is caTgLangs[cur_tag-iFirstDictTag]
                                          //    ar caIxLangs[uiIxFIdx], nes pilno teksto
                                          //    indexas gali buti ivairiu kalbu

// EC_Types m_iEcTyp;                     // pakeistas iaIxEncodings[uiIxFIdx]

   HRESULT CutEndings(void);              // cut endings of index words

   HRESULT PutValueSingle(int iIxFileIdx, int iLanguage);
   HRESULT PutValue(void);                // put collected index buffer to index file

   HRESULT PutSpace(void);
   HRESULT PutEol(void);

// Combined ('/') entries processing
   HRESULT PutDelLeftComb(int iCutPos, bool bPutDelim);
                                          // Sends to child object index entry text
                                          //    without one word left from iCutPos
   HRESULT PutDelRightComb(int iCutPos, bool bPutDelim);
                                          // Sends to child object index entry text
                                          //    without one word right from iCutPos
                                          // bPutDelim - if set, "/" wil be left in
                                          //    output entry for further elimination
                                          //    of words

   HRESULT PutOptional(int iCutPos, bool bPutWith);
                                          // puts to child objects: 1. whole text
                                          //    without limiting parentheses;  2. entry
                                          //    without text between parantheses.
                                          // iCutPos must point to opening parenthese
                                          // bPutWith - if set, text between parentheses
                                          //    will be output to index file

   HRESULT PutDiffValParetheses(int iCutPos);
                                          // Puts text in parentheses as different index
                                          //    entry; enclosed text must be on the end
                                          //    of the source text string

   HRESULT PutDiffVal(int iCutPos);       // Splits different index entries

   HRESULT PutSwapped(int iCutPos);       // Puts personal name and inverted name

public:

   XmlIs_IndexRecord
   (
      XmlO1 *lpXmlFileOb,
      const int /* XL_Indexes */ uiIxFileIdx,
      const long lMainKeyValue,
      bool bTstInverted,
      bool bTstCombinedLeft,
      bool bTstCombinedRight,
      bool bProcessSubkeys,
      unsigned char ucLanguage,       // language identifier for endings skipper: TV_XE_LIT, TV_XE_ENG, TV_XE_RUS, TV_XE_GER etc.
//    EC_Types iEcType,
      int iMinEntryLength
   );

   ~XmlIs_IndexRecord();

   HRESULT PutChar(KpChar uiChOut); // put character to index buffer

   HRESULT GetParLev(int *piParLev);

   HRESULT CompleteIndexRecord(bool bWholeRecord); // bWholeRecord - for output of '#' at the end of the initial index entry
};


// ar raðant á indeksus numetinëti galûnes po apostrofo
// turi bûti apibrëþtas lokaliam aplikacijos (stiliaus) faile 
extern bool bCutEndingsAfterApostrophe; 
 

// abbreviations to expand
extern const KpChar lpszaAbbrExp_l[][2][TV_X_MAX_ABBR_LENGTH];
extern const KpChar lpszaAbbrExp_e[][2][TV_X_MAX_ABBR_LENGTH];
extern const KpChar lpszaAbbrExp_v[][2][TV_X_MAX_ABBR_LENGTH]; // former lpszaAbbrExp_g
extern const KpChar lpszaAbbrExp_f[][2][TV_X_MAX_ABBR_LENGTH];
extern const KpChar lpszaAbbrExp_r[][2][TV_X_MAX_ABBR_LENGTH];

// conjunctors to delete
extern const unsigned char *lpszaCjt_l[]; // former lpszaAbbrev_l
extern const unsigned char *lpszaCjt_e[]; // former lpszaAbbrev_e
extern const unsigned char *lpszaCjt_v[]; // former lpszaAbbrev_g, lpszaCjt_g
extern const unsigned char *lpszaCjt_f[]; // former lpszaAbbrev_f
extern const unsigned char *lpszaCjt_r[]; // former lpszaAbbrev_r


extern HRESULT ExpandAbbr
(
   KpChar *auiDest,
   const KpChar *auiSrc,
   int *iValIdx,
   int iStrBuifSize,
   unsigned char ucLang
);    // expands abbreviations in index entry / search string
      // text must be in uppercase KpChar coding
      // returns processed string in auiDest, new length - in iValIdx
      // iStrBuifSize - max length of auiDest

extern HRESULT DelComments(KpChar *auiValBuf, int *iValIdx);
      // deletes comments [...] from index entry / search string

extern HRESULT DelCjts(unsigned char *lpszDest, const unsigned char *lpszSrc, unsigned char ucLanguage, EC_Types iEcType);
                                          // delete conjunctions, former DelAbbr
                                          // allocated size of lpszDest must be not less than length of lpszSrc
extern HRESULT CutEndingsApost(KpChar *iaBuffer); // Steve'o --> Steve
extern HRESULT CutEndingsSmall(KpChar *iaBuffer); // STEVEo --> STEVE

extern HRESULT KpCharToIndexEntry // former Chars16ToIndexEntry()
(
   unsigned char *lpszStrBuf,
   const KpChar *auiValue,
   int iValLen,
   int iStrBufSize,
   unsigned char ucLang,
   EC_Types iEcType
);   // converts Char16 string to XML index entry / search string without spec chars and endings,
     // expands abbreviations

// converts index entry heading text to string for comparing
// removes '*' and '#' at the end of index entry, removes spaces, dots and dashes inside
// lpszStrBuf ir lpszIndexEntry gali sutapti
extern HRESULT IndexEntryToCompareStr(unsigned char *lpszStrBuf, const unsigned char *lpszIndexEntry, bool bClearDoubleEntriesChr, bool bClearExactEntryChr, EC_Types iEncoding);
   // bClearDoubleEntriesChr == True - isvalo '*' gale
   // bClearExactEntryChr == True - isvalo '#' gale
extern HRESULT KpIndexEntryToCompareKpStr(KpChar *iazStrBuf, const KpChar *iazIndexEntry, bool bClearDoubleEntriesChr, bool bClearExactEntryChr);

#endif
