// ==================================================
// tvxmlrm.h
// McMillan dictionary RTF to XML converter
// XML file references creator


#ifndef tvxmlrm_included
#define tvxmlrm_included


// --------------------------------------------------
#define TV_XR_REF_THRESHOLD 3
#define TV_XR_UNGET_WDT 10

#define MCM_COMMENT_START ('[')
#define MCM_COMMENT_END (']')


// --------------------------------------------------
class TvXmlR_DataRecord_tag
{
   XmlO1 *lpOutFilObj;
   KpChar aiRefBuf[TV_XL_MAX_IX_LEN+1];     // buffer for reference text
   int iRefBufIdx;
   KpChar auiLWordBuf[TV_XL_MAX_IX_LEN+1];   // buffer for last word, not
   int iLWordBufIdx;                               //    belonging to reference
   int m_iLastWordLength; // character count of last word in aiRefBuf[]

   unsigned char ucaUnGetBuf[TV_XR_UNGET_WDT];     // buffer for saving extra chars
   int iUnGetCnt;                                  //    at the bottom of the reference

   bool bTextToBuffer;
                  // set, when chars must be sent to buffer
                  // reset, when directly to output file (waiting for start of
                  //    word)

   bool bInsideComent; // set when inside of '[' and ']' (XC_TechNote, XC_TechNote_e)

   bool bCollectReference;
                  // flag of reference processing

   HRESULT SeparateLastWord(bool bWrdFlg);
                  // separate last word from reference buffer
                  //    to last word buffer.
                  // bWrdFlg - detach whole word or only
                  //    trailing spaces

   HRESULT FlushLastWord(void);
                  // put last word to file

   HRESULT TestFreeParentheses();
                  // skips parentheses before output of reference in auiRefBuf[]
   HRESULT UnGetLastBufChar();
                  // ungets last character and preceeding spaces of auiRefBuf[]
                  // used in TestFreeParentheses()
   HRESULT PutFirstBufChar(void);
                  // outputs first character and trailing spaces of auiRefBuf[]
                  // used in TestFreeParentheses()
   HRESULT UnGetChar(unsigned char ucChar);
                  // saves character to ucaUnGetBuf[] for further output

public:

   TvXmlR_DataRecord_tag(XmlO1 *lpOutFileOb, bool bRefFlg);
                  // bRefFlg - reference processing flag
   ~TvXmlR_DataRecord_tag(void);

   HRESULT PutChar
   (
      KpChar iOutch,
      XmlTagPars *pTagPars,
      int iFileIndex
   );             // Put character to output file
                  //    pTagPars - parameters for XML tags.
                  //    Uses fFiles[iFileIndex]

   HRESULT PutCharProc(KpChar uiChOut, bool bProcRef, /* const */ XmlTagPars *pTagPars);
                  // put character to buffer
                  // bProcRef - process references flag

   HRESULT FlushRefVal();
                  // put reference tag to file

   HRESULT GetCurTag(/* enum XmlDictChars */ KpChar *piCurTag);
};


// --------------------------------------------------
extern unsigned char lpszTvRefSpaces[];      // word delimiters
extern unsigned char lpszTvXmlNoSpcChars[];  // characters, not needed spaces around
extern unsigned char lpszTvRefCtrls[];       // spec characters, belonging to referencies,
                                             //    except parentheses
extern unsigned char lpszTvRefCtrlsAndPar[]; // allready not applicable, == lpszTvRefCtrls
extern unsigned char lpszTvRefDelims[];      // reference delimiters

extern KpChar iazTvCommentDelims[];             // comment delimiters

#endif
