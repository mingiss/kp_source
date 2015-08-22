// ==================================================
// xmloi2.h
// base class for XML aplications with two (input and output) files and index support


#ifndef xmloi2_included
#define xmloi2_included


// --------------------------------------------------
#define TV_XR_REF_THRESHOLD 3

// --------------------------------------------------
class XmlOI2
{
// --------------------------------
public:
   HRESULT m_lhOpenResult;

   unsigned char m_lpszInFileName[KP_MAX_FNAME_LEN+1];
   unsigned char m_lpszOutFileName[KP_MAX_FNAME_LEN+1];

   XmlI *m_lpInFileObj;
   XmlI *m_lpOutFileObj;

   TvXmlTagStack *m_pTagStack;   // XML tag stack ptr

   long m_lLastIdx;       // last standard entry index for error output

   long m_lMaxSeIx;       // autoincremental index value for irregular se entries

// unsigned char m_lpszHwSav[TV_XL_HW_IX_LEN+1]; // current <hw> saving buffer
   long m_lEntryId;       // current processed dictionary entry id (<se id=...> value)

   const unsigned char *m_acIndexLanguages;    // pointer to index languages array
   const EC_Types *m_aiIndexEncodings;         // pointer to index encoding array
           
private:
// ------------------------ fields for references
   KpChar m_auiRefBuf[TV_XL_MAX_IX_LEN+1];     // buffer for reference text
   int m_iRefBufIdx;
   KpChar m_auiLWordBuf[TV_XL_MAX_IX_LEN+1];   // buffer for last word, not
   int m_iLWordBufIdx;                               //    belonging to reference

   bool m_bTextToBuffer;  // set, when chars must be sent to buffer
                        // reset, when directly to output file (waiting for start of
                        //    word)

   bool m_bCollectReference;
                        // flag of reference processing

   bool m_bProcessSubkeys;   // if False switches off all MCM subkey processing in index generator ( "(", ")", "/", "," etc.)

public:
// --------------------------------
   XmlOI2(bool bProcessSubkeys); // bProcessSubkeys - initial value for m_bProcessSubkeys 
   virtual ~XmlOI2(void); // former void XmlOI2_tag_destructor(void); // 

private:
// -------------------------------- reference methods
   HRESULT StartReferenceProcessing(bool bRefFlg);
                                             // bRefFlg - reference processing flag
   HRESULT StopReferenceProcessing(void);

   HRESULT PutRefChar(KpChar uiChOut); // put character to buffer

   HRESULT SeparateLastRefWord(bool bWrdFlg);// separate last word from reference buffer
                                             //    to last word buffer.
                                             // bWrdFlg - detach whole word or only
                                             //    trailing spaces

   HRESULT FlushRefVal(void);                // put reference tag to file

   HRESULT FlushLastRefWord(void);           // put last word to file

public:
   HRESULT OpenFile
   (
      const unsigned char *lpszInFname, const unsigned char *lpszInMode,
      const unsigned char *lpszOutFname, const unsigned char *lpszOutMode,
      const unsigned char *acIndexLangs, const EC_Types *aiIndexEncs
   );          // opens XMLT files, for another XML-like files use local defined OpenLocalFile()
                           

   HRESULT GetOpenResult(void);  // Returns value of OpenResult -
                                 //    object creation error code

   HRESULT CloseFiles(bool bCheckFileExist);
                                 // Closes input and output files. After that only
                                 //    destroying of the object is reasonable.
                                 // bCheckFileExist - if not set, no file
                                 //    presence will be tested

   HRESULT PutTag(KpChar iTag, XmlTagPars *pTagParsObj); // puts tag with necessary indent, does not touch the tag stack
   HRESULT PutOpenTag(KpChar iTag, XmlTagPars *pTagParsObj); // puts tag, pushes it to tag stack, processes group tag indent, if necessary
   HRESULT PutClosingTag(KpChar iTag, XmlTagPars *pTagParsObj); // puts top tag from tag stack, compares it with iTag, pops tag stack, processes group tag indent, if necessary

   HRESULT TransferField
   (
      const KpChar uiStartTag,
      const KpChar uiEndTag,
      const XL_Indexes uiIxFileIdx,
      const long lMainKeyValue,
      bool bTstInverted,
      bool bTstCombined,
      XmlTagPars *pTagPar
   );
                                 // copy input file field to output XML file,
                                 //    using uiEndTag as field separator
                                 // TransferField() leaves field as is, all converting
                                 //    is made only on index entry (control characters
                                 //    ';', ',', '/' '(', ')', '[' and ']', look file
                                 //    mcmr2x.c
                                 // uiStartTag and uiEndTag - tags of XML field
                                 // uiIxFileIdx - index to output index file, to which
                                 //    field must be added as index entry,
                                 //    XL_IX_NoIndex for no index file
                                 // lMainKeyValue - main index numeric value, with
                                 //    which current index must be bound, for standard
                                 //    entry index se - any value, character position
                                 //    in the output file will be used instead.
                                 // bTstInverted and bTstCombined turns on special
                                 //    conversion of index entries
};


#endif
