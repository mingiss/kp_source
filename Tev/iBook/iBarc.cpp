// ===================================================
// iBarc.cpp
// arksh (iBsh) failø archyvatorius
// visus dst katalogo failus sukiða á arksh.arc ir pagamina tekstinius indeksus
//

// ------------------------------------
#include "envir.h"
#include "iBshn.h"

#include <stdio.h>
// #include <iostream.h>
#include <iostream>
// #include <fstream.h>
#include <fstream>
#include <string>
#include <windows.h>
#include <time.h>
#include <richedit.h>
#include <Richole.h>

#include "kpstdlib.h"
#include "kperrno.h"
#include "kptt.h"
#include "kptree.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpsort.h"
#include "kpcolors.h"
#include "kpfonts.h"
#include "kpstdio.h"
#include "kpttucf.h"
#include "res_com.h"
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
#include "tvxml.h"
#include "xmlp.h"
#include "xmlh.h"
#include "xmlf.h"
#include "xml8.h"
#include "xmlu.h"
#include "tvrtf.h"
#include "tvrtfo.h"
#include "tvtex.h"
#include "xmlo1.h"
#include "xmlt.h"
#include "xmlis.h"
#include "xmli.h"
#include "KpFileSys.h"
#include "xmln.h"
#include "kpstap.h"
#include "htmt.h"

#include "iBarc.h"

// --------------------------
const unsigned char lpszProdName[] = "iBarc";
int iProdVerGlob = 0;
int iUpdNumGlob = -1;
bool bServiceFl = False;
KpErrorProcClass KpErrorProc(True, 43);

int KpHp11NumOfExtFun = KP_RC_CBIX_NumOfCommonIxs;
KpHp11ExtFun KpHp11ExtFunTab[KP_RC_CBIX_NumOfCommonIxs_5 + 1] =
// HRESULT (*KpHp11ExtFunTab)(void *pPars)[] =
{
   GetCommonCompID_RC,
   TestFlashID_RC,
   TestIniChSum_RC,
   SetIniChSum_RC,

   CheckResRequest_RC,
   CheckRelRequest_RC,

   InitRestDays_RC,
   ResumeRestDays_RC,
   ProcessRestDays_RC,

   NULL
};

// --------------------------
extern iBarc *piBarc = NULL;


// -----------------------------------------
HRESULT TestCompilerSettingsLocal(void)
{
#include "kpstcs.cpp"
}


// ------------------------------------
iBarc::iBarc(const unsigned char *lpszInFolderName, const unsigned char *lpszOutFname)
: XmlO1 // XmlI
   (
      lpszOutFname, (const unsigned char *)"w", CreateNew8File, plpszaXmlSpecCharTagsMain,
      alpszIndexNames, aiIndexWidths, // caIxLangs, iaIxEncodings, 
      XC_FirstDictTag, plpszaXmlttDictTags, 
      False, // bool bExternalTagsArray
      XM_VERS_XML10, iaXmlDictNulCodeTables, 
      False, // bool bMultiLine
      False // , // bool bMapToPrivate
//    False // bool bProcessSubkeys
   )
{
   KP_ASSERTC(lpszInFolderName, E_INVALIDARG, null, True);
   KP_ASSERTC(strlen(lpszInFolderName) <= KP_MAX_FNAME_LEN, E_INVALIDARG, null, True);
   if(SUCCEEDED(m_lhOpenResult)) strcpy(m_lpszInFolderName, lpszInFolderName);

   m_iFileIx = 1L;
   m_iArcFilePos = 0L;
}


// ------------------------------------
HRESULT iBarc::ProcFolder(const unsigned char *lpszInFolderName)
{
HRESULT retc = S_OK;
unsigned char *src_fmask = null;
unsigned char *src_file = null;
HANDLE enumeration = INVALID_HANDLE_VALUE;
WIN32_FIND_DATA file_data;
long retv = ERROR_SUCCESS;
fstream in_file;
unsigned char in_ch;

   KP_ASSERT(lpszInFolderName, E_INVALIDARG, null, True);
   
   KP_NEWA(src_fmask, unsigned char, strlen(lpszInFolderName) + 100); 
   KP_NEWA(src_file, unsigned char, KP_MAX_FNAME_LEN + 1); 

   if(SUCCEEDED(retc))
   {
      strcpy(src_fmask, lpszInFolderName);
      strcat(src_fmask, "\\*.*");
   }

// --------------- atidarom
   if(SUCCEEDED(retc)) enumeration = FindFirstFile((const char *)src_fmask, &file_data);
   KP_ASSERT(enumeration != INVALID_HANDLE_VALUE, KP_E_FILE_NOT_FOUND, GetLastError(), True);
   
   if(SUCCEEDED(retc)) do   
   {
      KP_ASSERT(strlen(lpszInFolderName) + 1 + strlen(file_data.cFileName) < KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, null, True);
      if(SUCCEEDED(retc))
      {
         strcpy(src_file, lpszInFolderName);
         strcat(src_file, "/"); // "\\"
         strcat(src_file, file_data.cFileName);
      }

      if(SUCCEEDED(retc))
      {
// ---------- pakatalogis – archyvuojam rekursiðkai
         if(file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) 
         {
            if((strcmp(file_data.cFileName, ".") != 0) && (strcmp(file_data.cFileName, "..") != 0))
               retc = ProcFolder(src_file);
         }
         else
         {
// ------------------ paprastas failas 

// ------------------ pildom indeksus            
            if(SUCCEEDED(retc)) retc = PutNumVal(m_iFileIx, XL_IX_SeIndex);
            if(SUCCEEDED(retc)) retc = CompleteIndexEntry(XL_IX_SeIndex);
            if(SUCCEEDED(retc)) retc = PutNumVal(m_iArcFilePos, XL_IX_SeIndex);
            if(SUCCEEDED(retc)) retc = PutCharProc(C_Lf, NULL, XL_IX_SeIndex); // '\n'

            KP_ASSERT(strstr(src_file, m_lpszInFolderName) == src_file, KP_E_SYSTEM_ERROR, null, True);
            KP_ASSERT(src_file[strlen(m_lpszInFolderName)] == '/', KP_E_SYSTEM_ERROR, null, True); // '\\'
            
            if(SUCCEEDED(retc)) retc = PutStr(src_file + strlen(m_lpszInFolderName) + 1, XL_IX_HxIndex);
            if(SUCCEEDED(retc)) retc = CompleteIndexEntry(XL_IX_HxIndex);
            if(SUCCEEDED(retc)) retc = PutNumVal(m_iFileIx++, XL_IX_HxIndex);
            if(SUCCEEDED(retc)) retc = PutCharProc(C_Lf, NULL, XL_IX_HxIndex); // '\n'
            
// ------------------ prijungiam prie archyvo 
            if(SUCCEEDED(retc))
            {
KP_TRACE(src_file);         

               in_file.open((const char *)src_file, ios_base::in | ios_base::binary);
               if(in_file.fail()) KP_ERROR(KP_E_FILE_NOT_FOUND, src_file)
               else
               {
                  do
                  {            
                     in_file.get((char &)in_ch); // in_file >> ch;
                     if(in_file.eof()) retc = KP_E_EOF;
                     if(SUCCEEDED(retc)) if(in_file.fail()) KP_ERROR(KP_E_FERROR, src_file);
                  
                     if(SUCCEEDED(retc)) m_iArcFilePos++;
                     
                     if(SUCCEEDED(retc)) retc = PutImage(&in_ch, sizeof(unsigned char), XL_IX_DefDataFile);
                     
                  } while(SUCCEEDED(retc));
               
                  if(retc == KP_E_EOF) retc = S_OK;
                  
                  in_file.close();
               }
            }

         } // else // if(file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)

      } // if(SUCCEEDED(retc))

// ---------------- kitas failas
      retv = ERROR_SUCCESS;
      if(SUCCEEDED(retc))
         if(!FindNextFile(enumeration, &file_data))
         {
            retv = GetLastError();
            if(retv == ERROR_NO_MORE_FILES)
            {
               // retc = KP_E_FILE_NOT_FOUND;
            }
            else KP_ERROR(KP_E_SYSTEM_ERROR, retv);
         }

   } while((retv != ERROR_NO_MORE_FILES) && SUCCEEDED(retc));

// --------------- uþdarom
   if((enumeration != INVALID_HANDLE_VALUE) && SUCCEEDED(retc))
   {
      if(!FindClose(enumeration))
         /* retc = */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retv, False, __FILE__, __LINE__, 0L, NULL);
      enumeration = INVALID_HANDLE_VALUE;

   } // if(enumeration != INVALID_HANDLE_VALUE)

   KP_DELETEA(src_file);
   KP_DELETEA(src_fmask);

return(retc);
}


// ------------------------------------
HRESULT iBarc::Process(void)
{
HRESULT retc = S_OK;

   retc = ProcFolder(m_lpszInFolderName);
   
return(retc);
}

   
// ------------------------------------
int main(void)
{
HRESULT retc = S_OK;

   printf("\niBsh failø archyvatorius\n\n");

   if(SUCCEEDED(retc)) retc = KpInit();

   KP_NEWO(piBarc, iBarc(IBARC_IN_FOLDER, IBARC_OUT_FNAME));
      
// ------------------
   if(SUCCEEDED(retc)) retc = piBarc->Process();

// ------------------
   KP_DELETE(piBarc);

/* if(SUCCEEDED(retc)) retc = */ KpFinit();

return(RET_CODE_MAIN(retc));
}
