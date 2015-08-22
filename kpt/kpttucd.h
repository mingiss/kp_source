// ==================================================
// kpttucd.cpp
// Definitions for Unicode charset generator


#ifndef kpttucd_included
#define kpttucd_included

#define KPTTUCD_REV_WORD_CNT 3

// --------------------------------------------------
class KpttUcd_tag
{
   unsigned char lpszInFName[KP_MAX_FNAME_LEN+1];
   UcFile_tag *lpInFile;
   unsigned char lpszOutFName[KP_MAX_FNAME_LEN+1];
   FILE *lpOutFile;

   HRESULT lhOpenResult;

public:
   KpttUcd_tag
   (
      const unsigned char *lpszInFileName,
      const unsigned char *lpszOutFileName,
      UC_Modes iUcMode
   );  // opens file lpszInFileName in coding iUcMode and creates file lpszOutFileName

   ~KpttUcd_tag();

   HRESULT GetOpenResult(void);  // Returns value of OpenResult -
                                 //    object creation error code

   HRESULT ProcessContents(bool bJava);
   HRESULT ProcessCpp(void);
   HRESULT ProcessJava(void);

   HRESULT ProcessJavaRevContents(void);

   HRESULT CloseFiles(bool bCheckFileExist);
                                 // Closes input and output files. After that only
                                 //    destroying of the object is reasonable.
                                 // bCheckFileExist - if not set, no file
                                 //    presence will be tested
};


#endif
