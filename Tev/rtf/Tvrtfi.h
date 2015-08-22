// ==================================================
// tvrtfi.h
// RTF input file definitions


#ifndef tvrtfi_included
#define tvrtfi_included


#define RT_UNGET_BUF_SIZ  (/*RT_CHAR_POS_THRESHOLD*/KP_MSG_LEN + TV_TAG_LEN)

// --------------------------------------------------
class TvRtfI: public TvRtfIO
{
   unsigned char ucUnGetBuf;     // UnGetChar() variables
   bool bUnGetPresent;

   KpChar iaUnGetProcBuf[RT_UNGET_BUF_SIZ];
   int iUnGetProcCnt;            // UnGetCharProc() variables

   unsigned char cFieldChar;     // buffer for RTF Symbol field character
   bool bFieldCharPresent;

   bool m_bShowPict;   

   HRESULT SkipChars(const unsigned char *lpszCharsToSkip);
                                 // Skips chars from input file.
                                 // Input:
                                 //    lpszCharsToSkip - null terminated string
                                 //    with chars to skip.
                                 //    Uses GetChar() and UnGetChar().

   HRESULT SkipCharsProc(const unsigned char *lpszCharsToSkip);
                                 // Skips chars with RTF tag processing.
                                 // Input:
                                 //    lpszCharsToSkip - null terminated string
                                 //    with chars to skip.
                                 //    Uses GetCharProc() and UnGetCharProc().

   HRESULT CharEncode(KpChar *piOutChar, const unsigned char cInChar);
                                 // Converts cInChar to Kpt char *piOutChar,
                                 //    using pFonts[pCurrentField->iFont],

   HRESULT ProcessKeyword
   (
      KpChar *piInChar,
      bool *pbInChFlg,
      RT_FieldTypes *piFieldType,
      int *piCurFont,
      const unsigned char *lpszKeywrd,
      const long lNumVal,
      const unsigned char *lpszTextVal
   );   
                                 // RTF tag processing
                                 // Input:
                                 //    lpszKeywrd, iNumVal, lpszTextVal - keyword
                                 //       values, returned from GetWord(),
                                 // Output:
                                 //    *piFieldType, *piCurFont - current field type
                                 //       and font - may be changed during ProcessKeyword()
                                 //    *pbInChFlg - flag, if new character from input
                                 //        file is available,
                                 //    pcInChar - input char, if available.
                                 // Uses GetKwrdIndex(), CharEncode(), pCurrentField
                                 //    and pFonts

public:

   TvRtfI(const unsigned char *lpszInfname);
                                 // Opens input file
   ~TvRtfI(void);

   HRESULT SetTablePars(long lTableWidth, int iNumOfCols);
   HRESULT GetTablePars(long *plTableWidth, int *piNumOfCols);
                                                // get/set table field parameters

// ---------------------------------------------- low level input
   HRESULT GetChar(unsigned char *pcInchar, bool bCheckFeof);
                                 // Gets current char. from file
                                 // bCheckFeof is used to swith on end of file error
                                 //    output
                                 // Uses lpfRtfFile

   HRESULT UnGetChar(unsigned char cChar);
                                 // Put char. back to input stream for GetChar()

   HRESULT SkipSpaces(void);     // Skips spaces and tabs (not ends of lines)
                                 //    Uses GetChar() and UnGetChar().

   HRESULT SkipSpcEol(void);     // Skips spaces, tabs and ends of lines
                                 //    Uses GetChar() and UnGetChar().

   HRESULT SkipEols(void);       // Skips ends of lines
                                 //    Uses GetChar() and UnGetChar().

   HRESULT SkipToChar(unsigned char *pcDelimCh, const unsigned char *lpszDelim);
                                 // Skips all chars from input file until one of
                                 //    delimiter characters from delimiter string
                                 //    lpszDelim is reached. That character is returned
                                 //    in pcDelimCh, also put back to input stream.
                                 // Input:
                                 //    lpszDelim - Null-terminated string
                                 //    with all possible delimitter characters.
                                 // Output:
                                 //    pcDelimCh
                                 //    If no delimiters are found (end of input
                                 //    file reached), pcDelimCh contains '/0'.
                                 //    Uses GetChar() and UnGetChar().
   
   HRESULT GetWord
   (
      unsigned char *lpszKeywrd,
      long *lNumVal,
      unsigned char *lpszTextVal,
      unsigned char *pcDelimCh,
      const unsigned char *lpszDelim
   );                            // Reads current word from file until one of
                                 //    chars from lpszDelim is reached.  This char
                                 //    is returned in pcDelimCh.  If it is not space
                                 //    or eol char, it is left in input stream.
                                 // Input:
                                 //    lpszDelim - Null-terminated string with all
                                 //    possible delimitter characters. Word without
                                 //    trailing digits is returned in null
                                 //    terminated string buffer lpszKeywrd, which
                                 //    must be not shorter than TV_TAG_LEN+1 bytes.
                                 //    Trailing digits are parsed as long integer to
                                 //    lNumVal, text values between '\"' - to
                                 //    lpszTextVal.
                                 // Output:
                                 //    lpszKeywrd - address of buffer for keyword -
                                 //       not shorter, than TV_TAG_LEN+1 bytes;
                                 //    lpszTextVal - address of buffer for text value
                                 //       - not shorter, than TV_TAG_LEN+1 bytes;
                                 //    *lNumVal - numeric value in tail of keyword
                                 //       name;
                                 //    *pcDelimCh - first character after the keyword
                                 //       (and text value), treated as delimiter; in
                                 //       case of end of the file is returned Nul char.
                                 //    Uses GetChar() and UnGetChar().

   HRESULT SkipCurrLevel(void);
                                 // Skips characters from input file until closing
                                 //    parenthese "}" of current parenthese level is
                                 //    read. This closing parenthese is skipped.
                                 //    Uses GetChar().

// ---------------------------------------------- input with RTF tag processing
   HRESULT GetCharProc(KpChar *piInchar, bool bCheckFeof);
                                 // Get current char. from file, taking into account
                                 //    RTF tag processing.  Converts to Kpt charset.
                                 // bCheckFeof is used to swith on end of file error
                                 //    output
                                 // Uses GetChar(), GetWord(), ProcessKeyword(),
                                 //    GetKwrdIndex(),
                                 //    CharEncode(), pCurrentField and pFonts

   HRESULT UnGetCharProc(KpChar iChar);
                                 // Put char. back to input stream for GetCharProc()

   HRESULT GetCharProcSkipSpc(KpChar *piInch); // former GetProcCharSkipSpc()
                                 // Get current char. from file, taking into account
                                 //    RTF tag processing. All multiple spaces, tabs
                                 //    & eol's, even splitted in separate RTF blocks
                                 //    are being conwerted into one space.
                                 //    Uses GetChar(), GetWord() and ProcessKeyword().

   HRESULT SkipSpacesProc(void); // Skips spaces and tabs (not ends of lines),
                                 //    using RTF tag processing.
                                 //    Uses GetCharProc() and UnGetCharProc().

   HRESULT SkipSpcEolProc(void); // Skips spaces, tabs and ends of lines,
                                 //    using RTF tag processing.
                                 //    Uses GetCharProc() and UnGetCharProc().

   HRESULT GetWordProc(KpChar *piazWordBuf, int iBufSize);
      // in case when Lf was input returns empty string (length=0)


// -------------------------------------------------- additional functions
   HRESULT SearchFont(int *piFontNumber, const unsigned char *lpszFontName);
                                 // Searches font with name lpszFontName in font table
                                 //    pFonts
};


#endif
