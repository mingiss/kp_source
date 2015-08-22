// ==================================================
// xmlb.h
// 8-bit low level XML RAM file definitions
// puts data to buffer, used generally for RTF output to RichEdit controls
//

#ifndef tvxmlb_included
#define tvxmlb_included


// --------------------------------------------------
class TvXmlBFile: public KpFile
{
public:
   unsigned char *m_lpszBufPtr;  // input / output buffer start address
   long m_lBufLen;   // size of output buffer

   int m_iCharPos;   // Current character position from beginning of the line
   long m_lCharNum;  // Current char position from beginning of the buffer

   TvXmlBFile
   (
      const unsigned char *lpszFileName,
      const unsigned char *lpszMode,
      XL_FileTypes uiFileType,
      bool bMapToPrivate
   );                            // Opens RAM file for output
                                 //    open for input (lpszMode=="r...") not yet realised,
                                 //       results an error
                                 //    lpszFileName must contain two hexadecimal numbers,
                                 //       meaning buffer start address and buffer size
                                 //       like "12A3F456 3D56"
                                 //    bMapToPrivate - fictive flag for compatibility with Unicode files

   virtual HRESULT GetRawFilePtr(FILE **lppFilePtrPtr, bool bCheckError);
                                 // only for compatibility with other file formats,
                                 //    results an error

   virtual HRESULT CloseFile(bool bCheckFileExist);
                                 // only for compatibility with other file formats,

   virtual HRESULT VirtDestruct(void);
                                 // explicit destructor, must be called from parent class before
                                 //    destroying of the object

// ------------------------------------- text output
   virtual HRESULT PutChar(KpChar iOutch, bool bCheckErrors);
                                 // Put character to the buffer current position
                                 // if bCheckErrors=False, no error message
                                 //    will be output in case of nonexisting
                                 //    output equivalent, TV_E_UNKN_CHR
                                 //    is returned in this case

   virtual HRESULT GetCharPos(int *piCharPos);  // Current character position from beginning of the line
   virtual HRESULT GetCharNum(long *plCharNum); // Current char position from beginning of the file

   virtual HRESULT Reset(void); // resets buffer pointer and clears the buffer (first character)

// ------------------------------------- text input
   virtual HRESULT GetChar(KpChar *piInch);

   virtual HRESULT Fseek(long lOffset, int iOrigin); // analog of fseek();
};


// ================================================== low level file creation procedure
extern XmlfLowLevelCrFun CreateNewBFile;

#endif
