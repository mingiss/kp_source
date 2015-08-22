// ==================================================
// xmlrcp.h
// search for compounds with no headword translation (':' needed)
// definitions of main module


#ifndef xmlrcp_included
#define xmlrcp_included


// --------------------------------------------------
class XmlRcp_tag
{
   unsigned char lpszInFName[KP_MAX_FNAME_LEN+1];
   unsigned char lpszOutFName[KP_MAX_FNAME_LEN+1];

   XmlO1_tag *lpInFileObj;
   UcFile_tag *lpOutFile;

   HRESULT lhOpenResult;

   long lEntryId;

   int lpiazHwSav[KP_MAX_FILE_LIN_LEN+1];
   int iHwPtr;
   bool bHwInput;
   bool bCpdReached;
   bool bTrReached;

public:
   XmlRcp_tag(const unsigned char *lpszInFname, const unsigned char *lpszOutFname);
   ~XmlRcp_tag();

   HRESULT GetOpenResult(void);  // Returns value of OpenResult -
                                 //    object creation error code

   HRESULT PutSeId(void);
   HRESULT PutChar(int iInChar);
   HRESULT PutStrInt(const int *iazOutStr);
   HRESULT Process(void);

   HRESULT CloseFiles(bool bCheckFileExist);
                                 // Closes input and output files. After that only
                                 //    destroying of the object is reasonable.
                                 // bCheckFileExist - if not set, no file
                                 //    presence will be tested
};




#endif
