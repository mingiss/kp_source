// ==================================================
// xmlt2g.h
// XML UTF-8 to SGML CTBL-80 Tage dictionary converter
// definitions of main module


#ifndef xmlt2g_included
#define xmlt2g_included

#if Envir!=MSWin32Con
#error "Envir!=MSWin32Con"
#endif

// --------------------------------------------------
class XmlT2G_tag: public XmlOI2_tag
{
public:
   XmlT2G_tag(const unsigned char *lpszInFname, const unsigned char *lpszOutFname);
   ~XmlT2G_tag(void);

   HRESULT OpenFileLocal(const unsigned char *lpszInFname, const unsigned char *lpszOutFname);
   HRESULT CloseFilesLocal(bool bCheckFileExist);

   HRESULT Process(void);  // bTrimSpaces - skip spaces before and after tag contents
};


// --------------------------------------------------
extern XmlT2G_tag *pXmlT2G;

#endif
