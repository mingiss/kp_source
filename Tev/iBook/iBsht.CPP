// ---------------------------
// iBsht.cpp
// el. knygø perþiûros programa
// koduota failø sistema
//
//    2012.10.30  mp    blogas xGecko lango pozicionavimas, kai nurodytas iðorinis backgroundas StartGrp <background capt="...">;
//                      KpPubDlg::m_iWndSoftBorderWdt iðskaidytas á m_iWndSoftHorBorderWdt, m_iWndSoftTopBorderWdt ir m_iWndSoftBotBorderWdt
//


// -----------------------------------------
#include "envir.h"
#include "iBshn.h"
#include "lzdshn.h"

#include <stdio.h>
#include <string>
#include <fstream>
#include <windows.h>
#include <commctrl.h>
#include <richedit.h>
#include <Richole.h>
#include <time.h>

#ifdef IBSH_RES_MODE_MSHTML
#if CompilerGr==Mingw
#include "HTMLWindow.h"
#endif
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
#include "kptt.h"
#include "kptree.h"
#include "kpcolors.h"
#include "kpfonts.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpsort.h"
#include "kpstdio.h"
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
#include "tvrtf.h"
#include "tvrtfo.h"
#include "tvtex.h"
#include "tvxml.h"
#include "xmlp.h"
#include "xmlh.h"
#include "xmlf.h"
#include "xml8.h"
#include "xmlu.h"
#include "xmlb.h"
#include "xmlo1.h"
#include "xmlt.h"
#include "htmt.h"
#include "xmlis.h"
#include "xmli.h"
#include "KpFileSys.h"
#include "KpPubDlg.h"
#include "KpGecko.h"
#include "KpRtfDlg.h"
#include "xmln.h"
#include "xmlg.h"
#include "kpstap.h"
#include "tvxmle.h"
#include "xmlsty.h"
#include "iBsh.h"
#include "iBshl.h"
#include "iBsht.h"


// -----------------------------
#ifndef iBshn_included
#error iBshn.h not included
#endif

#if Envir != MSWin32
#error Envir != MSWin32
#endif


// ----------------------------------
iBshFileSys::iBshFileSys(const unsigned char *lpszFirstEntryFileName)
{
HRESULT retc = m_lhOpenResult;

   m_lpszFtype[0] = Nul;
   m_bGeckoShowFl = True;
   m_bXmlEncodeFl = True;

   KP_ASSERT(lpszFirstEntryFileName != null, E_INVALIDARG, null, True);
   KP_ASSERT(strlen(lpszFirstEntryFileName) <= KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, null, True);
   if(SUCCEEDED(retc)) strcpy(m_lpszCurSearchKwd, lpszFirstEntryFileName);

// atkelta ið KpFileSys konstruktoriaus
#ifndef IBSH_TRANSPARENT
   if(SUCCEEDED(retc)) retc = ProcessAnswer(0);
#endif

   if(SUCCEEDED(m_lhOpenResult)) m_lhOpenResult = retc;
}


// ----------------------------------
iBshFileSys::~iBshFileSys(void)
{
   CloseFiles(False);
}


// ----------------------------------
HRESULT iBshFileSys::OpenFiles
(
   const unsigned char *
//    lpszInFileName
      ,
   XmlVersions
#if IBSH_PROJ != IBSH_PROJ_LZDSH
      iVersion
#endif
      ,
   HRESULT
#if IBSH_PROJ != IBSH_PROJ_LZDSH
      KpInFileFactory
#endif
   (
      KpFile **lppFileObjPtrPtr,
      const unsigned char *lpszFNam,
      const unsigned char *lpszFMod,
      XL_FileTypes uiFTyp,
      bool bMapToPrivate
   ),
   HRESULT
#if IBSH_PROJ != IBSH_PROJ_LZDSH
      KpOutFileFactory
#endif
   (
      KpFile **lppFileObjPtrPtr,
      const unsigned char *lpszFNam,
      const unsigned char *lpszFMod,
      XL_FileTypes uiFTyp,
      bool bMapToPrivate
   )
)
{
HRESULT retc = S_OK;

#if IBSH_PROJ != IBSH_PROJ_LZDSH

unsigned char str_buf[100];
static unsigned char fname[KP_MAX_FNAME_LEN + 1];

// PutLogMessage_(">>>> iBshFileSys::OpenFiles()");

   BlockSemaphore();

// KP_ASSERT(theKpStAppPtr, KP_E_NO_FILE, null, True);

// ------------------------------ m_lpszCurSearchKwd pradinë reikðmë
// jei yra cmd eilutës parametras - failo vardas – nustatom já pradiniu failu
   if(SUCCEEDED(retc)) if(theKpStAppPtr != NULL) if(theKpStAppPtr->m_plCmdLineArgs)
   {
const unsigned char *pnts = (const unsigned char *)theKpStAppPtr->m_plCmdLineArgs->GetValue();
      KP_ASSERT(pnts != null, KP_E_SYSTEM_ERROR, null, True);
      KP_ASSERT(strlen(pnts) <= KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, null, True);

// -------------------- nustatom darbiná katalogà (IrfanView reikia, kad darbinis katalogas bûtø ten, kur nuotraukos)
static unsigned char disk[KP_MAX_FNAME_LEN + 1];
static unsigned char path[KP_MAX_FNAME_LEN + 1];
static unsigned char name[KP_MAX_FNAME_LEN + 1];
static unsigned char type[KP_MAX_FTYPE_LEN + 1];

      if(SUCCEEDED(retc)) retc = TvFnameSplit(disk, path, name, type, pnts);

      if(SUCCEEDED(retc)) SetCurrentDirectory((const char *)path);

// èia jeigu parametras – katalogo vardas, ne failas; failo atveju bus klaida ir nieko nepasikeis
      if(SUCCEEDED(retc))
      {
         strcpy(fname, path);
         strcat(fname, "\\");
         strcat(fname, name);
         strcat(fname, ".");
         strcat(fname, type);

         SetCurrentDirectory((const char *)fname);
      }

// --------------------
      if(SUCCEEDED(retc)) strcpy(m_lpszCurSearchKwd, pnts);

// --------------------
      if(SUCCEEDED(retc)) retc = ExtractFileType();
   }

// --------------------------
   m_pKpInFileFactory = KpInFileFactory;
   m_pKpOutFileFactory = KpOutFileFactory;

// --------------------------
#  ifdef IBSHT_ARCHIVE
   if(SUCCEEDED(retc))
   {
      strcpy(fname, IBSHT_ARCFNAME);
#     ifdef IBSHT_ENCODED
      strcat(fname, ".xdb");
#     else
//    strcat(fname, ".xml");
//    strcat(fname, ".htm");
      strcat(fname, ".arc");
#     endif
   }

// -------------------------------- m_lpInFileObj
   KP_NEWO(m_lpInFileObj, XmlI
      (
         fname,
         (const unsigned char *)"rb",
         CreateNew8File,
         plpszaHtmSpecCharTags,
         alpszIndexNames, aiIndexWidths, caIxLangs, iaIxEncodings,
         HTM_TG_FirstTag, plpszaHtmlTags,
         iVersion, // XM_VERS_HTML401_TRANS,
         iaHtmCodeTables71, // iaHtmNulCodeTables, // yra 8-bièiø simboliø jau prieð <meta http-equiv=Content-Type content="text/html; charset=windows-1257">
         True, False
         , False
      ));
#  endif // #ifdef IBSHT_ARCHIVE

// -------------------------------- m_lpOutFileObj
   KP_ASSERT(m_pResBuf != NULL, KP_E_NO_FILE, null, True);

#  ifdef IBSHT_ARCHIVE
   KP_ASSERT(m_lpInFileObj->FilePtr, KP_E_NO_FILE, null, True);
#  endif

   if(SUCCEEDED(retc))
      sprintf((char *)str_buf, "%x %x", m_pResBuf, KP_FILESYS_RESULT_BUF_LEN);

   KP_NEWO(m_lpOutFileObj, XmlO1((const unsigned char *)str_buf, (const unsigned char *)"w",
                        m_pKpOutFileFactory, // CreateNewUniBFile, // CreateNewBFile,
                        plpszaHtmSpecCharTags,
                        NULL, NULL,
                        HTM_TG_FirstTag,
#  ifdef IBSHT_ARCHIVE
                        m_lpInFileObj->
                           FilePtr->
                           GetTagsArrPtr(), True,
#  else
                        plpszaHtmlTags, False,
#  endif
                        XM_VERS_XHTML, // XM_VERS_HTML401_TRANS,
                        (m_pKpOutFileFactory == CreateNewUniBFile)?iaHtmNulCodeTables:iaHtmCodeTables71,
                        False, // True,
                        False));

#  ifndef IBSH_TRANSPARENT
   if(SUCCEEDED(retc)) retc = m_lpOutFileObj->SetPathMode(
#     ifdef IBSH_RES_MODE_MSHTML
      XL_AbsolutePath
#     endif
#     ifdef IBSH_RES_MODE_XGECKO
      XL_TuxPath
#     endif
      );
#  endif

// --------------------
   ReleaseSemaphore();

#endif // #if IBSH_PROJ != IBSH_PROJ_LZDSH

return(retc);
}


// --------------------------------------------------
HRESULT iBshFileSys::CloseFiles(bool bCheckFileExist)
{
HRESULT retc = S_OK;
HRESULT retc0 = S_OK;

   BlockSemaphore();

   if(m_lpInFileObj != NULL)
   {
#ifdef IBSHT_ARCHIVE
XmlI
#else
XmlO1
#endif
   *in_file;
      in_file = m_lpInFileObj;
      m_lpInFileObj = NULL;
      retc = in_file->CloseFile(bCheckFileExist);
      KP_DELETE(in_file);
   }
   else
   {
      if(!bCheckFileExist) retc = KP_E_NO_FILE;
      else retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, 0L);
   }

   if(m_lpOutFileObj != NULL)
   {
      retc0 = m_lpOutFileObj->CloseFile(bCheckFileExist);
      if(SUCCEEDED(retc)) retc = retc0;

      KP_DELETE(m_lpOutFileObj);
   }
   else
   {
      if(SUCCEEDED(retc))
      {
         if(!bCheckFileExist) retc = KP_E_NO_FILE;
         else retc = KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, 0L);
      }
   }

   ReleaseSemaphore();

return(retc);
}


// ----------------------------------
HRESULT iBshFileSys::ExtractFileType()
{
HRESULT retc = S_OK;

// -------------------------- ieðkom failo tipo
   if(SUCCEEDED(retc))
   {
const unsigned char *pnts, *pnts1;

      m_lpszFtype[0] = Nul;

      pnts = strchr(m_lpszCurSearchKwd, '.');
      if(pnts)
      {
         do
         {
            pnts1 = strchr(pnts + 1, '.');
            if(pnts1) pnts = pnts1;
         } while(pnts1);

         strcpy(m_lpszFtype, pnts);
         strlwr(m_lpszFtype);
         if(
            (strcmp(m_lpszFtype, ".htm") == 0) || (strcmp(m_lpszFtype, ".html") == 0) ||
            (strcmp(m_lpszFtype, ".xml") == 0) || (strcmp(m_lpszFtype, ".xhtml") == 0) ||
            (strcmp(m_lpszFtype, ".svg") == 0)
           )
         {
            m_bGeckoShowFl = True;
            m_bXmlEncodeFl = True;
         }
         else if(
                  (strcmp(m_lpszFtype, ".jpg") == 0) || (strcmp(m_lpszFtype, ".png") == 0) || (strcmp(m_lpszFtype, ".gif") == 0) ||
                  (strcmp(m_lpszFtype, ".bmp") == 0) || (strcmp(m_lpszFtype, ".tif") == 0) ||
                  (strcmp(m_lpszFtype, ".js") == 0) ||
                  (strcmp(m_lpszFtype, ".swf") == 0) || (strcmp(m_lpszFtype, ".flv") == 0) ||
                  (strcmp(m_lpszFtype, ".mp4") == 0)
                )
         {
            m_bGeckoShowFl = True;
            m_bXmlEncodeFl = False;
         }
         else
         {
            m_bGeckoShowFl = False;
            m_bXmlEncodeFl = False;
         }
      }
   }

return(retc);
}


// ----------------------------------
HRESULT iBshFileSys::SearchForEntry
(
   KpPubDlg *pDialogPtr,
   const unsigned char *lpszFileName,
   XmlO1 **pInFilePtr,
   unsigned char **pEntryImgPtr
)
{
HRESULT retc = S_OK;

   BlockSemaphore();

// --------------------------
   if((lpszFileName != null) && SUCCEEDED(retc))
   {
//    KP_ASSERT(strlen(lpszFileName) <= KP_MAX_FILE_LIN_WDT, KP_E_BUFFER_OVERFLOW, null, True);
      if(SUCCEEDED(retc))
      {
         strncpy(m_lpszCurSearchKwd, lpszFileName, KP_MAX_FILE_LIN_WDT);
         m_lpszCurSearchKwd[KP_MAX_FILE_LIN_WDT] = Nul;
         m_lCurEntryId = -1;
      }
   }
// PutLogMessage_("iBshFileSys::SearchForEntry(): %s", m_lpszCurSearchKwd);

// -------------------------- ieðkom failo tipo
   if(SUCCEEDED(retc)) retc = ExtractFileType();

#ifndef IBSHT_ARCHIVE
// ------------------------- naikinam ankstesná failà
#if FALSE // naikinam iðkarto ðito iBshFileSys::SearchForEntry() pabaigoj
   if(m_lpInFileObj != NULL)
   {
XmlO1 *in_file;
      in_file = m_lpInFileObj;
      m_lpInFileObj = NULL;
      retc = in_file->CloseFile(True);
      KP_DELETE(in_file);
   }
#endif
   KP_ASSERT(m_lpInFileObj == NULL, KP_E_SYSTEM_ERROR, null, True);

// -------------------------------- m_lpInFileObj
#ifdef IBSHT_ENCODED
unsigned char *file_buf = null;
#endif
   if(m_bGeckoShowFl && SUCCEEDED(retc))
   {
#ifdef IBSHT_ENCODED
long file_len = 0L;
      if(SUCCEEDED(retc)) retc = ReadFileContents(m_lpszCurSearchKwd, &file_buf, &file_len, True, True);

// ------ atkoduojam
      KP_ASSERTE(file_buf != null, KP_E_SYSTEM_ERROR, null, True);

long entry_id = 0L; // TODO: èia ákomponuot kaþkaip failo pavadinimà ar ilgá (lzdsht èia naudojamas lEntryId)

#if FALSE // KpHp11 iðkvietimai kaþko lauþia multithreadiná Gecko streamø kûrimà
static KpRcPars rc_pars;
      KP_ASSERT(file_len < (Maxint + 1) * 4, KP_E_BUFFER_OVERFLOW, null, False); // perkoduoja tik tiek, galas lieka neperkoduotas

      if(SUCCEEDED(retc))
      {
         rc_pars.iOpCode = KP_RC_ENCODE_ENTRY;
         rc_pars.iParBlSize = sizeof(rc_pars);
         rc_pars.enc.iDataLen = ((file_len + 4) / 4) * 4;
         rc_pars.enc.pData = file_buf;
         rc_pars.enc.lCtrl = entry_id;

         retc = EmuTv.ExecRemoteCall(&rc_pars /* , lMainThreadId */);
      }
#else
int prod_ver = 0;
      KP_ASSERT(theKpStAppPtr, KP_E_NO_FILE, null, True);
      if(SUCCEEDED(retc)) retc = theKpStAppPtr->GetIniProdVer(&prod_ver);

//    if(SUCCEEDED(retc)) retc = EnctBufMed(file_buf, file_len, prod_ver, entry_id);
      if(SUCCEEDED(retc)) retc = EnctBufInc(file_buf, file_len, prod_ver, entry_id, False);
#endif

unsigned char str_buf[100];
      if(SUCCEEDED(retc))
         sprintf((char *)str_buf, "%x %x", file_buf, file_len);
// PutLogMessage_("iBshFileSys::SearchForEntry() [%s] %lx %ld [%s]", str_buf, file_buf, file_len, m_lpszCurSearchKwd);
#endif

      KP_NEWO(m_lpInFileObj, XmlO1
         (
#ifdef IBSHT_ENCODED
            str_buf,
#else
            m_lpszCurSearchKwd,
#endif
            (const unsigned char *)"rb",
// Kaþkokiu bûdu reikia atpaþinti/áhardkodinti, koks failas bus skaitomas – unicodinis ar 8-bitis.
// Pagal tai CreateNew8File arba CreateNewUniFile
// CreateNewUniFile ir ðiaip neveikia – 'þ' raidæ rodo kvadratuku su kodu 0xFFFD
            m_pKpInFileFactory,
            plpszaHtmSpecCharTags,
            NULL, NULL,
            HTM_TG_FirstTag, plpszaHtmlTags,
            False,
            XM_VERS_XHTML, // XM_VERS_HTML401_TRANS,
            iaHtmCodeTables71, // iaHtmNulCodeTables, // yra 8-bièiø simboliø jau prieð <meta http-equiv=Content-Type content="text/html; charset=windows-1257">
            True, False
         ));
   }

#endif // #ifndef IBSHT_ARCHIVE

// -----------------------------------------
KpChar cur_tag = XC_Nul;
unsigned char *entry_img = null;
long img_len = 0L;
#ifdef IBSHT_ARCHIVE
#  ifdef IBSHT_ENCODED
XmlO1 *in_file = NULL;
#  else
XmlI *in_file = NULL;
#  endif
long entry_id;
long offset;
unsigned char cur_kwd[TV_XL_MAX_IX_LEN+1];
#else
XmlO1 *in_file = NULL;
#endif // #ifdef IBSHT_ARCHIVE

   if(m_bGeckoShowFl && SUCCEEDED(retc))
   {
      KP_ASSERT(m_lpInFileObj, KP_E_NO_FILE, null, True);
      KP_ASSERT(m_lpOutFileObj, KP_E_NO_FILE, null, True);
      KP_ASSERT(pDialogPtr, KP_E_NO_FILE, null, True);

#ifdef IBSHT_ARCHIVE
      KP_ASSERT(m_lpInFileObj->FilePtr, KP_E_NO_FILE, null, True);
#endif
   }

// ------------------------ lango antraðtë
#if IBSH_SKIN == IBSH_SKIN_MIKO
const unsigned char *pnts, *pnts1;
unsigned char *pntd, *pntd1;

   if(SUCCEEDED(retc))
   {
// --------- ieðkom failo vardo (praleidþiam kelià)
      pnts = m_lpszCurSearchKwd;
      do
      {
         pnts1 = strchr(pnts, '\\');
         if(pnts1 == NULL) pnts1 = strchr(pnts, '/');
         if(pnts1) pnts = pnts1 + 1;
      } while(pnts1);

// --------- nustatom lango antraðtæ
      strncpy(pDialogPtr->m_lpszCaption, pnts, TV_XL_MAX_IX_LEN);
      pDialogPtr->m_lpszCaption[TV_XL_MAX_IX_LEN] = Nul;

// --------- ieðkom paskutinio taðko – kirpsim failo prievardá
      pntd = strchr(pDialogPtr->m_lpszCaption, '.');
      if(pntd) do
      {
         pntd1 = strchr(pntd + 1, '.');
         if(pntd1) pntd = pntd1;
      } while(pntd1);
      if(pntd) *pntd = Nul;
   }

   if(SUCCEEDED(retc)) if(pDialogPtr->m_hCaption)
   {
unsigned char caption[TV_XL_MAX_IX_LEN + 100];

      strcpy(caption, pDialogPtr->m_lpszCaption);
      strcat(caption, " – ");
      strcat(caption, IBSH_WND_CAPTION);

      retc = KpSetCtrlText(pDialogPtr->m_hCaption, caption);
   }
#endif

// ------------------------
#ifdef IBSHT_ARCHIVE
   if(SUCCEEDED(retc))
   {
      strncpy(cur_kwd, m_lpszCurSearchKwd, TV_XL_MAX_IX_LEN);
      cur_kwd[TV_XL_MAX_IX_LEN] = Nul;
   }

   if(SUCCEEDED(retc)) CvtIndexEntry(cur_kwd);

   if(SUCCEEDED(retc)) retc = m_lpInFileObj->SearchEntry(&entry_id, &offset, cur_kwd, m_iCurIndexFile, True);
   if(SUCCEEDED(retc)) m_lCurEntryId = entry_id;

#  ifdef IBSHT_ENCODED
int prod_ver;
unsigned char str_buf[100];

   KP_ASSERT(theKpStAppPtr, KP_E_SYSTEM_ERROR, null, True);
   if(SUCCEEDED(retc)) retc = theKpStAppPtr->GetIniProdVer(&prod_ver);

   if(SUCCEEDED(retc)) retc = m_lpInFileObj->ReadEntryImg(entry_id, &entry_img, &img_len);
   KP_ASSERT(entry_img, KP_E_SYSTEM_ERROR, null, True);

   if(SUCCEEDED(retc)) retc = EnctBufMed(entry_img, img_len, prod_ver, entry_id);

   if(m_bGeckoShowFl && SUCCEEDED(retc))
   {
      sprintf((char *)str_buf, "%x %x", entry_img, img_len);

      KP_NEWO(in_file, XmlO1((const unsigned char *)str_buf, (const unsigned char *)"rb",
                        CreateNewBFile,
                        plpszaHtmSpecCharTags,
                        NULL, NULL,
                        HTM_TG_FirstTag,
                        m_lpInFileObj->
                           FilePtr->
                           GetTagsArrPtr(), True, // plpszaHtmlTags, False,
                        XM_VERS_HTML401_TRANS,
                        m_bXmlEncodeFl?iaHtmCodeTables71:iaHtmNulCodeTables, // yra 8-bièiø simboliø jau prieð <meta http-equiv=Content-Type content="text/html; charset=windows-1257">
                        True, False));
   }

#  else // #  ifdef IBSHT_ENCODED
   if(SUCCEEDED(retc)) retc = m_lpInFileObj->SeekEntry(entry_id);

   if(SUCCEEDED(retc)) in_file = m_lpInFileObj;
#  endif

#else // #ifdef IBSHT_ARCHIVE
#ifndef IBSHT_ENCODED
   if(SUCCEEDED(retc)) retc = m_lpInFileObj->Fseek(XL_IX_DefDataFile, 0, SEEK_SET); // fseek neveikia buferiniams failams, be to, èia to ir nereikia – visada vienas failas, atvertas nuo pradþios
#endif
   if(SUCCEEDED(retc)) m_lCurEntryId = 0;

   if(SUCCEEDED(retc)) in_file = m_lpInFileObj;
#endif // #else // #ifdef IBSHT_ARCHIVE

   if(SUCCEEDED(retc))
   {
      if(m_bGeckoShowFl)
      {
         KP_ASSERT(in_file, KP_E_SYSTEM_ERROR, null, True);

         if(m_bXmlEncodeFl)
         {
//          KP_ASSERT(m_pCurEntry == NULL, KP_E_SYSTEM_ERROR, null, True);
            KP_DELETE(m_pCurEntry);

            do
            {
               retc = ReadEntry(&m_pCurEntry, in_file, False, HTM_TG_FirstTag, plpszaHtmlTags);
               KP_ASSERT(m_pCurEntry, KP_E_SYSTEM_ERROR, null, True);

               if(SUCCEEDED(retc)) retc = m_pCurEntry->GetNodeTag(&cur_tag);

               if((cur_tag != HTM_TG_HTML) && SUCCEEDED(retc)) KP_DELETE(m_pCurEntry);

            } while((cur_tag != HTM_TG_HTML) && SUCCEEDED(retc));

#ifdef Debug // #if FALSE //
fstream out_file("iBsh1.txt", ios::out | ios::binary);
KpChar *pnti;
// ((XmlNode *)(m_pCurEntry->m_pFirstChild->m_pNextBrother->m_pFirstChild->m_pNextBrother->m_pFirstChild))->GetNodeTag(&cur_tag);
// out_file << cur_tag << endl;
// ((XmlNode *)(m_pCurEntry->m_pFirstChild->m_pNextBrother->m_pFirstChild->m_pNextBrother->m_pFirstChild->m_pFirstChild))->GetContentsPtr(&pnti);
// ((XmlNode *)(m_pCurEntry->m_pFirstChild->m_pFirstChild->m_pNextBrother->m_pNextBrother->m_pNextBrother->m_pNextBrother->m_pFirstChild))->GetContentsPtr(&pnti);
// while(*pnti) out_file << (char)(*pnti++);
out_file.close();
#endif

// TODO !!!!! pridët prieðdëlá "tux:" <style> parametrams url(...)

// PutLogMessage_("iBshFileSys::SearchForEntry() 1");
            if(SUCCEEDED(retc)) retc = FormatEntry(m_pCurEntry, pDialogPtr);

#ifndef IBSH_SAVE_AS
            KP_DELETE(m_pCurEntry);
#endif
         }

      } // if(m_bGeckoShowFl)

      else // if(m_bGeckoShowFl)
      {
// --------------------------------
// GetLocalPath(..., KP_Temp_Dir) + TvUniFname.Generate() + m_lpszFtype[]
#ifdef IBSHT_ARCHIVE
static unsigned char out_fname[2 * KP_MAX_FNAME_LEN + KP_MAX_FILE_LIN_WDT /* KP_MAX_FNAME_LEN */ + 1];
fstream *out_file = NULL;
unsigned char *pnts;

// --------------
         if(SUCCEEDED(retc)) retc = GetLocalPath(out_fname, KP_Temp_Dir);
         if(SUCCEEDED(retc))
         {
            pnts = out_fname + strlen(out_fname);
            retc = TvUniFname.Generate(pnts);
         }
         if(SUCCEEDED(retc))
         {
            pnts = strchr(pnts, '.');
            if(pnts) strcpy(pnts, m_lpszFtype);
         }

// --------------
         KP_NEW(out_file, fstream((const char *)out_fname, ios::out | ios::binary));
         KP_ASSERT(!out_file->fail(), KP_E_DIR_ERROR, null, True);

         KP_ASSERT(entry_img != NULL, KP_E_SYSTEM_ERROR, m_lpszCurSearchKwd, True);

         if(SUCCEEDED(retc))
         {
            out_file->write((const char *)entry_img, img_len);
            KP_ASSERT(!out_file->fail(), KP_E_FERROR, null, True);
         }

         if(out_file) out_file->close();

#endif // #ifdef IBSHT_ARCHIVE

// --------------
static unsigned char cmd_line[KP_MAX_FNAME_LEN + 1];
HANDLE cmd_proc = NULL;

#ifdef IBSHT_ARCHIVE
         KP_ASSERT(strlen(out_fname) < KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, null, True);
         if(SUCCEEDED(retc))
         {
            strcpy(cmd_line, out_fname);
#else
         KP_ASSERT(strlen(m_lpszCurSearchKwd) < KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, null, True);
         if(SUCCEEDED(retc))
         {
            strcpy(cmd_line, m_lpszCurSearchKwd);
#endif
            retc = StartCmdProcess(cmd_line, KP_CUR_DIR, NULL, &cmd_proc, True, SW_SHOWNORMAL);
         }

         if(SUCCEEDED(retc)) retc = WaitForProcessEnd(cmd_proc, NULL);
         if(SUCCEEDED(retc)) retc = KpSleep(1000, HWND_DESKTOP);

// --------------
// kai paleidþiamos antra MS Word sesija (arksh.exe), WaitForProcessEnd() gráþta ið karto (GetExitCodeProcess() gràþina 0), MS Wordui dar neuþsidarius
#ifdef IBSHT_ARCHIVE
         KP_ASSERT(DeleteFile((const char *)out_fname), KP_E_DIR_ERROR, GetLastError(), False); // True);
#endif
      } // else // if(m_bGeckoShowFl)

   } // if(SUCCEEDED(retc))

#ifdef IBSHT_ARCHIVE
#  ifdef IBSHT_ENCODED
   if(m_bXmlEncodeFl)
   {
// XML enkodinamø failø neiðeina rekursinti, o gal ir nereikia
      KP_DELETE(in_file);
      KP_DELETEA(entry_img);
   }
   else
   {
      if(m_bGeckoShowFl && SUCCEEDED(retc))
      {
// gràþinam binarinio failo pointerius
         KP_ASSERT(in_file != NULL, E_POINTER, null, True);
         KP_ASSERT(pInFilePtr != NULL, E_INVALIDARG, null, True);
         if(SUCCEEDED(retc)) *pInFilePtr = in_file;
         in_file = NULL;
   
         KP_ASSERT(entry_img != NULL, E_POINTER, null, True);
         KP_ASSERT(pEntryImgPtr != NULL, E_INVALIDARG, null, True);
         if(SUCCEEDED(retc)) *pEntryImgPtr = entry_img;
         entry_img = NULL;
      }
   }
#  endif

#else // #ifdef IBSHT_ARCHIVE

#if TRUE // FALSE // !!!!!
   if(m_lpInFileObj != NULL)
   {
XmlO1 *in_file;
      in_file = m_lpInFileObj;
      m_lpInFileObj = NULL;
      retc = in_file->CloseFile(True);
      KP_DELETE(in_file);
   }

#  ifdef IBSHT_ENCODED
   KP_DELETEA(file_buf);
#  endif
#endif // #if FALSE

#endif

   ReleaseSemaphore();

return(retc);
}


// ----------------------------------
// extern int write_node_cnt;
HRESULT iBshFileSys::FormatEntry
(
XmlNode *
#ifndef IBSH_RES_MODE_RTF
   pCurEntry
#endif
   ,
KpPubDlg *
#ifndef IBSH_RES_MODE_RTF
   pDialogPtr
#endif
)
{
HRESULT retc=S_OK;

#ifdef IBSH_RES_MODE_RTF
KP_ERROR(KP_E_SYSTEM_ERROR, null);
#else
XmlVersions vers;

   if((pCurEntry==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if((m_lpOutFileObj==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, 0L);

   if((pDialogPtr==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc = m_lpOutFileObj->Reset();

// -------------------- zoom/resize
int doc_dx = 0;
int doc_dy = 0;
   if(SUCCEEDED(retc)) retc = pCurEntry->GetBgrDim(&doc_dx, &doc_dy); // iðtraukia <img id="background" parametrus

   if((doc_dx != 0) && (doc_dy != 0) && SUCCEEDED(retc))
   {
// ----------------------------- keièiam lango dydá
#ifdef IBSH_NOZOOM
#if (IBSH_SKIN == IBSH_SKIN_MIKO) || (IBSH_SKIN == IBSH_SKIN_START_GRP) || (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON) || (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_LIGHT) || (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D)
      if(pDialogPtr->m_BgrBmpData.m_hBitMap != NULL) // langas turi <background> bitmapà
      {
         pDialogPtr->m_iWndCurDXprec = pDialogPtr->m_BgrBmpData.m_iBmpWdt;
         pDialogPtr->m_iWndCurDYprec = pDialogPtr->m_BgrBmpData.m_iBmpHgt;
         pDialogPtr->m_iWndSoftHorBorderWdt = (pDialogPtr->m_BgrBmpData.m_iBmpWdt - doc_dx) / 2; // dokumento langelá centruojam fono bitmapo atþvilgiu
         pDialogPtr->m_iWndSoftTopBorderWdt = pDialogPtr->m_iWndSoftBotBorderWdt = (pDialogPtr->m_BgrBmpData.m_iBmpHgt - doc_dy) / 2;
         pDialogPtr->m_iWndSoftCaptHgt = pDialogPtr->m_BgrBmpData.m_iCaptHgt; // - pDialogPtr->m_iWndSoftVertBorderWdt; // <background caption="123" kepurë apima ir virðutiná m_iWndSoftBorderWdt
         if(pDialogPtr->m_iWndSoftCaptHgt != 0)
         {
            pDialogPtr->m_iWndSoftTopBorderWdt = 0;
            pDialogPtr->m_iWndSoftBotBorderWdt = pDialogPtr->m_BgrBmpData.m_iBmpHgt - doc_dy - pDialogPtr->m_iWndSoftCaptHgt;
            if(pDialogPtr->m_iWndSoftBotBorderWdt < 0) pDialogPtr->m_iWndSoftBotBorderWdt = 0;
         }
//       if(pDialogPtr->m_iWndSoftCaptHgt < 0) pDialogPtr->m_iWndSoftCaptHgt = 0; // gali bût ir neigiamas – kai centravimo kraðèiukai platesni uþ kietai nurodytà kepuræ
         if(pDialogPtr->m_iWndCurDYprec < pDialogPtr->m_iWndSoftTopBorderWdt + pDialogPtr->m_iWndSoftCaptHgt + doc_dy + pDialogPtr->m_iWndSoftBotBorderWdt)
            pDialogPtr->m_iWndCurDYprec = pDialogPtr->m_iWndSoftTopBorderWdt + pDialogPtr->m_iWndSoftCaptHgt + doc_dy + pDialogPtr->m_iWndSoftBotBorderWdt;
// PutLogMessage_("iBshFileSys::FormatEntry() m_iWndCurDYprec: %d  m_iWndSoftHorBorderWdt: %d  m_iWndSoftTopBorderWdt: %d  m_iWndSoftBotBorderWdt: %d  m_iWndSoftCaptHgt: %d  doc_dy: %d", pDialogPtr->m_iWndCurDYprec, pDialogPtr->m_iWndSoftHorBorderWdt, pDialogPtr->m_iWndSoftTopBorderWdt, pDialogPtr->m_iWndSoftBotBorderWdt, pDialogPtr->m_iWndSoftCaptHgt, doc_dy);
      }
      else // <background> nëra, skaièiuojam pagal <img id="background" parametrus
#endif
      {
         pDialogPtr->m_iWndCurDXprec = doc_dx + 2 * pDialogPtr->m_iWndHardBorderWdt + 2 * pDialogPtr->m_iWndSoftHorBorderWdt;
         pDialogPtr->m_iWndCurDYprec = doc_dy + 2 * pDialogPtr->m_iWndHardBorderWdt + pDialogPtr->m_iWndSoftTopBorderWdt + pDialogPtr->m_iWndSoftBotBorderWdt +
            pDialogPtr->m_iWndHardCaptHgt + pDialogPtr->m_iWndSoftCaptHgt;
      }

      if(SUCCEEDED(retc)) retc = pDialogPtr->Resize();

   } // if((doc_dx != 0) && (doc_dy != 0) && SUCCEEDED(retc))

#else // #ifdef IBSH_NOZOOM

// ----------------------------- keièiam mastelá, kad lango dydis nepasikeistø
int fact_y;
      fact_y = doc_dy * 1000L / pDialogPtr->m_iScrDY;
#  ifdef IBSH_PRESERVE_RATIO
int fact_x;
      fact_x = doc_dx * 1000L / pDialogPtr->m_iScrDX;
      pDialogPtr->m_iFact = pDialogPtr->m_iFact * 1000 / max(fact_x, fact_y);
#  else
      pDialogPtr->m_iFact = pDialogPtr->m_iFact * 1000 / fact_y;
#  endif

   } // if((doc_dx != 0) && (doc_dy != 0) && SUCCEEDED(retc))

#endif // #else // #ifdef IBSH_NOZOOM

// ------------------------
#ifndef IBSH_TRANSPARENT
   if(SUCCEEDED(retc)) retc = pCurEntry->SetCtrls((KpFileSys *)this);
#endif

#if FALSE // #ifdef Debug //
fstream out_file("iBsh1.txt", ios::out | ios::binary);
KpChar *pnti;
XmlTagPars *tag_pars;
((XmlNode *)(pCurEntry->m_pFirstChild->m_pNextBrother->m_pFirstChild))->GetTagParsPtr(&tag_pars);
unsigned char par_nam[TV_TAG_LEN+1];
static unsigned char par_val[MAX_XML_PAR_VAL_LEN + 1];
tag_pars->GetTextPar(par_nam, par_val, 1);
out_file << "----" << par_nam << " " << par_val << endl;
// out_file.close();
#endif

// unsigned char *pnts = null;
// KP_NEWA(pnts, unsigned char, 10000);
// PutLogMessage_("iBshFileSys::FormatEntry() in %x %x %x [%s] [%x] [%x]", pnts, &iBshFileSys::FormatEntry, m_lpOutFileObj->m_lpszFName,
//   ((TvXmlBFile *)(((TvXmlUniFile *)(m_lpOutFileObj->m_fFiles[0]->m_lpLowLevelFile))->lpfUniFilePtr->lpFile))->m_lpszBufPtr,
//   ((TvXmlBFile *)(((TvXmlUniFile *)(m_lpOutFileObj->m_fFiles[0]->m_lpLowLevelFile))->lpfUniFilePtr->lpFile))->m_lCharNum);
// KP_DELETEA(pnts);
// write_node_cnt = 0;

#ifdef DebugStartGrp // Debug //
PutLogMessage_("iBshFileSys::FormatEntry() >>>>>>>>>>>>>>>>>>>>>>>");
#endif
#ifdef IBSH_RES_MODE_RTF
// if(SUCCEEDED(retc)) retc = pCurEntry->WriteRtf(m_lpOutFileObj, ...
#else
   if(SUCCEEDED(retc)) retc = pCurEntry->WriteNode(m_lpOutFileObj);
#endif
#ifdef DebugStartGrp // Debug //
PutLogMessage_("iBshFileSys::FormatEntry() <<<<<<<<<<<<<<<<<<<<<<<");
#endif

// KP_NEWA(pnts, unsigned char, 10000);
// PutLogMessage_("iBshFileSys::FormatEntry() ou %x %x %x [%s] [%x] [%x]", pnts, &iBshFileSys::FormatEntry, m_lpOutFileObj->m_lpszFName,
//   ((TvXmlBFile *)(((TvXmlUniFile *)(m_lpOutFileObj->m_fFiles[0]->m_lpLowLevelFile))->lpfUniFilePtr->lpFile))->m_lpszBufPtr,
//   ((TvXmlBFile *)(((TvXmlUniFile *)(m_lpOutFileObj->m_fFiles[0]->m_lpLowLevelFile))->lpfUniFilePtr->lpFile))->m_lCharNum);
// KP_DELETEA(pnts);

#if FALSE // #ifdef Debug //
((XmlNode *)(pCurEntry->m_pFirstChild->m_pNextBrother->m_pFirstChild))->GetTagParsPtr(&tag_pars);
tag_pars->GetTextPar(par_nam, par_val, 1);
out_file << "----" << par_nam << " " << par_val << endl;
out_file.close();
#endif


#ifdef Debug // #if TRUE // #if FALSE //
#  if TRUE // ifndef TEST_GECKO_FROM_FILE
if(SUCCEEDED(retc))
{
fstream out_file
(
   (pDialogPtr->m_iXmlVers == XML_VERS_XML10)?
   "iBsh1.xml":
   (
      (pDialogPtr->m_iXmlVers == XML_VERS_HTML401_TRANS)?
      "iBsh1.htm":
      (
         (pDialogPtr->m_iXmlVers == XML_VERS_XHTML)?
         "iBsh1.htm": // "iBsh1.xhtml":
         "iBsh1.htm"
      )
   ),
   ios_base::out | ios_base::binary
);
out_file.write((const char *)m_pResBuf, strlen((const unsigned char *)m_pResBuf));
out_file.close();
}
#  endif
#endif

#ifndef DebugStartGrp
   if(SUCCEEDED(retc)) retc = pDialogPtr->DisplayResult();
   if(SUCCEEDED(retc)) retc = pDialogPtr->RedrawWindow();
#endif

#endif // #else // #ifdef IBSH_RES_MODE_RTF
return(retc);
}


// ----------------------------------
HRESULT XmlNode::SetCtrls(KpFileSys *KpFileSysPtr)
{
HRESULT retc = S_OK;
XmlNode *loop_brother = NULL;
XmlNode *cur_child = NULL;
XmlNode *next_brother = NULL;
XmlNode *grand_father = NULL;
KpChar cur_tag;
KpChar grand_father_tag;
XmlTagPars *tag_pars = NULL;
XmlTagPars *grand_father_pars = NULL;
// static unsigned char par_val[MAX_XML_PAR_VAL_LEN + 100];
static unsigned char submit_type[MAX_XML_PAR_VAL_LEN + 100];
static unsigned char submit_name[MAX_XML_PAR_VAL_LEN + 100];
int par_num;
bool cont = True;
const unsigned char *pnts = NULL;
int answ_no;
// int answ_mask;
int task_no;

   KP_ASSERT(KpFileSysPtr, KP_E_SYSTEM_ERROR, null, True);

// loop on brothers
   loop_brother = this;
// while((loop_brother != NULL) && SUCCEEDED(retc))
   if((loop_brother != NULL) && SUCCEEDED(retc))
   {
//    retc = loop_brother->GetFirstChild((KpTreeEntry **)&cur_child);
      cur_child = (XmlNode *)loop_brother->m_pFirstChild;

// -------------------------- loop through next children
      while((cur_child != NULL) && SUCCEEDED(retc))
      {

// recursion through children of children first
         if(SUCCEEDED(retc)) retc = cur_child->SetCtrls(KpFileSysPtr);

         if(SUCCEEDED(retc)) retc = cur_child->GetNextBrother((KpTreeEntry **)&next_brother);
         if(SUCCEEDED(retc)) retc = cur_child->GetNodeTag(&cur_tag);

// <input type="RADIO" name="a2" onclick="sel_task('p1', 'a2')"/>
         if((cur_tag == HTM_TG_INPUT) && SUCCEEDED(retc))
         {
            retc = cur_child->GetTagParsPtr(&tag_pars);
            if(SUCCEEDED(retc))
            {
               if(tag_pars == NULL) KP_WARNING(KP_E_FILE_FORMAT, null)
               else
               {
                  retc = tag_pars->SeekTextPar("name", submit_name, &par_num);
                  if(FAILED(retc)) KP_WARNING(retc, null)
                  else
                  {
                     retc = tag_pars->SeekTextPar("type", submit_type, &par_num);
                     if(FAILED(retc)) KP_WARNING(retc, null)
                     else
                     {
                        strlwr(submit_type);

                        if(strcmp(submit_type, "radio") == 0)
                        {
                           cont = ((KpFileSysPtr->m_iTaskNo >= 0) && (KpFileSysPtr->m_iTaskNo < KP_FILESYS_NUM_TASKS));
                           KP_ASSERT(cont, E_UNEXPECTED, null, False);

                           if(cont && SUCCEEDED(retc))
                           {
                              cont = (submit_name[0] == 'a');
                              KP_ASSERT(cont, E_INVALIDARG, submit_name, False);
                           }
                           if(cont && SUCCEEDED(retc))
                           {
                              cont = (sscanf((const char *)submit_name+1, "%d", &answ_no) == 1);
                              KP_ASSERT(cont, E_INVALIDARG, null, False);
                           }
                           if(cont && SUCCEEDED(retc))
                           {
                              cont = ((answ_no >= 0) && (answ_no <= KP_FILESYS_MAX_ANSWER));
                              KP_ASSERT(cont, E_INVALIDARG, null, False);
                           }
                           if(cont && SUCCEEDED(retc))
                           {
//                            answ_mask = (1 << answ_no);
//                            if(KpFileSysPtr->m_aiAnswers[KpFileSysPtr->m_iTaskNo] & answ_mask)
                              if(KpFileSysPtr->m_aiAnswers[KpFileSysPtr->m_iTaskNo] == answ_no)
                                 retc = tag_pars->AddTextPar("checked", "");
                           }

                        } // if(strcmp(submit_type, "radio") == 0)

                        else if(strcmp(submit_type, "submit") == 0)
                        {
                           pnts = submit_name;
                           while(*pnts && (!TvIsDigit(*pnts))) pnts++;

                           cont = (sscanf((const char *)pnts, "%d", &task_no) == 1);
                           KP_ASSERT(cont, E_INVALIDARG, null, False);

                           if(cont && SUCCEEDED(retc))
                           {
                              cont = ((task_no >= 0) && (task_no < KP_FILESYS_NUM_TASKS));
                              KP_ASSERT(cont, E_INVALIDARG, null, False);
                           }

                           if(cont && SUCCEEDED(retc))
                              if(KpFileSysPtr->m_aiAnswers[task_no])
                              {
                                 grand_father = (XmlNode *)m_pFather;
                                 cont = (grand_father != NULL); KP_ASSERT(cont, KP_E_FILE_FORMAT, null, False);

                                 if(cont && SUCCEEDED(retc)) retc = grand_father->GetNodeTag(&grand_father_tag);

                                 if(cont && SUCCEEDED(retc)){ cont = (grand_father_tag == HTM_TG_TD); KP_ASSERT(cont, KP_E_FILE_FORMAT, null, False); }

                                 if(cont && SUCCEEDED(retc)) retc = grand_father->GetTagParsPtr(&grand_father_pars);
                                 if(cont && SUCCEEDED(retc)){ cont = (grand_father_pars != NULL); KP_ASSERT(cont, KP_E_FILE_FORMAT, null, False); }

                                 if(cont && SUCCEEDED(retc)) retc = grand_father_pars->AddTextPar("bgcolor", "green");
                              }

                        } // if(strcmp(submit_type, "submit") == 0)

                     } // else // if(FAILED(retc)) // retc = tag_pars->SeekTextPar("type", par_val, &par_num);

                  } // else // if(FAILED(retc)) // retc = tag_pars->SeekTextPar("name", submit_name, &par_num);

               } // else // if(tag_pars == NULL)

            } // if(SUCCEEDED(retc)) // retc = cur_child->GetTagParsPtr(&tag_pars);

         } // if((cur_tag == HTM_TG_INPUT) && SUCCEEDED(retc))

         cur_child = next_brother;

      } // while((cur_child!=NULL) && SUCCEEDED(retc))

//    if(SUCCEEDED(retc)) retc=loop_brother->GetNextBrother((KpTreeEntry **)&loop_brother);

   } // while((loop_brother!=NULL) && SUCCEEDED(retc))

// recursion on brothers
// if((pNextBrother != NULL) && SUCCEEDED(retc)) retc = pNextBrother->SetCtrls();

return(retc);
}


// --------------------------------------------
HRESULT iBshFileSys::CvtIndexEntry(unsigned char *lpscKwd)
{
HRESULT retc = S_OK;
unsigned char *pntd;

   KP_ASSERT(lpscKwd, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc))
   {
      pntd = lpscKwd;
      while(*pntd)
      {
         if(*pntd == '\\') *pntd = '/';
         pntd++;
      }
   }

return(retc);
}
