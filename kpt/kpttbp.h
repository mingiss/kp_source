// ==================================================
// kpttbp.h
// Print code table
// definitions of main module


#ifndef kpttbp_included
#define kpttbp_included

// --------------------------------------------------
class KptTbp_tag
{
   HRESULT lhOpenResult;

   unsigned char lpszOutFileName[KP_MAX_FNAME_LEN+1]; // file name
   TvXmlTagStack_tag *pTagStack;   // XML tag stack ptr

   TvXmlFile_tag *lpOutFileObj;

   int iCtbl;
   unsigned char lpszTitle[KP_MAX_FILE_LIN_WDT+1];

public:
   KptTbp_tag(int iKptTbl, const unsigned char *lpszOutFname);
   ~KptTbp_tag(void);

   HRESULT GetOpenResult(void);

   HRESULT OpenFile(const unsigned char *lpszOutFname);

   HRESULT CloseFile(bool bCheckFileExist);
                                 // Closes output file. After that only
                                 //    destroying of the object is reasonable.
                                 // bCheckFileExist - if not set, no file
                                 //    presence will be tested
   HRESULT Process(void);
};


// --------------------------------------------------
extern KptTbp_tag *pKptTbp;

#endif
