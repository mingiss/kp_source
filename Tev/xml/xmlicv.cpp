// ==================================================
// xmlicv.cpp, former tvxmlxcv.cpp
// compressing of symbolic XML indexes


// ================================================== definitions
#include "envir.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string>
#include <fstream>
#if (Envir==MSWin32Con) || (Envir==MSWin32) || (Envir==MSWin32Mfc) || (Envir==MSWin32ConMfc)
#include <windows.h>
#endif

#include "kperrno.h"
#include "kpstdlib.h"
#include "kptree.h"
#include "kptt.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpsort.h"
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
#include "xmlu.h"
#include "xmlo1.h"
#include "xmlt.h"
#include "xmlicv.h"
#include "tvxmls.h"


// ================================================== objects
const unsigned char lpszProdName[] = "xmlicv";
bool bServiceFl = False;

XmlIcvClass *pXmlIcv = NULL;

KpErrorProcClass KpErrorProc(TRUE, 43);


// -----------------------------------------
HRESULT TestCompilerSettingsLocal(void)
{
#include "kpstcs.cpp"
}


// ================================================== private methods of XmlIcv_tag
// --------------------------------------------------
HRESULT XmlIcvClass::CompressSE(const XL_Indexes iFileIndex)
{
HRESULT retc=S_OK;
long idx;
long loop;
long layout;
bool eof_fl=FALSE;   

   if(lpInFileObj==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, 0L);

   for(loop=0; (!eof_fl) && SUCCEEDED(retc); loop++)
   {
      do
      {
         retc=lpInFileObj->GetNumVal(&idx, iFileIndex, FALSE);
         if(retc==KP_E_EOF)
         {
            retc=S_OK;
            eof_fl=TRUE;
         }

         if((idx<loop) && (!eof_fl) && SUCCEEDED(retc))
         {
            retc=KpErrorProc.OutputErrorMessage(TV_E_DOUBLE_INDEX, (idx==0L)?(unsigned char *)"0":null, FALSE, __FILE__, __LINE__, idx);
            retc=lpInFileObj->GetNumVal(&layout, iFileIndex, TRUE);
         }
      }
      while((idx<loop) && (!eof_fl) && SUCCEEDED(retc));


      while((idx>loop) && (!eof_fl) && SUCCEEDED(retc))
      {
         retc=lpOutFileObj->PutLong(MAXLONG, iFileIndex);
         if(SUCCEEDED(retc)) retc=lpOutFileObj->PutLong(0L, iFileIndex);
         loop++;
      }

      if((!eof_fl) && SUCCEEDED(retc)) retc=lpInFileObj->GetNumVal(&layout, iFileIndex, TRUE);
      if((!eof_fl) && SUCCEEDED(retc))
         retc=lpOutFileObj->PutLong(layout, iFileIndex);
      if((!eof_fl) && SUCCEEDED(retc))
         retc=lpOutFileObj->PutLong(0L, iFileIndex);
   }

   m_lSeSize=loop-1;
   
return(retc);
}


// --------------------------------------------------
// int (__cdecl *compare )(const void *, const void *)
// int __cdecl CompareOffsets(const void *plFirst, const void *plSecond)
int CompareOffsets(const void *plFirst, const void *plSecond)
{                             
int retv=0;

const long *pfirst=(const long *)plFirst;
const long *psecond=(const long *)plSecond;
   
   if(pfirst[1]==psecond[1]) retv=0;
   else if(pfirst[1]>psecond[1]) retv=1;
   else retv=(-1);
   
return(retv);   
}


// --------------------------------------------------
int CompareIds(const void *plFirst, const void *plSecond)
{                             
int retv=0;
   
const long *pfirst=(const long *)plFirst;
const long *psecond=(const long *)plSecond;
   
   if(pfirst[0]==psecond[0]) retv=0;
   else if(pfirst[0]>psecond[0]) retv=1;
   else retv=(-1);
   
return(retv);   
}


// --------------------------------------------------
HRESULT XmlIcvClass::RecalcSE(void)
{
HRESULT retc=S_OK;
HRESULT retc0=S_OK;
unsigned char full_name[KP_MAX_FNAME_LEN+3+1];
unsigned char path[KP_MAX_FNAME_LEN+1];
unsigned char fnam[KP_MAX_FNAME_LEN+1];
unsigned char type[KP_MAX_FTYPE_LEN+1];
FILE *file_ptr=NULL;
long ll=0;
long *sort_buf=NULL;
long id;

// --------------------               
// if((lpInFileObj==NULL) && SUCCEEDED(retc))
//    retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

// --------------------               
   if(SUCCEEDED(retc))
   {
//    if((lpInFileObj->aiFileIndexLengthsPtr[XL_IX_DefSeIndex]!=2*sizeof(long)))
      if((aiIndexWidths[XL_IX_DefSeIndex]!=2*sizeof(long)))
      {
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
      }
   }
              
// --------------------               
   if(SUCCEEDED(retc))
      retc=TvFnameSplit(full_name, path, fnam, type, m_lpszFileName);
                           
   if(SUCCEEDED(retc))
   {
      strcat(full_name, path);
      strcat(full_name, "\\");
      strcat(full_name, fnam);
      strcat(full_name, "_se.ix");
      
      file_ptr=fopen((const char *)full_name, "rb");
      if(file_ptr==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_NOT_FOUND, full_name, TRUE, __FILE__, __LINE__, 0L);
   }              

   if(SUCCEEDED(retc)) retc=KpGetFileSizeFile(file_ptr, &ll);
   if((ll!=m_lSeSize*2*sizeof(long)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      sort_buf=new long[3*m_lSeSize];
      if(sort_buf==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, TRUE, __FILE__, __LINE__, 0L);
   }
                           
   for(id=0; (id<m_lSeSize) && SUCCEEDED(retc); id++)
   {
      sort_buf[3*id]=id;
      if(fread(sort_buf+3*id+1, sizeof(long), 2, file_ptr)!=2)
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR /* KP_E_FILE_FORMAT */, null, TRUE, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) if(ferror(file_ptr))
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, TRUE, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) if(feof(file_ptr))
         retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, TRUE, __FILE__, __LINE__, 0L);
   }
   
   if(file_ptr!=NULL) if(fclose(file_ptr))
   {
      retc0=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, null, TRUE, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) retc=retc0;
   }
   file_ptr=NULL;

// --------------------               
   if(SUCCEEDED(retc)) qsort(sort_buf, m_lSeSize, 3*sizeof(long), CompareOffsets);

   if(SUCCEEDED(retc)) for(id=0; (id<m_lSeSize-1) && (sort_buf[3*(id+1)+1]<Maxlong) && SUCCEEDED(retc); id++)
   {
      sort_buf[3*id+2]=sort_buf[3*(id+1)+1]-sort_buf[3*id+1];
// printf(">> %d[%d]\n", sort_buf[3*id+1], sort_buf[3*id+2]);
   }   

   if(SUCCEEDED(retc))
   {
      file_ptr=fopen((const char *)m_lpszFileName, "rb");
      if(file_ptr==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_NOT_FOUND, m_lpszFileName, TRUE, __FILE__, __LINE__, 0L);
   }      
   if(SUCCEEDED(retc)) retc=KpGetFileSizeFile(file_ptr, &ll);
   if(file_ptr!=NULL) if(fclose(file_ptr))
   {
      retc0=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, null, TRUE, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) retc=retc0;
   }
   file_ptr=NULL;

   if((m_lSeSize>0) && SUCCEEDED(retc))
      sort_buf[3*id+2]=ll-sort_buf[3*id+1]; // id=m_lSeSize-1
   id++;

   for(; (id<m_lSeSize) && SUCCEEDED(retc); id++) sort_buf[3*id+2]=0L;

   if(SUCCEEDED(retc)) qsort(sort_buf, m_lSeSize, 3*sizeof(long), CompareIds);

// --------------------               
   if(SUCCEEDED(retc))
   {
      file_ptr=fopen((const char *)full_name, "wb");
      if(file_ptr==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, full_name, TRUE, __FILE__, __LINE__, 0L);
   }              

   for(id=0; (id<m_lSeSize) && SUCCEEDED(retc); id++)
   {
      if(fwrite(sort_buf+3*id+1, 2*sizeof(long), 1, file_ptr)!=1)
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, TRUE, __FILE__, __LINE__, 0L);
// printf("-- %d[%d]\n", sort_buf[3*id+1], sort_buf[3*id+2]);
      if(SUCCEEDED(retc))
         if(ferror(file_ptr) || feof(file_ptr))
            retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, TRUE, __FILE__, __LINE__, 0L);
   }

   if(file_ptr!=NULL) if(fclose(file_ptr))
   {
      retc0=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, null, TRUE, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) retc=retc0;
   }
   file_ptr=NULL;

// --------------------               
   KP_DELETEA(sort_buf);

return(retc);
}


// --------------------------------------------------
HRESULT XmlIcvClass::CompressTextIndex(const XL_Indexes iFileIndex, int iIndexWidth)
{
HRESULT retc=S_OK;
bool eof_fl=FALSE;
unsigned char txt_buf[TV_XL_MAX_IX_LEN+1];
unsigned char empty_ix[TV_XL_MAX_IX_LEN+1];
unsigned char prev_entry[TV_XL_MAX_IX_LEN+1];
int double_count = 0;
int len;
int ii;
bool hash_fl = False;
bool out_fl = True;
unsigned char *pntd;
long idx;
long prev_idx = 0L;

   if(((iFileIndex < 0) || (iFileIndex >= XL_IX_NumOfIndexes0) || (iIndexWidth > TV_XL_MAX_IX_LEN)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if((lpInFileObj==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      prev_entry[0] = Nul;
      double_count = 0;
   }
   
   if(SUCCEEDED(retc))
   {
      memset(empty_ix, Spc, iIndexWidth); // ' '
      empty_ix[iIndexWidth] = Nul;
   }

   
   if(SUCCEEDED(retc)) do
   {
      out_fl = True;
      
// ---------------- input text value
      if(SUCCEEDED(retc))
      {
         retc=lpInFileObj->GetImage(txt_buf, iIndexWidth, iFileIndex, FALSE);
         if(SUCCEEDED(retc)) txt_buf[iIndexWidth]=Nul;
         if(retc==KP_E_EOF)
         {
            retc=S_OK;
            eof_fl=TRUE;
         }
      }

// ---------------- read node id
      if((!eof_fl) && SUCCEEDED(retc))
      { 
         retc=lpInFileObj->GetNumVal(&idx, iFileIndex, TRUE);
         if(retc==KP_E_EOF)
         {
            retc=S_OK;
            eof_fl=TRUE;
         }
      }

      if((!eof_fl) && SUCCEEDED(retc))
      {
// ---------------- process text value
//                  cut spaces, '*'s and '#'s 
         if(SUCCEEDED(retc)) retc = CutTrailSpcs(txt_buf);

         if(SUCCEEDED(retc))
         {
            pntd = strchr(txt_buf, EXACT_ENTRY_CHR); // '#'
            if(pntd) *pntd = Nul;
            hash_fl = (pntd != NULL);
         }

         if((iaIxEncodings[iFileIndex] == EC_ASCII) && SUCCEEDED(retc))
         {
            pntd = strchr(txt_buf, DOUBLE_ENTRIES_CHR); // '*'
            if(pntd) *pntd = Nul;
         }

//                  check double entries
         if(SUCCEEDED(retc))
         {
#ifdef Debug
if(strcmp(txt_buf, "A.") == 0)
out_fl = True;
#endif
//          if(strcmp(txt_buf, prev_entry) == 0)
            if(TvStrCmp(txt_buf, prev_entry, True, SortMode, False, 1, True) == 0) double_count++;
            else double_count = 0;
  
            if(TvStrCmp(txt_buf, prev_entry, False, SortMode, True, 1, True) == 0)
            {
               if(idx == prev_idx) out_fl = False;
            }
            else strcpy(prev_entry, txt_buf);
                     
            prev_idx = idx;
         }
       

         if(out_fl && SUCCEEDED(retc))
         {
// to lower case
            if((iaIxEncodings[iFileIndex] == EC_ASCII) && SUCCEEDED(retc)) strlwr(txt_buf);
         
//                  add "*"'s 
            if(SUCCEEDED(retc))
            {
               len = strlen(txt_buf);
               if(len > iIndexWidth) 
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, TRUE, __FILE__, __LINE__, 0L);
               if((len == iIndexWidth) && double_count && SUCCEEDED(retc)) 
                  retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, txt_buf, False, __FILE__, __LINE__, 0L);
            }

            if(SUCCEEDED(retc)) for(ii=0; (ii < double_count) && (len < iIndexWidth); ii++)
            {
               txt_buf[len++] = DOUBLE_ENTRIES_CHR; txt_buf[len] = Nul;
               if((len == iIndexWidth) && (ii < double_count-1) && SUCCEEDED(retc)) 
                  retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, txt_buf, False, __FILE__, __LINE__, 0L);
            }
         
//                  add tail hash, spaces
            if(hash_fl && SUCCEEDED(retc))
            {
               if(len < iIndexWidth){ txt_buf[len++] = EXACT_ENTRY_CHR; txt_buf[len] = Nul; }
               else  
                  retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, txt_buf, False, __FILE__, __LINE__, 0L);
            }

            if(SUCCEEDED(retc)) strcat(txt_buf, empty_ix+len);

// ---------------- output text value
            if(SUCCEEDED(retc))
               retc=lpOutFileObj->PutImage(txt_buf, iIndexWidth, iFileIndex);

// ---------------- output node id
            if(SUCCEEDED(retc))
               retc=lpOutFileObj->PutLong(idx, iFileIndex);


// -----------------
         } // if(out_fl && SUCCEEDED(retc))


         if(SUCCEEDED(retc))
         {
            retc=lpInFileObj->SkipEol(iFileIndex);
            if(retc==KP_E_EOF)
            {
               retc=S_OK;
               eof_fl=TRUE;
            }
         }

// -----------------
      } // if((!eof_fl) && SUCCEEDED(retc)) 
   
   } while((!eof_fl) && SUCCEEDED(retc));

return(retc);
}


// ================================================== public methods of XmlIcv_tag
XmlIcvClass::XmlIcvClass(const unsigned char *lpszFname)
{
   m_lSeSize=0L;

   lpInFileObj=NULL;
   lpOutFileObj=NULL;
   lhOpenResult=S_OK;

   m_lpszFileName[0]=Nul;            
   
   if((lpszFname==NULL) && SUCCEEDED(lhOpenResult))
      lhOpenResult=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);
   
   if(SUCCEEDED(lhOpenResult))
      strcpy(m_lpszFileName, lpszFname);

   if(SUCCEEDED(lhOpenResult))
   {
      lpInFileObj = new XmlO1(lpszFname, (const unsigned char *)"r", CreateNewUniFile,
                             plpszaXmlSpecCharTagsMain,
                             alpszIndexNames, aiIndexWidths, 
                             (KpChar)XC_FirstDictTag, plpszaXmlttDictTags, True,
                             XM_VERS_XML10, iaXmlDictNulCodeTables, True, True);
      if(lpInFileObj!=NULL)
         lhOpenResult=lpInFileObj->GetOpenResult();
      else
         lhOpenResult=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, TRUE, __FILE__, __LINE__, 0L);
   }
   
   if(SUCCEEDED(lhOpenResult))
   {
      lpOutFileObj = new XmlO1(lpszFname, (const unsigned char *)"wb", CreateNewUniFile,
                             plpszaXmlSpecCharTagsMain,
                             alpszIndexNames, aiIndexWidths, 
                             (KpChar)XC_FirstDictTag, plpszaXmlttDictTags, True,
                             XM_VERS_XML10, iaXmlDictNulCodeTables, True, True);
      if(lpOutFileObj!=NULL)
         lhOpenResult=lpOutFileObj->GetOpenResult();
      else
         lhOpenResult=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, TRUE, __FILE__, __LINE__, 0L);
   }
}


// --------------------------------------------------
XmlIcvClass::~XmlIcvClass(void)
{
   CloseFiles(FALSE);
}


// --------------------------------------------------
HRESULT XmlIcvClass::GetOpenResult(void)
{
return(lhOpenResult);
}


// --------------------------------------------------
HRESULT XmlIcvClass::Process(void)
{
HRESULT retc=S_OK;
int ii;

// standard entry index file
   retc=CompressSE(XL_IX_SeIndex);
   if((retc == KP_E_FILE_NOT_FOUND) || (retc == KP_E_NO_FILE)) retc = S_OK;

   for(ii=XL_IX_SeIndex+1; (ii<XL_IX_NumOfIndexes0) && SUCCEEDED(retc); ii++)
   {
      retc=CompressTextIndex((const XL_Indexes)ii, aiIndexWidths[ii]-sizeof(long));
      if((retc == KP_E_FILE_NOT_FOUND) || (retc == KP_E_NO_FILE)) retc = S_OK;
   }

return(retc);
}


// --------------------------------------------------
HRESULT XmlIcvClass::CloseFiles(bool bCheckFileExist)
{
HRESULT retc=S_OK;
HRESULT retc0;

   if(lpOutFileObj!=NULL)
   {
      retc=lpOutFileObj->CloseFile(bCheckFileExist);
      KP_DELETE(lpOutFileObj);
   }
   else
   {
      if(!bCheckFileExist) retc=KP_E_NO_FILE;
      else retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, 0L);
   }

   if(lpInFileObj!=NULL)
   {
      KP_DELETE(lpInFileObj);
   }
   else
   {
      if(SUCCEEDED(retc)) retc=KP_E_NO_FILE;
      if(bCheckFileExist)
      {
         retc0=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, 0L);
         if(SUCCEEDED(retc)) retc=retc0;
      }
   }

return(retc);
}


// ================================================== main
//---------------------------------------------
int main(int argc, char **argv)
{
HRESULT retc=S_OK;
HRESULT retc0;
int l_argc;
char *l_argv[2];
int ii;                                         
unsigned char disk[KP_MAX_FNAME_LEN+1];
unsigned char path[KP_MAX_FNAME_LEN+1];
unsigned char fnam[KP_MAX_FNAME_LEN+1];
unsigned char type[KP_MAX_FTYPE_LEN+1];

   printf("\nXML index compressing\n\n");

   if(SUCCEEDED(retc)) retc=KpInit();

   l_argc=argc;
   if(argc==2) for(ii=0; ii<argc; ii++) l_argv[ii]=argv[ii];
#ifdef Debug
   else // if(strstr(strlwr(argv[0]), "debug")>0)
   {
      l_argc=2;

      l_argv[0]="xmlicv";

//    l_argv[1]="f:\\kp\\source\\tev\\lvz\\kpn3.xml";
//    l_argv[1]="g:\\kp\\source\\tev\\lvz\\lvz_s2.xml";
//    l_argv[1]="g:\\kp\\source\\tev\\lvz\\lvz2.xml";
//    l_argv[1]="f:\\kp\\source\\tev\\lzdsh\\kpn2.xml";
//    l_argv[1]="f:\\kp\\source\\tev\\mcm\\mcm_out\\mcmx2.xml";
//    l_argv[1]="f:\\kp\\source\\tev\\mcm\\mcm_out\\emcx2.xml";
//    l_argv[1]="f:\\kp\\source\\tev\\xml\\kpn1.xml";
//    l_argv[1]="f:\\kp\\source\\tev\\vlz\\kpn1.xml";
      l_argv[1]="f:\\kp\\source\\tev\\elz05e\\elz05e.xml";
   }
#endif      

   if(l_argc==2)
   {                                 
      if(SUCCEEDED(retc))
         retc=TvFnameSplit(disk, path, fnam, type, (const unsigned char *)l_argv[1]);
      if(SUCCEEDED(retc))
      {
         SortMode=tolower(fnam[0]);
#ifdef Debug
         SortMode=KP_LNG_LIT;
#endif
         retc=TvXmlSortTextIndexes((unsigned char *)l_argv[1]);
      }
      
      if(SUCCEEDED(retc))
      {
         pXmlIcv = new XmlIcvClass((unsigned char *)l_argv[1]);
         if(pXmlIcv!=NULL)
         {
            retc=pXmlIcv->GetOpenResult();

            if(SUCCEEDED(retc)) retc=pXmlIcv->Process();

            retc0=pXmlIcv->CloseFiles(TRUE);
            if(SUCCEEDED(retc)) retc=retc0;

            if(SUCCEEDED(retc)) retc=pXmlIcv->RecalcSE();

            KP_DELETE(pXmlIcv);
         }
         else
            retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, TRUE, __FILE__, __LINE__, 0L);
      }
   }
   else
   {
      printf("Bad number of parameters:\n");
      printf("               c:>xmlicv.exe file.xml\n");
   }

/* if(SUCCEEDED(retc)) retc = */ KpFinit();

#ifdef Debug
#if (Compiler==Watcom)
system("pause");
#endif
#endif

return(RET_CODE_MAIN(retc));
}
