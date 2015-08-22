// ==================================================
// xmlque.cpp
// XML nodes extractor depending on criteria
// like xmlext.exe, but uses indexes

// ================================================== definitions
#include "envdef.h"
#include "envir.h"
#include "envsupp.h"

#include "kpstdlib.h"
#include "kptt.h"
#include "kperr.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpcolors.h"
#include "kpfonts.h"

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>

#include "tvmain.h"
#include "kpttucf.h"
#include "tvxml.h"
#include "xmlh.h"
#include "xmlp.h"
#include "xmlf.h"
#include "tvxmle.h"
#include "xmlo1.h"
#include "xmlt.h"
#include "xmlis.h"
#include "xmli.h"
#include "xmloi2.h"
#include "tvxmls.h"
#include "xml8.h"
#include "tvrtf.h"
#include "tvrtfo.h"
#include "tvtex.h"
#include "xmln.h"
#include "xmlque.h"
// #include "mcmt.h"


// ================================================== objects
XmlQue_tag *pXmlQue=NULL;
// TvXmlFmse_tag *pTvXmlFmse=NULL;
KpErrorProc_tag KpErrorProc(TRUE, 71);


// --------------------------------------------------
HRESULT XmlNode_tag::TestChildContents(int iTestTag, Chars16 *lpiazTestValue, bool *pFoundFlg)
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

// ================================================== public methods of XmlQue_tag
XmlQue_tag::XmlQue_tag
(
const unsigned char *lpszInFname,
const unsigned char *lpszOutFname,
const unsigned char *lpszIndexName,
const unsigned char *lpszMinValue,
const unsigned char *lpszMaxValue
): XmlOI2_tag()
{
Chars16 str_buf_i[TV_XL_MAX_IX_LEN+1];
Chars16 str_buf_ii[TV_XL_MAX_IX_LEN+1];
int ii;
int chr_cnt;

   KpErrorProc.SetLPar(0L);

   m_iIndexFile=XL_IX_NoIndex;
   m_lpszMinIxValue[0]=Nul;
   m_lpszMaxIxValue[0]=Nul;

   if(SUCCEEDED(lhOpenResult))
      lhOpenResult=OpenFile(lpszInFname, (const unsigned char *)"rb",
                           lpszOutFname, (const unsigned char *)"w",
                           caIxLangs);

// ------------------------------
   if(SUCCEEDED(lhOpenResult))
   {
      for(ii=XL_IX_DefSeIndex; (ii<XL_IX_NumOfIndexes1) && (m_iIndexFile==XL_IX_NoIndex); ii++)
         if(strcmp(alpszIndexNames[ii], lpszIndexName)==0)
         {
            m_iIndexFile=(XL_Indexes)ii;
            break;
         }
      if(m_iIndexFile==XL_IX_NoIndex)
         lhOpenResult=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);
   }

// ------------------------------
   if(SUCCEEDED(lhOpenResult))
      if((lpszMinValue==NULL) || (lpszMaxValue==NULL))
         lhOpenResult=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(lhOpenResult))
   {
      strncpy(m_lpszMinIxValue, lpszMinValue, TV_XL_MAX_IX_LEN);
      m_lpszMinIxValue[TV_XL_MAX_IX_LEN]=Nul;
      strncpy(m_lpszMaxIxValue, lpszMaxValue, TV_XL_MAX_IX_LEN);
      m_lpszMaxIxValue[TV_XL_MAX_IX_LEN]=Nul;
   }
   
// !!! keist i Chars16ToIndexEntry()
   if(SUCCEEDED(lhOpenResult)) lhOpenResult=KptStrEncode((int *)str_buf_i, m_lpszMinIxValue, &chr_cnt, 1);
   if(SUCCEEDED(lhOpenResult)) lhOpenResult=ExpandAbbr(str_buf_ii, str_buf_i, &chr_cnt, TV_XL_MAX_IX_LEN, caIxLangs[m_iIndexFile]);
   if(SUCCEEDED(lhOpenResult)) lhOpenResult=DelComments(str_buf_ii, &chr_cnt);
   if(SUCCEEDED(lhOpenResult)) str_buf_ii[chr_cnt]=C_Nul;
   if(SUCCEEDED(lhOpenResult)) lhOpenResult=TvXmlEs.CutEndingsDelCjts(str_buf_i, str_buf_ii, caIxLangs[m_iIndexFile], True);
   if(SUCCEEDED(lhOpenResult)) chr_cnt=TvIntStrLen(str_buf_i);
   if(SUCCEEDED(lhOpenResult)) lhOpenResult=Chars16ToStrNoCtrl(m_lpszMinIxValue, str_buf_i, chr_cnt, TV_XL_MAX_IX_LEN);
   if(SUCCEEDED(lhOpenResult)) TvStrLwr(m_lpszMinIxValue);
   if(SUCCEEDED(lhOpenResult)) lhOpenResult=CutInitSpcs(m_lpszMinIxValue);
   if(SUCCEEDED(lhOpenResult)) lhOpenResult=CutTrailSpcs(m_lpszMinIxValue);

   if(SUCCEEDED(lhOpenResult)) lhOpenResult=KptStrEncode((int *)str_buf_i, m_lpszMaxIxValue, &chr_cnt, 1);
   if(SUCCEEDED(lhOpenResult)) lhOpenResult=ExpandAbbr(str_buf_ii, str_buf_i, &chr_cnt, TV_XL_MAX_IX_LEN, caIxLangs[m_iIndexFile]);
   if(SUCCEEDED(lhOpenResult)) lhOpenResult=DelComments(str_buf_ii, &chr_cnt);
   if(SUCCEEDED(lhOpenResult)) str_buf_ii[chr_cnt]=C_Nul;
   if(SUCCEEDED(lhOpenResult)) lhOpenResult=TvXmlEs.CutEndingsDelCjts(str_buf_i, str_buf_ii, caIxLangs[m_iIndexFile], True);
   if(SUCCEEDED(lhOpenResult)) chr_cnt=TvIntStrLen(str_buf_i);
   if(SUCCEEDED(lhOpenResult)) lhOpenResult=Chars16ToStrNoCtrl(m_lpszMaxIxValue, str_buf_i, chr_cnt, TV_XL_MAX_IX_LEN);
   if(SUCCEEDED(lhOpenResult)) TvStrLwr(m_lpszMaxIxValue);
   if(SUCCEEDED(lhOpenResult)) lhOpenResult=CutInitSpcs(m_lpszMaxIxValue);
   if(SUCCEEDED(lhOpenResult)) lhOpenResult=CutTrailSpcs(m_lpszMaxIxValue);
}


// --------------------------------------------------
XmlQue_tag::~XmlQue_tag(void)
{
   XmlOI2_tag_destructor();
}


// --------------------------------------------------
HRESULT XmlQue_tag::Process(void)
{
HRESULT retc=S_OK;
bool eof_fl=FALSE;
XmlTagPars_tag *tag_par=NULL;
bool in_dict=FALSE;
bool after_dict=FALSE;
XmlTagPars_tag *tag_par1=NULL;
unsigned char read_kwd[TV_XL_MAX_IX_LEN+1];
long text_size;
long full_size;
bool end_fl;
XmlNode_tag *cur_entry=NULL;
long entry_id;
long offset;
long end_offset;

   if((lpInFileObj==NULL) || (lpOutFileObj==NULL))
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
      if(lpInFileObj->FilePtr==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=PutXmlHat(lpOutFileObj->FilePtr, lpszOutFileName);

   if(SUCCEEDED(retc))
   {
      retc=lpInFileObj->SearchEntry(&entry_id, &offset, m_lpszMinIxValue, m_iIndexFile, False);
      if(retc==KP_E_KWD_NOT_FOUND) retc=S_OK;
   }

   if(SUCCEEDED(retc))
      retc=lpInFileObj->FilePtr->GetIndexSize(&end_offset, m_iIndexFile);

   if((offset<end_offset) && SUCCEEDED(retc))
   {
      full_size=lpInFileObj->aiFileIndexLengthsPtr[m_iIndexFile];
      text_size=full_size-sizeof(long);

      retc=lpInFileObj->FilePtr->fFiles[m_iIndexFile]->Fseek(offset, SEEK_SET);

      if(SUCCEEDED(retc)) do
      {
         end_fl=False;

         if(offset>=end_offset) end_fl=True;

         if((!end_fl) && SUCCEEDED(retc))
         {
            retc=lpInFileObj->FilePtr->GetImage(read_kwd, text_size, m_iIndexFile, True);
            if(SUCCEEDED(retc))
            {
               read_kwd[text_size]=Nul;
               retc=CutTrailSpcs(read_kwd);
            }
            if(SUCCEEDED(retc))
               if(TvStrCmp(read_kwd, m_lpszMaxIxValue, SortSkipSpc, SortMode, True, 1, True)>0)
                  end_fl=True;
         }

         if((!end_fl) && SUCCEEDED(retc))
         {
            retc=lpInFileObj->FilePtr->GetImage(&entry_id, sizeof(long), m_iIndexFile, True);
            offset+=full_size;

            if(SUCCEEDED(retc)) retc=lpInFileObj->FilePtr->SeekEntry(entry_id);

            cur_entry=NULL;
            if(SUCCEEDED(retc)) retc=ReadEntry(&cur_entry, lpInFileObj, True);

            if(SUCCEEDED(retc)) retc=cur_entry->WriteNode(lpOutFileObj);

            KP_DELETE(cur_entry);
         }

      } while((!end_fl) && SUCCEEDED(retc));

   } // if((offset<end_offset) && SUCCEEDED(retc))

   KpErrorProc.SetLPar(0L);

   if(SUCCEEDED(retc)) retc=PutXmlTail(lpOutFileObj->FilePtr);

return(retc);
}


// ================================================== main
//---------------------------------------------
int main(int argc, char **argv)
{
HRESULT retc=S_OK;
HRESULT retc0;
int l_argc;
const unsigned char *l_argv[6];
int ii;

   printf("\nXML query\n");

   if(SUCCEEDED(retc)) retc=KpInit();

   l_argc=argc;
   if(argc==6)
      for(ii=0; ii<argc; ii++) l_argv[ii]=(const unsigned char *)argv[ii];
#ifdef Debug
   else if(strstr(strlwr(argv[0]), "debug")>0)
   {
      l_argc=6;

      l_argv[0]=(const unsigned char *)"xmlque";
      
//    l_argv[1]=(const unsigned char *)"f:\\wrk\\kp\\source\\tev\\mcm\\mcm_out\\mcm1.xml";
      l_argv[1]=(const unsigned char *)"f:\\wrk\\kp\\source\\tev\\vlz\\vlz_xmlt\\vlz_a.xml";
      
//    l_argv[2]=(const unsigned char *)"f:\\wrk\\kp\\source\\tev\\mcm\\mcm_out\\mcm2.xml";
//    l_argv[2]=(const unsigned char *)"f:\\wrk\\kp\\source\\tev\\vlz\\vlz_ast\\vlza_%1.xml";
      l_argv[2]=(const unsigned char *)"f:\\wrk\\kp\\source\\tev\\vlz\\vlza_%1.xml";

//    l_argv[3]=(const unsigned char *)"ed";
      l_argv[3]=(const unsigned char *)"ast";

//    l_argv[4]=(const unsigned char *)"2003.11.14";
//    l_argv[4]=(const unsigned char *)"2000.01.01";
      l_argv[4]=(const unsigned char *)"A";

//    l_argv[5]=(const unsigned char *)"2003.11.24";
//    l_argv[5]=(const unsigned char *)"2003.12.03";
      l_argv[5]=(const unsigned char *)"zzzzzz";
   }
#endif

   if(l_argc==6)
   {
      if(SUCCEEDED(retc))
      {
         KP_NEWO(pXmlQue, XmlQue_tag(l_argv[1], l_argv[2], l_argv[3], l_argv[4], l_argv[5]));

         if(SUCCEEDED(retc)) retc = pXmlQue->Process();
         
         if(pXmlQue!=NULL)
         {
            retc0=pXmlQue->CloseFiles(SUCCEEDED(retc));
            if(SUCCEEDED(retc)) retc=retc0;
         }

         KP_DELETE(pXmlQue);
      }
   }
   else
   {
      printf("Bad number of parameters:\n");
      printf("               c:>XmlQue.exe infile.xml outfile.xml ed 2000.01.01 2003.12.03\n");
      printf("                                                     ^       ^          ^\n");
      printf("                         querying tag ---------------'       !          !\n");
      printf("                         min value (ed>=2000.01.01) ---------'          !\n");
      printf("                         max value (ed<=2003.12.03) --------------------'\n\n");
   }

/* if(SUCCEEDED(retc)) retc = */ KpFinit();

return(RET_CODE(retc));
}
