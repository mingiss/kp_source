// ==================================================
// xmlspl.h
// splitting of comma-delimited xml tag contents to separate tags
// definitions of main module


#ifndef xmlspl_included
#define xmlspl_included


// --------------------------------------------------
class XmlSpl_tag: public XmlO2_tag
{
   TvXmlTagStack_tag *pTagStack;   // XML tag stack ptr

public:
   XmlSpl_tag(const unsigned char *lpszInFname, const unsigned char *lpszOutFname);
   ~XmlSpl_tag(void);

   HRESULT PutTag(int iTag, XmlTagPars_tag *pTagParsObj); // puts tag with necessary indent, does not touch the tag stack
   HRESULT PutOpenTag(int iTag, XmlTagPars_tag *pTagParsObj); // puts tag, pushes it to tag stack, processes group tag indent, if necessary
   HRESULT PutClosingTag(int iTag, XmlTagPars_tag *pTagParsObj); // puts top tag from tag stack, compares it with iTag, pops tag stack, processes group tag indent, if necessary
   HRESULT Process(void);
};


#endif
