// ==================================================
// kpctype.h
// type conversations & character processing for KP C++ projects
//

#ifndef kpctype_included
#define kpctype_included


// ================================================== encypherings
class A85decoder
{
   HRESULT m_lhOpenResult;
   KpString m_sOutStr;
   const /* unsigned */ char *m_lpszPnts;
   unsigned long m_lTuple;
   int m_iCount;

   HRESULT wput(int iBytes);

public:
   A85decoder(/* const */ KpString *psA85Str);
   ~A85decoder();
   HRESULT GetOpenResult(void);
   HRESULT Process(void);
   HRESULT RetrieveResult(KpString *psOutStr);
};
extern HRESULT A85toStr(KpString *psOutStr, /* const */ KpString sA85Str); // Ascii85 string decyphering

class A85encoder
{
   HRESULT m_lhOpenResult;
   KpString m_sOutStr;
   unsigned long m_lPos;
   const /* unsigned */ char *m_lpszPnts;
   int m_iCount;
   unsigned long m_lTuple;
   unsigned long m_lWidth;
   int m_iInBufLen;

   HRESULT encode();

   void InitMembers(void);

public:
   A85encoder(/* const */ KpString *psInStr);
   A85encoder(const UniChar *psaInStr);
   HRESULT GetOpenResult(void);
   HRESULT Process(void);
   HRESULT RetrieveResult(KpString *psOutA85Str);
};
extern HRESULT StrToA85(KpString *psOutA85Str, /* const */ KpString sInStr); // Ascii85 string encyphering
extern HRESULT UniStrToA85(KpString *psOutA85Str, const UniChar *psaInUniStr);


// ------------------------------------------------------- hyphenating
extern HRESULT KpStrHyphenate(KpChar *aizSentence); // aizSentence[KP_MAX_FILE_LIN_LEN+1], skiemenuoja frazę, naudoja KpWordHyphenate()
extern HRESULT KpWordHyphenate(KpChar *aizWord); // aizWord[KP_MAX_FILE_LIN_WDT+1], gali būti su spec. simboliais, skiemenuoja tik raidinius žodžius, TODO: ignoruoti tagus

#endif // #ifndef kpctype_included

