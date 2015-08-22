// ==================================================
// xmlext.h
// XML nodes extractor depending on criteria
// like xmlext, but does not need indexes, uses sequential testing
// definitions of main module
//


#ifndef xmlext_included
#define xmlext_included


// --------------------------------------------------
class XmlExt_tag: public XmlOI2_tag
{
   int m_iSearchTag; // tagas, pagal kuri ieskom
   unsigned char m_lpszMinValue[TV_TAG_LEN+1];
   unsigned char m_lpszMaxValue[TV_TAG_LEN+1];
   bool m_bExtractSubNodes;   // if True, subnodes of <hg> not containing
                              // querying tag m_iSearchTag will be deleted
public:
   XmlExt_tag
   (
      const unsigned char *lpszInFname,
      const unsigned char *lpszOutFname,
      const unsigned char *lpszTagName,
      const unsigned char *lpszMinValue,
      const unsigned char *lpszMaxValue,
      const unsigned char *lpszExtractSubNodes
   );

   ~XmlExt_tag(void);

   HRESULT Process(void);

};

#endif
