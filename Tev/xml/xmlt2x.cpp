// ==================================================
// xmlt2x.cpp, former lvzt2x.cpp
// converting XML dictionary to (LVZ03) TeX file
//


// ================================================== definitions
#include "envir.h"

#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <string>
#include <stdio.h>
#include <fstream>
#if OsGr==MSWin
#include <windows.h>
#endif

// #include <iostream.h>
#include <iostream>

#include "kpstdlib.h"
#include "kperrno.h"
#include "kptree.h"
#include "kptt.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kperr.h"
#include "kpcolors.h"
#include "kpfonts.h"
#include "tvmain.h"
#include "tvxml.h"
#include "xmlh.h"
#include "xmlp.h"
#include "xmlf.h"
#include "kpttucf.h"
#include "xmlu.h"
#include "xml8.h"
#include "xmlo1.h"
#include "tvxmle.h"
#include "xmlt.h"
#include "xmlis.h"
#include "xmli.h"
#include "xmlsty.h"
#include "tvrtf.h"
#include "tvrtfo.h"
#include "tvtex.h"
#include "xmln.h"
#include "xmlt2x0.h"
#include "xmlt2x.h"


#if Envir!=MSWin32Con
#error Envir!=MSWin32Con
#endif

// -----------------------------------------
HRESULT TestCompilerSettingsLocal(void)
{
#include "kpstcs.cpp"
}


// --------------------------------------------------
HRESULT XmlNode::TestChildContents(KpChar /* iTestTag */, KpChar *lpiazTestValue, bool *pFoundFlg)
{
HRESULT retc=S_OK;

   if(pFoundFlg==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      *pFoundFlg=False;
      if(lpiazTestValue==NULL) *pFoundFlg=True;
   }

return(retc);
}

XmlT2X::XmlT2X(const unsigned char *lpszInFname, const unsigned char *lpszOutFname, bool bTagFormat)
// :XmlT2X0_tag(lpszInFname, lpszOutFname)
{
   XmlT2X0_constructor(lpszInFname, lpszOutFname, bTagFormat);
}


// --------------------------------------------------
HRESULT XmlT2X::OpenFilesLocal(const unsigned char *lpszInFname, const unsigned char *lpszOutFname)
{
HRESULT retc=S_OK;

// --------------------------------------------------
   if((lpszInFname==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc)) if(strlen(lpszInFname)>=KP_MAX_FNAME_LEN)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
   {
      strcpy(m_lpszInFileName, lpszInFname);
      m_lpInFileObj = new XmlI(m_lpszInFileName, (const unsigned char *)"rb", CreateNewUniFile,
                                       plpszaXmlSpecCharTagsMain,
                                       alpszIndexNames, aiIndexWidths, caIxLangs, iaIxEncodings,
                                       (KpChar)XC_FirstDictTag, plpszaXmlttDictTags,
                                       XM_VERS_XML10, iaXmlDictNulCodeTables, True, True, False);
      if(m_lpInFileObj!=NULL)
         retc=m_lpInFileObj->GetOpenResult();
      else
         retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, True, __FILE__, __LINE__, 0L);
   }

// --------------------------
   if((lpszOutFname==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc)) if(strlen(lpszOutFname)>=KP_MAX_FNAME_LEN)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
   {
      strcpy(m_lpszOutFileName, lpszOutFname);
      m_lpOutFileObj = new TvTexFile(m_lpszOutFileName, (const unsigned char *)"w", iNumOfTexTagsLocal);
      if(m_lpOutFileObj!=NULL)
         retc=m_lpOutFileObj->GetOpenResult();
      else
         retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, True, __FILE__, __LINE__, 0L);
   }

return(retc);
}


// --------------------------------------------------
HRESULT XmlT2X::Process(const KpChar *piazFromHw, const KpChar *piazToHw, int iLevel)
{
HRESULT retc=S_OK;
KpChar in_ch;
XmlTagPars *tag_pars=NULL;
XmlNode *cur_entry = NULL;
XmlNode *first_child = NULL;
long entr_id;
int par_num;
const KpChar *hw_ptr=NULL;
KpChar hw_lwr[TV_XL_MAX_IX_LEN+1];
KpChar prev_tag=(KpChar)XC_Nul;
KpChar last_char=C_Nul;
int num_of_chars;
int l_word_start;
int l_word_rest;
int char_pos;
KpChar err_txt_i[KP_MSG_LEN+1];
unsigned char err_txt[KP_MSG_LEN+1];
const KpChar *pnts;
unsigned char *pntd;
bool tilde_fl;
bool found_fl=False;
int ii;

   if((m_lpInFileObj==NULL) || (m_lpOutFileObj==NULL))
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   if((m_pTagStack==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

   while(SUCCEEDED(retc))
   {
      do
      {
         retc=m_lpInFileObj->GetCharProc(&in_ch, &tag_pars, False, False);

#ifdef Debug
if(in_ch==(KpChar)'(')
in_ch=(KpChar)'(';
#endif

         if((in_ch==XC_StEntry) && SUCCEEDED(retc))
         {
            m_lEntryId++;
            entr_id=0L;
            if(tag_pars!=NULL) retc=tag_pars->SeekNumPar("id", &entr_id, &par_num);
            if(entr_id!=0L)
            {
               KpErrorProc.SetLPar(entr_id);
               m_lEntryId=entr_id;
            }
            else KpErrorProc.SetLPar(m_lEntryId);

// unsigned char out_buf[TV_XM_MAX_TAG_CONTENTS_WDT+1];
// printf("-------------------- %ld   %ld\n",m_lEntryId, entr_id);
// if(m_lEntryId==5L)
// m_lEntryId=5L;

            if((cur_entry!=NULL) && SUCCEEDED(retc))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
            if(SUCCEEDED(retc))
            {
               cur_entry = new XmlNode(in_ch, tag_pars, NULL, NULL, (const unsigned char *)"", 
                              (KpChar)XC_FirstDictTag, plpszaXmlttDictTags, NULL);
               if(cur_entry==NULL)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, True, __FILE__, __LINE__, 0L);
            }
            if(SUCCEEDED(retc)) retc=cur_entry->GetOpenResult();
         }
         KP_DELETE(tag_pars);

      } while((in_ch!=XC_StEntry) && SUCCEEDED(retc));

// printf("------------- %d\n", m_lpOutFileObj->GetFldDepth());

      if(SUCCEEDED(retc)) retc=cur_entry->ReadNode(m_lpInFileObj);

// if(SUCCEEDED(retc)) retc = cur_entry->TestNode();

// ------------------------- process level
//    if(SUCCEEDED(retc)) retc=cur_entry->SupressToLevel(iLevel);
//    if(SUCCEEDED(retc)) retc=cur_entry->DelLevelTags(iLevel);
//    if(SUCCEEDED(retc)) retc=cur_entry->DelTags(XC_Level);
//    if(SUCCEEDED(retc)) retc=cur_entry->UpLevelGroups();
//    if(SUCCEEDED(retc)) retc=cur_entry->DelEmptyTags();
//    if(SUCCEEDED(retc)) retc=cur_entry->RenumCtgMng();
//// ------------------------- delete author remarks
//    if(SUCCEEDED(retc)) retc=cur_entry->DelTags(XC_TechNote);

      for(ii=iLevel; (ii!=0) && SUCCEEDED(retc); ii/=10)
         retc=cur_entry->ProcessLevel(ii%10, (ii/10)==0);

if(SUCCEEDED(retc)) retc = cur_entry->TraceContents();

// -------------------------
      found_fl=False;
      if(SUCCEEDED(retc)) retc=cur_entry->DelTagsByValue((KpChar)XC_Label, (const unsigned char *)"geogr. vard.", &found_fl);

// -------------------------
      if(((!found_fl) || (!bDelGeogr)) && SUCCEEDED(retc))
      {
         tilde_fl=False;
         if(SUCCEEDED(retc)) retc=cur_entry->TestTilde(&tilde_fl);
         if((!tilde_fl) && SUCCEEDED(retc)) retc=cur_entry->DelVert();

// if(SUCCEEDED(retc)) retc=cur_entry->TestNode();

// ----------------------------
         hw_ptr=NULL;
         if(SUCCEEDED(retc)) retc=cur_entry->GetHw((KpChar **)&hw_ptr);
         if((hw_ptr==NULL) && SUCCEEDED(retc))
         {
            hw_ptr=iNullStr;
            first_child=NULL;
            retc=cur_entry->GetFirstChild((KpTreeEntry **)&first_child);
            if((first_child!=NULL) && SUCCEEDED(retc))
               retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, False, __FILE__, __LINE__, 0L);
         }

         if(SUCCEEDED(retc))
         {
            TvKpStrNCpy(m_iaLastHw, hw_ptr, TV_XL_MAX_IX_LEN);
            m_iaLastHw[TV_XL_MAX_IX_LEN]=C_Nul;

            TvKpStrNCpy(err_txt_i, hw_ptr, KP_MSG_LEN);
            err_txt_i[KP_MSG_LEN]=C_Nul;
            TvKpStrLat(err_txt_i);
            pnts=err_txt_i;
            pntd=err_txt;
            while(*pnts) *(pntd++)=(unsigned char)(*pnts++);
            *pntd=Nul;
            retc=KpErrorProc.SetLTxt(err_txt);
       }

// if(SUCCEEDED(retc))
// {
// KptStrDecode(out_buf, hw_ptr, TvIntStrLen(hw_ptr), 71);
// printf("%s\n", out_buf);
// }

         if(SUCCEEDED(retc))
         {
            TvKpStrNCpy(hw_lwr, hw_ptr, TV_XL_MAX_IX_LEN);
            hw_lwr[TV_XL_MAX_IX_LEN]=C_Nul;
            TvKpStrLwr(hw_lwr);
            TvKpStrLat(hw_lwr);

            if(TvKpStrCmp(hw_lwr, piazToHw)>0) retc=KP_E_EOF;

            if((TvKpStrCmp(hw_lwr, piazFromHw)>=0) && SUCCEEDED(retc))
            {
               num_of_chars=0;
               retc=cur_entry->CountCharactersTex(&num_of_chars, prev_tag, m_bTagOutFormat);

               l_word_start=0;
               l_word_rest=LAST_WORD_LEN;
               if(SUCCEEDED(retc))
               {
                  char_pos=0;
                  retc=cur_entry->GetLastWordPosTex(&l_word_start, &l_word_rest, &char_pos, num_of_chars, prev_tag, m_bTagOutFormat);
               }

               if(SUCCEEDED(retc))
               {
                  char_pos=0;
                  retc=cur_entry->WriteTex(m_lpOutFileObj, &char_pos,
#ifdef PROCESS_LAST_WORD
                     l_word_start, l_word_rest,
#else
                     MAXLONG, 0,
#endif
                     num_of_chars, (KpChar)XC_Dict, prev_tag, &last_char, m_bTagOutFormat);
               }

// printf("%d %d %d %d\n", num_of_chars, char_pos, l_word_start, l_word_rest);

// patikrint DelimStrLenTex() - issiderino su WriteTex()
               if((num_of_chars!=char_pos) && SUCCEEDED(retc))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L);

               if(SUCCEEDED(retc)) retc=cur_entry->GetNodeTag(&prev_tag);

            } // if((TvIntStrCmp(hw_lwr, piazFromHw)>=0) && SUCCEEDED(retc))

         } // if(SUCCEEDED(retc))

      } // if(((!found_fl) || (!bDelGeogr)) && SUCCEEDED(retc))

      KP_DELETE(cur_entry);

      /* retc= */ KpErrorProc.SetLTxt((const unsigned char *)"");

   } // while(SUCCEEDED(retc))

   if(retc==KP_E_EOF) retc=S_OK;

   KpErrorProc.SetLPar(0L);

return(retc);
}
