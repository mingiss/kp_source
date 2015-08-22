// ==================================================
// tvrtfo.h
// RTF output file definitions


#ifndef tvrtfo_included
#define tvrtfo_included


// --------------------------------------------------
class TvRtfO: public TvRtfIO
{
   KpChar m_iPrevChar;
public:
   TvRtfO
   (
      const unsigned char *OutFName,
      XmlfLowLevelCrFun *CreateLowLevelObj,
//    (*CreateLowLevelObj)(
//       KpFile **lppFileObjPtrPtr,
//       const unsigned char *lpszFNam,
//       const unsigned char *lpszFMod,
//       XL_FileTypes uiFTyp,
//       bool bMapToPrivate
//    ),
   /* const */ RT_FontDescriptor_tag *pFontTbl
   );
                                       // Opens file for output
                                       //    lppFileObjPtrPtr - CreateNew8File or CreateNewBFile
                                       //    pFontTbl - pointer to font table of RT_MAX_NUM_OF_FONTS
                                       //       entries, managed (defined and deleted) on user aplication side
                                       // const pFontTbl neleidzia iskviesti IsDefined() ir co.
   ~TvRtfO();

   HRESULT OpenField();
   HRESULT CloseField();

   HRESULT PutChar(KpChar iOutch, bool bRtfFlag);    // Put character to file,
                                                      // bRtfFlag - output higher chars as \'xx

   HRESULT PutCharCrLf(KpChar iOutch, bool bRtfFlag);// Put character to file, process Cr/Lf chars
                                                      // bRtfFlag - output higher chars as \'xx

   HRESULT PutStr(const unsigned char *lpszOutstr);
                                       // Put 7-bit or Kpt encoded 8-bit string to file

   HRESULT PutStrCtbl(const unsigned char *lpszOutStr, int iCtbl);
                                       // Put 8-bit string to file, 
                                       // iCtbl - kpt codetable number of the string
                                       // converts \n to \par, \r to \line

   HRESULT PutKwrd(RT_TagIds iOutTag, int iPar);      // Put RTF command with parameter
   HRESULT PutKwrd(RT_TagIds iOutTag, char *lpszPar); // Put RTF command with parameter
   HRESULT PutKwrd(RT_TagIds iOutTag);                // Put RTF command without parameter

   HRESULT WriteHeader(RGB_Color *plColorTbl, int iSizeOfCtbl);
                                       // write file header according to !!!
   HRESULT PutStyleSheet(void);        // must be defined in user application
   HRESULT WriteTail(void);            // close fields open by WriteHeader()

   HRESULT CloseFile(bool bCheckFileExist);
                                       // Closes current Rtf file
                                       //   this call makes sence only for result code retrieving,
                                       //   after CloseFile() no other calls except ~TvRtfO()
                                       //   are acceptable

//-------------------------------
   HRESULT PutCharProc(KpChar iOutch, bool bRtfFlag);// Put character to file,
                                                      // bRtfFlag - output higher chars as \'xx

   HRESULT PutStrProc(const unsigned char *lpszOutstr);
                                       // Put 7-bit string to file

   HRESULT PutKpStr(const KpChar *lpaizOutStr, bool bRtfFlag);  // Put 16-bit Kpt string to file; // former PutIntStr
                                                                  // bRtfFlag - output higher chars as \'xx
};


#endif
