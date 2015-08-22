// ==================================================
// xmlo2.h
// base class for XML aplications with two (input and output) files


#ifndef xmlo2_included
#define xmlo2_included


// --------------------------------------------------
#define TV_XR_REF_THRESHOLD 3

// --------------------------------------------------
class XmlO2
{
// ------------------------ fields for references
   KpChar auiRefBuf[TV_XL_MAX_IX_LEN+1];     // buffer for reference text
   int iRefBufIdx;
   KpChar auiLWordBuf[TV_XL_MAX_IX_LEN+1];   // buffer for last word, not
   int iLWordBufIdx;                               //    belonging to reference

   bool bTextToBuffer;  // set, when chars must be sent to buffer
                        // reset, when directly to output file (waiting for start of
                        //    word)

   bool bCollectReference;               // flag of reference processing

// -------------------------------- reference methods
   HRESULT StartReferenceProcessing(bool bRefFlg);
                                             // bRefFlg - reference processing flag
   HRESULT StopReferenceProcessing(XmlTagPars *pTagPar);
                                             // pTagPar - jei jau buvo nuoroda <xr href="...">

   HRESULT PutRefChar(KpChar uiChOut, XmlTagPars *pTagPar); // put character to buffer

   HRESULT SeparateLastRefWord(bool bWrdFlg);// separate last word from reference buffer
                                             //    to last word buffer.
                                             // bWrdFlg - detach whole word or only
                                             //    trailing spaces

   HRESULT FlushRefVal(XmlTagPars *pTagPar);
                                             // put reference tag to file
                                             // pTagPar - jei jau buvo nuoroda <xr href="...">

   HRESULT FlushLastRefWord(void);           // put last word to file

// --------------------------------
public:
   HRESULT m_lhOpenResult;

   unsigned char m_lpszInFileNames[MAX_NUM_OF_LIST_ENTRIES][KP_MAX_FNAME_LEN+1];
   unsigned char m_lpszOutFileName[KP_MAX_FNAME_LEN+1];

   XmlO1 *m_lpInFileObjs[MAX_NUM_OF_LIST_ENTRIES];  // first file - real input file,
   int m_iNumOfInFiles;                               // others - only for reference searching
   XmlO1 *m_lpOutFileObj;

   long lLastIdx;       // last standard entry index for error output

// long lMaxSeIx;       // autoincremental index value for irregular se entries

   long m_lEntryId;     // current processed dictionary entry id (<se id=...> value)
	KpChar aiHwMsgText[KP_MSG_LEN+1];       // <hw> text collector for error messages
   int iHwMsgPtr;       // current pointer to szaHwMsgText

// --------------------------------
   XmlO2(void);
   virtual ~XmlO2(void);   // void XmlO2_tag_destructor(void); 

   HRESULT OpenFiles
   (
      const unsigned char * const *lpszInFnames, int iNumOfInFiles, const unsigned char *lpszInMode,
      const unsigned char *lpszOutFname, const unsigned char *lpszOutMode
   );          // opens files
                           

   HRESULT OpenFile
   (
      const unsigned char *lpszInFname, const unsigned char *lpszInMode,
      const unsigned char *lpszOutFname, const unsigned char *lpszOutMode
   );          // variant of OpenFiles for single input file

   HRESULT GetOpenResult(void);  // Returns value of OpenResult -
                                 //    object creation error code

   HRESULT CloseFiles(bool bCheckFileExist);
                                 // Closes input and output files. After that only
                                 //    destroying of the object is reasonable.
                                 // bCheckFileExist - if not set, no file
                                 //    presence will be tested

   HRESULT TransferField
   (
      KpChar uiStartTag,
      KpChar uiEndTag,
      XL_Indexes uiIxFileIdx, 
      long lMainKeyValue,
      bool bTstInverted,
      bool bTstCombined,
      bool bProcessSubkeys,
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
                                 // if bProcessSubkeys==False - all subkey processing is off
};


#endif
