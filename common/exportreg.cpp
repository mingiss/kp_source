// -------------------------
// former compat.cpp
// ið kpstart\klaida_Vista_compatibility_assistant
// former compat.cpp
//
// paleidus be parametrø, suformuoja uþkoduotà registro turinio failà exportreg.log
// su parametru -x tik iðkoduoja failà export.log á failà exportreg.txt
//

// ----------------------------------------
#include <stdio.h>
#include <windows.h>


#define Spc ((unsigned char)(' '))
#define Nul 0
#define null NULL
#define True TRUE
#define False FALSE

#define OUT_BUF_SIZE 10000

// ----------------------------------------
// iðvedamø raktø reikðmiø vardø sàraðas
// "@" – iðvedinëjam paties rakto tekstà (dar nerealizuota)
// elementas vienintelis null – iðvedinëjam viskà
const char *lpszaKeyFilter[] = { /* "@", */ "DisplayName", "DisplayVersion", "Publisher", null }; 

// ignoruojamø raktø reikðmiø sàraðas
// ieðko substringø, jeigu yra – neiðvedinëja
const char *lpszaValueFilter[] = 
{ 
"Update for Microsoft", // "Update for Microsoft .NET Framework", "Security Update for Microsoft Windows" 
"Update for Windows", // "Update for Windows XP", "Security Update for Windows Media Player", "Security Update for Windows XP", "Security Update for Windows Internet Explorer 8", "Update for Windows Internet Explorer 8"
"Microsoft Software Update", // "Microsoft Software Update for Web Folders  (English) 12"
"Windows XP Service Pack",
"Update for 2007 Microsoft Office", // "Update for 2007 Microsoft Office System"
"Microsoft Office 2007 Service Pack", // "Microsoft Office 2007 Service Pack 3 (SP3)" 
// "Microsoft Office Proofing Tools 2007 Service Pack", // "Microsoft Office Proofing Tools 2007 Service Pack 3 (SP3)"
"Microsoft .NET Framework 1.1 Security Update",
"Microsoft .NET Framework 2.0 Service Pack",
"Microsoft .NET Framework 3.0 Service Pack", 
"Hotfix for Microsoft", // "Hotfix for Microsoft .NET Framework"
"Hotfix for Windows", // "Hotfix for Windows XP" 
"Update Rollup 1 for Windows", // "Update Rollup 1 for Windows 2000 SP4"
"Windows 2000 Hotfix",
"Hotfix for MDAC",
"Windows Media Player Hotfix",
"Windows Media Player system update",
"Java(TM) 6 Update",
"J2SE Runtime Environment 5.0 Update",
null 
};

// ignoruojamø Publisher raktø reikðmiø sàraðas
const char *lpszaPublisherFilter[] = { /* "TEV", */ null };


// tikrina, ar iðvedinëti rakto reikðmës vardà lpszValName
bool ProcessKey(const char *lpszValName)
{
bool retv = True;
 
   if(lpszaKeyFilter[0] != null)
   {
      retv = False;
const char **pntss = lpszaKeyFilter;
      while(*pntss != null)
      {
         if(strcmp(lpszValName, *pntss) == 0)
         {
            retv = True;
            break;
         }
         pntss++;
      }
   }
   
return(retv);         
}

// tikrina, ar iðvedinëti rakto reikðmæ lpszValue
bool ExcludeKey(const char *lpszValName, const char *lpszValue)
{
bool retv = False;
 
const char **pntss = lpszaValueFilter;
   while(*pntss != null)
   {
      if(strstr(lpszValue, *pntss) != null)
      {
         retv = True;
         break;
      }
      pntss++;
   }

   if(!retv) if(strcmp(lpszValName, "Publisher") == 0)
   {
      pntss = lpszaPublisherFilter;
      while(*pntss != null)
      {
         if(strcmp(lpszValue, *pntss) == 0)
         {
            retv = True;
            break;
         }
         pntss++;
      }
   }
      
return(retv);         
}


// ----------------------------------------
#define enc_fprintf(buffer /* file */, ...) \
   { \
   static unsigned char str_buf[2000]; \
      sprintf((char *)str_buf, (const char *)__VA_ARGS__); \
      EncodeText(str_buf); \
   /* KP_ASSERT(strlen(buffer) <= OUT_BUF_SIZE, KP_E_BUFFER_OVERFLOW, null, True); */ \      
      strcat((char *)buffer, (const char *)str_buf); /* fputs((const char *)str_buf, file); */ \
   }


HRESULT EncodeText(unsigned char *lpszString)
{
HRESULT retc = S_OK;
unsigned char *pnts;

// KP_ASSERT(lpszString, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc))
   {
      pnts = lpszString;
      while(*pnts)
      {
         if((*pnts < Spc) || (*pnts >= 127)); // *pnts = '?';
         else (*pnts) = 126 - (*pnts - Spc);
         pnts++;
      }
   }

return(retc);
}


// ----------------------------------------
void enum_key(FILE *out_file, HKEY hQueryKey, const char *lpszKeyName)
{
HKEY hKey = NULL;
char key_name[200 + 1];
char sub_key_name[400 + 1];
char class_name[200 + 1];
union
{
   char text[200 + 1];
   DWORD num;
} val_buf;
DWORD key_ix;
DWORD name_len;
DWORD class_len;
LONG retw = ERROR_SUCCESS;
DWORD dwBufLen;
DWORD dwValType;
unsigned char *out_buf = null;
   KP_NEWA(out_buf, unsigned char, OUT_BUF_SIZE + 1);

   out_buf[0] = Nul;
   
   if(ProcessKey("@")) enc_fprintf(out_buf /* out_file */, "\n%s", lpszKeyName);

   retw = RegOpenKeyEx(hQueryKey, lpszKeyName, 0, KEY_QUERY_VALUE|KEY_ENUMERATE_SUB_KEYS, &hKey);
   if(retw != ERROR_SUCCESS)
   {
      if(ProcessKey("@")) enc_fprintf(out_buf /* out_file */, "------------ neatsidaro retw=%ld\n", retw);
   }
   else
   {
// ---------------------------------- enum values
bool out_fl = True;

      key_ix = 0;
      do
      {
         name_len = 200;
         dwBufLen = 200;

//       retw = RegQueryValueEx(hKey, key_name, NULL, &dwValType, 
         retw = RegEnumValue(hKey, key_ix++, key_name, &name_len, NULL, &dwValType, (LPBYTE)&val_buf, &dwBufLen);
         if(retw == ERROR_NO_MORE_ITEMS) break;

         if(ProcessKey(key_name)) 
         {         
            if(retw != ERROR_SUCCESS)
            {
               if(ProcessKey("@")) enc_fprintf(out_buf /* out_file */, "--------- neskaito retw=%ld %ld\n", retw, key_ix - 1);
            }
            else switch(dwValType)
            {
            case REG_DWORD: enc_fprintf(out_buf /* out_file */, "%s: 0x%lx\n", key_name, val_buf.num); break;
            case REG_SZ: enc_fprintf(out_buf /* out_file */, "%s: %s\n", key_name, val_buf.text); out_fl &= (!ExcludeKey(key_name, val_buf.text));  break;
            default: if(ProcessKey("@")) enc_fprintf(out_buf /* out_file */, "%s: ------------- dwValType=%ld\n", key_name, dwValType); break;
            }
         }
         
         if(!out_fl) break;
      
      } while(TRUE); // (retw == ERROR_SUCCESS);
      
      if(out_fl && (strlen((const char *)out_buf) > 0)){ fputs((const char *)out_buf, out_file); fputs("\n", out_file); }

// ---------------------------------- enum subkeys
      key_ix = 0;
      do
      {
         name_len = 200;
         class_len = 200;
         retw = RegEnumKeyEx(hKey, key_ix++, key_name, &name_len, NULL, class_name, &class_len, NULL);
         if(retw == ERROR_NO_MORE_ITEMS) break;
         else if(retw != ERROR_SUCCESS)
         {
            if(ProcessKey("@")) enc_fprintf(out_buf /* out_file */, "--------- nesinumeruoja retw=%ld %ld\n", retw, key_ix - 1);
         }
         else
         {   
//          enc_fprintf(out_buf /* out_file */, "%s\\%s [%s] ", lpszKeyName, key_name, class_name);

            strcpy(sub_key_name, lpszKeyName);
            strcat(sub_key_name, "\\");
            strcat(sub_key_name, key_name);

            enum_key(out_file, hQueryKey, sub_key_name);
         }
         
      } while(TRUE); // (retw == ERROR_SUCCESS);
   }         

   if(hKey) RegCloseKey(hKey);
   
   KP_DELETEA(out_buf);
}


int main(int argc, char** argv)
{
FILE *out_file = NULL;
FILE *in_file = NULL;
static unsigned char in_str[2000];
static unsigned char fname[2000];

   if(argc > 1) if(strcmp(argv[1], "-x") == 0)
   {
      strcpy((char *)fname, argv[0]);
      strcat((char *)fname, ".log");
      in_file = fopen((const char *)fname, "r");
      strcpy((char *)fname, argv[0]);
      strcat((char *)fname, ".txt");
      out_file = fopen((const char *)fname, "w");
      
      if(in_file)
      {
         while(TRUE)
         {
            if(fgets((char *)in_str, 2000, in_file) == NULL) break;
            EncodeText(in_str);
            fputs((const char *)in_str, out_file);
         }
         fclose(out_file);
      }
   }
   
   if(argc <= 1)
   {

//    out_file = fopen("compat.log", "a");
//    out_file = fopen("exportreg.log", "a");
      strcpy((char *)fname, argv[0]);
      strcat((char *)fname, ".log");
      out_file = fopen((const char *)fname, "a");
   
      if(out_file)
      {
unsigned char out_buf[1000];
 
//       fputs("======================================\n", out_file);
         out_buf[0] = Nul;
         enc_fprintf(out_buf /* out_file */, "COMPUTERNAME: %s\n\n", getenv("COMPUTERNAME"));
         fputs((const char *)out_buf, out_file);

//       enum_key(out_file, "Software\\Microsoft\\Windows NT\\CurrentVersion\\AppCompatFlags");
//       enum_key(out_file, "Software\\Adobe\\Acrobat Reader\\7.0");
//       enum_key(out_file, "Software\\TEV\\3012");
//       enum_key(out_file, "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders");
//       enum_key(out_file, HKEY_CURRENT_USER, "Software\\Adobe\\LocalData\\Descriptors\\{75BCD15-DFB38D-149AA44-1B3A0C8-1126}");
//       enum_key(out_file, HKEY_LOCAL_MACHINE, "Software\\Adobe\\LocalData\\Descriptors");
         enum_key(out_file, HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall");
         enum_key(out_file, HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall");
//       enum_key(out_file, HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Services\\USBSTOR\\Enum");
//       enum_key(out_file, HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Services\\Disk\\Enum");

//       enum_key(out_file, HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System");

   
         fputs("\n", out_file);

         fclose(out_file);
      }
   }
   
return(0);
}
