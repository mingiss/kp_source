// ---------------------------
// kpstapa.cpp failø archyvas KpStArc
//

// -----------------------------------------
#include "envir.h"

#include <string>
#include <fstream>
#include <windows.h>
#include <richedit.h>
#include <Richole.h>

#include "kpstdlib.h"
#include "kperrno.h"
#include "kptt.h"
#include "kptree.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpcolors.h"
#include "kpstdio.h"
#include "res_com.h"
#include "kpwindow.h"
#include "kperr.h"
#include "kpstapa.h"


KpStArc::KpStArc(const unsigned char *lpszObjFileName, long lStartPos, long lLength)
{
HRESULT retc = S_OK;

   m_lhOpenResult = S_OK;

   m_lpszObjFileName[0] = Nul;

   m_lDirEnd = m_lContentsStart = m_lStartPos = 0L;
   m_lLength = 0L;

   KP_ASSERT(lpszObjFileName, E_INVALIDARG, null, True);
   KP_ASSERT(strlen(lpszObjFileName) <= KP_MAX_FNAME_LEN, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc))
   {
      strcpy(m_lpszObjFileName, lpszObjFileName);

      m_lDirEnd = m_lStartPos = lStartPos;
      m_lLength = lLength;
      m_lContentsStart = m_lStartPos + m_lLength;
   }

   if(SUCCEEDED(m_lhOpenResult)) m_lhOpenResult = retc;
}


HRESULT KpStArc::GetOpenResult(void)
{
return(m_lhOpenResult);
}


HRESULT KpStArc::FormatArc(void)
{
HRESULT retc = S_OK;

fstream obj_file((const char *)m_lpszObjFileName, ios::in | ios::out | ios::binary);
   KP_ASSERT(!obj_file.fail(), KP_E_FILE_NOT_FOUND, m_lpszObjFileName, True);

   if(SUCCEEDED(retc)) obj_file.seekp(m_lStartPos);
   KP_ASSERT(!obj_file.fail(), KP_E_FILE_FORMAT, m_lpszObjFileName, True);

   if(SUCCEEDED(retc)) for(long ll = 0; ll < m_lLength; ll++) obj_file.write("", 1);
   KP_ASSERT(!obj_file.fail(), KP_E_FERROR, m_lpszObjFileName, True);

   obj_file.close();
   KP_ASSERT(!obj_file.fail(), KP_E_FERROR, m_lpszObjFileName, True);

   m_lDirEnd = m_lStartPos;
   m_lContentsStart = m_lStartPos + m_lLength;

return(retc);
}


HRESULT KpStArc::LookupArc(void)
{
HRESULT retc = S_OK;
KpStArcDirEntry dir_entry;

fstream obj_file((const char *)m_lpszObjFileName, ios::in | ios::binary);
   KP_ASSERT(!obj_file.fail(), KP_E_FILE_NOT_FOUND, m_lpszObjFileName, True);

   if(SUCCEEDED(retc)) obj_file.seekp(m_lStartPos);
   KP_ASSERT(!obj_file.fail(), KP_E_FILE_FORMAT, m_lpszObjFileName, True);

   do
   {
      obj_file.read((char *)&dir_entry, sizeof(dir_entry));
      KP_ASSERT(!obj_file.eof(), KP_E_FILE_FORMAT, m_lpszObjFileName, True);
      KP_ASSERT(!obj_file.fail(), KP_E_FERROR, m_lpszObjFileName, True);

      if(dir_entry.m_lpszFileName[0] && SUCCEEDED(retc))
      {
         KP_ASSERT(m_lDirEnd + sizeof(KpStArcDirEntry) < m_lContentsStart, KP_E_FILE_FORMAT, m_lpszObjFileName, True);
         if(SUCCEEDED(retc)) if(dir_entry.m_lFileStart < m_lContentsStart)
         {
            KP_ASSERT(m_lDirEnd + sizeof(KpStArcDirEntry) < dir_entry.m_lFileStart, KP_E_FILE_FORMAT, m_lpszObjFileName, True);
            if(SUCCEEDED(retc)) m_lContentsStart = dir_entry.m_lFileStart;
         }
         if(SUCCEEDED(retc)) m_lDirEnd += sizeof(KpStArcDirEntry);
      }

   } while(dir_entry.m_lpszFileName[0] && SUCCEEDED(retc));

   obj_file.close();

return(retc);
}


HRESULT KpStArc::AppendFolder(const unsigned char *lpszSrcPath, const unsigned char *lpszBasePath)
{
HRESULT retc = S_OK;
HANDLE enumeration = INVALID_HANDLE_VALUE;
WIN32_FIND_DATA file_data;
DWORD retw = ERROR_SUCCESS;
static unsigned char enum_path[KP_MAX_FNAME_LEN + 100];
static unsigned char src_file[KP_MAX_FNAME_LEN + 1];

   KP_ASSERT(lpszSrcPath, E_INVALIDARG, null, True);
   KP_ASSERT(lpszBasePath, E_INVALIDARG, null, True);
   KP_ASSERT(strstr(lpszSrcPath, lpszBasePath) == lpszSrcPath, E_INVALIDARG, null, True);
   KP_ASSERT(strlen(lpszSrcPath) <= KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, null, True);

   if(SUCCEEDED(retc))
   {
      strcpy(enum_path, lpszSrcPath);
      strcat(enum_path, "/*.*");
      enumeration = FindFirstFile((const char *)enum_path, &file_data);
      if((enumeration == INVALID_HANDLE_VALUE) && SUCCEEDED(retc))
      {
         retw = GetLastError();
         if((retw != ERROR_FILE_NOT_FOUND) && (retw != ERROR_PATH_NOT_FOUND) && (retw != ERROR_NO_MORE_FILES))
         KP_ERROR(KP_E_SYSTEM_ERROR, retw);
      }
   }
   if((enumeration != INVALID_HANDLE_VALUE) && SUCCEEDED(retc)) do
   {
      KP_ASSERT(strlen(lpszSrcPath) + 1 + strlen(file_data.cFileName) <= KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, null, True);
      if(SUCCEEDED(retc))
      {
         strcpy(src_file, lpszSrcPath);
         strcat(src_file, "\\");
         strcat(src_file, file_data.cFileName);
      }

      if(SUCCEEDED(retc))
      {
// ---------- pakatalogis
         if(file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
         {
            if((strcmp(file_data.cFileName, ".") != 0) && (strcmp(file_data.cFileName, "..") != 0))
               retc = AppendFolder(src_file, lpszBasePath);
         }
         else retc = AppendFile(src_file, lpszBasePath);

      } // if(SUCCEEDED(retc))

// ---------------- kitas failas
      retw = ERROR_SUCCESS;
      if(SUCCEEDED(retc))
         if(!FindNextFile(enumeration, &file_data))
         {
            retw = GetLastError();
            if(retw == ERROR_NO_MORE_FILES)
            {
               // retc = KP_E_FILE_NOT_FOUND;
            }
            else KP_ERROR(KP_E_SYSTEM_ERROR, retw);
         }

   } while((retw != ERROR_NO_MORE_FILES) && SUCCEEDED(retc));

return(retc);
}


HRESULT KpStArc::AppendFile(const unsigned char *lpszSrcPath, const unsigned char *lpszBasePath)
{
HRESULT retc = S_OK;
const unsigned char *dst_file = null;
KpStArcDirEntry dir_entry;
char cur_byte;

   KP_ASSERT(lpszSrcPath, E_INVALIDARG, null, True);
   KP_ASSERT(lpszBasePath, E_INVALIDARG, null, True);
   KP_ASSERT(strstr(lpszSrcPath, lpszBasePath) == lpszSrcPath, E_INVALIDARG, null, True);
   KP_ASSERT(strlen(lpszSrcPath) <= KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, null, True);

   if(SUCCEEDED(retc)) retc = KpGetFileSizeName(lpszSrcPath, &(dir_entry.m_lFileLen));
// printf("[%s], dydis: %d  m_lDirEnd: %d  m_lContentsStart: %d  liko: %d\n", lpszSrcPath, dir_entry.m_lFileLen, m_lDirEnd, m_lContentsStart, m_lContentsStart - m_lDirEnd);
   KP_ASSERT(sizeof(KpStArcDirEntry) + 1 + // katalogo áraðas + nulinis baitas katalogo galo poþymiui
             dir_entry.m_lFileLen + 1 <= // failo turinys + galo nulinis baitas
             m_lContentsStart - m_lDirEnd, // laisvos srities ilgis
             KP_E_BUFFER_OVERFLOW, lpszSrcPath, True);

   if(SUCCEEDED(retc))
   {
      dst_file = lpszSrcPath + strlen(lpszBasePath);
      if((*dst_file == '/') || (*dst_file == '\\')) dst_file++;

printf("%s\n", dst_file);

      strcpy(dir_entry.m_lpszFileName, dst_file);
      dir_entry.m_lFileStart = m_lContentsStart - dir_entry.m_lFileLen - 1;
   }

fstream obj_file((const char *)m_lpszObjFileName, ios::in | ios::out | ios::binary);
   KP_ASSERT(!obj_file.fail(), KP_E_FILE_NOT_FOUND, m_lpszObjFileName, True);

   if(SUCCEEDED(retc)) obj_file.seekp(m_lDirEnd);
   KP_ASSERT(!obj_file.fail(), KP_E_FILE_FORMAT, m_lpszObjFileName, True);

   if(SUCCEEDED(retc)) obj_file.write((const char *)&dir_entry, sizeof(dir_entry));
   KP_ASSERT(!obj_file.fail(), KP_E_FERROR, m_lpszObjFileName, True);

   if(SUCCEEDED(retc)) obj_file.seekp(dir_entry.m_lFileStart);
   KP_ASSERT(!obj_file.fail(), KP_E_FILE_FORMAT, m_lpszObjFileName, True);

fstream in_file((const char *)lpszSrcPath, ios::in | ios::binary);
   KP_ASSERT(!in_file.fail(), KP_E_FILE_NOT_FOUND, m_lpszObjFileName, True);

   if(SUCCEEDED(retc)) for(long ll = 0; (ll < dir_entry.m_lFileLen) && SUCCEEDED(retc); ll++)
   {
      in_file.get(cur_byte);
      KP_ASSERT(!in_file.eof(), KP_E_EOF, lpszSrcPath, True);
      KP_ASSERT(!in_file.fail(), KP_E_FERROR, lpszSrcPath, True);

      if(SUCCEEDED(retc))
      {
         obj_file.put(cur_byte);
         KP_ASSERT(!obj_file.fail(), KP_E_FERROR, m_lpszObjFileName, True);
      }
   }
   if(SUCCEEDED(retc)) obj_file.put(Nul);
   KP_ASSERT(!obj_file.fail(), KP_E_FERROR, m_lpszObjFileName, True);

   in_file.close();

   obj_file.close();
   KP_ASSERT(!obj_file.fail(), KP_E_FERROR, m_lpszObjFileName, True);

   if(SUCCEEDED(retc))
   {
      m_lDirEnd += sizeof(KpStArcDirEntry);
      m_lContentsStart = dir_entry.m_lFileStart;
   }

return(retc);
}


HRESULT KpStArc::ExtractFiles(const unsigned char *lpszBasePath)
{
HRESULT retc = S_OK;
KpStArcDirEntry dir_entry;
static unsigned char dst_file[KP_MAX_FNAME_LEN + 1];
long cur_dir_pos;
long ll;
char cur_byte;

   KP_ASSERT(lpszBasePath, E_INVALIDARG, null, True);

fstream obj_file((const char *)m_lpszObjFileName, ios::in | ios::binary);
   KP_ASSERT(!obj_file.fail(), KP_E_FILE_NOT_FOUND, m_lpszObjFileName, True);

   cur_dir_pos = m_lStartPos;

   do
   {
      if(SUCCEEDED(retc)) obj_file.seekp(cur_dir_pos);
      KP_ASSERT(!obj_file.fail(), KP_E_FILE_FORMAT, m_lpszObjFileName, True);

      obj_file.read((char *)&dir_entry, sizeof(dir_entry));
      KP_ASSERT(!obj_file.eof(), KP_E_FILE_FORMAT, m_lpszObjFileName, True);
      KP_ASSERT(!obj_file.fail(), KP_E_FERROR, m_lpszObjFileName, True);

      cur_dir_pos += sizeof(KpStArcDirEntry);
      KP_ASSERT(cur_dir_pos < m_lContentsStart, KP_E_FILE_FORMAT, m_lpszObjFileName, True);

      if(dir_entry.m_lpszFileName[0] && SUCCEEDED(retc))
      {
         ll = strlen(lpszBasePath);
         KP_ASSERT(ll + 1 + strlen(dir_entry.m_lpszFileName) <= KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, dir_entry.m_lpszFileName, True);
         if(SUCCEEDED(retc))
         {
            strcpy(dst_file, lpszBasePath);
            if(ll) if((dst_file[ll - 1] != '/') && (dst_file[ll - 1] != '\\')) strcpy(dst_file + ll, "/"); // strcat(dst_file, "/");
            strcat(dst_file, dir_entry.m_lpszFileName);

            if(SUCCEEDED(retc)) retc = CreatePath(dst_file, True);

fstream out_file((const char *)dst_file, ios::out | ios::binary);
            KP_ASSERT(!out_file.fail(), KP_E_DIR_ERROR, dst_file, True);

            if(SUCCEEDED(retc)) obj_file.seekp(dir_entry.m_lFileStart);
            KP_ASSERT(!obj_file.fail(), KP_E_FILE_FORMAT, m_lpszObjFileName, True);

            for(ll = 0; (ll < dir_entry.m_lFileLen) && SUCCEEDED(retc); ll++)
            {
               obj_file.get(cur_byte);
               KP_ASSERT(!obj_file.eof(), KP_E_EOF, m_lpszObjFileName, True);
               KP_ASSERT(!obj_file.fail(), KP_E_FERROR, m_lpszObjFileName, True);

               if(SUCCEEDED(retc))
               {
                  out_file.put(cur_byte);
                  KP_ASSERT(!out_file.fail(), KP_E_FERROR, dst_file, True);
               }
            }

            out_file.close();
            KP_ASSERT(!out_file.fail(), KP_E_FERROR, dst_file, True);

         } // if(SUCCEEDED(retc))

      } // if(dir_entry.m_lpszFileName[0] && SUCCEEDED(retc))

   } while(dir_entry.m_lpszFileName[0] && SUCCEEDED(retc));

   obj_file.close();

return(retc);
}


HRESULT KpStArc::DelFiles(const unsigned char *lpszBasePath)
{
HRESULT retc = S_OK;
KpStArcDirEntry dir_entry;
static unsigned char dst_file[KP_MAX_FNAME_LEN + 1];
long cur_dir_pos;
long ll;

   KP_ASSERT(lpszBasePath, E_INVALIDARG, null, True);

fstream obj_file((const char *)m_lpszObjFileName, ios::in | ios::binary);
   KP_ASSERT(!obj_file.fail(), KP_E_FILE_NOT_FOUND, m_lpszObjFileName, True);

   if(SUCCEEDED(retc)) obj_file.seekp(m_lStartPos);
   KP_ASSERT(!obj_file.fail(), KP_E_FILE_FORMAT, m_lpszObjFileName, True);
   cur_dir_pos = m_lStartPos;

   do
   {
      obj_file.read((char *)&dir_entry, sizeof(dir_entry));
      KP_ASSERT(!obj_file.eof(), KP_E_FILE_FORMAT, m_lpszObjFileName, True);
      KP_ASSERT(!obj_file.fail(), KP_E_FERROR, m_lpszObjFileName, True);

      cur_dir_pos += sizeof(KpStArcDirEntry);
      KP_ASSERT(cur_dir_pos < m_lContentsStart, KP_E_FILE_FORMAT, m_lpszObjFileName, True);

      if(dir_entry.m_lpszFileName[0] && SUCCEEDED(retc))
      {
         ll = strlen(lpszBasePath);
         KP_ASSERT(ll + 1 + strlen(dir_entry.m_lpszFileName) <= KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, dir_entry.m_lpszFileName, True);
         if(SUCCEEDED(retc))
         {
            strcpy(dst_file, lpszBasePath);
            if(ll) if((dst_file[ll - 1] != '/') && (dst_file[ll - 1] != '\\')) strcpy(dst_file + ll, "/"); // strcat(dst_file, "/");
            strcat(dst_file, dir_entry.m_lpszFileName);

            KP_ASSERT(DeleteFile((const char *)dst_file), KP_E_DIR_ERROR, dst_file, True);

         } // if(SUCCEEDED(retc))

      } // if(dir_entry.m_lpszFileName[0] && SUCCEEDED(retc))

   } while(dir_entry.m_lpszFileName[0] && SUCCEEDED(retc));

   obj_file.close();

return(retc);
}
