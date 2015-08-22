// -----------------------------------------
// iBsht.h
// el. knyg� per�i�ros programa
// koduota fail� sistema
// paprasta failo paie�ka viename hx indexe
//

#ifndef iBsht_included
#define iBsht_included

// ---------------------------
#ifndef iBshn_included
#error iBshn.h not included
#endif


// -----------------------------
class iBshFileSys : public KpFileSys
{
private:
   unsigned char m_lpszFtype[KP_MAX_FILE_LIN_WDT /* KP_MAX_FNAME_LEN */ + 1];
public:
   bool m_bGeckoShowFl;   // ar pradin� fail� rodyti per xGecko (htm, etc.), jei ne � i�traukti � Temp ir i�kviesti viewer�
   bool m_bXmlEncodeFl;   // ar fail� analizuoti XML parseriu, jei ne � praleid�iam skaidriai (binariniai failai, paveikslai ir kt.)

// -----------------------
   iBshFileSys(const unsigned char *lpszFirstEntryFileName = IBSHT_FIRST_ENTRY);
   virtual ~iBshFileSys(void);

   HRESULT OpenFiles // atidaro archyvo fail� m_lpInFileObj (jei IBSHT_ARCHIVE), atidaro buferin� i�vedimo fail� m_lpInFileObj --> m_pResBuf
   (
      const unsigned char *lpszInFileName = null,
      XmlVersions iVersion = XM_VERS_XHTML, // XM_VERS_HTML401_TRANS,
      HRESULT KpInFileFactory
      (
         KpFile **lppFileObjPtrPtr,
         const unsigned char *lpszFNam,
         const unsigned char *lpszFMod,
         XL_FileTypes uiFTyp,
         bool bMapToPrivate
      ) = CreateNew8File,
      HRESULT KpOutFileFactory
      (
         KpFile **lppFileObjPtrPtr,
         const unsigned char *lpszFNam,
         const unsigned char *lpszFMod,
         XL_FileTypes uiFTyp,
         bool bMapToPrivate
      ) = CreateNewUniBFile
   ); // isijungia m_bSemBlocked semafora
      // KpFileFactory � kokiu �emo lygio formatu skaityti input failus � CreateNew8File ar CreateNewUniFile
   HRESULT CloseFiles(bool bCheckFileExist); // isijungia m_bSemBlocked semafora

   HRESULT ExtractFileType(); // i�traukia m_lpszFtype i� m_lpszCurSearchKwd, nustato m_bGeckoShowFl

   HRESULT SearchForEntry
   (
      KpPubDlg *pDialogPtr,
      const unsigned char *lpszFileName = null,
      XmlO1 **pInFilePtr = NULL,
      unsigned char **pEntryImgPtr = NULL
   );       // ie�ko einamojo lizdo/failo,
            // prie� tai galima nustatyti nauj� m_lpszCurSearchKwd arba �ra�yti m_lCurEntryId = -1, norint forsuoti atnaujinim�
            // jeigu nurodytas lpszKeyWord, tai tai padaro pats
            // isijungia m_bSemBlocked semafora
            // nustato archyv� � failo prad�i�, perskaito fail� � laikin� XmlNode (i�kvie�ia ReadEntry()),
            // suformuoja HTML bufer� pDialogPtr->m_pResBuf[] ir perkelia j� � Gecko (i�kvie�ia FormatEntry()),
            // laikin� XmlNode i�trina
            // parametrai i�kvie�iant i� KpFileSys::CreateGeckoStream dvejetainiams objektams (m_bXmlEncodeFl == False):
            // pInFilePtr � skaitomo failo objektas, po panaudojimo reikia sunaikinti
            // pEntryImgPtr - skaitomo failo turinio buferis, po panaudojimo reikia sunaikinti

   HRESULT FormatEntry(XmlNode *pCurEntry, KpPubDlg *pDialogPtr); // outputs pCurEntry to m_lpOutFileObj // former CvtToRtf
            // paskai�iuoja zoominimo koeficient� pDialogPtr->m_iFact
            // pakoreguoja i�vedamo failo JavaScript� ir stilius (pCurEntry->SetCtrls())
            // suformuoja HTML bufer� pDialogPtr->m_pResBuf[] (pCurEntry->WriteNode())
            // i�kvie�ia DisplayResult() ir pDialogPtr->RedrawWindow()

   HRESULT CvtIndexEntry(unsigned char *lpscKwd); // konvertuoja pai�kos fraz� pagal arksh indekso taisykles � kei�ia '\\' � '/'
};


#endif // #ifndef iBsht_included
