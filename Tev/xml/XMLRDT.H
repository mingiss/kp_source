// ==================================================
// xmlrdt.h
// XML dictionary tag eliminator
// definitions of main module


#ifndef xmlrdt_included
#define xmlrdt_included

#define RP_MAX_TAGS 5

// --------------------------------------------------
class XmlRdt_tag: public XmlOI2_tag
{
   unsigned char lpszInFileName[KP_MAX_FNAME_LEN+1];  // file names
   unsigned char lpszOutFileName[KP_MAX_FNAME_LEN+1];
   TvXmlTagStack_tag *pTagStack;   // XML tag stack ptr
   short bAccFl;
   int aiXmlAccDeclArr[RP_MAX_TAGS+1];  // array of accepted/declined tags - only these tags will (not) be output

public:
   XmlRdt_tag(const unsigned char *lpszInFname, const unsigned char *lpszOutFname);
   ~XmlRdt_tag(void);
   HRESULT AcceptDeclineXmlTag(const unsigned char *lpszTag);
   HRESULT PutTag(int iTag, XmlTagPars_tag *pTagParsObj); // puts tag with necessary indent, does not touch the tag stack
   HRESULT PutOpenTag(int iTag, XmlTagPars_tag *pTagParsObj, bool bOutFlag); // puts tag, pushes it to tag stack, processes group tag indent, if necessary
   HRESULT PutClosingTag(int iTag, XmlTagPars_tag *pTagParsObj, bool bOutFlag); // puts top tag from tag stack, compares it with iTag, pops tag stack, processes group tag indent, if necessary
   HRESULT Process(void);
};


// --------------------------------------------------
extern XmlRdt_tag *pXmlRdt;

#endif
