// --------------------
// lzdenc.cpp
// zodyno xml uzkodavimas
//
// lzdenc.exe – dël lzdsh.exe, neapibrëþtas LZDENC_WEAK_CODED
// lzdencw.exe – dël arksh.exe, apibrëþtas LZDENC_WEAK_CODED, lizdai ilgesni uþ Maxint
//

// ================================================== definitions
#include "envir.h"

#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <String>
#include <windows.h>
#include <richedit.h>
#include <Richole.h>
#include <time.h>

#include "kpstdlib.h"
#include "kperrno.h"
#include "kptree.h"
#include "kptt.h"
#include "kpctype.h"
#include "kpcolors.h"
#include "kpfonts.h"
#include "kpstring.h"
#include "kpstdio.h"
#include "res_com.h"
#include "kpwindow.h"
#include "kperr.h"
#include "kpsock.h"
#include "kphp11i.h"
#include "kphp11t.h"
#include "kphp11y.h"
#include "kphp11m.h"
#include "kphp11w.h"
#include "kphp11d.h"
#include "kphp11rc.h"
#include "tvmain.h"
#include "tvxml.h"
#include "xmlh.h"
#include "xmlp.h"
#include "xmlf.h"
#include "xmlo1.h"
#include "xmlt.h"
#include "kpcapp.h"
#include "kpstap.h"

#include "lzdenc.h"


// --------------------
LzdEnc_tag *pLzdEnc=NULL;
KpErrorProcClass KpErrorProc(TRUE, 43);
const unsigned char lpszProdName[] = "lzdenc"; 
int iProdVerGlob=0;
int iUpdNumGlob = -1;
bool bServiceFl=False;   

int KpHp11NumOfExtFun=KP_RC_CBIX_NumOfCommonIxs;
KpHp11ExtFun KpHp11ExtFunTab[KP_RC_CBIX_NumOfCommonIxs_3+1]=
// HRESULT (*KpHp11ExtFunTab)(void *pPars)[]=
{
   GetCommonCompID_RC,
   TestFlashID_RC,
   TestIniChSum_RC,
   SetIniChSum_RC,
   
   CheckResRequest_RC,
   CheckRelRequest_RC,

   NULL
};


// -----------------------------------------
HRESULT TestCompilerSettingsLocal(void)
{
#include "kpstcs.cpp"
}


// --------------------
LzdEnc_tag::LzdEnc_tag(const unsigned char *lpszFname)
{                   
unsigned char disk[KP_MAX_FNAME_LEN+1];
unsigned char path[KP_MAX_FNAME_LEN+1];
unsigned char name[KP_MAX_FNAME_LEN+1];
unsigned char ext[KP_MAX_FTYPE_LEN+1];

   m_lhOpenResult=S_OK;
   
   m_lpXmlFileObj=NULL;
   m_lpXdbFileObj=NULL;
   m_lpSeIxFileObj=NULL;
   
   m_lpszXmlFileName[0]=Nul;
   m_lpszXdbFileName[0]=Nul;
   m_lpszSeIxFileName[0]=Nul;
   
// ----------------------
   if((lpszFname==NULL) && SUCCEEDED(m_lhOpenResult))
      m_lhOpenResult=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(m_lhOpenResult)) if(strlen(lpszFname)>=KP_MAX_FNAME_LEN)
      m_lhOpenResult=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, TRUE, __FILE__, __LINE__, 0L);
   
// ----------------------
   if(SUCCEEDED(m_lhOpenResult))
   {
      strncpy(m_lpszXmlFileName, lpszFname, KP_MAX_FNAME_LEN);
      m_lpszXmlFileName[KP_MAX_FNAME_LEN]=Nul;
   }
   if(SUCCEEDED(m_lhOpenResult))
   {
      m_lpXmlFileObj=fopen((const char *)m_lpszXmlFileName, "rb");
      if(m_lpXmlFileObj==NULL)
         m_lhOpenResult=KpErrorProc.OutputErrorMessage(KP_E_FILE_NOT_FOUND, m_lpszXmlFileName, TRUE, __FILE__, __LINE__, 0L);
   }

// ----------------------
   if(SUCCEEDED(m_lhOpenResult))
      m_lhOpenResult=TvFnameSplit(disk, path, name, ext, m_lpszXmlFileName);
      
// ----------------------
   if(SUCCEEDED(m_lhOpenResult))
   {
      strcpy(m_lpszSeIxFileName, disk);
      strcat(m_lpszSeIxFileName, path);
      strcat(m_lpszSeIxFileName, "\\");
      strcat(m_lpszSeIxFileName, name);
      strcat(m_lpszSeIxFileName, "_se.ix");
   }   
   if(SUCCEEDED(m_lhOpenResult))
   {
      m_lpSeIxFileObj=fopen((const char *)m_lpszSeIxFileName, "rb");
      if(m_lpSeIxFileObj==NULL)
         m_lhOpenResult=KpErrorProc.OutputErrorMessage(KP_E_FILE_NOT_FOUND, m_lpszSeIxFileName, TRUE, __FILE__, __LINE__, 0L);
   }
   
// ----------------------
   if(SUCCEEDED(m_lhOpenResult))
   {
      strcpy(m_lpszXdbFileName, disk);
      strcat(m_lpszXdbFileName, path);
      strcat(m_lpszXdbFileName, "\\");
      strcat(m_lpszXdbFileName, name);
      strcat(m_lpszXdbFileName, ".xdb");
   }   
   if(SUCCEEDED(m_lhOpenResult))
   {
      m_lpXdbFileObj=fopen((const char *)m_lpszXdbFileName, "wb");
      if(m_lpXdbFileObj==NULL)
         m_lhOpenResult=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, m_lpszXdbFileName, TRUE, __FILE__, __LINE__, 0L);
   }
}


// --------------------------------------------------
LzdEnc_tag::~LzdEnc_tag(void)
{
   CloseFiles(False);
}


// --------------------------------------------------
HRESULT LzdEnc_tag::GetOpenResult(void)
{
return(m_lhOpenResult);
}


// --------------------------------------------------
HRESULT LzdEnc_tag::EncodeEntry(unsigned char *pcEncodeBuf, long lBufLen, long lEntryId)
{
HRESULT retc=S_OK;

   KP_ASSERT(pcEncodeBuf, E_INVALIDARG, null, True);

#ifdef LZDENC_WEAK_CODED
int prod_ver;

   if(SUCCEEDED(retc)) retc = GetIniProdVer(&prod_ver);

   if(SUCCEEDED(retc)) retc = EnctBufMed(pcEncodeBuf, lBufLen, prod_ver, lEntryId);
   
#else
static KpRcPars rc_pars;

   KP_ASSERT(lBufLen <= Maxint, E_INVALIDARG, null, True);
// KP_ASSERT(lEntryId <= Maxint, E_INVALIDARG, null, True); // koduojam 16 bitø uodega
   
   if(SUCCEEDED(retc))
   {
      rc_pars.iOpCode=KP_RC_ENCODE_ENTRY;
      rc_pars.iParBlSize=sizeof(rc_pars);
      rc_pars.enc.iDataLen=((lBufLen+4)/4)*4;
      rc_pars.enc.pData=pcEncodeBuf;
      rc_pars.enc.lCtrl=lEntryId;

      retc = EmuTv.ExecRemoteCall(&rc_pars);
   }
#endif

return(retc);
}
                     
                     
// --------------------------------------------------
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
HRESULT LzdEnc_tag::Process(void)
{
HRESULT retc=S_OK;
long entry_id=0L;
long ll=0;
long *sort_buf=NULL;
long id;
long cur_offset=0L;
unsigned char *enc_buf=NULL;
long entry_size;
long num_of_entries;

   if(((m_lpSeIxFileObj==NULL) || (m_lpXmlFileObj==NULL) || (m_lpXdbFileObj==NULL)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   if((aiIndexWidths[XL_IX_DefSeIndex]!=2*sizeof(long)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

// ---------------------------------
#if FALSE
// while((entry_id<10) && SUCCEEDED(retc))
   while(SUCCEEDED(retc))
   {
      if(fread(&offset, sizeof(offset), 1, m_lpSeIxFileObj)!=1)
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, m_lpszSeIxFileName, True, __FILE__, __LINE__, entry_id);
      if(ferror(m_lpSeIxFileObj) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, m_lpszSeIxFileName, True, __FILE__, __LINE__, entry_id);
      if(feof(m_lpSeIxFileObj) && SUCCEEDED(retc))
         retc=KP_E_EOF;
               
      if(fread(&size, sizeof(size), 1, m_lpSeIxFileObj)!=1)
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, m_lpszSeIxFileName, True, __FILE__, __LINE__, entry_id);
      if(ferror(m_lpSeIxFileObj) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, m_lpszSeIxFileName, True, __FILE__, __LINE__, entry_id);
      if(feof(m_lpSeIxFileObj) && SUCCEEDED(retc))
         retc=KP_E_EOF;
               
      if((offset<Maxlong) && SUCCEEDED(retc))
      {
printf("%ld %ld[%ld]\n", entry_id, offset, size);
      }   
      
      entry_id++;
   }
   
   if(retc==KP_E_EOF) retc=S_OK;
#endif

// ---------------------------------
   if(SUCCEEDED(retc)) retc=KpGetFileSizeFile(m_lpSeIxFileObj, &ll);
   if(((ll % aiIndexWidths[XL_IX_DefSeIndex])!=0) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
      
   if(SUCCEEDED(retc)) num_of_entries=ll/aiIndexWidths[XL_IX_DefSeIndex];

   KP_NEWA(sort_buf, long, 3 * num_of_entries);
                           
   for(id=0; (id<num_of_entries) && SUCCEEDED(retc); id++)
   {
      sort_buf[3*id]=id;
      if(fread(sort_buf+3*id+1, sizeof(long), 2, m_lpSeIxFileObj)!=2)
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR /* KP_E_FILE_FORMAT */, null, TRUE, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) if(ferror(m_lpSeIxFileObj))
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, TRUE, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) if(feof(m_lpSeIxFileObj))
         retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, TRUE, __FILE__, __LINE__, 0L);
   }
   
// ---------------------------------
   if(SUCCEEDED(retc)) qsort(sort_buf, num_of_entries, 3*sizeof(long), CompareOffsets);

   cur_offset=0L;
   for(id=0; (id<num_of_entries) && SUCCEEDED(retc); id++)
   {
      if((cur_offset>sort_buf[3*id+1]) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, TRUE, __FILE__, __LINE__, 0L);
      
// ---------------------------------- hole
      if((cur_offset<sort_buf[3*id+1]) && (sort_buf[3*id+1]<Maxlong) && SUCCEEDED(retc))
      {
         entry_size=sort_buf[3*id+1] - cur_offset;
         cur_offset+=entry_size;
         
         enc_buf = NULL;
         KP_NEWA(enc_buf, unsigned char, entry_size + 4);
      
         if(SUCCEEDED(retc))
            if(fread(enc_buf, sizeof(unsigned char), entry_size, m_lpXmlFileObj)!=entry_size)
               retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR /* KP_E_FILE_FORMAT */, null, TRUE, __FILE__, __LINE__, 0L);
         if(SUCCEEDED(retc)) if(ferror(m_lpXmlFileObj))
            retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, TRUE, __FILE__, __LINE__, 0L);
         if(SUCCEEDED(retc)) if(feof(m_lpXmlFileObj))
            retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, TRUE, __FILE__, __LINE__, 0L);
   
         if(SUCCEEDED(retc)) retc = EncodeEntry(enc_buf, entry_size, 0L);
   
         if(SUCCEEDED(retc))
            if(fwrite(enc_buf, sizeof(unsigned char), entry_size, m_lpXdbFileObj)!=entry_size)
               retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, TRUE, __FILE__, __LINE__, 0L);
         if(SUCCEEDED(retc)) if(ferror(m_lpXdbFileObj) || feof(m_lpXdbFileObj))
            retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, TRUE, __FILE__, __LINE__, 0L);
      
// besàlygiðkai trint negalima – gali bûti uþsilikæs EncodeEntry()
         KP_DELETEA(enc_buf);
      
      } // if((cur_offset<sort_buf[3*id+1]) && SUCCEEDED(retc))

// ---------------------------------- entry
      if((sort_buf[3*id+2]>0) && (sort_buf[3*id+1]<Maxlong) && SUCCEEDED(retc))
      {
         if(cur_offset!=sort_buf[3*id+1])
            retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, TRUE, __FILE__, __LINE__, 0L);
         
         enc_buf = NULL;
         if(SUCCEEDED(retc))
         {         
            entry_size=sort_buf[3*id+2];
            cur_offset+=entry_size;
            
            KP_NEWA(enc_buf, unsigned char, entry_size + 4);
         }
         
         if(SUCCEEDED(retc))
            if(fread(enc_buf, sizeof(unsigned char), entry_size, m_lpXmlFileObj)!=entry_size)
               retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, TRUE, __FILE__, __LINE__, 0L);
         if(SUCCEEDED(retc)) if(ferror(m_lpXmlFileObj))
            retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, TRUE, __FILE__, __LINE__, 0L);
         if(SUCCEEDED(retc)) if(feof(m_lpXmlFileObj))
            retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, TRUE, __FILE__, __LINE__, 0L);
   
         if(SUCCEEDED(retc)) retc = EncodeEntry(enc_buf, entry_size, sort_buf[3*id]);
   
         if(SUCCEEDED(retc))
            if(fwrite(enc_buf, sizeof(unsigned char), entry_size, m_lpXdbFileObj)!=entry_size)
               retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, TRUE, __FILE__, __LINE__, 0L);
         if(SUCCEEDED(retc)) if(ferror(m_lpXdbFileObj) || feof(m_lpXdbFileObj))
            retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, TRUE, __FILE__, __LINE__, 0L);
      
// besàlygiðkai trint negalima – gali bûti uþsilikæs EncodeEntry()
         KP_DELETEA(enc_buf);
      
      } // if(sort_buf[3*id+2]>0) && SUCCEEDED(retc))

   } // for(id=0; (id<num_of_entries) && SUCCEEDED(retc); id++)  
   
   KP_DELETEA(sort_buf);
     
return(retc);
}


// --------------------------------------------------
HRESULT LzdEnc_tag::CloseFiles(bool bCheckFileExist)
{
HRESULT retc=S_OK;
HRESULT retc0=S_OK;

   if(m_lpXdbFileObj!=NULL)
   {
      if(fclose(m_lpXdbFileObj))
         retc0=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, m_lpszXdbFileName, TRUE, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) retc=retc0;
      m_lpXdbFileObj=NULL;
   }
   else
   {
      if(!bCheckFileExist) retc=KP_E_NO_FILE;
      else retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, 0L);
   }

   if(m_lpXmlFileObj!=NULL)
   {
      if(fclose(m_lpXmlFileObj))
         retc0=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, m_lpszXmlFileName, TRUE, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) retc=retc0;
      m_lpXmlFileObj=NULL;
   }
   else
   {
      if(SUCCEEDED(retc)) retc=KP_E_NO_FILE;
      if(bCheckFileExist)
         KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, 0L);
   }

   if(m_lpSeIxFileObj!=NULL)
   {
      if(fclose(m_lpSeIxFileObj))
         retc0=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, m_lpszSeIxFileName, TRUE, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) retc=retc0;
      m_lpSeIxFileObj=NULL;
   }
   else
   {
      if(SUCCEEDED(retc)) retc=KP_E_NO_FILE;
      if(bCheckFileExist)
         KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, 0L);
   }

return(retc);
}


// --------------------
#define ARG_NUM 3

int main(int argc, char **argv)
{
HRESULT retc=S_OK;
HRESULT retc0;
int l_argc;
unsigned char *l_argv[ARG_NUM];
unsigned char cmd_line[KP_MAX_FNAME_LEN*2+2];

   printf("\nXmlt encoding");

   retc = KpErrorProc.SetLPar(0L);

   if(SUCCEEDED(retc)) retc = KpInit();

   if(SUCCEEDED(retc))
   {
      l_argc=argc;
      if(argc==ARG_NUM)
      {    
         l_argv[0]=(unsigned char *)argv[0];
         l_argv[1]=(unsigned char *)argv[1];
         l_argv[2]=(unsigned char *)argv[2];
      }
#ifdef Debug
      else
      {
         l_argc=ARG_NUM;
         l_argv[0]=(unsigned char *)"lzdenc";

//       l_argv[1]=(unsigned char *)"f:/kp/source/tev/lzdsh/lvz2.xml";
//       l_argv[1]=(unsigned char *)"f:/kp/source/tev/lzdsh/kpn2.xml";
//       l_argv[1]=(unsigned char *)"f:/kp/source/tev/lzdsh/vlzd2.xml";
//       l_argv[1]=(unsigned char *)"f:/kp/source/tev/lzdsh/elz0d.xml";
         l_argv[1]=(unsigned char *)"f:/kp/source/tev/lzdsh/elz05e.xml";

//       l_argv[2]=(unsigned char *)"f:/kp/source/tev/lzdsh/lzdsh.ini";
//       l_argv[2]=(unsigned char *)"f:/kp/source/tev/lzdsh/lzdshd.ini";
         l_argv[2]=(unsigned char *)"f:/kp/source/tev/lzdsh/lzdshp.ini";
      }

#endif

      printf(", input file %s\n\n", l_argv[1]);
   }
   
   if((l_argc!=ARG_NUM) && SUCCEEDED(retc))
   {
//    retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);
      retc=E_INVALIDARG;
      printf("Bad number of parameters, use:\n");
      printf("               c:>lzdenc.exe file.xml lzdsh.ini\n");
      printf("                                        ^\n");
      printf("             starter .ini file name ----'\n\n");
   }

// -------------------------
   KP_NEWO(pLzdEnc, LzdEnc_tag(l_argv[1]));
   if(SUCCEEDED(retc)) theKpStAppPtr = pLzdEnc;
   
// -------------------------
   if(SUCCEEDED(retc))
   {
      strncpy(cmd_line, l_argv[1], KP_MAX_FNAME_LEN);
      cmd_line[KP_MAX_FNAME_LEN] = Nul;
      strcat(cmd_line, " ");
      strncpy(cmd_line + strlen(cmd_line), l_argv[2], KP_MAX_FNAME_LEN);
      cmd_line[2*KP_MAX_FNAME_LEN] = Nul;
      
      retc = pLzdEnc->InitStApp(NULL, l_argv[2], (LPSTR)cmd_line, KpStEditMode);

   }

   if(SUCCEEDED(retc)) cMemBank[KP11_BLOCK_PROCESSING/2] = False;
   
   if(SUCCEEDED(retc)) retc = pLzdEnc->Process();

   if(pLzdEnc!=NULL)
   {
      retc0=pLzdEnc->CloseFiles(True);
      if(SUCCEEDED(retc)) retc=retc0;
   }

   if(pLzdEnc!=NULL)
   {
      retc0 = pLzdEnc->CloseStApp(retc, KP_My_Documents);
      if(SUCCEEDED(retc)) retc = retc0;
   }

   KP_DELETE(pLzdEnc);
   theKpStAppPtr = NULL;

/* if(SUCCEEDED(retc)) retc = */ KpFinit();

#ifdef Debug
system("pause");
#endif

return(RET_CODE_MAIN(retc));
}
