// ==================================================
// kpttucf.cpp
// Unicode files (UTF-8, UTF-16, UTF-16 big endian)


// ================================================== definitions
#include "stdafx.h"

#include "envir.h"

#if CompilerGr==Msvc
#include <afx.h>
#endif
#include <ctype.h>
#include <string.h>
#include <string>
#include <stdio.h>
#include <fstream>
#if OsGr==MSWin
#include <windows.h>
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
#include "kpctype.h"
#include "kpstring.h"
#include "kpctype.h"
#include "kpstdio.h"
#include "res_com.h"
#include "tvxml.h"
#include "kpwindow.h"
#include "kperr.h"
#include "tvmain.h"
#include "xmlp.h"
#include "xmlh.h"
#include "xmlf.h"
#include "kpttucf.h"


// ================================================== private methods of UcFile_tag
// ================================================== public methods of UcFile_tag
// --------------------------------------------------
UcFile::UcFile
(
const unsigned char *lpszFileName,
UC_Modes iUnicMode,
const unsigned char *lpszMode,
XmlfLowLevelCrFunPtr
#ifdef KPTTUCF_XMLF_FILE
   CreateLowLevelObj
#endif
   ,
bool
#ifdef KPTTUCF_XMLF_FILE
   bMapToPrivate
#endif
)
{
unsigned char ch;
const unsigned char *mode=(const unsigned char *)"";

   m_lhOpenResult=S_OK;

   lpFile=NULL;
   m_iUcMode=UC_No_Mode;

   m_cUnGetChLowBuf=0L;
   m_bUnGetChLowFl=False;

   m_lUnGetChBuf=0L;
   m_bUnGetChFl=False;

   iUnGetChProcBuf=C_Nul;
   bUnGetChProcFl=False;

   m_iCharPos=0;
   m_lCharNum=0L;

   if(iUnicMode==UC_UTF_7)
      m_lhOpenResult=KpErrorProc.OutputErrorMessage(E_NOTIMPL, null, True, __FILE__, __LINE__, 0L);

   strncpy((char *)lpszFName, (const char *)lpszFileName, KP_MAX_FNAME_LEN);
   lpszFName[KP_MAX_FNAME_LEN]=Nul;

   if((TvStrChr(lpszMode, C_w /* 'w' */)!=NULL) || (TvStrChr(lpszMode, C_W /* 'W' */)!=NULL))
      m_iFMode='w';
   else
   {
      if((TvStrChr(lpszMode, C_a /* 'a' */)!=NULL) || (TvStrChr(lpszMode, C_A /* 'A' */)!=NULL))
         m_iFMode='a';
      else
         m_iFMode='r';
   }

   if((iUnicMode<=UC_No_Mode) || (iUnicMode>=UC_Num_Of_Modes))
      m_lhOpenResult=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(m_lhOpenResult))
   {
      switch(m_iFMode)
      {
      case 'w':
         mode=(const unsigned char *)((iUnicMode==UC_PlainText)?"w":"wb");
#ifdef KPTTUCF_XMLF_FILE
         m_lhOpenResult=CreateLowLevelObj(&lpFile, lpszFName, mode, XL_FT_DataFile, bMapToPrivate);
         if(lpFile && SUCCEEDED(m_lhOpenResult))
            m_lhOpenResult=lpFile->SetEncoding(UC_No_Mode /* iUnicMode */, TV_CTBL_TRANSPARENT);
#else
         lpFile=fopen((const char *)lpszFName, (const char *)mode);
#endif
         if((lpFile==NULL) && SUCCEEDED(m_lhOpenResult))
            m_lhOpenResult=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, lpszFName, True, __FILE__, __LINE__, 0L);
         if(SUCCEEDED(m_lhOpenResult))
         {
            m_iUcMode=iUnicMode;
            switch(m_iUcMode)
            {
            case UC_PlainText:
            case UC_Binary:
            case UC_UTF_8:
                break;
            case UC_UTF_16:
               m_lhOpenResult=PutCharLow(0xFF);
               if(SUCCEEDED(m_lhOpenResult))
                  m_lhOpenResult=PutCharLow(0xFE);
               m_lCharNum+=2;
               break;
            case UC_UTF_16_Big_Endian:
               m_lhOpenResult=PutCharLow(0xFE);
               if(SUCCEEDED(m_lhOpenResult))
                  m_lhOpenResult=PutCharLow(0xFF);
               m_lCharNum+=2;
               break;
            default:
                m_lhOpenResult=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

            }
         }
         break;

      case 'a':
         mode=(const unsigned char *)((iUnicMode==UC_PlainText)?"a":"ab");
#ifdef KPTTUCF_XMLF_FILE
         m_lhOpenResult=CreateLowLevelObj(&lpFile, lpszFName, mode, XL_FT_DataFile, bMapToPrivate);
         if(lpFile && SUCCEEDED(m_lhOpenResult)) m_lhOpenResult=lpFile->SetEncoding(UC_No_Mode /* iUnicMode */, TV_CTBL_TRANSPARENT);
#else
         lpFile=fopen((const char *)lpszFName, (const char *)mode);
#endif
         if(lpFile==NULL)
            m_lhOpenResult=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, lpszFName, True, __FILE__, __LINE__, 0L);
         if(SUCCEEDED(m_lhOpenResult))
         {
            m_iUcMode=iUnicMode;
            switch(m_iUcMode)
            {
            case UC_PlainText:
            case UC_Binary:
            case UC_UTF_8:
            case UC_UTF_16:
            case UC_UTF_16_Big_Endian:
                break;
            default:
                m_lhOpenResult=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

            }
         }
         break;

      case 'r':
         mode=(const unsigned char *)((iUnicMode==UC_PlainText)?"r":"rb");
#ifdef KPTTUCF_XMLF_FILE
         m_lhOpenResult=CreateLowLevelObj(&lpFile, lpszFName, mode, XL_FT_DataFile, bMapToPrivate);
         if(lpFile && SUCCEEDED(m_lhOpenResult)) m_lhOpenResult=lpFile->SetEncoding(UC_No_Mode /* iUnicMode */, TV_CTBL_TRANSPARENT);

// char str_buf[200];
// sprintf(str_buf, "%lx %s", lpFile, lpszFName);
// KpMsgOut(str_buf, IDI_ASTERISK, KP_MB_TESTI);

#else
         lpFile=fopen((const char *)lpszFName, (const char *)mode);
#endif
         if(lpFile==NULL)
            m_lhOpenResult=KpErrorProc.OutputErrorMessage(KP_E_FILE_NOT_FOUND, lpszFName, True, __FILE__, __LINE__, 0L);
         if(SUCCEEDED(m_lhOpenResult))
         {
            if((iUnicMode==UC_Binary) || (iUnicMode==UC_PlainText))
                m_iUcMode=iUnicMode;
            else
            {
               m_lhOpenResult=GetCharLow(&ch);
               if(SUCCEEDED(m_lhOpenResult)) switch(ch)
               {
               case 0xFF:
                  m_iUcMode=UC_UTF_16;
                  m_lhOpenResult=GetCharLow(&ch);
                  if(ch!=0xFE)
                     m_lhOpenResult=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, lpszFName, True, __FILE__, __LINE__, 0L);
                  break;
               case 0xFE:
                  m_iUcMode=UC_UTF_16_Big_Endian;
                  m_lhOpenResult=GetCharLow(&ch);
                  if(ch!=0xFF)
                     m_lhOpenResult=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, lpszFName, True, __FILE__, __LINE__, 0L);
                  break;
               default:
                  m_iUcMode=UC_UTF_8;
                  if(SUCCEEDED(m_lhOpenResult))
                  {
//                   m_lhOpenResult=UnGetCharLow(ch);
                     m_lhOpenResult=Fseek(0L, SEEK_SET);
                  }
                  break;
               }
            }
         }

         if(SUCCEEDED(m_lhOpenResult))
            if(m_iUcMode!=iUnicMode)
               m_lhOpenResult=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, lpszFName, True, __FILE__, __LINE__, 0L);

         break;

      } // switch(m_iFMode)

   } // if(SUCCEEDED(m_lhOpenResult))
}


// --------------------------------------------------
UcFile::~UcFile(void)
{
   CloseFile(False);
}


// --------------------------------------------------
HRESULT UcFile::GetOpenResult(void)
{
return(m_lhOpenResult);
}


// --------------------------------------------------
HRESULT UcFile::GetRawFilePtr(FILE **lppFilePtrPtr)
{
HRESULT retc=S_OK;

   if((lppFilePtrPtr==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(lpFile==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      *lppFilePtrPtr=NULL;

#ifdef KPTTUCF_XMLF_FILE
      retc=lpFile->GetRawFilePtr(lppFilePtrPtr, True);
#else
      *lppFilePtrPtr=lpFile;
#endif
   }

return(retc);
}


// --------------------------------------------------
HRESULT UcFile::CloseFile(bool bCheckFileExist)
{
HRESULT retc=S_OK;
HRESULT retc0=S_OK;

   if(lpFile!=NULL)
   {
#ifdef KPTTUCF_XMLF_FILE
      retc = lpFile->CloseFile(bCheckFileExist);
      KP_DELETE(lpFile);
#else
      if(fflush(lpFile) != 0)
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, lpszFName, True, __FILE__, __LINE__, 0L);
      if(fclose(lpFile) != 0)
      {
         retc0 = KpErrorProc.OutputErrorMessage(KP_E_FERROR, lpszFName, True, __FILE__, __LINE__, 0L);
         if(SUCCEEDED(retc)) retc = retc0;
      }
      lpFile = NULL;
#endif
   }
   else
   {
      if(!bCheckFileExist) retc = KP_E_NO_FILE;
      else retc = KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
   }

return(retc);
}


// --------------------------------------------------
HRESULT UcFile::GetCharLow(unsigned char *pcChar)
{
HRESULT retc=S_OK;
KpChar ii;

   if((pcChar==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if((lpFile==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      if(m_bUnGetChLowFl)
      {
         *pcChar=m_cUnGetChLowBuf;
         m_cUnGetChLowBuf=0L;
         m_bUnGetChLowFl=False;
      }
      else
      {
#ifdef KPTTUCF_XMLF_FILE
         retc=lpFile->GetChar(&ii);
         if((ii>=KPT_Ctbsiz) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_UNKN_CHR, ii, True, __FILE__, __LINE__, 0L);
#else
         ii=(KpChar)getc(lpFile);
         if(ferror(lpFile) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, True, __FILE__, __LINE__, 0L);
         if(feof(lpFile) && SUCCEEDED(retc))
            retc=KP_E_EOF;
#endif
         if(SUCCEEDED(retc)) *pcChar=(unsigned char)ii;
      }
   }

return(retc);
}


HRESULT UcFile::GetCharLow(int *piChar)
{
HRESULT retc=S_OK;
unsigned char ch;

   if((piChar==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=GetCharLow(&ch);

   if(SUCCEEDED(retc)) *piChar=ch;

return(retc);
}


HRESULT UcFile::GetCharLow(unsigned long *plChar)
{
HRESULT retc=S_OK;
unsigned char ch;

   if((plChar==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=GetCharLow(&ch);

   if(SUCCEEDED(retc)) *plChar=ch;

return(retc);
}


// --------------------------------------------------
HRESULT GetCharLowStat(int *piChar, UcFile *pUcFile, const unsigned char ** /* ppStrPtr */)
{
HRESULT retc=S_OK;

   if(((pUcFile==NULL) || (piChar==NULL)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=pUcFile->GetCharLow(piChar);

return(retc);
}


// --------------------------------------------------
HRESULT UcFile::UnGetCharLow(unsigned char cChar)
{
HRESULT retc=S_OK;

#ifdef KPTTUCF_XMLF_FILE
   if(m_bUnGetChLowFl)
      retc=KpErrorProc.OutputErrorMessage(KP_E_DOUBLE_UNGET, null, False, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      m_cUnGetChLowBuf=cChar;
      m_bUnGetChLowFl=True;
   }
#else
   if((lpFile==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      ungetc(cChar, lpFile);
   }
#endif

return(retc);
}


// --------------------------------------------------
HRESULT UcFile::PutCharLow(unsigned char cChar)
{
HRESULT retc=S_OK;

   if((lpFile==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPTTUCF_XMLF_FILE
      retc=lpFile->PutChar((KpChar)cChar, True);
#else
      putc(cChar,lpFile);
      if((ferror(lpFile) || feof(lpFile)) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, True, __FILE__, __LINE__, 0L);
#endif
   }

return(retc);
}


HRESULT UcFile::PutCharLow(int iChar)
{
HRESULT retc=S_OK;

   if(((iChar<0) || (iChar>=KPT_Ctbsiz)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_UNKN_CHR, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=PutCharLow((unsigned char)iChar);

return(retc);
}


HRESULT UcFile::PutCharLow(unsigned long lChar)
{
HRESULT retc=S_OK;

   if((/* (lChar<0) || */ (lChar>=KPT_Ctbsiz)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_UNKN_CHR, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=PutCharLow((unsigned char)lChar);

return(retc);
}


// --------------------------------------------------
extern HRESULT GetEncodeUniChar(unsigned long *plInCh, HRESULT (*GetCharLowCallBack)(int *, UcFile *, const unsigned char **), UcFile *pUcFile, const unsigned char **ppStrPtr, UC_Modes iUcMode)
{
HRESULT retc=S_OK;
int add_bytes;
int ii;
int kk;

   if(((plInCh==NULL) || (GetCharLowCallBack==NULL)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) switch(iUcMode)
   {
   case UC_UTF_8:
      add_bytes=0;
      retc=GetCharLowCallBack(&ii, pUcFile, ppStrPtr);

      if(SUCCEEDED(retc))
      {

// 7-bit character?
         if((ii & 0x80)!=0)
         {
            if((ii & 0x40)!=0)
            {
               add_bytes++;
               if((ii & 0x20)!=0)
               {
                  add_bytes++;
                  if((ii & 0x10)!=0)
                  {
                     add_bytes++;
                     if((ii & 0x8)==0)
                        *plInCh=ii & 0x7;
                     else
                     {
                        retc=KP_E_FILE_FORMAT;
                        KpErrorProc.OutputErrorMessage(retc, (pUcFile?pUcFile->lpszFName:NULL), False, __FILE__, __LINE__, 0L);
                     }
                  }
                  else *plInCh=ii & 0xF;
               }
               else *plInCh=ii & 0x1F;
            }
            else
            {
               retc=KP_E_FILE_FORMAT;
               KpErrorProc.OutputErrorMessage(retc, (pUcFile?pUcFile->lpszFName:null), False, __FILE__, __LINE__, 0L);
            }
         }
         else *plInCh=ii;
      }

// additional bytes
      if(SUCCEEDED(retc))
      {
         for(kk=0; (kk<add_bytes) && SUCCEEDED(retc); kk++)
         {
            retc=GetCharLowCallBack(&ii, pUcFile, ppStrPtr);
            if(retc==KP_E_EOF)
               KpErrorProc.OutputErrorMessage(retc, (pUcFile?pUcFile->lpszFName:NULL), False, __FILE__, __LINE__, 0L);

            if(SUCCEEDED(retc))
            {
               if((ii & 0xC0) == 0x80)
                  *plInCh = (*plInCh << 6) | (ii & 0x3F);
               else
               {
                  retc=KP_E_FILE_FORMAT;
                  KpErrorProc.OutputErrorMessage(retc, (pUcFile?pUcFile->lpszFName:NULL), False, __FILE__, __LINE__, 0L);
               }
            }
         }
      }

// Cr Lf
      if(SUCCEEDED(retc))
      {
// #ifndef KPTTUCF_XMLF_FILE
         while(*plInCh==C_Cr) // '\r'
// #endif
         {
            retc=GetCharLowCallBack(&ii, pUcFile, ppStrPtr);

            if(SUCCEEDED(retc))
            {
            /* if(ii==C_Lf) */ *plInCh=ii; // '\n'
//             else ungetc(ii,lpFile);
            }
         }
      }

      break;

   default:
      retc=E_NOTIMPL;
      break;
   }

return(retc);
}


HRESULT GetEncodeKpUniChar(KpChar *piInCh, HRESULT (*GetCharLowCallBack)(int *, UcFile *, unsigned char const **), UcFile *pUcFile, unsigned char const **ppStrPtr, UC_Modes iUcMode)
{
HRESULT retc=S_OK;
unsigned long ll;
int kk;

   *piInCh=C_Nul;

   retc=GetEncodeUniChar(&ll, GetCharLowCallBack, pUcFile, ppStrPtr, iUcMode);

   if(SUCCEEDED(retc))
   {
      if((ll>=KPT_UniPrivateStart) && (ll<KPT_UniPrivateEnd))
      {
         *piInCh=KpChar(ll-KPT_UniPrivateStart);
         kk=0;
      }
      else
         for(kk=0; kk<C_CharSize0; kk++)
         {
            if(iaUniChars[kk]==ll)
            {
               *piInCh=(KpChar)kk;
               break;
            }
         }
   }

   if(((kk<0) || (kk>=C_CharSize0)) && SUCCEEDED(retc))
   {
      *piInCh=C_Quest;
      retc=KpErrorProc.OutputErrorMessage(KP_E_UNKN_CHR, null, False, __FILE__, __LINE__, 0L);
   }

return(retc);
}


// --------------------------------------------------
HRESULT UcFile::GetChar(unsigned long *plInCh)
{
HRESULT retc=S_OK;
// int add_bytes;
int ii;
int jj;
// int kk;
unsigned long ll;

   if((plInCh==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if((lpFile==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      *plInCh=0L;

      if(m_bUnGetChFl)
      {
         *plInCh=m_lUnGetChBuf;
         m_lUnGetChBuf=0L;
         m_bUnGetChFl=False;
      }
      else
      {
         switch(m_iUcMode)
         {
         case UC_Binary:
         case UC_PlainText:
            retc=GetCharLow(plInCh);
            break;

         case UC_UTF_8:

#if FALSE
// first byte
            add_bytes=0;
            retc=GetCharLow(&ii);

            if(SUCCEEDED(retc))
            {

// 7-bit character?
               if((ii & 0x80)!=0)
               {
                  if((ii & 0x40)!=0)
                  {
                     add_bytes++;
                     if((ii & 0x20)!=0)
                     {
                        add_bytes++;
                        if((ii & 0x10)!=0)
                        {
                           add_bytes++;
                           if((ii & 0x8)==0)
                              *plInCh=ii & 0x7;
                           else
                              retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, lpszFName, True, __FILE__, __LINE__, 0L);
                        }
                        else *plInCh=ii & 0xF;
                     }
                     else *plInCh=ii & 0x1F;
                  }
                  else
                     retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, lpszFName, True, __FILE__, __LINE__, 0L);
               }
               else *plInCh=ii;
            }

// additional bytes
            if(SUCCEEDED(retc))
            {
               for(kk=0; (kk<add_bytes) && SUCCEEDED(retc); kk++)
               {
                  retc=GetCharLow(&ii);
                  if(retc==KP_E_EOF)
                     retc=KpErrorProc.OutputErrorMessage(retc, lpszFName, True, __FILE__, __LINE__, 0L);

                  if(SUCCEEDED(retc))
                  {
                     if((ii & 0xC0) == 0x80)
                        *plInCh = (*plInCh << 6) | (ii & 0x3F);
                     else
                        retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, lpszFName, True, __FILE__, __LINE__, 0L);
                  }
               }
            }

// Cr Lf
            if(SUCCEEDED(retc))
            {
// #ifndef KPTTUCF_XMLF_FILE
               while(*plInCh==C_Cr) // '\r'
// #endif
               {
                  retc=GetCharLow(&ii);

                  if(SUCCEEDED(retc))
                  {
                  /* if(ii==C_Lf) */ *plInCh=ii; // '\n'
//                   else ungetc(ii,lpFile);
                  }
               }
            }
#endif
            retc=GetEncodeUniChar(plInCh, GetCharLowStat, this, NULL, m_iUcMode);

            break;

         case UC_UTF_16:
            retc=GetCharLow(&ii);
            if(SUCCEEDED(retc)) retc=GetCharLow(&jj);

            if(SUCCEEDED(retc))
            {
               if((jj & 0xFC)==0xDC)
               {
                  *plInCh = ii | ((jj & 0x3) << 8);

                  retc=GetCharLow(&ii);
                  if(SUCCEEDED(retc)) retc=GetCharLow(&jj);
                  if(retc==KP_E_EOF)
                     retc=KpErrorProc.OutputErrorMessage(retc, lpszFName, True, __FILE__, __LINE__, 0L);

                  if(SUCCEEDED(retc))
                  {
                     if((jj & 0xFC)==0xD8)
                        *plInCh |= (ii | ((jj & 0x3) << 8)) << 10;
                     else
                        retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, lpszFName, True, __FILE__, __LINE__, 0L);
                  }
               }
               else *plInCh = ii | (jj<<8);
            }

// Cr Lf
            if(SUCCEEDED(retc))
            {
// #ifndef KPTTUCF_XMLF_FILE
               while(*plInCh==C_Cr) // '\r'
// #endif
               {
                  retc=GetCharLow(&ii);
                  if(SUCCEEDED(retc)) retc=GetCharLow(&jj);

                  if(SUCCEEDED(retc))
                  {
                     ll= ii | (jj<<8);

                  /* if(ll==C_Lf) */ *plInCh=ll; // '\n'
//                   else
//                   {
//                      ungetc(jj,lpFile);
//                      ungetc(ii,lpFile);
//                   }
                  }
               }
            }
            break;

         case UC_UTF_16_Big_Endian:
            retc=GetCharLow(&ii);
            if(SUCCEEDED(retc)) retc=GetCharLow(&jj);

            if(SUCCEEDED(retc))
            {
               if((ii & 0xFC)==0xD8)
               {
                  *plInCh = (jj | ((ii & 0x3) << 8)) << 10;

                  retc=GetCharLow(&ii);
                  if(SUCCEEDED(retc)) retc=GetCharLow(&jj);
                  if(retc==KP_E_EOF)
                     KpErrorProc.OutputErrorMessage(retc, lpszFName, True, __FILE__, __LINE__, 0L);

                  if(SUCCEEDED(retc))
                  {
                     if((ii & 0xFC)==0xDC)
                        *plInCh |= jj | ((ii & 0x3) << 8);
                     else
                        retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, lpszFName, True, __FILE__, __LINE__, 0L);
                  }
               }
               else *plInCh = jj | (ii<<8);
            }

// Cr Lf
            if(SUCCEEDED(retc))
            {
// #ifndef KPTTUCF_XMLF_FILE
               while(*plInCh==C_Cr) // '\r'
// #endif
               {
                  retc=GetCharLow(&ii);
                  if(SUCCEEDED(retc)) retc=GetCharLow(&jj);

                  if(SUCCEEDED(retc))
                  {
                     ll = jj | (ii<<8);

                  /* if(ll==C_Lf) */ *plInCh=ll; // '\n'
//                   else
//                   {
//                      ungetc(jj,lpFile);
//                      ungetc(ii,lpFile);
//                   }
                  }
               }
            }
            break;

         default:
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
            break;

         } // switch(m_iUcMode)

      } // else // if(m_bUnGetChFl)

   } // if(SUCCEEDED(retc))

return(retc);
}


// --------------------------------------------------
HRESULT UcFile::UnGetChar(unsigned long lChar)
{
HRESULT retc=S_OK;

   if(m_bUnGetChFl)
      retc=KpErrorProc.OutputErrorMessage(KP_E_DOUBLE_UNGET, null, False, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      m_lUnGetChBuf=lChar;
      m_bUnGetChFl=True;
   }

return(retc);
}


// --------------------------------------------------
HRESULT UcFile::GetCharProc(KpChar *piInCh)
{
HRESULT retc=S_OK;
unsigned long ll;
int kk;

   *piInCh=C_Nul;

   if(bUnGetChProcFl)
   {
      *piInCh=iUnGetChProcBuf;
      iUnGetChProcBuf=C_Nul;
      bUnGetChProcFl=False;
   }
   else
   {
      retc=GetChar(&ll);

      if(SUCCEEDED(retc))
      {
         if((ll>=KPT_UniPrivateStart) && (ll<KPT_UniPrivateEnd))
         {
            *piInCh=KpChar(ll-KPT_UniPrivateStart);
            kk=0;
         }
         else
            for(kk=0; kk<C_CharSize0; kk++)
            {
               if(iaUniChars[kk]==ll)
               {
                  *piInCh=(KpChar)kk;
                  break;
               }
            }
      }

      if(((kk<0) || (kk>=C_CharSize0)) && SUCCEEDED(retc))
      {
         *piInCh=C_Quest;
         retc=KpErrorProc.OutputErrorMessage(KP_E_UNKN_CHR, null, False, __FILE__, __LINE__, 0L);
      }
   }

return(retc);
}


// --------------------------------------------------
HRESULT UcFile::UnGetCharProc(KpChar iChar)
{
HRESULT retc=S_OK;

   if(bUnGetChProcFl)
      retc=KpErrorProc.OutputErrorMessage(KP_E_DOUBLE_UNGET, null, False, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      iUnGetChProcBuf=iChar;
      bUnGetChProcFl=True;
   }

// if(SUCCEEDED(retc))
// {
//    m_iCharPos--;
//    if((m_iCharPos<0) || (TvStrChr(lpszEols, iChar)!=NULL)) m_iCharPos=0;  // does not process line positions after ungetting of Lf !!!
//    m_lCharNum--;
// }

return(retc);
}


// --------------------------------------------------
HRESULT UcFile::GetIntStr(KpChar *lpaizInBuf, int iBufSize)
{
HRESULT retc=S_OK;
KpChar *pnti;
bool eol_fl;

   if(lpaizInBuf==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, lpszFName, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      pnti=lpaizInBuf;
      eol_fl=False;
      do
      {
         if(pnti-lpaizInBuf>=iBufSize-1)
            retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, lpszFName, True, __FILE__, __LINE__, 0L);
         if(SUCCEEDED(retc)) retc=GetCharProc(pnti);
         if((*pnti==C_Lf) && SUCCEEDED(retc)) eol_fl=True;
         if((!eol_fl) && (*pnti!=C_Cr) && SUCCEEDED(retc)) pnti++;

      } while((!eol_fl) && SUCCEEDED(retc));

      if(pnti-lpaizInBuf<iBufSize) *pnti=C_Nul;
   }

return(retc);
}


// --------------------------------------------------
HRESULT UcFile::PutChar(unsigned long lOutCh)
{
HRESULT retc=S_OK;
int kk;
unsigned long ll;
unsigned char bytes[4+1];
int num_bytes;

   if(lpFile==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      m_iCharPos++;
      if(TvStrChr(lpszEols, (KpChar)lOutCh)!=NULL)
         m_iCharPos=0;

      switch(m_iUcMode)
      {
      case UC_Binary:
      case UC_PlainText:
         if((/* (lOutCh<0L) || */ (lOutCh>=KPT_Ctbsiz)) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, lpszFName, True, __FILE__, __LINE__, 0L);
         if(SUCCEEDED(retc)) retc=PutCharLow(lOutCh);
         if(SUCCEEDED(retc)) m_lCharNum++;
         break;

      case UC_UTF_8:

// Cr Lf
         if(lOutCh==C_Lf) // '\n'
         {
// #ifndef KPTTUCF_XMLF_FILE
            retc=PutCharLow(C_Cr); // '\r'
// #endif
            if(SUCCEEDED(retc)) m_lCharNum++;
         }

         num_bytes=0;
         if(SUCCEEDED(retc))
         {
            retc=EncodeUnicodeChar(bytes, &num_bytes, lOutCh, m_iUcMode);
            if(FAILED(retc))
               retc=KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);
         }

         if(SUCCEEDED(retc))
         {
            for(kk=0; (kk<num_bytes) && SUCCEEDED(retc); kk++)
            {
               retc=PutCharLow(bytes[kk]);
               m_lCharNum++;
            }

         }  // if(SUCCEEDED(retc))

         break;

      case UC_UTF_16:
// Cr Lf
         if(lOutCh==C_Lf) // '\n'
         {
// #ifndef KPTTUCF_XMLF_FILE
            retc=PutCharLow(C_Cr); // '\r'
            if(SUCCEEDED(retc)) retc=PutCharLow(0);
// #endif
            if(SUCCEEDED(retc)) m_lCharNum+=2;
         }

         if(SUCCEEDED(retc))
         {

            if((lOutCh>0xFFFF) || ((lOutCh & 0xFC00) == 0xDC00))
            {
// two words
               ll=lOutCh;
               retc=PutCharLow(ll & 0xFF); m_lCharNum++;
               if(SUCCEEDED(retc))
               {
                  ll = ll >> 8;
                  retc=PutCharLow(0xDC | (ll & 0x03)); m_lCharNum++; // 0xDC00 ???
               }
               if(SUCCEEDED(retc))
               {
                  ll = ll >> 2;
                  retc=PutCharLow(ll & 0xFF); m_lCharNum++;
               }
               if(SUCCEEDED(retc))
               {
                  ll = ll >> 8;
                  retc=PutCharLow(0xD8 | (ll & 0x03)); m_lCharNum++; // 0xD800 ???
               }
               if(((ll & ~0x03L)!=0L) && SUCCEEDED(retc))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_UNKN_CHR, null, True, __FILE__, __LINE__, 0L);
            }
            else
            {
               ll=lOutCh;
               retc=PutCharLow(ll & 0xFF); m_lCharNum++;
               if(SUCCEEDED(retc))
               {
                  ll = ll >> 8;
                  retc=PutCharLow(ll & 0xFF); m_lCharNum++;
               }
               if(((ll & ~0xFFL)!=0L) && SUCCEEDED(retc))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_UNKN_CHR, null, True, __FILE__, __LINE__, 0L);
            }

         } // if(SUCCEEDED(retc))

         break;

      case UC_UTF_16_Big_Endian:
// Cr Lf
         if(lOutCh==C_Lf) // '\n'
         {
// #ifndef KPTTUCF_XMLF_FILE
            retc=PutCharLow(0);
            if(SUCCEEDED(retc)) retc=PutCharLow(C_Cr); // '\r'
// #endif
            if(SUCCEEDED(retc)) m_lCharNum+=2;
         }

         if(SUCCEEDED(retc))
         {

            if((lOutCh>0xFFFF) || ((lOutCh & 0xFC00) == 0xD800))
            {
// two words
               ll=lOutCh;
               bytes[3] = (unsigned char)(ll & 0xFF);
               ll = ll >> 8;
               bytes[2] = (unsigned char)(0xDC | (ll & 0x03)); // 0xDC00 ???
               ll = ll >> 2;
               bytes[1] = (unsigned char)(ll & 0xFF);
               ll = ll >> 8;
               bytes[0] = (unsigned char)(0xD8 | (ll & 0x03)); // 0xD800 ???
               if((ll & ~0x03L)!=0L)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_UNKN_CHR, null, True, __FILE__, __LINE__, 0L);

               if(SUCCEEDED(retc))
                  for(kk=0; (kk<4) && SUCCEEDED(retc); kk++)
                  {
                     retc=PutCharLow(bytes[kk]);
                     m_lCharNum++;
                  }
            }
            else
            {
               ll=lOutCh;
               bytes[1] = (unsigned char)(ll & 0xFF);
               ll = ll >> 8;
               bytes[0] = (unsigned char)(ll & 0xFF);
               if((ll & ~0xFFL)!=0L)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_UNKN_CHR, null, True, __FILE__, __LINE__, 0L);
               retc=PutCharLow(bytes[0]); m_lCharNum++;
               if(SUCCEEDED(retc)){ retc=PutCharLow(bytes[1]); m_lCharNum++; }
            }

         } // if(SUCCEEDED(retc))

         break;

      default:
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
         break;

      } // switch(m_iUcMode)

   } // if(SUCCEEDED(retc))

return(retc);
}


// --------------------------------------------------
HRESULT UcFile::PutCharProc(KpChar iOutCh, bool bCheckFlg, bool bMapToPrivate)
{
HRESULT retc=S_OK;

   if((iOutCh>=0) && (iOutCh<C_CharSize0))
   {
      if(iaUniChars[iOutCh] != C_Nul) retc = PutChar(iaUniChars[iOutCh]);
      else
      {
         if(bMapToPrivate) retc = PutChar(KPT_UniPrivateStart+iOutCh);
         else
         {
//          KP_ERRORWE(KP_E_UNKN_CHR, null, bCheckFlg);
            retc = KP_E_UNKN_CHR;
            KpErrorProc.OutputErrorMessage(retc, null, bCheckFlg, __FILE__, __LINE__, iOutCh, NULL, True, bCheckFlg);
         }
      }
   }
   else
   {
//    KP_ERROR(KP_E_UNKN_CHR, null);
      retc = KP_E_UNKN_CHR;
      KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, iOutCh);
   }

return(retc);
}


// --------------------------------------------------
HRESULT UcFile::PutStrProc(const unsigned char *lpszOutStr, bool bMapToPrivate)
{
HRESULT retc=S_OK;
const unsigned char *pnts;

   pnts=lpszOutStr;

   while((*pnts) && SUCCEEDED(retc))
      retc=PutCharProc((KpChar)(*pnts++), True, bMapToPrivate);

return(retc);
}


// --------------------------------------------------
HRESULT UcFile::GetCharPos(int *pm_iCharPos)
{
HRESULT retc=S_OK;

   if(pm_iCharPos==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc)) *pm_iCharPos=m_iCharPos;

return(retc);
}


// --------------------------------------------------
HRESULT UcFile::GetCharNum(long *pm_lCharNum)
{
HRESULT retc=S_OK;

   if(pm_lCharNum==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc)) *pm_lCharNum=m_lCharNum;

return(retc);
}


// --------------------------------------------------
HRESULT UcFile::Ftell(long *plOffset)
{
HRESULT retc=S_OK;
FILE *raw_file=NULL;

   if((plOffset==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=GetRawFilePtr(&raw_file);

   if((raw_file==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      *plOffset=ftell(raw_file);
      if(*plOffset==(-1L))
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, lpszFName, True, __FILE__, __LINE__, 0L);
   }

return(retc);
}


// --------------------------------------------------
HRESULT UcFile::Fseek(long lOffset, int iOrigin)
{
HRESULT retc=S_OK;
FILE *raw_file=NULL;

#ifdef KPTTUCF_XMLF_FILE
   if((lpFile==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=lpFile->Fseek(lOffset, iOrigin);
#else
   if(SUCCEEDED(retc)) retc=GetRawFilePtr(&raw_file);

   if((raw_file==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
      if(fseek(raw_file, lOffset, iOrigin)!=0)
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, lpszFName, True, __FILE__, __LINE__, 0L);
#endif

return(retc);
}


// --------------------------------------------------
HRESULT UcFile::Fscanf(const char *lpszFormat, void *pValue)
{
HRESULT retc=S_OK;
FILE *raw_file=NULL;

   if(((lpszFormat==NULL) || (pValue==NULL)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=GetRawFilePtr(&raw_file);

   if((raw_file==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      fscanf(raw_file, lpszFormat, pValue);
      if(ferror(raw_file))
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, lpszFName, True, __FILE__, __LINE__, 0L);
      if(feof(raw_file) && SUCCEEDED(retc)) retc=KP_E_EOF;
   }

return(retc);
}


// --------------------------------------------------
HRESULT UcFile::Fread(void *pvBufPtr, int iBytCnt)
{
HRESULT retc=S_OK;
FILE *raw_file=NULL;

   if((pvBufPtr==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=GetRawFilePtr(&raw_file);

   if((raw_file==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      fread(pvBufPtr, 1, iBytCnt, raw_file);
      if(ferror(raw_file))
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, lpszFName, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc) && feof(raw_file)) retc=KP_E_EOF;
   }

return(retc);
}


// --------------------------------------------------
HRESULT UcFile::Fwrite(const void *lpvBuffer, int iByteCount)
{
HRESULT retc=S_OK;
FILE *raw_file=NULL;

   if((lpvBuffer==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=GetRawFilePtr(&raw_file);

   if((raw_file==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      fwrite(lpvBuffer, 1, iByteCount, raw_file);
      m_lCharNum+=iByteCount;
      if(ferror(raw_file) || feof(raw_file))
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, lpszFName, True, __FILE__, __LINE__, 0L);
   }

return(retc);
}


// ------------------------------------
HRESULT EncodeUnicodeChar(unsigned char *lpcOutChars, int *piByteCount, long lOutCh, UC_Modes iUcMode)
{
HRESULT retc=S_OK;
int add_bytes;
unsigned long ll;
int kk;
unsigned int ii;
unsigned int jj;

   if((lpcOutChars==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) switch(iUcMode)
   {
   case UC_UTF_8:

// byte count
      add_bytes=0;
      if(lOutCh>0x007F) add_bytes++;
      if(lOutCh>0x07FF) add_bytes++;
      if(lOutCh>0xFFFF) add_bytes++;

      ll=lOutCh;
      for(kk=0; kk<add_bytes; kk++)
      {
         lpcOutChars[add_bytes-kk]=(unsigned char)(0x80 | (ll & 0x3F));
         ll = ll >> 6;
      }

      lpcOutChars[0]=(unsigned char)(ll); // & 0xFF ???
      ii=0x40;
      jj=0x80;
      if(add_bytes>0)
      {
         for(kk=0; (kk<add_bytes+1) && SUCCEEDED(retc); kk++)
         {
            if((lpcOutChars[0] & ii)!=0) retc=KP_E_UNKN_CHR;
            lpcOutChars[0] &= (unsigned char)(~ii); // & 0xFF ???
            lpcOutChars[0] |= (unsigned char)(jj); // & 0xFF ???
            ii = ii>>1;
            jj = jj>>1;
         }
      }
      else if((lpcOutChars[0] & 0x80)!=0) retc=KP_E_UNKN_CHR;

      lpcOutChars[add_bytes+1]=Nul;

      if(piByteCount) *piByteCount=add_bytes+1;
      break;

   default:
      retc=E_NOTIMPL;
      break;
   }

return(retc);
}

// ------------------------------------
HRESULT EncodeUnicodeKpChar(unsigned char *lpcOutChars, int *piByteCount, KpChar iOutCh, UC_Modes iUcMode)
{
HRESULT retc=S_OK;

   if(((lpcOutChars==NULL) || (iOutCh>=C_CharSize0)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) if(iaUniChars[iOutCh]==C_Nul) retc=KP_E_UNKN_CHR;

   if(SUCCEEDED(retc)) retc=EncodeUnicodeChar(lpcOutChars, piByteCount, iaUniChars[iOutCh], iUcMode);

return(retc);
}


// ------------------------------------
HRESULT EncodeUnicodeKpStr(unsigned char *lpszOutStr, int iBufSize, const KpChar *iazInStr, UC_Modes iUcMode)
{
HRESULT retc=S_OK;
const KpChar *pnts;
unsigned char *pntd;
int num_bytes;

   if(((lpszOutStr==NULL) || (iazInStr==NULL)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      pnts=iazInStr;
      pntd=lpszOutStr;

      while(*pnts && SUCCEEDED(retc))
      {
         if(pntd-lpszOutStr+4+1>=iBufSize) retc=KP_E_BUFFER_OVERFLOW;

         if(SUCCEEDED(retc)) retc=EncodeUnicodeKpChar(pntd, &num_bytes, *pnts++, iUcMode);

         if(SUCCEEDED(retc)) pntd+=num_bytes;
      }
   }

return(retc);
}


// ------------------------------------
HRESULT GetCharStr(int *piChar, UcFile * /* pUcFile */, const unsigned char **ppStrPtr)
{
HRESULT retc=S_OK;

   if(((piChar==NULL) || (ppStrPtr==NULL)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) if(**ppStrPtr==Nul) retc = KP_E_EOF;

   if(SUCCEEDED(retc)) *piChar = *((*ppStrPtr)++);

return(retc);
}


HRESULT DecodeKpStrUnicode(KpChar *iazInStr, int iBufSize, const unsigned char *lpszOutStr, UC_Modes iUcMode)
{
HRESULT retc=S_OK;
const unsigned char *pnts;
KpChar *pntd;
KpChar in_ch;

   if(((lpszOutStr==NULL) || (iazInStr==NULL)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      pnts=lpszOutStr;
      pntd=iazInStr;
      while((*pnts) && SUCCEEDED(retc))
      {
         retc=GetEncodeKpUniChar(&in_ch, GetCharStr, NULL, &pnts, iUcMode);
         if((pntd-iazInStr >= iBufSize-1) && SUCCEEDED(retc)) retc=KP_E_BUFFER_OVERFLOW;
         if(SUCCEEDED(retc)) *pntd++ = in_ch;
      }

      if(iBufSize>0) *pntd=C_Nul;
   }

return(retc);
}

