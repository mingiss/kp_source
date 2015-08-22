// ==================================================
// xmlt2h.cpp
// XMLT to HTML converter
// definitions of main module


#ifndef xmlg2t_included
#define xmlg2t_included

// --------------------------------------------------
class XmlT2H_tag: public XmlOI2_tag
{
public:
   XmlT2H_tag(const unsigned char *lpszInFname, const unsigned char *lpszOutFname);
   ~XmlT2H_tag(void);

   HRESULT OpenFileLocal(const unsigned char *lpszInFname, const unsigned char *lpszOutFname);

   HRESULT Process(bool bTrimSpaces);  // bTrimSpaces - skip spaces before and after tag contents
};


// --------------------------------------------------
extern XmlT2H_tag *pXmlT2H;

#endif
