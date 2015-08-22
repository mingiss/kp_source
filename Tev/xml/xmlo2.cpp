// ==================================================
// xmlo2.cpp, former tvxmlio2.cpp
// base class for XML applications with two (input and output) files
// adapted to MacMillan dictionary references corrector tvxmlrcr.cpp
//

// ================================================== definitions
#include "stdafx.h"

#include "envir.h"

#if CompilerGr==Msvc
#include <afx.h>
#endif
#include <string>
#include <stdio.h>
#include <fstream>
#if OsGr==MSWin
#include <windows.h>
#endif

#if Compiler != Watcom
using namespace std;
#endif

#include "kpstdlib.h"
#include "kperrno.h"
#include "kptt.h"
#include "kptree.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpcolors.h"
#include "kpfonts.h"
#include "kpstdio.h"
#include "kperr.h"
#include "tvmain.h"
#include "tvxml.h"
#include "xmlh.h"
#include "xmlp.h"
#include "xmlf.h"
#include "kpttucf.h"
#include "xmlo1.h"
#include "xmlt.h"
#include "xmlu.h"
#include "xmlo2.h"
#include "xmlis.h"
#include "tvxmle.h"
// #include "mcmt.h"


// ================================================== public members of XmlO2
XmlO2::XmlO2(void)
{
int ii;

   m_lhOpenResult=S_OK;

   for(ii=0; ii<MAX_NUM_OF_LIST_ENTRIES; ii++) m_lpszInFileNames[ii][0]=Nul;
   m_iNumOfInFiles=0;
   m_lpszOutFileName[0]=Nul;

   for(ii=0; ii<MAX_NUM_OF_LIST_ENTRIES; ii++) m_lpInFileObjs[ii]=NULL;
   m_lpOutFileObj=NULL;

   lLastIdx=0L;

// lMaxSeIx=0L;

   iRefBufIdx=0;
   iLWordBufIdx=0;
   bTextToBuffer=FALSE;
   bCollectReference=FALSE;

   m_lEntryId=0L;

   aiHwMsgText[0]=C_Nul;
   iHwMsgPtr=0;
// m_lhOpenResult=KpErrorProc.SetLTxt((const unsigned char *)"");
}


// --------------------------------------------------
XmlO2::~XmlO2(void)
{
   CloseFiles(FALSE);

KP_TRACE("~XmlO2");
}


// --------------------------------------------------
HRESULT XmlO2::OpenFiles
(
const unsigned char * const *lpszInFnames, int iNumOfInFiles, const unsigned char *lpszInMode,
const unsigned char *lpszOutFname, const unsigned char *lpszOutMode
)
{
HRESULT retc=S_OK;
int ii;
int jj;

   for(ii=0; ii<MAX_NUM_OF_LIST_ENTRIES; ii++) m_lpInFileObjs[ii]=NULL;
   m_lpOutFileObj=NULL;
   m_iNumOfInFiles=0;

   if(((lpszInFnames==NULL) || (lpszOutFname==NULL)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if((iNumOfInFiles<1) || (iNumOfInFiles>MAX_NUM_OF_LIST_ENTRIES))
      m_lhOpenResult=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

// --------------------- input files
   m_iNumOfInFiles=iNumOfInFiles;
   if(SUCCEEDED(retc)) for(ii=0; ii<iNumOfInFiles; ii++)
   {
      if((lpszInFnames[ii]==NULL) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

      if(SUCCEEDED(retc))
      {
         jj=strlen(lpszInFnames[ii]);
         if((jj<=0) || (jj>KP_MAX_FNAME_LEN))
            retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);
      }
      if(SUCCEEDED(retc)) strcpy(m_lpszInFileNames[ii], lpszInFnames[ii]);

      KP_NEWO(m_lpInFileObjs[ii], XmlO1(lpszInFnames[ii], lpszInMode, CreateNewUniFile,
                                       plpszaXmlSpecCharTagsMain, alpszIndexNames, aiIndexWidths, 
                                       (KpChar)XC_FirstDictTag, plpszaXmlttDictTags, False,
                                       XM_VERS_XML10, iaXmlDictNulCodeTables, True, True));
   }

// --------------------- output file
   if(SUCCEEDED(retc))
   {
      jj=strlen(lpszOutFname);
      if((jj<=0) || (jj>KP_MAX_FNAME_LEN))
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);
   }
   if(SUCCEEDED(retc)) strcpy(m_lpszOutFileName, lpszOutFname);

   KP_NEWO(m_lpOutFileObj, XmlO1(lpszOutFname, lpszOutMode, CreateNewUniFile,
                              plpszaXmlSpecCharTagsMain, alpszIndexNames, aiIndexWidths, 
                              (KpChar)XC_FirstDictTag, m_lpInFileObjs[0]->GetTagsArrPtr(), True, // plpszaXmlttDictTags, False, //  
                              XM_VERS_XML10, iaXmlDictNulCodeTables, True, True));

return(retc);
}


// --------------------------------------------------
HRESULT XmlO2::OpenFile
(
const unsigned char *lpszInFname, const unsigned char *lpszInMode,
const unsigned char *lpszOutFname, const unsigned char *lpszOutMode
)
{
HRESULT retc=S_OK;

   retc=OpenFiles(&lpszInFname, 1, lpszInMode, lpszOutFname, lpszOutMode);

return(retc);
}


// --------------------------------------------------
HRESULT XmlO2::CloseFiles(bool bCheckFileExist)
{
HRESULT retc=S_OK;
int ii;

   if(m_lpOutFileObj!=NULL)
   {
      retc = m_lpOutFileObj->CloseFile(bCheckFileExist);
      
      KP_DELETE(m_lpOutFileObj);
   }
   else
   {
      if(!bCheckFileExist) retc = KP_E_NO_FILE;
      else retc = KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, 0L);
   }

   for(ii=0; ii<MAX_NUM_OF_LIST_ENTRIES; ii++)
   {
      if(m_lpInFileObjs[ii]!=NULL) KP_DELETE(m_lpInFileObjs[ii])
      else if(ii == 0)
      {
         if(SUCCEEDED(retc)) retc = KP_E_NO_FILE;
         if(bCheckFileExist)
            KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, 0L);
      }
   }

return(retc);
}


// --------------------------------------------------
HRESULT XmlO2::GetOpenResult(void)
{
return(m_lhOpenResult);
}


// --------------------------------------------------
HRESULT XmlO2::TransferField
(
KpChar uiStartTag,
KpChar uiEndTag,
XL_Indexes uiIxFileIdx,
long lMainKeyValue,
bool bTstInverted,
bool bTstCombined,
bool bProcessSubkeys,
XmlTagPars *pTagPar
)
{
HRESULT retc=S_OK;
KpChar ch2, ch;
long ch_num;
int ch_pos;
bool text_available=FALSE;
XmlIs_IndexRecord *ind_rec;
int par_lev;
XmlTagPars *tag_par = NULL;
XmlTagPars *tag_par1 = NULL;
long entry_id=0L;
int par_num;
unsigned char str_buf[KP_MSG_LEN+1];
int ii;

   if((m_lpInFileObjs[0]==NULL) || (m_iNumOfInFiles<1) || (m_lpOutFileObj==NULL))
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, lLastIdx);
   if((m_iNumOfInFiles>MAX_NUM_OF_LIST_ENTRIES) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);
   for(ii=0; (ii<m_iNumOfInFiles) && SUCCEEDED(retc); ii++)
      if(m_lpInFileObjs[ii]==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, lLastIdx);

// put se index entry
   if((uiIxFileIdx==XL_IX_SeIndex) && SUCCEEDED(retc))
   {
      if(pTagPar==NULL)
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, lLastIdx);
      if(SUCCEEDED(retc))
      {
         retc=pTagPar->SeekNumPar("id", &entry_id, &par_num);
         if(retc==KP_E_KWD_NOT_FOUND)
            retc=KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND, null, TRUE, __FILE__, __LINE__, lLastIdx);
      }
      if(SUCCEEDED(retc))
         retc=m_lpOutFileObj->PutNumVal(entry_id, uiIxFileIdx);

      if(SUCCEEDED(retc))
         retc=m_lpOutFileObj->GetCharNum(&ch_num, XL_IX_DataFile);

      if(SUCCEEDED(retc))
         retc=m_lpOutFileObj->PutNumVal(ch_num, uiIxFileIdx);

      if(SUCCEEDED(retc))
         retc=m_lpOutFileObj->PutCharProc(C_Lf, NULL, uiIxFileIdx); // '\n'
   }

// text index object
   KP_NEW(ind_rec, XmlIs_IndexRecord(m_lpOutFileObj, uiIxFileIdx, lMainKeyValue,
                     bTstInverted, bTstCombined, bTstCombined, bProcessSubkeys,
                     caIxLangs[uiIxFileIdx], /* iaIxEncodings[uiIxFileIdx], */ 1));

// reference object
   if(SUCCEEDED(retc))
      retc=StartReferenceProcessing(uiStartTag==XC_Reference);

   if(SUCCEEDED(retc))
   {
      do
      {
         KP_DELETE(tag_par);
// input character
         retc=m_lpInFileObjs[0]->GetCharProc(&ch2, &tag_par, XL_IX_DataFile, True, True);

#ifdef Debug
// if(ch2==XC_StEntry_e)
// ch2=XC_StEntry_e;
#endif

#ifdef Debug
if(ch2==(KpChar)XC_Equiation)
ch2=(KpChar)XC_Equiation;
#endif

#ifdef Debug
if(ch2==(KpChar)XC_Italic)
ch2=(KpChar)XC_Italic;
#endif

// start tag output
         if((!text_available) && (uiStartTag!=0) && (uiStartTag!=XC_Reference) && SUCCEEDED(retc))
         {
            retc=m_lpOutFileObj->PutCharProc(uiStartTag, pTagPar, XL_IX_DataFile);
            text_available=TRUE;

            if(((uiStartTag==XC_UsNoteDst) || (uiStartTag==XC_UsNoteSrc)) && SUCCEEDED(retc))
            {
               if(SUCCEEDED(retc)) retc=m_lpOutFileObj->SetIndent((const unsigned char *)"         ", XL_IX_DataFile);
//             if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutCharProc('\n', NULL, XL_IX_DataFile);
            }
         }

// character analyze
         if(SUCCEEDED(retc))
         {
            if(ch2 != uiEndTag)
            {
// collect <hw> for error processing
               if((uiStartTag==XC_HeadWord) && (iHwMsgPtr<KP_MSG_LEN))
               {
                  aiHwMsgText[iHwMsgPtr++]=ch2;
                  aiHwMsgText[iHwMsgPtr]=C_Nul;
               }

               switch(ch2)
               {
               case XC_Dict:
               case XC_Dict_e:
               case XC_NrtEntry:
               case XC_NrtEntry_e:
               case XC_StEntry:
               case XC_StEntry_e:
               case XC_HeadWord_e:
               case XC_Variant_e:
               case XC_Label_e:
               case XC_TrWord_e:
               case XC_UsNoteDst_e:
               case XC_UsNoteSrc_e:
//!!!          case XC_Reference_e:
                  retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, TRUE, __FILE__, __LINE__, lLastIdx);
                  break;

               case XC_HeadWordGroup:
// skip next spaces
                  if(SUCCEEDED(retc))
                     retc=m_lpInFileObjs[0]->GetCharProc(&ch, &tag_par1, XL_IX_DataFile, True, True);
                  if((TvStrChr(lpszSpaces, ch)==NULL) && SUCCEEDED(retc))
                     retc=m_lpInFileObjs[0]->UnGetCharProc(ch, tag_par1, XL_IX_DataFile);
                  KP_DELETE(tag_par1);

                  if(SUCCEEDED(retc)) retc=m_lpOutFileObj->SetIndent((const unsigned char *)"   ", XL_IX_DataFile);
                  if(SUCCEEDED(retc))
                     retc=m_lpOutFileObj->PutCharProc(ch2, tag_par, XL_IX_DataFile);
                  if(SUCCEEDED(retc)) retc=m_lpOutFileObj->SetIndent((const unsigned char *)"      ", XL_IX_DataFile);
                  break;

               case XC_HeadWordGroup_e:
                  if(SUCCEEDED(retc)) retc=m_lpOutFileObj->SetIndent((const unsigned char *)"   ", XL_IX_DataFile);
                  if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutCharProc(C_Lf, NULL,  XL_IX_DataFile);

                  if(SUCCEEDED(retc)) retc=m_lpOutFileObj->SetIndent((const unsigned char *)"   ", XL_IX_DataFile);

                  if(SUCCEEDED(retc))
                     retc=m_lpOutFileObj->PutCharProc(ch2, tag_par, XL_IX_DataFile);

                  if(SUCCEEDED(retc)) retc=m_lpOutFileObj->SetIndent((const unsigned char *)"", XL_IX_DataFile);

// skip next spaces
                  if(SUCCEEDED(retc))
                     retc=m_lpInFileObjs[0]->GetCharProc(&ch, &tag_par1, XL_IX_DataFile, True, True);
                  if((TvStrChr(lpszSpaces, ch)==NULL) && SUCCEEDED(retc))
                     retc=m_lpInFileObjs[0]->UnGetCharProc(ch, tag_par1, XL_IX_DataFile);
                  KP_DELETE(tag_par1);
                  break;

               case XC_TranslGroup:
                  if(SUCCEEDED(retc))
                     retc=m_lpOutFileObj->PutCharProc(C_Lf, NULL, XL_IX_DataFile); // '\n'

                  if(SUCCEEDED(retc)) retc=m_lpOutFileObj->SetIndent((const unsigned char *)"      ", XL_IX_DataFile);
                  if(SUCCEEDED(retc))
                     retc=m_lpOutFileObj->PutCharProc(ch2, tag_par, XL_IX_DataFile);
                  if(SUCCEEDED(retc)) retc=m_lpOutFileObj->SetIndent((const unsigned char *)"         ", XL_IX_DataFile);
                  break;

               case XC_TranslGroup_e:
// skip next spaces
                  if(SUCCEEDED(retc))
                     retc=m_lpInFileObjs[0]->GetCharProc(&ch, &tag_par1, XL_IX_DataFile, True, True);
                  if((TvStrChr(lpszSpaces, ch)==NULL) && SUCCEEDED(retc))
                     retc=m_lpInFileObjs[0]->UnGetCharProc(ch, tag_par1, XL_IX_DataFile);
                  KP_DELETE(tag_par1);

                  if(SUCCEEDED(retc)) retc=m_lpOutFileObj->SetIndent((const unsigned char *)"      ", XL_IX_DataFile);

                  if(SUCCEEDED(retc))
                     retc=m_lpOutFileObj->PutCharProc(ch2, tag_par, XL_IX_DataFile);
                  break;

               case XC_HeadWord:
               case XC_Variant:
                  retc=TransferField(ch2, (KpChar)(ch2+1), XL_IX_HwIndex,
                                    (uiIxFileIdx==XL_IX_SeIndex)?entry_id:lMainKeyValue,
                                    TRUE, TRUE, bProcessSubkeys, tag_par);
                  break;

               case XC_Label:
                  retc=TransferField((KpChar)XC_Label, (KpChar)XC_Label_e, XL_IX_LaIndex,
                                    (uiIxFileIdx==XL_IX_SeIndex)?entry_id:lMainKeyValue,
                                    FALSE, FALSE, bProcessSubkeys, tag_par);
                  break;

               case XC_TrWord:
                  retc=TransferField((KpChar)XC_TrWord, (KpChar)XC_TrWord_e, XL_IX_TwIndex,
                                    (uiIxFileIdx==XL_IX_SeIndex)?entry_id:lMainKeyValue,
                                    FALSE, TRUE, bProcessSubkeys, tag_par);
                  break;

               case XC_UsNoteDst:
               case XC_UsNoteSrc:
// skip next spaces
                  if(SUCCEEDED(retc))
                     retc=m_lpInFileObjs[0]->GetCharProc(&ch, &tag_par1, XL_IX_DataFile, True, True);
                  if((TvStrChr(lpszSpaces, ch)==NULL) && SUCCEEDED(retc))
                     retc=m_lpInFileObjs[0]->UnGetCharProc(ch, tag_par1, XL_IX_DataFile);
                  KP_DELETE(tag_par1);

                  if(SUCCEEDED(retc)) retc=m_lpOutFileObj->SetIndent((const unsigned char *)"      ", XL_IX_DataFile);

                  if(SUCCEEDED(retc))
                     retc=TransferField(ch2, (KpChar)(ch2+1), XL_IX_DataFile /* XL_IX_NoIndex */,
                                       0L, FALSE, FALSE, bProcessSubkeys, tag_par);

// skip next spaces
                  if(SUCCEEDED(retc))
                     retc=m_lpInFileObjs[0]->GetCharProc(&ch2, &tag_par1, XL_IX_DataFile, True, True);
                  if((TvStrChr(lpszSpaces, ch2)==NULL) && SUCCEEDED(retc))
                     retc=m_lpInFileObjs[0]->UnGetCharProc(ch2, tag_par1, XL_IX_DataFile);
                  KP_DELETE(tag_par1);

                  break;

               case XC_Reference:
                  retc=TransferField((KpChar)XC_Reference, (KpChar)XC_Reference_e, XL_IX_DataFile /* XL_IX_NoIndex */, 0L,
                                    FALSE, FALSE, bProcessSubkeys, tag_par);
                  break;

               case XC_StEntryText:
                  retc=TransferField((KpChar)XC_StEntryText, (KpChar)XC_StEntryText_e, XL_IX_StIndex,
                                    (uiIxFileIdx==XL_IX_SeIndex)?entry_id:lMainKeyValue,
                                    FALSE, FALSE, bProcessSubkeys, tag_par);
                  break;

               case XC_TechNote:
                  if(uiStartTag==XC_StEntry)
                  {
                     retc=TransferField((KpChar)XC_TechNote, (KpChar)XC_TechNote_e, XL_IX_EdIndex,
                                    (uiIxFileIdx==XL_IX_SeIndex)?entry_id:lMainKeyValue,
                                    FALSE, FALSE, bProcessSubkeys, tag_par);
                     break;
                  }
               default:
// ordinary chars

// to data file
                  retc=PutRefChar(ch2, tag_par);

// split index list to different records
                  if(SUCCEEDED(retc)) retc=ind_rec->GetParLev(&par_lev);
                  if((ch2==C_Semic) && (par_lev<1) && SUCCEEDED(retc)) // ';'
                  {
                     retc = ind_rec->CompleteIndexRecord(True);
                     
                     KP_DELETE(ind_rec);

                     KP_NEW(ind_rec, XmlIs_IndexRecord(m_lpOutFileObj,
                                       uiIxFileIdx, lMainKeyValue,
                                       bTstInverted, bTstCombined, bTstCombined, bProcessSubkeys,
                                       caIxLangs[uiIxFileIdx], /* iaIxEncodings[uiIxFileIdx], */ 1));
                  }

// to index file
//!!!             if(TvIsAlpha(uiChOut) || uiChOut==C_Spc || uiChOut=='\'')
                  if(ch2!=C_Semic) // ';'
                     if(SUCCEEDED(retc)) retc=ind_rec->PutChar(ch2);

                  break;

               } // switch(ch2)

            } // if(ch2 != cFieldLimiter)
         }

         KP_DELETE(tag_par);

      } while((ch2 != uiEndTag) && SUCCEEDED(retc));

   } // if(SUCCEEDED(retc))

// complete index entry
   if(SUCCEEDED(retc) /* && !bEofFlg */)
      retc=ind_rec->CompleteIndexRecord(True);
   KP_DELETE(ind_rec);

// complete reference
#ifdef Debug
if(uiStartTag==(KpChar)XC_Reference)
uiStartTag=(KpChar)XC_Reference;
#endif
   if(SUCCEEDED(retc) /* && !bEofFlg */)
      retc=StopReferenceProcessing(pTagPar); // FlushRefVal();

// end tag
   if(text_available && (uiEndTag!=0) && (uiStartTag!=XC_Reference) && SUCCEEDED(retc))
   {
      switch(uiEndTag)
      {
      case XC_StEntry_e:
         aiHwMsgText[0]=C_Nul;
         iHwMsgPtr=0;
         retc=KpErrorProc.SetLTxt((const unsigned char *)"");
         break;

      case XC_HeadWord_e:
         retc=KpErrorProc.StrDecode(str_buf, aiHwMsgText);
         if(SUCCEEDED(retc)) retc=KpErrorProc.SetLTxt(str_buf);
         break;

//    case XC_HeadWordGroup_e:  // does not initiate recursive TransferField()
//       if(SUCCEEDED(retc)) retc=m_lpOutFileObj->SetIndent((const unsigned char *)"   ", XL_IX_DataFile);
//       if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutCharProc(C_Lf, NULL, uiIxFileIdx);
//       break;

      case XC_UsNoteDst_e:
      case XC_UsNoteSrc_e:
         if(SUCCEEDED(retc)) retc=m_lpOutFileObj->SetIndent((const unsigned char *)"   ", XL_IX_DataFile);
//       if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutCharProc(C_Lf, NULL, XL_IX_DataFile);
         break;
      }

      if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutCharProc(uiEndTag, NULL, XL_IX_DataFile);
   }

// two eol's between main entries
   if(
         ((uiStartTag==XC_StEntry) || (uiStartTag==XC_NrtEntry)) &&
         SUCCEEDED(retc)
     )
   {
      retc=m_lpOutFileObj->GetCharPos(&ch_pos, XL_IX_DataFile);
      if((ch_pos!=0) && SUCCEEDED(retc))
         retc=m_lpOutFileObj->PutCharProc(C_Lf, NULL, XL_IX_DataFile); // '\n'
//    if(SUCCEEDED(retc))
//       retc=m_lpOutFileObj->PutCharProc(C_Lf, NULL, XL_IX_DataFile); // '\n'
   }

   KP_DELETE(tag_par1);

return(retc);
}
