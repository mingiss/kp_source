// ==================================================
// xmlspc.h
// splittind of compounds and derivatives to different nodes
// definitions of main module
//


#ifndef xmlspc_included
#define xmlspc_included

#if Envir!=MSWin32Con
#error "Envir!=MSWin32Con"
#endif

// --------------------------------------------------
class XmlSpC_tag
{
   HRESULT lhOpenResult;

   unsigned char lpszInFileName[KP_MAX_FNAME_LEN+1];  // file names
   unsigned char lpszOutFileName[KP_MAX_FNAME_LEN+1];

   XmlI_tag *lpInFileObj;
   XmlO_tag *lpOutFileObj;

   TvXmlTagStack_tag *pTagStack;   // XML tag stack ptr

   long lEntryId;       // current processed dictionary entry id (<se id=...> value)

   int iaLastHw[TV_XL_MAX_IX_LEN+1];

public:
   XmlSpC_tag(const unsigned char *lpszInFname, const unsigned char *lpszOutFname, bool bTagFormat);
   ~XmlSpC_tag(void);
   HRESULT GetOpenResult(void);  // Returns value of OpenResult -
                                 //    object creation error code

   HRESULT CloseFiles(bool bCheckFileExist);
                                 // Closes input and output files. After that only
                                 //    destroying of the object is reasonable.
                                 // bCheckFileExist - if not set, no file
                                 //    presence will be tested

   HRESULT Process(const int *piazFromHw, const int *piazToHw);
                                 // piazFromHw and piazToHw output boundaries in lowercase
};


// --------------------------------------------------
extern XmlSpC_tag *pXmlSpC;
extern unsigned char caXmlSpCIxLangs[XL_IX_NumOfIndexes];

#endif
