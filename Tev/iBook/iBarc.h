// ==================================================
// iBarc.h
// arksh (iBsh) failø archyvatorius
//


#ifndef iBarc_included
#define iBarc_included

// --------------------------------------------------
#define IBARC_OUT_FNAME ((const unsigned char *)"arksh.arc")
#define IBARC_IN_FOLDER ((const unsigned char *)"dst")

// --------------------------------------------------
class iBarc: public XmlO1 // XmlI
{
   unsigned char m_lpszInFolderName[KP_MAX_FNAME_LEN + 1];

   long m_iFileIx; // eilinio apdorojamo failo numeris, indekso failo pildymui
   long m_iArcFilePos; // eilinë pozicija archyvo faile, XL_IX_DefSeIndex pildymui

public:
   iBarc(const unsigned char *lpszInFolderName, const unsigned char *lpszOutFname);

private:
   HRESULT ProcFolder(const unsigned char *lpszInFolderName);

public:
   HRESULT Process(void);
};

// --------------------------------------------------
extern iBarc *piBarc;

#endif
