// ==================================================
// tvxmls.cpp
// XML sort/search capabilities


// ================================================== definitions
#include "envir.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <fstream>
#if OsGr==MSWin
#include <windows.h>
#include <time.h>
#include <richedit.h>
#include <Richole.h>
#endif

#if Compiler != Watcom
using namespace std;
#endif

#include "kpstdlib.h"
#include "kperrno.h"
#include "kptt.h"
#include "kptree.h"
#include "kpcolors.h"
#include "kpfonts.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpctype.h"
#include "kpsort.h"
#include "res_com.h"
#include "tvxml.h"
#include "kpstdio.h"
#include "kpwindow.h"
#include "kperr.h"
#include "tvmain.h"
#include "tvxmls.h"
#include "tvxmle.h"
#include "xmlh.h"
#include "xmlp.h"
#include "xmlf.h"
#include "kpttucf.h"
#include "xmlo1.h"
#include "xmlis.h"
#include "xmlt.h"


// --------------------------------------------------
HRESULT TvXmlSortTextIndexes(const unsigned char *lpszFname)
{
HRESULT retc=S_OK;
unsigned char disk[KP_MAX_FNAME_LEN+1];
unsigned char path[KP_MAX_FNAME_LEN+1];
unsigned char fname[KP_MAX_FNAME_LEN+1];
unsigned char ftype[KP_MAX_FTYPE_LEN+1];
unsigned char cur_fname[KP_MAX_FNAME_LEN+7+1];
// unsigned char fnam_uni[KP_MAX_FNAME_LEN+7+1];
// unsigned char com_buf[KP_MAX_FNAME_LEN+7+8+1+8+8+1];
int ii;

   if(SUCCEEDED(retc))
      retc=TvFnameSplit(disk, path, fname, ftype, lpszFname);

   if(SUCCEEDED(retc))
   {
      strcat(disk, path);
      strcat(disk, "\\");
      strcat(disk, fname);
      strcpy(fname, disk);
   }

// if(SUCCEEDED(retc)) retc=TvUniFname.Generate(fnam_uni);

   for(ii=XL_IX_SeIndex; (ii<XL_IX_NumOfIndexes0) && SUCCEEDED(retc); ii++)
   {
      strcpy(cur_fname, fname);
      strcat(cur_fname, "_");
      strcat(cur_fname, alpszIndexNames[ii]);
      strcat(cur_fname, ".ixt");

#if FALSE

      sprintf((char *)com_buf,
#  if Os==Linux
         (ii==XL_IX_SeIndex)?"sort -n < %s > %s":
#  endif
         "sort < %s > %s", cur_fname, fnam_uni);
      if(system((const char *)com_buf)==(-1))
         retc=KpErrorProc.OutputErrorMessage(KP_E_COMMAND_ERROR, null, True, __FILE__, __LINE__, 0L);

      if(SUCCEEDED(retc)) retc=CheckEmpty(fnam_uni);

      if(SUCCEEDED(retc))
      {
         sprintf((char *)com_buf,
#  if OsGr==Unix
            "cp %s %s",
#  else
            "copy %s %s",
#  endif
            fnam_uni, cur_fname);
         if(system((const char *)com_buf)==(-1))
            retc=KpErrorProc.OutputErrorMessage(KP_E_COMMAND_ERROR, null, True, __FILE__, __LINE__, 0L);
      }

      if(SUCCEEDED(retc)) retc=CheckEmpty(cur_fname);

      if(SUCCEEDED(retc))
      {
         sprintf((char *)com_buf,
#  if OsGr==Unix
            "rm %s",
#  else
            "del %s",
#  endif
            fnam_uni);
         if(system((const char *)com_buf)==(-1))
            retc=KpErrorProc.OutputErrorMessage(KP_E_COMMAND_ERROR, null, True, __FILE__, __LINE__, 0L);
      }

#else // #if FALSE

      if(SUCCEEDED(retc))
      {
         retc = SortTextFile(cur_fname, False, ii != XL_IX_SeIndex);
         if(retc == KP_E_FILE_NOT_FOUND) retc = S_OK;
      }
#endif

   } // for(ii=XL_IX_SeIndex; (ii<XL_IX_NumOfIndexes0) && SUCCEEDED(retc); ii++)

return(retc);
}


// --------------------------------------------------
HRESULT XmlO1::GetIndexSize(long *plOffset, int iFileIndex)
{
HRESULT retc=S_OK;

   if((plOffset==NULL) || (iFileIndex<XL_IX_DefSeIndex) || (iFileIndex>=XL_IX_NumOfIndexes0))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
      if(m_fFiles[iFileIndex]==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
      retc=m_fFiles[iFileIndex]->Fseek(0L, SEEK_END);

   if(SUCCEEDED(retc)) retc=m_fFiles[iFileIndex]->Ftell(plOffset);

   if(SUCCEEDED(retc))
      if(*plOffset%m_aiFileIndexLengthsPtr[iFileIndex]!=0)
      {
         *plOffset-=(*plOffset)%m_aiFileIndexLengthsPtr[iFileIndex];
         retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, m_lppszFileIndexNamesPtr[iFileIndex], False, __FILE__, __LINE__, 0L);
      }

return(retc);
}


// --------------------------------------------------
HRESULT XmlO1::SearchEntry
(
long *plEntryIdx,
long *plOffset,
const unsigned char *lpszKeyword,
int iFileIndex,
bool bTestNotFound
)
{
HRESULT retc=S_OK;
long offset;
unsigned char kwd_buf[TV_XL_MAX_IX_LEN+1];
int kwd_len;

// char aa[100];
// strcpy(aa,(const char *)lpszKeyword);
// aa[3]=0;
// if(strcmp(aa, "LYG" /* "LYG PRANASCARONUM" */)==0)
// aa[6]=0;
// if(strcmp(aa, "SENIOR" /* "SENIOR NASSAU WILLIAM NASAU VILJAMAS SENIORAS" */)==0)
// if(strcmp(aa, "KEYNES" /* "KEYNES JOHN MAYNARD DZONAS MEINARDAS KEINSAS" */)==0)
// offset=0;


   if((plEntryIdx==NULL) || (plOffset==NULL) || (lpszKeyword==null) ||
      (iFileIndex<XL_IX_DefSeIndex) || (iFileIndex>=XL_IX_NumOfIndexes0))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
      retc=GetIndexSize(&offset, iFileIndex);

// if(SUCCEEDED(retc))
// {
//    kwd_len=strlen(lpszKeyword);
//    if(kwd_len>=TV_XL_MAX_IX_LEN) // TV_XL_MAX_IX_LEN-1)
//       retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, False, __FILE__, __LINE__, 0L);
// }

   if(SUCCEEDED(retc))
   {
      strncpy(kwd_buf, lpszKeyword, TV_XL_MAX_IX_LEN);
      kwd_buf[TV_XL_MAX_IX_LEN] = Nul;

      CutTrailSpcs(kwd_buf);

      kwd_len=strlen(kwd_buf);
// search for main entry
      kwd_buf[kwd_len]=EXACT_ENTRY_CHR; // '#'
      kwd_buf[kwd_len+1]=Nul;
      retc=SearchTextEntry(plEntryIdx, plOffset, kwd_buf, iFileIndex, bTestNotFound,
                           0L, offset);
      kwd_buf[kwd_len]=Nul;
   }

// search for derivative entry
   if(retc==KP_E_KWD_NOT_FOUND)
      retc=SearchTextEntry(plEntryIdx, plOffset, kwd_buf, iFileIndex, bTestNotFound,
                           0L, offset);
return(retc);
}


// --------------------------------------------------
HRESULT XmlO1::SearchEntryFirst
(
long *plEntryIdx,
long *plOffset,
const unsigned char *lpszKeyword,
int iFileIndex,
bool bTestNotFound
)
{
HRESULT retc=S_OK;
long text_size;
long full_size;
long offset;
unsigned char read_kwd[TV_XL_MAX_IX_LEN+1];
unsigned char *read_kwd_ptr = read_kwd;
unsigned char cur_search_kwd_buf[KP_MAX_FILE_LIN_WDT+1];
unsigned char *cur_search_kwd_buf_ptr = cur_search_kwd_buf;
int rc;
bool clear_exact_entry_chr = False;
int pos;

   if((plEntryIdx==NULL) || (plOffset==NULL) || (lpszKeyword==null) ||
      (iFileIndex<XL_IX_DefSeIndex) || (iFileIndex>=XL_IX_NumOfIndexes0))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
      retc=SearchEntry(plEntryIdx, plOffset, lpszKeyword, iFileIndex, bTestNotFound);

// -------------
   if(SUCCEEDED(retc))
   {
      strncpy(cur_search_kwd_buf, lpszKeyword, KP_MAX_FILE_LIN_WDT);
      cur_search_kwd_buf[KP_MAX_FILE_LIN_WDT] = Nul;
      if(strlen(cur_search_kwd_buf)>TV_XL_MAX_IX_LEN) cur_search_kwd_buf[TV_XL_MAX_IX_LEN]=Nul;

// jau yra IndexEntryToCompareStr()
//    if(iaIxEncodings[iFileIndex] == EC_ASCII) TvStrLwrLat(cur_search_kwd_buf);

      pos = strlen(cur_search_kwd_buf);
      if(pos > 0) if(cur_search_kwd_buf[pos-1] != EXACT_ENTRY_CHR) clear_exact_entry_chr = True;

      retc = IndexEntryToCompareStr(cur_search_kwd_buf, cur_search_kwd_buf, False, clear_exact_entry_chr, iaIxEncodings[iFileIndex]);
   }

   if(SUCCEEDED(retc))
   {
// to first occurence
      full_size=m_aiFileIndexLengthsPtr[iFileIndex];
      text_size=full_size-sizeof(long);
      offset=*plOffset;
      do
      {
         if(offset==0L) retc=KP_E_KWD_NOT_FOUND;
         else
         {
            offset-=full_size;

            retc=Fseek(iFileIndex, offset, SEEK_SET);
            if(SUCCEEDED(retc))
               retc=GetImage(read_kwd, text_size, iFileIndex, False);
            else retc=KP_E_KWD_NOT_FOUND;

            if(SUCCEEDED(retc))
            {
               read_kwd[text_size]=Nul;
               retc = IndexEntryToCompareStr(read_kwd, read_kwd, False, clear_exact_entry_chr, iaIxEncodings[iFileIndex]);
            }

            if(SUCCEEDED(retc))
            {
//             rc=TvStrCmp(read_kwd, cur_search_kwd_buf, SortSkipSpc, SortMode, True,
//                ((SortMode==KP_LNG_LIT) || (SortMode==KP_LNG_LIX) || (SortMode==KP_LNG_LIS) || (SortMode==KP_LNG_GER))?TV_IX_CTBL:1, // 71
//                True);
               rc = TvStrPtrCmpStrictSkipSpcCutLastWord(&read_kwd_ptr, &cur_search_kwd_buf_ptr);

#if FALSE // #ifdef Debug
char str_buf[200];
sprintf(str_buf, "--->>>%s<<< >>>%s<<< %d", read_kwd, cur_search_kwd_buf, rc);
KP_TRACE(str_buf);
#endif
               if(rc<0)
               {
                  retc=KP_E_KWD_NOT_FOUND;
                  offset+=full_size;
               }
               else
                  retc=GetImage(plEntryIdx, sizeof(long), iFileIndex, True);
            }

         } // else // if(offset==0)

      } while(SUCCEEDED(retc));
      if(retc==KP_E_KWD_NOT_FOUND) retc=S_OK;

      if(SUCCEEDED(retc)) *plOffset=offset;

   } // if(SUCCEEDED(retc))

return(retc);
}


// --------------------------------------------------
HRESULT XmlO1::SearchTextEntry
(
long *plEntryIdx,
long *plOffset,
const unsigned char *lpszKeyword,
int iFileIndex,
bool bTestNotFound,
long lStartFilePos,
long lEndFilePos
)
{
HRESULT retc=S_OK;
bool found=False;
long start;
long end;
long middle;
long prev_dif;
unsigned char read_kwd[TV_XL_MAX_IX_LEN+1];
unsigned char *read_kwd_ptr = read_kwd;
unsigned char cur_search_kwd_buf[KP_MAX_FILE_LIN_WDT+1];
unsigned char *cur_search_kwd_buf_ptr = cur_search_kwd_buf;
int rc;
long text_size;
long full_size;
long end_offset;
long entry_id;
bool clear_exact_entry_chr = False;
int pos;

   read_kwd[0]=Nul;

   if((plEntryIdx==NULL) || (plOffset==NULL) || (lpszKeyword==null) ||
      (iFileIndex<XL_IX_DefSeIndex) || (iFileIndex>=XL_IX_NumOfIndexes0))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
      if(m_fFiles[iFileIndex]==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=GetIndexSize(&end_offset, iFileIndex);

   if(SUCCEEDED(retc))
   {
      *plOffset=lEndFilePos;

      *plEntryIdx=0L;

      full_size=m_aiFileIndexLengthsPtr[iFileIndex];
      text_size=full_size-sizeof(long);

      start=lStartFilePos;
      end=lEndFilePos;
   }

// -------------
   if(SUCCEEDED(retc))
   {
      strncpy(cur_search_kwd_buf, lpszKeyword, KP_MAX_FILE_LIN_WDT);
      cur_search_kwd_buf[KP_MAX_FILE_LIN_WDT] = Nul;
      if(strlen(cur_search_kwd_buf)>TV_XL_MAX_IX_LEN) cur_search_kwd_buf[TV_XL_MAX_IX_LEN]=Nul;

      pos = strlen(cur_search_kwd_buf);
      if(pos > 0) if(cur_search_kwd_buf[pos-1] != EXACT_ENTRY_CHR) clear_exact_entry_chr = True;

      if(iaIxEncodings[iFileIndex] == EC_ASCII) TvStrLat(cur_search_kwd_buf, TV_IX_CTBL); // buvo TvStrLwrLat(cur_search_kwd_buf);?

#if FALSE // #ifdef Debug
char str_buf[100];
sprintf(str_buf, "SearchTextEntry: iFileIndex: %d iaIxEncodings[iFileIndex]: %d", iFileIndex, iaIxEncodings[iFileIndex]);
KP_TRACE(str_buf);
#endif

      retc = IndexEntryToCompareStr(cur_search_kwd_buf, cur_search_kwd_buf, False, clear_exact_entry_chr, iaIxEncodings[iFileIndex]);
   }

   if(SUCCEEDED(retc)) do
   {
      middle = start + ((end-start)/full_size/2)*full_size;

      if(middle<end_offset)
      {
         retc=m_fFiles[iFileIndex]->Fseek(middle, SEEK_SET);
         if(SUCCEEDED(retc))
            retc=GetImage(read_kwd, text_size, iFileIndex, True);
      }
      else retc=KP_E_KWD_NOT_FOUND;

      if(SUCCEEDED(retc))
      {
         read_kwd[text_size]=Nul;
         retc = IndexEntryToCompareStr(read_kwd, read_kwd, False, clear_exact_entry_chr, iaIxEncodings[iFileIndex]);
      }

      if(SUCCEEDED(retc))
      {
// jau yra IndexEntryToCompareStr()
//       TvStrLwr(read_kwd, (iaIxEncodings[iFileIndex] < EC_First_Type)?iaIxEncodings[iFileIndex]:1);

//       rc=TvStrCmp(read_kwd, cur_search_kwd_buf, SortSkipSpc, SortMode, False,
//          ((SortMode==KP_LNG_LIT) || (SortMode==KP_LNG_LIX) || (SortMode==KP_LNG_LIS) || (SortMode==KP_LNG_GER))?TV_IX_CTBL:1, // 71
//          True);
         rc = TvStrPtrCmpStrictSkipSpcCutLastWord(&read_kwd_ptr, &cur_search_kwd_buf_ptr);
#if FALSE // #ifdef Debug
char str_buf[200];
sprintf(str_buf, "...>>>%s<<< >>>%s<<< %d", read_kwd, cur_search_kwd_buf, rc);
KP_TRACE(str_buf);
#endif
         if(rc==0)
         {
            prev_dif=0;
            found=True;
            start=end=middle;
         }
         else
         {
            prev_dif=end-start;
            if(rc<0) start=middle;
            else end=middle;
         }
         *plOffset=start;
      }

   } while((prev_dif>full_size) && SUCCEEDED(retc));

   if(retc==KP_E_KWD_NOT_FOUND) retc=S_OK;

// if(SUCCEEDED(retc))
//    retc=fFiles[iFileIndex]->Fseek(middle+text_size, SEEK_SET);
   if((middle+text_size<lEndFilePos) && SUCCEEDED(retc))
      retc=GetImage(plEntryIdx, sizeof(long), iFileIndex, True);

// gal tolesni irasai bent jau apima paieskos zodi?
// KP_TRACE("------------");
   if((!found) && SUCCEEDED(retc))
   {
      entry_id=(*plEntryIdx);

      do
      {
         read_kwd[strlen(cur_search_kwd_buf)]=Nul;
//       rc=TvStrCmp(read_kwd, cur_search_kwd_buf, SortSkipSpc, SortMode, True,
//          ((SortMode==KP_LNG_LIT) || (SortMode==KP_LNG_LIX) || (SortMode==KP_LNG_LIS) || (SortMode==KP_LNG_GER))?TV_IX_CTBL:1, // 71
//          True);
         rc = TvStrPtrCmpStrictSkipSpcCutLastWord(&read_kwd_ptr, &cur_search_kwd_buf_ptr);
#ifdef Debug
// unsigned char str_buf[200];
// sprintf((char *)str_buf, "%d %s %s %d %x %x", start, cur_search_kwd_buf, read_kwd, rc, read_kwd, strstr(read_kwd, cur_search_kwd_buf));
// KP_TRACE(str_buf);
#endif
         if(rc==0)
         {
            *plOffset=start;
            *plEntryIdx=entry_id;
         }

         if(rc<0)
         {
            start+=full_size;
            if(start<lEndFilePos)
            {
               retc=GetImage(read_kwd, text_size, iFileIndex, True);
               if(SUCCEEDED(retc))
               {
                  read_kwd[text_size]=Nul;
                  retc = IndexEntryToCompareStr(read_kwd, read_kwd, False, clear_exact_entry_chr, iaIxEncodings[iFileIndex]);
               }
               if(SUCCEEDED(retc))
                  retc=GetImage(&entry_id, sizeof(long), iFileIndex, True);
            }
         }

      } while((rc<0) && (start<lEndFilePos) && SUCCEEDED(retc));

   } // if((!found) && SUCCEEDED(retc))

// -------------------
   if((!found) && SUCCEEDED(retc))
   {
      if(!bTestNotFound) retc=KP_E_KWD_NOT_FOUND;
      else retc=KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND, lpszKeyword, False, __FILE__, __LINE__, 0L);
   }

return(retc);
}


// -------------------------------
HRESULT XmlO1::SeekEntry(long lEntryIdx, long *plEntryLen)
{
HRESULT retc=S_OK;
long data_offset;

   if((m_fFiles[XL_IX_DefSeIndex] == NULL) || (m_fFiles[XL_IX_DefDataFile] == NULL))
      retc = KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   if((m_aiFileIndexLengthsPtr[XL_IX_DefSeIndex] != 2*sizeof(long)) && SUCCEEDED(retc))
      retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc = Fseek(XL_IX_DefSeIndex, lEntryIdx*m_aiFileIndexLengthsPtr[XL_IX_DefSeIndex], SEEK_SET);

   if(SUCCEEDED(retc)) retc = GetImage(&data_offset, sizeof(long), XL_IX_DefSeIndex, True);
   if(plEntryLen && SUCCEEDED(retc)) retc = GetImage(plEntryLen, sizeof(long), XL_IX_DefSeIndex, True);

   if(SUCCEEDED(retc)) retc=Fseek(XL_IX_DefDataFile, data_offset, SEEK_SET);

return(retc);
}


// -------------------------------
HRESULT XmlO1::ReadEntryImg(long lEntryIdx, unsigned char **plpszEntryImg, long *plEntryLen)
{
HRESULT retc=S_OK;
long data_offset;
long entry_size;

   if(((plpszEntryImg==NULL) || (plEntryLen==NULL)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(((m_fFiles[XL_IX_DefSeIndex]==NULL) || (m_fFiles[XL_IX_DefDataFile]==NULL)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   if((m_aiFileIndexLengthsPtr[XL_IX_DefSeIndex]!=2*sizeof(long)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=Fseek(XL_IX_DefSeIndex, lEntryIdx*m_aiFileIndexLengthsPtr[XL_IX_DefSeIndex], SEEK_SET);

   if(SUCCEEDED(retc)) retc=GetImage(&data_offset, sizeof(long), XL_IX_DefSeIndex, True);
   if(SUCCEEDED(retc)) retc=GetImage(&entry_size, sizeof(long), XL_IX_DefSeIndex, True);

   KP_NEWA(*plpszEntryImg, unsigned char, ((entry_size + 4 + 1) / 4) * 4); // islyginam iki zodzio ribos kphp11 konverteriui

   if(SUCCEEDED(retc)) retc=Fseek(XL_IX_DefDataFile, data_offset, SEEK_SET);
   if(SUCCEEDED(retc)) retc=GetImage(*plpszEntryImg, entry_size, XL_IX_DefDataFile, True);
   if(SUCCEEDED(retc)) (*plpszEntryImg)[entry_size]=Nul;
// PutLogMessage_("XmlO1::ReadEntryImg() entry_size: %d", entry_size);

   if(SUCCEEDED(retc)) *plEntryLen=entry_size;

return(retc);
}
