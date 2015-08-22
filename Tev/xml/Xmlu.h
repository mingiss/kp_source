// ==================================================
// xmlu.h
// Unicode XML file definitions
//

#ifndef tvxmlu_included
#define tvxmlu_included


// --------------------------------------------------
class TvXmlUniFile: public KpFile
{
public:
   UcFile *lpfUniFilePtr;    // file itself

   TvXmlUniFile
   (
      const unsigned char *lpszFileName,
      const unsigned char *lpszMode,
      XL_FileTypes uiFileType,
      XmlfLowLevelCrFunPtr CreateLowLevelObj,
      bool bMapToPrivate,
      UC_Modes iEncMode
   );                            // Opens file for input/output, depending on lpszMode
                                 //    (like fopen())

   virtual HRESULT GetRawFilePtr(FILE **lppFilePtrPtr, bool bCheckError);
                                 // returns pointer to FILE object of currently opened file;
                                 //    it can be used for direct binary file operations

   virtual HRESULT CloseFile(bool bCheckFileExist);
                                 // Closes current Xml file
                                 //   this call makes sence only for result code retrieving,
                                 //   after CloseFile() no other calls except ~TvXmlFile_tag
                                 //   are acceptable
                                 // bCheckFileExist - if not set, no file
                                 //    presence will be tested

   virtual HRESULT VirtDestruct(void);
                                 // explicit destructor, must be called from parent class before
                                 //    destroying of the object

// ------------------------------------- text output
   virtual HRESULT PutChar(KpChar iOutch, bool bCheckErrors);
                                 // Put character to file
                                 // if bCheckErrors=False, no error message
                                 //    will be output in case of nonexisting
                                 //    output equivalent, TV_E_UNKN_CHR
                                 //    is returned in this case

   virtual HRESULT GetCharPos(int *piCharPos);    // Current character position from beginning of the line
   virtual HRESULT GetCharNum(long *plCharNum);   // Current char position from beginning of the file

   virtual HRESULT Reset(void); // for compatibility with RAM files (xmlb.cpp)

// ------------------------------------- text input
   virtual HRESULT GetChar(KpChar *piInch); // Gets current char. from file

   virtual HRESULT Fseek(long lOffset, int iOrigin); // analog of fseek();
};

// ================================================== low level file creation procedure
extern XmlfLowLevelCrFun CreateNewUniFile; // real file
extern XmlfLowLevelCrFun CreateNewUniBFile; // "RAM" file
extern XmlfLowLevelCrFun CreateNewUni16BFile; // "RAM" UTF-16 file

#endif
