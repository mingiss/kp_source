// ==================================================
// xmlque.h
// XML nodes extractor depending on criteria
// definitions of main module
//


#ifndef xmlque_included
#define xmlque_included


// --------------------------------------------------
class XmlQue_tag: public XmlOI2_tag
{
   XL_Indexes m_iIndexFile;
   unsigned char m_lpszMinIxValue[TV_XL_MAX_IX_LEN+1];
   unsigned char m_lpszMaxIxValue[TV_XL_MAX_IX_LEN+1];

public:
   XmlQue_tag
   (
      const unsigned char *lpszInFname,
      const unsigned char *lpszOutFname,
      const unsigned char *lpszIndexName,
      const unsigned char *lpszMinValue,
      const unsigned char *lpszMaxValue
   );

   ~XmlQue_tag(void);

   HRESULT Process(void);

};

#endif
