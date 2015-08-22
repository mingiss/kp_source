// ==================================================
// xmlicv.h
// compressing of symbolic XML indexes
// definitions of main module


#ifndef xmlicv_included
#define xmlicv_included


// --------------------------------------------------
class XmlIcvClass
{
   unsigned char m_lpszFileName[KP_MAX_FNAME_LEN+1];

   XmlO1  *lpInFileObj;
   XmlO1 *lpOutFileObj;

   long m_lSeSize;

   HRESULT lhOpenResult;

   HRESULT CompressSE(const XL_Indexes iFileIndex); // compressing of main index <se>
   
   HRESULT CompressTextIndex(const XL_Indexes iFileIndex, int iIndexWidth);
                                 // compressing of indexes <hw>, <tw> and <la>
public:
   XmlIcvClass(const unsigned char *lpszFname);
   ~XmlIcvClass();

   HRESULT GetOpenResult(void);  // Returns value of OpenResult -
                                 //    object creation error code

   HRESULT Process();

   HRESULT RecalcSE(void); // prideda lizdu dydzius i antra *_se.ix irasu elementa

   HRESULT CloseFiles(bool bCheckFileExist);
                                 // Closes input and output files. After that only
                                 //    destroying of the object is reasonable.
                                 // bCheckFileExist - if not set, no file
                                 //    presence will be tested
};


#endif
