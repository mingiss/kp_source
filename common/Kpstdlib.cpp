// ==================================================
// kpstdlib.cpp
// common tools
//


// ======================================= definitions
#include "stdafx.h"

#include "envir.h"
#include "iBshn.h"
#include "lzdshn.h"

#if CompilerGr==Msvc
#include <afx.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string>
#include <math.h>
#include <fstream>
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <richedit.h>
#include <Richole.h>
#if (CompilerGr==Watcom) && (__WATCOMC__ >= 1202)
#include <shlobj.h>
#endif

#if Envir==MSWin32
#include "res_com.h"
#endif

#ifdef IBSH_RES_MODE_XGECKO
#if CompilerGr==Mingw
#include "IInputStream.hh"
#include "IString.hh"
#include "XApplication.hh"
#include "XGecko.hh"
#include "XGeckoDOMEvent.hh"
#include "XGeckoInit.hh"
#endif
#endif

#if Compiler != Watcom
using namespace std;
#endif

#include "kpstdlib.h"
#include "kperrno.h"
#include "kpmsg.h"
#include "kptt.h"
#include "kptree.h"
#include "kpthp.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpctype.h"
#include "kpcolors.h"
#include "kpfonts.h"
#include "kpstdio.h"
#include "kpttucf.h"
#include "res_com.h"
#include "tvxml.h"
#include "kpwindow.h"
#include "kpsock.h"
#include "kperr.h"
#include "kphp11i.h"
#include "kphp11t.h"
#include "kphp11y.h"
#include "kphp11d.h"
#include "kphp11rc.h"
#include "kpcapp.h"
#include "tvmain.h"
#include "tvrtf.h"
#include "tvrtfo.h"
#include "tvtex.h"
#include "tvxml.h"
#include "xmlp.h"
#include "xmlh.h"
#include "xmlf.h"
#include "xml8.h"
#include "xmlu.h"
#include "xmlo1.h"
#include "xmlt.h"
#include "xmlis.h"
#include "xmli.h"
#include "KpFileSys.h"
#include "KpPubDlg.h"
#include "xmln.h"
#include "kpstap.h"



// ================================================== global variables
// -------------------------------------------
void *StackTop = NULL;

unsigned char lpszMathOperators[] = {"+-*/!=<>&|"};

#ifdef KP_ALLOC_SAFE
KpHeapEntry KpHeapArray[KP_HEAP_SIZE];
int iCurKpHeapIx = 0; // einamasis KpHeapArray elementø skaièius
#endif


// ================================================== malloc
int SearchHeapEntry(const void *pPtr) // -1 – nerado
{
HRESULT retc = S_OK;
int ret_val = -1;

   for(int ii = 0; ii < iCurKpHeapIx; ii++)
      if(KpHeapArray[ii].m_pAddress == pPtr)
      {
         ret_val = ii;
         break;
      }

return(ret_val);
}


HRESULT InsertHeapPtr(const void *pNewPtr, bool bArrayFl)
{
HRESULT retc = S_OK;
HRESULT retc0 = S_OK;

unsigned char msg_out[MAX_LONG_HEX_DIGITS + 5];
   sprintf((char *)msg_out, "%x", pNewPtr);

int ix = SearchHeapEntry(pNewPtr);
   KP_ASSERT0E(ix < 0, KP_E_DOUBLE_CALL, null, False);

   KP_ASSERT0E(iCurKpHeapIx < KP_HEAP_SIZE - 1, KP_E_BUFFER_OVERFLOW, msg_out, False);
   if(SUCCEEDED(retc0))
   {
      KpHeapArray[iCurKpHeapIx].m_pAddress = pNewPtr;
      KpHeapArray[iCurKpHeapIx].m_bArrayFl = bArrayFl;
      iCurKpHeapIx++;
   }

return(S_OK);
}


HRESULT RemoveHeapPtr(const void *pDelPtr, bool bArrayFl)
{
HRESULT retc = S_OK;
HRESULT retc0 = S_OK;

unsigned char msg_out[MAX_LONG_HEX_DIGITS + 5];
   sprintf((char *)msg_out, "%x", pDelPtr);

int ix = SearchHeapEntry(pDelPtr);
   KP_ASSERT0E(ix >= 0, KP_E_SYSTEM_ERROR, msg_out, False);
   KP_ASSERT0E(KpHeapArray[ix].m_bArrayFl == bArrayFl, KP_E_SYSTEM_ERROR, msg_out, False);
   if(FAILED(retc0)) StackDump(&retc);

   if((ix >= 0) /* SUCCEEDED(retc0) */)
   {
      memmove(&(KpHeapArray[ix]), &(KpHeapArray[ix + 1]), (iCurKpHeapIx - ix - 1) * sizeof(KpHeapEntry));
      iCurKpHeapIx--;
   }

return(retc0);
}


//============================================ date/time
// ----------------------
bool IsLeapYear(int iYear)
{
return((iYear%4==0) && (iYear%100!=0));
}


// ----------------------
HRESULT CheckKpDate(KpDate lDate)
{
HRESULT retc=S_OK;
int year, month, day;

   retc=ExtractRawKpDate(lDate, &year, &month, &day);

   if(
      (
         (year==0) ||
         (month<0 /* <1 */) || (month>12) ||
         (day<0 /* <1 */) || (day>31)
      ) &&
      SUCCEEDED(retc)
     )
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(
      ((month==4) || (month==6) || (month==9) || (month==11)) &&
      (day>30) &&
      SUCCEEDED(retc)
     )
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if((month==2) && (day>29) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if((!IsLeapYear(year)) && (month==2) && (day>28) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

return(retc);
}


// ----------------------
HRESULT ExtractRawKpDate(KpDate lDate, int *piYear, int *piMonth, int *piDay)
{
HRESULT retc=S_OK;

   if((piYear==NULL) || (piMonth==NULL) || (piDay==NULL))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      *piYear= ((lDate&KP_DATE_YEAR_MASK )>>KP_DATE_YEAR_POS);
      *piMonth=((lDate&KP_DATE_MONTH_MASK)>>KP_DATE_MONTH_POS);
      *piDay=  ((lDate&KP_DATE_DAY_MASK  )>>KP_DATE_DAY_POS);
   }

return(retc);
}


// ----------------------
HRESULT ExtractKpDate(KpDate lDate, int *piYear, int *piMonth, int *piDay)
{
HRESULT retc=S_OK;

   retc=CheckKpDate(lDate);

   if(SUCCEEDED(retc))
      retc=ExtractRawKpDate(lDate, piYear, piMonth, piDay);

return(retc);
}


// ----------------------
HRESULT ComposeRawKpDate(KpDate *plDate, int iYear, int iMonth, int iDay)
{
HRESULT retc=S_OK;

   if(
      (plDate==NULL) ||
      (
         ((iYear&(~(KP_DATE_YEAR_MASK>>KP_DATE_YEAR_POS)))!=0L) &&
         ((iYear|(KP_DATE_YEAR_MASK>>KP_DATE_YEAR_POS))!= -1L)
      ) ||
      ((iMonth&(~(KP_DATE_MONTH_MASK>>KP_DATE_MONTH_POS)))!=0L) ||
      ((iDay&(~(KP_DATE_DAY_MASK>>KP_DATE_DAY_POS)))!=0L)
     )
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      *plDate=
         (
            ((iYear<<KP_DATE_YEAR_POS)&KP_DATE_YEAR_MASK) |
            ((iMonth<<KP_DATE_MONTH_POS)&KP_DATE_MONTH_MASK) |
            ((iDay<<KP_DATE_DAY_POS)&KP_DATE_DAY_MASK)
         );
   }

return(retc);
}


// ----------------------
HRESULT ComposeKpDate(KpDate *plDate, int iYear, int iMonth, int iDay)
{
HRESULT retc=S_OK;

   retc=ComposeRawKpDate(plDate, iYear, iMonth, iDay);

   if(SUCCEEDED(retc)) retc=CheckKpDate(*plDate);

return(retc);
}


// ----------------------
HRESULT GetWeekNumber(LPSYSTEMTIME lpSystemTime, int *piWeekOfTheYear)
{
HRESULT retc=S_OK;
int day_num;
int week_day;

   if((lpSystemTime==NULL) || (piWeekOfTheYear==NULL))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc))
      retc=GetDayOfYear(lpSystemTime, &day_num);

   if(SUCCEEDED(retc))
   {
      week_day=lpSystemTime->wDayOfWeek-1;
      if(week_day<0) week_day=6;

      day_num-=week_day+1;
      if(day_num<0) day_num=0;

      *piWeekOfTheYear=day_num/7+1;
   }

return(retc);
}


// ----------------------
HRESULT GetDayOfYear(LPSYSTEMTIME lpSystemTime, int *piDayOfTheYear)
{
HRESULT retc=S_OK;
int days;
int ii;

   if((lpSystemTime==NULL) || (piDayOfTheYear==NULL))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc))
   {
      *piDayOfTheYear=lpSystemTime->wDay;
      for(ii=1; (ii<=lpSystemTime->wMonth-1) && SUCCEEDED(retc); ii++)
      {
         retc=GetMonthsDayCount(lpSystemTime->wYear, ii, &days);
         if(SUCCEEDED(retc)) *piDayOfTheYear+=days;
      }
   }

return(retc);
}


// ----------------------
HRESULT GetMonthsDayCount(int iYear, int iMonth, int *piNumOfDays)
{
HRESULT retc=S_OK;

   if((piNumOfDays==NULL) || (iMonth<1) || (iMonth>12))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc)) switch(iMonth)
   {
   case 1: *piNumOfDays=31; break;
   case 2: *piNumOfDays=28+IsLeapYear(iYear); break;
   case 3: *piNumOfDays=31; break;
   case 4: *piNumOfDays=30; break;
   case 5: *piNumOfDays=31; break;
   case 6: *piNumOfDays=30; break;
   case 7: *piNumOfDays=31; break;
   case 8: *piNumOfDays=31; break;
   case 9: *piNumOfDays=30; break;
   case 10: *piNumOfDays=31; break;
   case 11: *piNumOfDays=30; break;
   case 12: *piNumOfDays=31; break;
   }

return(retc);
}


// =======================================================
// ----------------------
HRESULT DotRotate(double dAngle, double *pdX, double *pdY, double *pdZ)
{
HRESULT retc=S_OK;
double xx, yy, zz;
double rr;
double alpha;
double beta;
double dd;
double pi=2*asin(1.0);

#ifdef Debug
double alpha0;
// unsigned char str_buf[200];
#endif

   if((pdX==NULL) || (pdY==NULL) || (pdZ==NULL))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      xx=*pdX;
      yy=*pdY;
      zz=*pdZ;

      dd=yy*yy+zz*zz;
      rr=sqrt(xx*xx+dd);

      dd=sqrt(dd);

      if(dd!=0.0) alpha=asin(zz/dd);
      else alpha=0.0;

      if(yy<0.0) alpha=pi-alpha;
      else if(zz<0.0) alpha+=2*pi;

      if(rr!=0.0) beta=asin(dd/rr);
      else beta=0.0;

      if(xx<0.0) beta=pi-beta;

#ifdef Debug
alpha0=alpha;
#endif

      alpha+=dAngle;
      while(alpha>=2*pi)
      {
         alpha-=2*pi;
      }
      while(alpha<0.0)
      {
         alpha+=2*pi;
      }


//    xx=rr*cos(beta);
      dd=sin(beta);
      yy=rr*dd*cos(alpha);
      zz=rr*dd*sin(alpha);

#ifdef Debug
// sprintf((char *)str_buf, "%f %f (%f %f %f) (%f %f %f)", alpha0, alpha, *pdX, *pdY, *pdZ, xx, yy, zz); KP_TRACE(str_buf);
#endif

      *pdX=xx;
      *pdY=yy;
      *pdZ=zz;
   }

return(retc);
}


// ============================================= startup
HRESULT KpInit(void)
{
HRESULT retc = S_OK;

   if(StackTop == NULL) StackTop = &retc;

   if(SUCCEEDED(retc)) retc = DelLogFile();

   if(SUCCEEDED(retc)) retc = TestCompilerSettings();
   if(SUCCEEDED(retc)) retc = TestCompilerSettingsLocal();

   hypinit();

return(retc);
}

HRESULT TestCompilerSettings(void)
{
#include "kpstcs.cpp"
}


HRESULT KpFinit(void)
{
HRESULT retc=S_OK;

   hypfinit();

return(retc);
}


// =============================================
unsigned char lpszAppName[KP_MAX_FNAME_LEN+1] = "";

HRESULT GetAppName(unsigned char *lpszNameBuf)
{
HRESULT retc=S_OK;
unsigned char *pnts;
static unsigned char name_buf_tmp[KP_MAX_FNAME_LEN+1];
DWORD ll;

   KP_ASSERT(lpszNameBuf, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc))
   {
      if(lpszAppName[0])
         strcpy(lpszNameBuf, lpszAppName); // tik pirmà kartà bûna teisingas kelias, paskui nustatau SetCurrentDirectory() ir santykinis kelias iðsiderina
      else
      {
         pnts = (unsigned char *)GetCommandLine();

         if(*pnts != '\"')
         {
            strncpy(name_buf_tmp, pnts, KP_MAX_FNAME_LEN);
            name_buf_tmp[KP_MAX_FNAME_LEN] = Nul;

            pnts = strchr(name_buf_tmp, Spc);
         }
         else
         {
            strncpy(name_buf_tmp, pnts + 1, KP_MAX_FNAME_LEN);
            name_buf_tmp[KP_MAX_FNAME_LEN] = Nul;

            pnts = strchr(name_buf_tmp, '\"');
         }
         if(pnts) *pnts=Nul;

         if(SUCCEEDED(retc))
         {
            ll = GetFullPathName((const char *)name_buf_tmp, KP_MAX_FNAME_LEN, (char *)lpszAppName, NULL);
            if(!ll) retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L);
            else if(ll >= KP_MAX_FNAME_LEN)
               retc = KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
         }

         if(SUCCEEDED(retc))
         {
            strlwr(lpszAppName);
            strcpy(lpszNameBuf, lpszAppName);
         }
      }
   }

return(retc);
}


// -----------------------------------------------
HRESULT GetAppPath(unsigned char *lpszPathBuf, bool bAppendSlash)
{
HRESULT retc=S_OK;
static unsigned char full_path[KP_MAX_FNAME_LEN+1];
static unsigned char app_disk[KP_MAX_FNAME_LEN+1];
static unsigned char app_path[KP_MAX_FNAME_LEN+1];
static unsigned char app_name[KP_MAX_FNAME_LEN+1];
static unsigned char app_type[KP_MAX_FTYPE_LEN+1];

   if((lpszPathBuf==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc = GetAppName(full_path);

   if(SUCCEEDED(retc)) retc = TvFnameSplit(app_disk, app_path, app_name, app_type, full_path);
   if(SUCCEEDED(retc))
   {
      full_path[0] = Nul;
      strcpy(full_path, app_disk); // diskas gali nesuveikti - gal reikëtø specialiai? !!!!
      strcat(full_path, app_path);
      if(/* (strlen(app_path)==0) || */ bAppendSlash) strcat(full_path, "\\");

      strcpy(lpszPathBuf, full_path);
   }

return(retc);
}


// -----------------------------------------------
HRESULT GetIniFname(unsigned char *lpszIniFnameBuf)
{
HRESULT retc=S_OK;
unsigned char *ini_fname_ptr;
// unsigned char *pntd;

   if(lpszIniFnameBuf==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc = GetAppName(lpszIniFnameBuf);

   if(SUCCEEDED(retc))
   {
      strlwr(lpszIniFnameBuf);
      ini_fname_ptr=strstr(lpszIniFnameBuf, ".exe");
      if(ini_fname_ptr==NULL)
      {
         ini_fname_ptr=strstr(lpszIniFnameBuf, ".bin");
         if(ini_fname_ptr==NULL)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, lpszIniFnameBuf, True, __FILE__, __LINE__, 0L);
      }
   }

   if(SUCCEEDED(retc))
   {
      strcpy(ini_fname_ptr, ".ini");
#if FALSE
      do
      {
         if(*(--ini_fname_ptr)=='\\') break;
      } while(ini_fname_ptr>lpszIniFnameBuf);
      if(*ini_fname_ptr=='\\') ini_fname_ptr++;

      pntd=lpszIniFnameBuf;
      while(*ini_fname_ptr) *(pntd++)=(*ini_fname_ptr++);
      *pntd=Nul;
#endif
   }

return(retc);
}


HRESULT GetCmdPath(unsigned char *lpszPathBuf, bool bAppendSlash)
{
HRESULT retc=S_OK;
/* const */ unsigned char *pnts = NULL;
unsigned char *pntd = NULL;
static unsigned char path_buf[KP_MAX_FNAME_LEN+1];

   KP_ASSERT(lpszPathBuf, E_INVALIDARG, null, True);

#if FALSE
   if(SUCCEEDED(retc))
   {
      pntd = pnts = lpszPathBuf;
      while(pnts)
      {
         pnts = strchr(pntd, '\\');
         if(pnts == NULL) pnts = strchr(pntd, '/');\
         if(pnts) pntd = pnts + 1;
      }
#if FALSE
      if(pntd > lpszPathBuf)
      {
         pntd--;
         if(bAppendSlash) *pntd++ = '/';
      }
      else
      {
         if(bAppendSlash)
         {
            *pntd++ = '.';
            *pntd++ = '/';
         }
      }
#endif
      *pntd = Nul;
   }
#endif

   KP_ASSERT(GetFullPathName((const char *)lpszPathBuf, KP_MAX_FNAME_LEN, (char *)path_buf, (char **)&pntd), KP_E_SYSTEM_ERROR, GetLastError(), True);

   if(SUCCEEDED(retc))
   {
      *pntd = Nul;

      if(!bAppendSlash) if(pntd > path_buf)
      {
         pntd--;
         if((*pntd == '\\') || (*pntd == '/')) *pntd = Nul;
      }

      strcpy(lpszPathBuf, path_buf);
   }

return(retc);
}


// ============================================= KpStdApp implementation
KpStdApp::KpStdApp(void)
{
// pastoviai atidarytas failas loginimui netinka, reikia atidaryt, palogint ir ið karto vël uþdaryt
#if FALSE // #ifdef Logging
int retv;

   m_pLogFile=NULL;
   m_pLogFile=fopen((const char *)lpszLogFileName, "a");
#if (Envir==MSWin32) || (Envir==MSWin32Con) || (Envir==MSWin32Mfc) || (Envir==MSWin32ConMfc)
   if(m_pLogFile==NULL) retv=GetLastError();
#endif
#endif
}

KpStdApp::~KpStdApp(void)
{
#if FALSE // #ifdef Logging
   if(m_pLogFile) fclose(m_pLogFile);
   m_pLogFile=NULL;
#endif
}


//----------------------------------------------
KpPoint::KpPoint(double dX, double dY, double dZ)
{
   m_Coords[AxisX]=dX;
   m_Coords[AxisY]=dY;
   m_Coords[AxisZ]=dZ;
}

//=============================================
KpPoint::KpPoint(KpPoint *pOrig)
{
   if(pOrig==NULL)
   {
   /* m_lhOpenResult= */ KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

      m_Coords[AxisX]=0.0;
      m_Coords[AxisY]=0.0;
      m_Coords[AxisZ]=0.0;
   }
   else
   {
      m_Coords[AxisX]=pOrig->m_Coords[AxisX];
      m_Coords[AxisY]=pOrig->m_Coords[AxisY];
      m_Coords[AxisZ]=pOrig->m_Coords[AxisZ];
   }
}


//----------------------------------------------
KpPoint::KpPoint(void)
{
   m_Coords[AxisX]=0.0;
   m_Coords[AxisY]=0.0;
   m_Coords[AxisZ]=0.0;
}


//----------------------------------------------
HRESULT KpDifPoints(const KpPoint *pPoint1, const KpPoint *pPoint2, double *pdDiff)
{
HRESULT retc=S_OK;
double XX1, XX2, YY1, YY2, ZZ1, ZZ2; // pradiniu tasku pPoint1 ir pPoint2 koordinates
double XX, YY, ZZ; // koordinaciu skirtumai (xx2-xx1), ...

   if(((pPoint1==NULL) || (pPoint2==NULL) || (pdDiff==NULL)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      XX1=pPoint1->m_Coords[AxisX];
      YY1=pPoint1->m_Coords[AxisY];
      ZZ1=pPoint1->m_Coords[AxisZ];
      XX2=pPoint2->m_Coords[AxisX];
      YY2=pPoint2->m_Coords[AxisY];
      ZZ2=pPoint2->m_Coords[AxisZ];

      XX=XX2-XX1;
      YY=YY2-YY1;
      ZZ=ZZ2-ZZ1;

      *pdDiff=sqrt((XX*XX)+(YY*YY)+(ZZ*ZZ));
   }

return(retc);
}


//----------------------------------------------
HRESULT RotateLeft(KpPoint *pPoint)
{
HRESULT retc=S_OK;
double tmp;

   if((pPoint==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      tmp=pPoint->m_Coords[AxisX];
      pPoint->m_Coords[AxisX]=pPoint->m_Coords[AxisY];
      pPoint->m_Coords[AxisY]=pPoint->m_Coords[AxisZ];
      pPoint->m_Coords[AxisZ]=tmp;
   }

return(retc);
}


//----------------------------------------------
HRESULT RotateRight(KpPoint *pPoint)
{
HRESULT retc=S_OK;
double tmp;

   if((pPoint==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      tmp=pPoint->m_Coords[AxisX];
      pPoint->m_Coords[AxisX]=pPoint->m_Coords[AxisZ];
      pPoint->m_Coords[AxisZ]=pPoint->m_Coords[AxisY];
      pPoint->m_Coords[AxisY]=tmp;
   }

return(retc);
}


//----------------------------------------------
HRESULT ExtractSetupVariable(const unsigned char **plpszInPtr, unsigned char **plpszOutPtr, int iValBufSize,
                                 const unsigned char *lpszAppPath)
{
HRESULT retc=S_OK;
static unsigned char path_val[KP_MAX_FNAME_LEN+1];
const unsigned char *pnt_val = NULL;

   KP_ASSERT(plpszInPtr && plpszOutPtr, E_INVALIDARG, null, True);
   KP_ASSERT(*plpszInPtr && *plpszOutPtr, E_INVALIDARG, null, True);
   KP_ASSERT(**plpszInPtr == '{', E_INVALIDARG, null, True);

   if(SUCCEEDED(retc))
   {
      if((strstr(*plpszInPtr, "{app}") == *plpszInPtr) || (strstr(*plpszInPtr, "{src}") == *plpszInPtr))
      {
         if(lpszAppPath) pnt_val = lpszAppPath;
         else
         {
            retc = GetAppPath(path_val, False);
            pnt_val = path_val;
         }
      }
      else if(strstr(*plpszInPtr, "{cf}") == *plpszInPtr)
      {
         retc = GetLocalPath(path_val, KP_Common_Files, False);
         pnt_val = path_val;
      }
      else KP_ERROR(E_NOTIMPL, null);
   }

   KP_ASSERT(strlen(pnt_val) < iValBufSize, KP_E_BUFFER_OVERFLOW, null, True);

   if(SUCCEEDED(retc))
   {
      strcpy(*plpszOutPtr, pnt_val);
      *plpszOutPtr += strlen(pnt_val);

      while((**plpszInPtr != '}') && **plpszInPtr) (*plpszInPtr)++;
      if(**plpszInPtr == '}') (*plpszInPtr)++;
      else KP_ERROR(E_INVALIDARG, null);
   }

return(retc);
}


HRESULT ExtractSetupTextValue(const unsigned char *lpszInStr, const char *lpszKey,
   unsigned char *lpszValBuf, int iValBufSize,
   const unsigned char *lpszAppPath)
{
HRESULT retc=S_OK;
const unsigned char *pnts = NULL;
unsigned char *pntd = NULL;

   KP_ASSERT(lpszInStr && lpszKey && lpszValBuf, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc))
   {
      *lpszValBuf = Nul;
      retc = KP_E_KWD_NOT_FOUND;

      pnts = strstr(lpszInStr, lpszKey);
      if(pnts)
      {
         retc = S_OK;

         pntd = lpszValBuf;
         while(*pnts && (*pnts != '\"') && SUCCEEDED(retc)) pnts++;
         if((*pnts == '\"') && SUCCEEDED(retc)) pnts++;
         while(*pnts && (*pnts != '\"') && SUCCEEDED(retc))
         {
            if(*pnts == '{') retc = ExtractSetupVariable(&pnts, &pntd, iValBufSize - (pntd - lpszValBuf), lpszAppPath);
            else
            {
               KP_ASSERT(pntd - lpszValBuf < iValBufSize, KP_E_BUFFER_OVERFLOW, null, True);
               if(SUCCEEDED(retc)) *pntd++ = *pnts++;
            }
         }
         *pntd = Nul;
      }
   }

return(retc);
}


HRESULT RunFlashSetup(const unsigned char *lpszAppPath, const unsigned char *lpszFlashSetupFname, bool *pbSetupPerformed)
{
HRESULT retc=S_OK;
static unsigned char flash_setup_file[KP_MAX_FNAME_LEN + 1];
static unsigned char cmd_str[KP_MAX_FNAME_LEN + 1];
FILE *test_file = NULL;
HANDLE proc_handle = NULL;
DWORD exit_code;
static unsigned char flash_vers_txt[KP_KWD_LEN + 1];
HKEY key;
DWORD buf_len;
DWORD val_type;
long ver_val = 0L;
long flash_vers = 0L;
long vers_part = 0L;
unsigned char *pntd;

   KP_ASSERT(lpszAppPath, E_INVALIDARG, null, True);
   KP_ASSERT(lpszFlashSetupFname, E_INVALIDARG, null, True);
   KP_ASSERT(pbSetupPerformed, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc))
   {
      strcpy(flash_setup_file, lpszAppPath);
      if(strlen(flash_setup_file) + strlen(lpszFlashSetupFname) + 1 >= KP_MAX_FNAME_LEN)
         KP_ERROR(KP_E_BUFFER_OVERFLOW, null);
   }
   if(SUCCEEDED(retc))
   {
      strcat(flash_setup_file, "\\");
      strcat(flash_setup_file, lpszFlashSetupFname);

// --------------------- tikrinam, ar yra setup failas
// KpMsgOutF("RunFlashSetup() %s", flash_setup_file);
      test_file = fopen((const char *)flash_setup_file, "r");
      if(test_file)
      {
         fclose(test_file);
         test_file = NULL;
// KpMsgOutF_0("RunFlashSetup() found");

// ----------- dabar diegsima versija
         ver_val = 0L;
         if(strcmp(lpszFlashSetupFname, KPSTPD_FLASH_7_SETUP_FNAME) == 0) ver_val = 7001400L; // 7,0,14,0
         if(strcmp(lpszFlashSetupFname, KPSTPD_FLASH_9_SETUP_FNAME) == 0) ver_val = 9011500; // 9.0.115.0 // blogai - suveiks ir 9.1.15.0

// ------------ tikrinam esamà versijà
         strcpy(flash_vers_txt, "0.0.0.0");

         if(ERROR_SUCCESS == RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Active Setup\\Installed Components\\{D27CDB6E-AE6D-11CF-96B8-444553540000}", 0, KEY_QUERY_VALUE, &key))
         {
            buf_len = KP_KWD_LEN;
            if(ERROR_SUCCESS == RegQueryValueEx(key, "Version", NULL, &val_type, flash_vers_txt, &buf_len))
            {
               if(val_type == REG_SZ) flash_vers_txt[buf_len] = Nul;
               else strcpy(flash_vers_txt, "0.0.0.0");
            }
            else strcpy(flash_vers_txt, "0.0.0.0");

            RegCloseKey(key);
         }

         flash_vers = 0L;

         if(SUCCEEDED(retc))
         {
            pntd = flash_vers_txt;
            sscanf((const char *)pntd, "%ld", &flash_vers);
// long flash_vers_sav;
            while(*pntd)
            {
               if(*pntd == ',') *pntd = '.';
               if(*pntd == '.')
               {
                  pntd++;

                  vers_part = 0L;
                  sscanf((const char *)pntd, "%ld", &vers_part);
// flash_vers_sav = flash_vers;
                  flash_vers = (flash_vers * 100L) + vers_part;
// KpMsgOutF_4("%s %s %ld %ld", flash_vers_txt, pntd, flash_vers_sav, flash_vers);
               }
               else pntd++;
            }
            if(flash_vers > 0L) while(flash_vers < 1000000L) flash_vers *= 100L;
         }
// KpMsgOutF_2("%s %ld", flash_vers_txt, flash_vers);
// KpMsgOutF_4("%ld %ld %d %d", ver_val, flash_vers, iWindowsVersion, iWindowsSP);

// int win_ver_sav = iWindowsVersion;
// iWindowsVersion = WinXPc;

#ifndef Debug
         if((ver_val > 7001400) || ((iWindowsVersion < WinVistaC) /* && ((iWindowsVersion < WinXPc) || (iWindowsSP < 2)) */ )) // Pas Raimá buvo XP SP3, bet flash'as neveikë
#endif
            if(flash_vers < ver_val)
            {
// iWindowsVersion = win_ver_sav;

// ---------------- tikrinam adminà
               if(SUCCEEDED(retc))
//                if(iWindowsVersion < WinVistaC) // automatiðkai kaþkodël nepasikelia (Win7)
                     if(!IsUserAdmin())
                     {
                        KpMsgOut(KP_MSG_FIRST_TIME_ADMIN, IDI_ERROR, KP_MB_TESTI);
                        retc = KP_E_ACCESS_DENIED;
                     }

// ------------------- formuojam komandà
               if(SUCCEEDED(retc))
               {
                  if(strstr(flash_setup_file, ".msi"))
                  {
                     if(strlen(KPSTPD_MSIEXEC_CMD_STR) + strlen(flash_setup_file) + 2 >= KP_MAX_FNAME_LEN)
                        KP_ERROR(KP_E_BUFFER_OVERFLOW, null);
                     if(SUCCEEDED(retc))
                     {
                        strcpy(cmd_str, KPSTPD_MSIEXEC_CMD_STR);
                        strcat(cmd_str, "\"");
                        strcat(cmd_str, flash_setup_file);
                        strcat(cmd_str, "\"");
                     }
                  }
                  else strcpy(cmd_str, flash_setup_file);
               }

// -------------- paleidþiam
               if(SUCCEEDED(retc))
               {
                  KpMsgOutF_0(KP_MSG_FLASH_PLAYER_INSTALL);

//                retc = StartCmdProcess(flash_setup_file, KPST_CUR_DIR, NULL, &proc_handle, False, SW_SHOWDEFAULT);
                  retc = StartProcess(cmd_str, KPST_CUR_DIR, NULL, &proc_handle, SW_SHOWNORMAL); // SW_SHOWDEFAULT);
               }
               if(SUCCEEDED(retc)) do
               {
                  Sleep(500);
                  if(!GetExitCodeProcess(proc_handle, &exit_code))
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
               }
               while((exit_code == STILL_ACTIVE) && SUCCEEDED(retc));

// KpMsgOutF_0(cmd_str);
// ---------------
               if(SUCCEEDED(retc)) *pbSetupPerformed = True;

            } // if(flash_vers < ver_val) // if((ver_val > 7001400) || (iWindowsVersion >= WinVistaC) || ((iWindowsVersion >= WinXPc) && (iWindowsSP >= 2)))

      } // if(test_file)

   } // if(SUCCEEDED(retc))

return(retc);
}


HRESULT ProcessSetup(const unsigned char *lpszAppPath, bool *pbSetupPerformed)
{
HRESULT retc=S_OK;
const unsigned char **ppnts = NULL;
const unsigned char *pnts = NULL;
bool files_section = False;
static unsigned char src_fname[KP_MAX_FNAME_LEN + 1];
static unsigned char dst_fname[KP_MAX_FNAME_LEN + 1];
static unsigned char file_disk[KP_MAX_FNAME_LEN+1];
static unsigned char file_path[KP_MAX_FNAME_LEN+1];
static unsigned char file_name[KP_MAX_FNAME_LEN+1];
static unsigned char file_type[KP_MAX_FTYPE_LEN+1];
FILE *test_file = NULL;
// bool admin_tested = False;

   KP_ASSERT(pbSetupPerformed, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc)) *pbSetupPerformed = False;

// skanuojam setup scriptà
   ppnts = GenIssArr;

   while((*ppnts) && SUCCEEDED(retc))
   {
      if(strchr(*ppnts, '['))
      {
         if(strstr(*ppnts, "[Files]")) files_section = True;
         else files_section = False;
      }
      else if(files_section)
      {
         pnts = *ppnts;
         while((*pnts == Spc) && (*pnts)) pnts++;
// praleidþiam komentarus
         if(*pnts != ';')
         {

// iðtraukiam kopijuojamø failø vardus
            src_fname[0] = Nul;
            if(SUCCEEDED(retc)) retc = ExtractSetupTextValue(*ppnts, "Source:", src_fname, KP_MAX_FNAME_LEN, lpszAppPath);
            dst_fname[0] = Nul;
            if(SUCCEEDED(retc)) retc = ExtractSetupTextValue(*ppnts, "DestDir:", dst_fname, KP_MAX_FNAME_LEN, lpszAppPath);
            if(SUCCEEDED(retc))
            {
               if(SUCCEEDED(retc)) retc = TvFnameSplit(file_disk, file_path, file_name, file_type, src_fname);
               KP_ASSERT(strlen(dst_fname) + 1 + strlen(file_name) + 1 + strlen(file_type) < KP_MAX_FNAME_LEN,
                  KP_E_BUFFER_OVERFLOW, null, True);
               if(SUCCEEDED(retc))
               {
                  strcat(dst_fname, "\\");
                  strcat(dst_fname, file_name);
                  if(strlen(file_type))
                  {
                     strcat(dst_fname, ".");
                     strcat(dst_fname, file_type);
                  }
               }

// tikrinam, gal jau yra
               if(SUCCEEDED(retc))
               {
                  test_file = fopen((const char *)dst_fname, "r");
                  if(test_file){ fclose(test_file); test_file = NULL; }
                  else
                  {
// tikrinam, ar adminas
// ne, gal suveiks ir paprastam vartotojui (pvz., Vistos virtualizatorius)
//                   if((!admin_tested) && (!IsUserAdmin()))
//                   {
//                      KpMsgOut(KP_MSG_FIRST_TIME_ADMIN, IDI_ERROR, KP_MB_TESTI);
//                      retc = KP_E_ACCESS_DENIED;
//                   }
//                   admin_tested = True;

// kopijuojam
                     if(SUCCEEDED(retc))
                     {
                        retc = CreatePath(dst_fname, False /* True */);
                        if(SUCCEEDED(retc))
                           if(!CopyFile((const char *)src_fname, (const char *)dst_fname, False))
                              retc = KP_E_FERROR;
                        if(FAILED(retc))
                        {
                           KpMsgOut(KP_MSG_FIRST_TIME_ADMIN /* KP_MSG_COPY_FILE_ACCESS_DENIED */, IDI_ERROR, KP_MB_TESTI);
                           KP_WARNING(retc, src_fname);
                           KP_WARNING(retc, dst_fname);
                           retc = KP_E_ACCESS_DENIED;
                        }
                     }

                     if(SUCCEEDED(retc)) *pbSetupPerformed = True;
                  }
               }

            } // if(SUCCEEDED(retc)) // retc = ExtractSetupTextValue()

            if(retc == KP_E_KWD_NOT_FOUND) retc = S_OK;

         } // if(*pnts != ';')

      } // else if(files_section) // if(strchr(*ppnts, '['))

      else if(strstr(*ppnts, "procedure CheckMacromediaPlayer;"))
      {
// -----------------
         retc = RunFlashSetup(lpszAppPath, KPSTPD_FLASH_7_SETUP_FNAME, pbSetupPerformed);
         if(SUCCEEDED(retc)) retc = RunFlashSetup(lpszAppPath, KPSTPD_FLASH_9_SETUP_FNAME, pbSetupPerformed);

      } // else if(strstr(*ppnts, "procedure CheckMacromediaPlayer;")

      ppnts++;
   }

return(retc);
}


// ------------------------------------------
int KpCompareLong(const void *plVal1, const void *plVal2)
{
int retv = 0;
HRESULT retc = S_OK;

   KP_ASSERT(plVal1 != NULL, E_INVALIDARG, null, True);
   KP_ASSERT(plVal2 != NULL, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc))
   {
      if(*(long *)plVal1 > *(long *)plVal2) retv = 1;
      else if(*(long *)plVal1 < *(long *)plVal2) retv = (-1);
//    else /* if(*plVal1 == *plVal2) */ retv = 0;
   }

return(retv);
}
