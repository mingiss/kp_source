// ---------------------------------------
// KpFileSys.cpp
// el. knygø failai ir duomenys
//

#include "envir.h"
#include "iBshn.h"
#include "lzdshn.h"

#include <stdio.h>
#include <string>
#include <fstream>
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <time.h>
#include <richedit.h>
#include <Richole.h>

#if CompilerGr==Mingw
#include "IInputStream.hh"
#include "IString.hh"
#include "XApplication.hh"
#include "XGecko.hh"
#include "XGeckoDOMEvent.hh"
#include "XGeckoInit.hh"
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
#include "kpttucf.h"
#include "kpttucf.h"
#include "res_com.h"
#include "kpwindow.h"
#include "kpsock.h"
#include "kperr.h"
#include "kphp11i.h"
#include "kphp11y.h"
#include "kphp11m.h"
#include "kphp11d.h"
#include "kphp11rc.h"
#include "kphp11t.h"
#include "kpcapp.h"
#include "tvmain.h"
#include "tvxml.h"
#include "xmlp.h"
#include "xmlh.h"
#include "xmlf.h"
#include "xml8.h"
#include "xmlu.h"
#include "xmlo1.h"
#include "xmlt.h"
#include "htmt.h"
#include "xmlis.h"
#include "xmli.h"
#include "tvrtf.h"
#include "tvrtfo.h"
#include "tvtex.h"
#include "KpFileSys.h"
#include "KpPubDlg.h"
#include "KpGecko.h"
#include "xmln.h"
#include "xmlsty.h"
#include "kpstap.h"


// -------------------------------------------------
KpFileSys::KpFileSys(void)
{
HRESULT retc = S_OK;
int ii;

   m_lhOpenResult = S_OK;

   m_lThreadId = 0L;

   m_iSemBlocked = 0;
   m_lSemBlockingThread = 0L;

// ----------------------
// #if IBSH_PROJ == IBSH_PROJ_TEVT
   m_iMask = 123456789;

   strcpy(m_lpszUserName, "Kaulas");
   strcpy(m_lpszUserSurName, "Maulas");

   strcpy(m_lpszUserName, "Àèæë");
   strcpy(m_lpszUserSurName, "Áðøû");

// ----------------------
   for(ii = 0; ii < KP_FILESYS_NUM_TASKS; ii++) m_aiAnswers[ii] = 0;
// iðkelta á paveldëtos klasës konstruktoriø - lzdsh nereikia
// if(SUCCEEDED(retc)) retc = ProcessAnswer(0);

// #endif

   m_lpszCurSearchWord[0] = Nul;
   m_lpszCurSearchKwd[0] = Nul;
   m_lpszCurSearchKwdPrev[0] = Nul;
// m_lpszCurSearchResult[0] = Nul;

   m_lpszToSearch[0] = Nul;
   m_lpszLastSearchStr[0] = Nul;

// ----------------
   m_pCurEntry = NULL;

   m_lCurEntryId = (-1L);

   strcpy(m_lpszCurSearchKwd, IBSHT_FIRST_ENTRY);
   m_iTaskNo = -1;

// -------------------
   m_pResBuf = NULL;
   KP_NEWA(m_pResBuf, UniChar, KP_FILESYS_RESULT_BUF_LEN + 1);

   if(SUCCEEDED(retc)) m_pResBuf[0] = C_Nul;

   m_iCurIndexFile = m_iIndexFile = XL_IX_HxIndex; // normaliai indeksas su diakritais - pozicionavimui liste

   m_lpInFileObj = NULL;
   m_lpOutFileObj = NULL;

   m_pKpInFileFactory = CreateNew8File;
   m_pKpOutFileFactory = CreateNewUniBFile;

// -------------------- buvæ LzdShSearch laukai
   m_iLevel = BigLevel; // FullLevel;
   m_bAccFl = True;

   m_iToHistListFlags = 0; // LZDSH_HIST_NONE;

   m_lQuietTime = 0L;

   m_lpszToHistStr[0] = Nul;
   m_lpszPrevHistWord[0] = Nul;

   m_bReactToSelFlag = False;

   m_lpszClipBuf[0] = Nul;

   if(SUCCEEDED(m_lhOpenResult)) m_lhOpenResult = retc;
}


// ----------------------------------
KpFileSys::~KpFileSys()
{
HRESULT retc = S_OK;
XmlNode *cur_entry;

// CloseFiles(False); // èia tuðèios zaglûðkës KpFileSys::CloseFiles() iðkvietimas, ne paveldëtos funkcijos

   if(m_pCurEntry != NULL)
   {
      cur_entry = m_pCurEntry;
      m_pCurEntry = NULL;
// PutLogMessage_("delete\t%x\tKpFileSys::~KpFileSys() cur_entry", cur_entry);
      KP_DELETE(cur_entry);
   }

// PutLogMessage_("KpFileSys::~KpFileSys() %x %x", this, m_pResBuf);
// KP_STACK_DUMP;
   KP_DELETEA(m_pResBuf);
}


// ----------------------------------
HRESULT KpFileSys::GetOpenResult(void)
{
return(m_lhOpenResult);
}


// -----------------------------------------------------------
#define KPFILESYS_BLOCKSEMAPHORE_POLLING_TIMER 30
HRESULT KpFileSys::BlockSemaphore(void)
{
HRESULT retc = S_OK;
DWORD cur_thread;

   cur_thread = GetCurrentThreadId();
   if(cur_thread == EmuTv.m_lKphp11ThreadId) cur_thread = EmuTv.m_lMainThreadId;

   if((cur_thread==0L) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

   if(m_iSemBlocked && (m_lSemBlockingThread != cur_thread) && SUCCEEDED(retc))
   {
int ii = 0;
      for(ii = 0; (ii < KP_TIMEOUT_TIMEOUT/KPFILESYS_BLOCKSEMAPHORE_POLLING_TIMER) && (m_iSemBlocked != 0) && SUCCEEDED(retc); ii++)
         retc = KpSleep(KPFILESYS_BLOCKSEMAPHORE_POLLING_TIMER, NULL); // theDialog.m_hDialogWindow); // Sleep(KPFILESYS_BLOCKSEMAPHORE_POLLING_TIMER);
                       // jeigu nurodytas langas, sunaikinamas kito threado paleistas KpSleep taimeris
      KP_ASSERTE(ii < KP_TIMEOUT_TIMEOUT/KPFILESYS_BLOCKSEMAPHORE_POLLING_TIMER, KP_E_TIMEOUT, null, False);
   }

// if(SUCCEEDED(retc))
   {
      m_iSemBlocked++;
      m_lSemBlockingThread = cur_thread;
   }

// PutLogMessage_("KpFileSys::BlockSemaphore() %d %d", m_iSemBlocked, cur_thread); 
// StackDump(&retc, False);

return(retc);
}


HRESULT KpFileSys::ReleaseSemaphore(void)
{
HRESULT retc = S_OK;

   m_iSemBlocked--;
   if(m_iSemBlocked < 0)
   {
      KP_ASSERTE(m_iSemBlocked >= 0, KP_E_SYSTEM_ERROR, null, False);
      m_iSemBlocked = 0;
      retc = S_OK;
   }
   if(m_iSemBlocked == 0) m_lSemBlockingThread = 0L;

// PutLogMessage_("KpFileSys::ReleaseSemaphore() %d %d", m_iSemBlocked, GetCurrentThreadId()); 
// StackDump(&retc, False);

return(retc);
}


// #if IBSH_PROJ == IBSH_PROJ_TEVT
// -----------------------------------
HRESULT KpFileSys::ProcessAnswer(int iAnswNo)
{
HRESULT retc = S_OK;
bool cont = True;
// int answ_mask = 0;

   if(cont && SUCCEEDED(retc))
   {
      cont = ((m_iTaskNo >= 0) && (m_iTaskNo < KP_FILESYS_NUM_TASKS));
      KP_ASSERT(cont, KP_E_NO_FILE, null, False);
   }

   if(cont && SUCCEEDED(retc))
   {
      cont = ((iAnswNo >= 0) && (iAnswNo <= KP_FILESYS_MAX_ANSWER));
      KP_ASSERT(cont, E_INVALIDARG, null, False);
   }
// if(cont && SUCCEEDED(retc)) answ_mask = (1 << iAnswNo);

   if(cont && SUCCEEDED(retc))
   {
//    if(m_aiAnswers[m_iTaskNo] & answ_mask) m_aiAnswers[m_iTaskNo] &= ~answ_mask;
//    else m_aiAnswers[m_iTaskNo] = answ_mask; // |= answ_mask;
      m_aiAnswers[m_iTaskNo] = iAnswNo;
   }

   if(SUCCEEDED(retc))
   {
// TODO: keisti failà - kelti kur nors á vartotojo sritá !!!!
fstream out_file("arksh.dat", ios::out | ios::binary);
      out_file.write(m_aiAnswers, sizeof(m_aiAnswers));
      out_file.close();
   }

   if(cont && SUCCEEDED(retc)) retc = SendAnswers(m_iTaskNo);

return(retc);
}


// -----------------------------------
// tarpiniai
// sl=5%7cKaulas%7cMaulas%7c7kl%7c336958036%7c898201907%7c944121410%7c741695590%7c875913318%7c67870980
// galutiniai
// sl=Kaulas%7cMaulas%7c7kl%7c336958036%7c898201907%7c944121410%7c741695590%7c875913318%7c67870980
//
time_t aclock = 0;

HRESULT KpFileSys::SendAnswers(int iTaskNo)
{
HRESULT retc = S_OK;
KpSocket sock;
static unsigned char out_field[KP_MAX_FILE_LIN_LEN + 1]; // [KPST_TXTCD_CHARS_PER_VAL_REZ+2]; // [MAX_LONG_DIGITS+1];
static unsigned char out_buf[KP_MAX_FILE_LIN_LEN*2 + 100 + 1];
static unsigned char rez_var[KP_MAX_FNAME_LEN + 1];
int fields_cnt = 0;
int coded_cnt = 0;
int rez_fields_cnt = 0;
int rez_cnt = 0;
unsigned long rez_val = 0;
// int factor;
int ii;
int jj;
static unsigned char reg_url[KP_MAX_FNAME_LEN+1];
int port;
unsigned char testc[KPST_TXTCD_CHARS_PER_VAL_TID*2+1];
struct tm *newtime;

   KP_ASSERT(theKpStAppPtr, KP_E_SYSTEM_ERROR, null, True);

   KP_ASSERT(((iTaskNo >= 0) && (iTaskNo < KP_FILESYS_NUM_TASKS)), KP_E_NO_FILE, null, False);

   if(SUCCEEDED(retc)) retc = theKpStAppPtr->GetIniShuffCnt(&coded_cnt);

   if(SUCCEEDED(retc)) retc = theKpStAppPtr->GetIniRezVar(rez_var);
   if(SUCCEEDED(retc)) retc = CountStrings(&fields_cnt, rez_var, (const unsigned char *)" ", False);

   if((coded_cnt || fields_cnt) && SUCCEEDED(retc))
   {
      if(coded_cnt) KP_ASSERT(fields_cnt - coded_cnt == 3, E_NOTIMPL, null, True);

      if(SUCCEEDED(retc))
      {
         rez_fields_cnt = fields_cnt
            - 3 /* neuþkoduoti vardas, pavardë ir klase/kodas áraðo pradþioje */
            - 4; /* uþkoduoti vardas, pavardë, testo id. ir laikas áraðo gale */
         KP_ASSERT(rez_fields_cnt >= 0, KP_E_SYSTEM_ERROR, null, True);
      }
      if(SUCCEEDED(retc))
      {
         rez_cnt = rez_fields_cnt * KPST_TXTCD_CHARS_PER_VAL_REZ;
         KP_ASSERT(rez_cnt <= KP_FILESYS_NUM_TASKS, KP_E_SYSTEM_ERROR, null, True);
      }

      out_field[0] = Nul; // galutiniai duomenys
      if(iTaskNo && SUCCEEDED(retc)) sprintf((char *)out_field, "%d|", iTaskNo); // tarpiniai duomenys

      if(SUCCEEDED(retc)) sprintf((char *)out_buf, "sl=%s%s|%s|7kl|", out_field, m_lpszUserName, m_lpszUserSurName);

// ------------ atsakymai
      for(ii = 0; (ii < rez_fields_cnt) && SUCCEEDED(retc); ii++)
      {
//       factor = 1;
         rez_val = 0;
         for(jj = 0; (jj < KPST_TXTCD_CHARS_PER_VAL_REZ) && SUCCEEDED(retc); jj++)
         {
            KP_ASSERT(m_aiAnswers[ii * KPST_TXTCD_CHARS_PER_VAL_REZ + jj] <= KP_FILESYS_MAX_ANSWER, KP_E_SYSTEM_ERROR, null, True);

            if(SUCCEEDED(retc))
            {
//             rez_val += m_aiAnswers[ii * KPST_TXTCD_CHARS_PER_VAL_REZ + jj] * factor;
//             factor *= KPST_TXTCD_RADIX_REZ;

//             rez_val *= KPST_TXTCD_RADIX_REZ;
//             rez_val += m_aiAnswers[ii * KPST_TXTCD_CHARS_PER_VAL_REZ + jj];

               rez_val <<= KPST_TXTCD_BITS_REZ;
               rez_val &= ~KPST_TXTCD_MASK_REZ;
               rez_val |= (m_aiAnswers[ii * KPST_TXTCD_CHARS_PER_VAL_REZ + jj] & KPST_TXTCD_MASK_REZ);
            }
         }

         if(SUCCEEDED(retc))
         {
            rez_val <<= 1;
            if(rez_val & 0x2) rez_val &= ~0x1;
            else rez_val |= 0x1;

            rez_val ^= m_iMask;

            sprintf((char *)out_field, "%ld|", rez_val);

            KP_ASSERT((strlen(out_buf) + strlen(out_field) <= KP_MAX_FILE_LIN_LEN), KP_E_BUFFER_OVERFLOW, null, True);
         }
         if(SUCCEEDED(retc)) strcat(out_buf, out_field);
      }

// --------- uþkoduoti vardas/pavarde
      if(SUCCEEDED(retc)) retc = EncodeUserName(&rez_val, m_lpszUserName);
      if(SUCCEEDED(retc)) sprintf((char *)out_field, "%ld|", rez_val);
      KP_ASSERT((strlen(out_buf) + strlen(out_field) <= KP_MAX_FILE_LIN_LEN), KP_E_BUFFER_OVERFLOW, null, True);
      if(SUCCEEDED(retc)) strcat(out_buf, out_field);

      if(SUCCEEDED(retc)) retc = EncodeUserName(&rez_val, m_lpszUserSurName);
      if(SUCCEEDED(retc)) sprintf((char *)out_field, "%ld|", rez_val);
      KP_ASSERT((strlen(out_buf) + strlen(out_field) <= KP_MAX_FILE_LIN_LEN), KP_E_BUFFER_OVERFLOW, null, True);
      if(SUCCEEDED(retc)) strcat(out_buf, out_field);

// --------- testo kodas
      if(SUCCEEDED(retc)) retc = theKpStAppPtr->GetIniTestCid(testc);
      if(SUCCEEDED(retc))
      {
         strcat(testc, "    "); // KPST_TXTCD_CHARS_PER_VAL_TID
         testc[KPST_TXTCD_CHARS_PER_VAL_TID] = Nul;

         rez_val = 0;
         for(ii = 0 ; ii < KPST_TXTCD_CHARS_PER_VAL_TID; ii++)
         {
            rez_val <<= KPST_TXTCD_BITS_TID;
            rez_val &= ~KPST_TXTCD_MASK_TID;
            rez_val |= ((testc[ii] - KPST_TXTCD_BASE_TID) & KPST_TXTCD_MASK_TID);
         }
         sprintf((char *)out_field, "%ld|", rez_val);
         KP_ASSERT((strlen(out_buf) + strlen(out_field) <= KP_MAX_FILE_LIN_LEN), KP_E_BUFFER_OVERFLOW, null, True);
      }
      if(SUCCEEDED(retc)) strcat(out_buf, out_field);

// ---------- laikas
      if(SUCCEEDED(retc))
      {
         if(!aclock) time(&aclock); // tik pirmà kartà
         newtime = localtime(&aclock);
         if(iTaskNo == 0) aclock = 0; // iðvalom po galutiniø duomenø siuntimo

         KP_ASSERT(newtime, KP_E_SYSTEM_ERROR, null, True);
      }
      if(SUCCEEDED(retc))
      {
         rez_val = 0;

         rez_val &= ~KPST_TXTCD_MASK_MIN;
         rez_val |= (newtime->tm_min & KPST_TXTCD_MASK_MIN);

         rez_val <<= KPST_TXTCD_BITS_HOUR;
         rez_val &= ~KPST_TXTCD_MASK_HOUR;
         rez_val |= (newtime->tm_hour & KPST_TXTCD_MASK_HOUR);

         rez_val <<= KPST_TXTCD_BITS_MONTH;
         rez_val &= ~KPST_TXTCD_MASK_MONTH;
         rez_val |= (newtime->tm_mon & KPST_TXTCD_MASK_MONTH);

         rez_val <<= KPST_TXTCD_BITS_DAY;
         rez_val &= ~KPST_TXTCD_MASK_DAY;
         rez_val |= (newtime->tm_mday & KPST_TXTCD_MASK_DAY);

         sprintf((char *)out_field, "%ld", rez_val);
         KP_ASSERT((strlen(out_buf) + strlen(out_field) <= KP_MAX_FILE_LIN_LEN), KP_E_BUFFER_OVERFLOW, null, True);
      }

      if(SUCCEEDED(retc)) strcat(out_buf, out_field);

// --------------------
      if(SUCCEEDED(retc)) retc = sock.GetOpenResult();

      if(SUCCEEDED(retc)) retc = theKpStAppPtr->GetIniRegURL(reg_url);
      if(SUCCEEDED(retc)) retc = theKpStAppPtr->GetServerPort(&port);
      if(SUCCEEDED(retc))
      {
         sprintf((char *)out_field, "%s:%d", reg_url, port);
         retc = sock.Resolve(out_field, True);
      }
      if(SUCCEEDED(retc)) retc = sock.Connect(True);

      if(SUCCEEDED(retc))
         retc = sock.SendHttpRequest((const unsigned char *)HTTP_POST_REQUEST_CMD, (const unsigned char *)"/", True, strlen(out_buf)); // "POST"
      if(SUCCEEDED(retc)) retc = sock.SendMsg(out_buf, strlen(out_buf), True);

// unsigned char in_buf[KP_MAX_FILE_LIN_LEN + 1];
// long ll;
//
//    ll = KP_MAX_FILE_LIN_LEN;
//    if(SUCCEEDED(retc)) retc = sock.RcvHttpMsg(in_buf, &ll, True);
//    if(((ll < 0) || (ll > KP_MAX_FILE_LIN_LEN)) && SUCCEEDED(retc))
//       retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
//    if(SUCCEEDED(retc)) in_buf[ll] = Nul;

   } // if((coded_cnt || fields_cnt) && SUCCEEDED(retc))

return(retc);
}


// -----------------------------------
HRESULT KpFileSys::EncodeUserName(unsigned long *pulRezVal, const unsigned char *lpszName)
{
HRESULT retc = S_OK;
unsigned char nam_buf[KPST_TXTCD_CHARS_PER_VAL_NAME * 2 + 1];
int ii;
unsigned long rez_val;

   KP_ASSERT(pulRezVal, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc))
   {
      strncpy(nam_buf, lpszName, KPST_TXTCD_CHARS_PER_VAL_NAME);
      nam_buf[KPST_TXTCD_CHARS_PER_VAL_NAME] = Nul;
      retc = CutInitTrailSpcs(nam_buf);
   }
   if(SUCCEEDED(retc))
   {
      strcat(nam_buf, "@@@@@@"); // KPST_TXTCD_CHARS_PER_VAL_NAME
      nam_buf[KPST_TXTCD_CHARS_PER_VAL_NAME] = Nul;
      TvStrLat(nam_buf, KPST_DATA_FILE_CTBL);
      TvStrUprLat(nam_buf);

      rez_val = 0;
      for(ii=0; (ii < KPST_TXTCD_CHARS_PER_VAL_NAME) && SUCCEEDED(retc); ii++)
      {
         rez_val <<= KPST_TXTCD_BITS_NAME;
         rez_val &= ~KPST_TXTCD_MASK_NAME;
         rez_val |= ((nam_buf[ii] - KPST_TXTCD_BASE_NAME) & KPST_TXTCD_MASK_NAME);
      }

      rez_val <<= 1;
      if(rez_val & 0x2)  rez_val &= ~0x1;
      else rez_val |= 0x1;

      *pulRezVal = rez_val;
   }

return(retc);
}


// -----------------------------------
HRESULT KpFileSys::CalcTaskNo(void)
{
HRESULT retc = S_OK;
bool cont = True;
const unsigned char *pnts;
const unsigned char *pnts1;

   if(cont && SUCCEEDED(retc))
   {
      pnts = m_lpszCurSearchKwd;
      while(True)
      {
         pnts1 = strchr(pnts, '\\');
         if(pnts1 == NULL) pnts1 = strchr(pnts, '/');
         if(pnts1 == NULL) break;
         pnts = pnts1 + 1;
      }

      while(*pnts && (!TvIsDigit(*pnts))) pnts++;

      cont = (sscanf((const char *)pnts, "%d", &m_iTaskNo) == 1);
      KP_ASSERT(cont, E_INVALIDARG, null, False);
   }

   if(cont && SUCCEEDED(retc))
   {
      cont = ((m_iTaskNo >= 0) && (m_iTaskNo < KP_FILESYS_NUM_TASKS));
      KP_ASSERT(cont, E_INVALIDARG, null, False);
   }

   if((!cont) || FAILED(retc)) m_iTaskNo = -1;

return(retc);
}
// #endif // #if IBSH_PROJ == IBSH_PROJ_TEVT


// --------------------------------------------
// standartinis GeckoStream sukûrimo metodas
// sukuria XKpGeckoStream skaitymui ið iðorinio failo
#if CompilerGr==Mingw
HRESULT KpFileSys::CreateGeckoStream(const unsigned char *lpszFName, const unsigned char *lpszURI, IInputStream **ppGeckoStream)
{
HRESULT retc = S_OK;
FILE *file = NULL;
XKpGeckoStream *ret_p = NULL;

KP_TRACE_("KpFileSys::CreateGeckoStream(%s)", lpszFName);

   KP_ASSERT(lpszFName != NULL, E_INVALIDARG, null, True);
   KP_ASSERT(lpszURI != NULL, E_INVALIDARG, null, True);
   KP_ASSERT(ppGeckoStream != NULL, E_INVALIDARG, null, True);
   KP_ASSERT(*ppGeckoStream == NULL, KP_E_DOUBLE_CALL, null, True);

   BlockSemaphore();

// ---------------------------------------
#ifdef IBSHT_EXT_FILES_ARCHIVED // iðoriniai HTML failai archyve

   KP_ASSERT(KpGeckoDialogPtr != NULL, E_POINTER, null, True);

// if(SUCCEEDED(retc)) retc = CloseFiles(True);

   KP_ASSERT(strlen(lpszFName) <= KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, null, True);
   if(SUCCEEDED(retc)) strcpy(m_lpszCurSearchKwd, lpszFName);

// keièiam failà
// if(SUCCEEDED(retc)) retc = OpenFiles();

   m_lCurEntryId = (-1L);

XmlO1 *in_file = NULL;
unsigned char *entry_img = null;
   if(SUCCEEDED(retc)) if(m_lThreadId == 0)
   {
      retc = SearchForEntry(KpGeckoDialogPtr, lpszFName, &in_file, &entry_img);

      KP_ASSERT(in_file != NULL, E_POINTER, lpszFName, True);

//    KP_NEW(ret_p, XKpGeckoStream(in_file, lpszURI, entry_img)); // registruot nereikia – iðtrina tux_gecko
      ret_p = new XKpGeckoStream(in_file, lpszURI, entry_img);
      KP_ASSERT(ret_p != NULL, KP_E_OUTOFMEM, null, True);

      if((ppGeckoStream != NULL) /* && SUCCEEDED(retc) */) *ppGeckoStream = ret_p;
      else if(ret_p != NULL) delete(ret_p); // KP_DELETE(ret_p);
      ret_p = NULL;
   }

#else // #ifdef IBSHT_EXT_FILES_ARCHIVED

// --------------------------------------- failai palaidi uþkoduoti
#  ifdef IBSHT_ENCODED
unsigned char *file_buf = null;
long file_len = 0L;
   if(SUCCEEDED(retc)) retc = ReadFileContents(lpszFName, &file_buf, &file_len, False, True);

// ------ atkoduojam
   KP_ASSERTE(file_buf != null, KP_E_SYSTEM_ERROR, null, True);

long entry_id = 0L; // TODO: èia ákomponuot kaþkaip failo pavadinimà ar ilgá (lzdsht èia naudojamas lEntryId)

#if FALSE // KpHp11 iðkvietimai kaþko lauþia multithreadiná Gecko streamø kûrimà
static KpRcPars rc_pars;
   KP_ASSERT(file_len < (Maxint + 1) * 4, KP_E_BUFFER_OVERFLOW, lpszFName, False); // perkoduoja tik tiek, galas lieka neperkoduotas

   if(SUCCEEDED(retc))
   {
      rc_pars.iOpCode = KP_RC_ENCODE_ENTRY;
      rc_pars.iParBlSize = sizeof(rc_pars);
      rc_pars.enc.iDataLen = ((file_len + 4) / 4) * 4;
      rc_pars.enc.pData = file_buf;
      rc_pars.enc.lCtrl = entry_id; // TODO: èia ákomponuot kaþkaip failo pavadinimà ar ilgá (lzdsht èia naudojamas lEntryId)

      retc = EmuTv.ExecRemoteCall(&rc_pars /* , lMainThreadId */);
   }
#else
int prod_ver = 0;
   KP_ASSERT(theKpStAppPtr, KP_E_NO_FILE, null, True);
   if(SUCCEEDED(retc)) retc = theKpStAppPtr->GetIniProdVer(&prod_ver);

// PutLogMessage_("KpFileSys::CreateGeckoStream(): %x %d %d %l", file_buf, file_len, prod_ver, entry_id); 
// if(SUCCEEDED(retc)) retc = EnctBufMed(file_buf, file_len, prod_ver, entry_id);
   if(SUCCEEDED(retc)) retc = EnctBufInc(file_buf, file_len, prod_ver, entry_id, False);
#endif

// ----------- kuriam streamà
// KP_NEW(ret_p, XKpGeckoStream(file_buf, lpszURI, file_len)); // registruot nereikia – iðtrina tux_gecko
   if(SUCCEEDED(retc)) ret_p = new XKpGeckoStream(file_buf, lpszURI, file_len);
   KP_ASSERT(ret_p != NULL, KP_E_OUTOFMEM, null, True);

// --------------------------------------- paprasti palaidi nekoduoti failai
#  else // #  ifdef IBSHT_ENCODED

   if(SUCCEEDED(retc))
   {
      file = fopen((const char *)lpszFName, (strstr(lpszFName, ".htm") || strstr(lpszFName, ".xml") ||
                               strstr(lpszFName, ".css") || strstr(lpszFName, ".txt"))?"r":"rb");
      if(file != NULL)
      {
//       KP_NEW(ret_p, XKpGeckoStream(file, lpszURI)); // registruot nereikia – iðtrina tux_gecko
         ret_p = new XKpGeckoStream(file, lpszURI);
         KP_ASSERT(ret_p != NULL, KP_E_OUTOFMEM, null, True);
      }
   }

#  endif

   if((ppGeckoStream != NULL) /* &&  SUCCEEDED(retc) */) *ppGeckoStream = ret_p;
   else if(ret_p != NULL) delete(ret_p); // KP_DELETE(ret_p);
   ret_p = NULL;

#endif

   ReleaseSemaphore();

return(retc);
}
#endif


// -----------------------------------------
HRESULT KpFileSys::GetReactToSel(bool *pbReactToSel)
{
HRESULT retc = S_OK;

   KP_ASSERT(pbReactToSel, KP_E_SYSTEM_ERROR, null, True);

   *pbReactToSel = False;

return(retc);
}
