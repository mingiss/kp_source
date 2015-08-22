// ==================================================
// xml8.h
// 8-bit low level XML file definitions
//

#ifndef tvxml8_included
#define tvxml8_included


// --------------------------------------------------
class TvXml8File: public KpFile
{
   FILE *lpfFilePtr;    // file itself

   int iCharPos;   // Current character position from beginning of the line
   long lCharNum;  // Current char position from beginning of the file

public:
   TvXml8File
   (
      const unsigned char *lpszFileName,
      const unsigned char *lpszMode,
      XL_FileTypes uiFileType,
      bool bMapToPrivate
   );                            // Opens file for input/output, depending on lpszMode
                                 //    (like fopen())
                                 //    bMapToPrivate - fictive flag for compatibility with Unicode files

/* virtual */ HRESULT GetRawFilePtr(FILE **lppFilePtrPtr, bool bCheckError);
                                 // returns pointer to FILE object of currently opened file;
                                 //    it can be used for direct binary file operations

/* virtual */ HRESULT CloseFile(bool bCheckFileExist);
                                 // Closes current Xml file
                                 //   this call makes sence only for result code retrieving,
                                 //   after CloseFile() no other calls except ~TvXmlFile_tag
                                 //   are acceptable
                                 // bCheckFileExist - if not set, no file
                                 //    presence will be tested

/* virtual */ HRESULT VirtDestruct(void);
                                 // explicit destructor, must be called from parent class before
                                 //    destroying of the object

// ------------------------------------- text output
/* virtual */ HRESULT PutChar(KpChar iOutch, bool bCheckErrors);
                                 // Put character to file
                                 // if bCheckErrors=False, no error message
                                 //    will be output in case of nonexisting
                                 //    output equivalent, TV_E_UNKN_CHR
                                 //    is returned in this case

/* virtual */ HRESULT GetCharPos(int *piCharPos);  // Current character position from beginning of the line
/* virtual */ HRESULT GetCharNum(long *plCharNum); // Current char position from beginning of the file

/* virtual */ HRESULT Reset(void); // resets buffer pointer and clears the buffer (first character)

// ------------------------------------- text input
/* virtual */ HRESULT GetChar(KpChar *piInch); // Gets current char. from file
   
/* virtual */ HRESULT Fseek(long lOffset, int iOrigin); // analog of fseek();
};


// ================================================== low level file creation procedure
extern XmlfLowLevelCrFun CreateNew8File;

#endif
