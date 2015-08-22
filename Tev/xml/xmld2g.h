// ==================================================
// xmld2g.h
// LzdData file to LzdSgm converter
// definitions of main module


#ifndef xmld2g_included
#define xmld2g_included

#if Envir!=MSWin32ConMfc
#error "Envir!=MSWin32ConMfc"
#endif

// --------------------------------------------------
class XmlD2G_tag: public XmlOI2_tag
{
public:
   XmlD2G_tag(const unsigned char *lpszInFname, const unsigned char *lpszOutFname);
   ~XmlD2G_tag(void);

   HRESULT OpenFileLocal(const unsigned char *lpszInFname, const unsigned char *lpszOutFname);

   HRESULT Process(bool bTrimSpaces);  // bTrimSpaces - skip spaces before and after tag contents
};


// --------------------------------------------------
extern XmlD2G_tag *pXmlD2G;

#endif
