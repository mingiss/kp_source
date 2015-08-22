// ==================================================
// xmlt2.h
// XML file dump to pipe
// definitions of main module


#ifndef xmlt2_included
#define xmlt2_included


// --------------------------------------------------
class XmlT2_tag
{
   unsigned char lpszInFName[KP_MAX_FNAME_LEN+1];

   XmlO1_tag *lpInFileObj;

   HRESULT lhOpenResult;

public:
   XmlT2_tag(const unsigned char *lpszInFname);
   ~XmlT2_tag();

   HRESULT GetOpenResult(void);  // Returns value of OpenResult -
                                 //    object creation error code

   HRESULT Process(void);

   HRESULT CloseFiles(bool bCheckFileExist);
                                 // Closes input and output files. After that only
                                 //    destroying of the object is reasonable.
                                 // bCheckFileExist - if not set, no file
                                 //    presence will be tested
};

// ================================================== low level file creation procedure
extern HRESULT CreateNewUniFile
(
   KpFile **lppFileObjPtrPtr,
   const unsigned char *lpszFNam,
   const unsigned char *lpszFMod,
   XL_FileTypes uiFTyp
);

#endif
