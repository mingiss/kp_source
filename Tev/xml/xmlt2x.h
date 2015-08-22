// ==================================================
// xmlt2x.h
// converting XML dictionary to (LVZ03) TeX file
// definitions of main module
//


#ifndef xmlt2x_included
#define xmlt2x_included

#if (Envir!=MSWin32Con) && (Envir!=MSWin32ConMfc)
#error "Envir!=MSWin32Con"
#endif
                 
                 
// --------------------------------------------------
class XmlT2X : public XmlT2X0
{
public:
   XmlT2X(const unsigned char *lpszInFname, const unsigned char *lpszOutFname, bool bTagFormat);

   HRESULT OpenFilesLocal(const unsigned char *lpszInFname, const unsigned char *lpszOutFname);

   HRESULT Process(const KpChar *piazFromHw, const KpChar *piazToHw, int iLevel);
                                 // piazFromHw and piazToHw output boundaries in lowercase
};


// --------------------------------------------------
extern XmlT2X *pXmlT2X;

#endif
