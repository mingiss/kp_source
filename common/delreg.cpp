// -------------------------
//

#include <stdio.h>
#include <windows.h>
#include <Winreg.h>

#if FALSE
// extern LONG WINAPI RegDeleteTreeA(HKEY hKey, LPCTSTR lpSubKey);
// extern LONG WINAPI RegDeleteTree(__in HKEY hKey, __in_opt  LPCTSTR lpSubKey);

void del_key(HKEY hQueryKey, const char *lpszKeyName, const char *lpszSubKeyToDelete)
{
LONG retw = ERROR_SUCCESS;
HKEY hkey = NULL;

   retw = RegOpenKeyEx(hQueryKey, lpszKeyName, 0, DELETE|KEY_QUERY_VALUE|KEY_ENUMERATE_SUB_KEYS, &hkey);
   if(retw != ERROR_SUCCESS) printf("------------ neatsidaro %s retw=%ld\n", lpszKeyName, retw);
   else
   {
//    RegDeleteTreeA(hkey, lpszSubKeyToDelete);
   }
}
#endif

void del_key(HKEY hQueryKey, const char *lpszKeyName, const char *lpszSubKeyToDelete)
{
HKEY hkey = NULL;
char key_name[200 + 1];
char val_name[200 + 1];
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

   if((lpszKeyName == NULL) || (lpszSubKeyToDelete == NULL)) printf("------------ blogi parametrai\n");
   else if(strlen(lpszKeyName) + strlen(lpszSubKeyToDelete) + 1 >= 400) printf("------------ per ilgas rakto vardas\n");
   else
   {
      strcpy(key_name, lpszKeyName);
      strcat(key_name, "\\");
      strcat(key_name, lpszSubKeyToDelete);
   
      printf("skanuojam raktà [%s]\\[%s]\\[%s]\n", (hQueryKey == HKEY_LOCAL_MACHINE)?"HKEY_LOCAL_MACHINE":((hQueryKey == HKEY_CURRENT_USER)?"HKEY_CURRENT_USER":"???"), lpszKeyName, lpszSubKeyToDelete);
      retw = RegOpenKeyEx(hQueryKey, key_name, 0, DELETE|KEY_QUERY_VALUE|KEY_SET_VALUE|KEY_ENUMERATE_SUB_KEYS, &hkey);
      if(retw != ERROR_SUCCESS) printf("------------ neatsidaro %s retw=%ld\n", key_name, retw);
      else
      {
// ---------------------------------- enum values
         key_ix = 0;
         do
         {
            name_len = 200;
            dwBufLen = 200;

            retw = RegEnumValue(hkey, key_ix++, val_name, &name_len, NULL, &dwValType, (LPBYTE)&val_buf, &dwBufLen); 
            if(retw == ERROR_NO_MORE_ITEMS) break;
            else if(retw != ERROR_SUCCESS) printf("--------- neskaito retw=%ld %ld\n", retw, key_ix - 1);
            else 
            {
               printf("trinam reikðmæ %s\n", val_name);
               retw = RegDeleteValue(hkey, val_name);
               if(retw != ERROR_SUCCESS) printf("--------- netrina reikðmës %s retw=%ld\n", val_name, retw);
            }
            
         } while(TRUE); // (retw == ERROR_SUCCESS);

// ---------------------------------- enum subkeys
         key_ix = 0;
         do
         {
            name_len = 200;
            class_len = 200;
            retw = RegEnumKeyEx(hkey, key_ix++, sub_key_name, &name_len, NULL, class_name, &class_len, NULL);
            if(retw == ERROR_NO_MORE_ITEMS) break;
            else if(retw != ERROR_SUCCESS) printf("--------- nesinumeruoja retw=%ld %ld\n", retw, key_ix - 1);
            else
            {   
               printf("rekursija [%s]\\[%s] [%s]\n", key_name, sub_key_name, class_name);
               printf("rekursija [%s]\\[%s]\\[%s]\n", (hQueryKey == HKEY_LOCAL_MACHINE)?"HKEY_LOCAL_MACHINE":((hQueryKey == HKEY_CURRENT_USER)?"HKEY_CURRENT_USER":"???"), key_name, sub_key_name, class_name);

               del_key(hQueryKey, key_name, sub_key_name);
            }
         
         } while(TRUE); // (retw == ERROR_SUCCESS);
      }
      
      if(hkey) RegCloseKey(hkey);
   
// ---------------------------------- trinam raktà      
      printf("trinam raktà [%s]\\[%s]\\[%s]\n", (hQueryKey == HKEY_LOCAL_MACHINE)?"HKEY_LOCAL_MACHINE":((hQueryKey == HKEY_CURRENT_USER)?"HKEY_CURRENT_USER":"???"), lpszKeyName, lpszSubKeyToDelete);
      retw = RegOpenKeyEx(hQueryKey, lpszKeyName, 0, DELETE|KEY_QUERY_VALUE|KEY_ENUMERATE_SUB_KEYS, &hkey);
      if(retw != ERROR_SUCCESS) printf("------------ neatsidaro %s retw=%ld\n", lpszKeyName, retw);
      else
      {
         retw = RegDeleteKey(hkey, lpszSubKeyToDelete);
         if(retw != ERROR_SUCCESS) printf("--------- netrina rakto %s retw=%ld\n", lpszSubKeyToDelete, retw);
      
      } // else // if(retw != ERROR_SUCCESS) // retw = RegOpenKeyEx(hQueryKey, key_name,          

      if(hkey) RegCloseKey(hkey);
   }
}


int main()
{
// DeleteFile("C:\\Users\\mindaugas\\AppData\\Local\\Temp\\Adobe\\LocalData\\Descriptors\\{75BCD15-DFB38D-149AA44-1B3A0C8-1126-48526}");
// DeleteFile("C:\\Program Files\\Common Files\\Adobe\\LocalData\\Descriptors\\{75BCD15-DFB38D-149AA44-1B3A0C8-1126-48526}");
// del_key(HKEY_CURRENT_USER, "Software\\Adobe\\LocalData\\Descriptors", "{75BCD15-DFB38D-149AA44-1B3A0C8-1126-48526}");
// del_key(HKEY_LOCAL_MACHINE, "Software\\Adobe\\LocalData\\Descriptors", "{75BCD15-DFB38D-149AA44-1B3A0C8-1126-48526}");

   DeleteFile("C:\\Users\\mindaugas\\AppData\\Local\\Temp\\Adobe\\LocalData\\Descriptors\\{75BCD15-DFB38D-149AA44-1B3A0C8-1030-8113996}");
   DeleteFile("C:\\Program Files\\Common Files\\Adobe\\LocalData\\Descriptors\\{75BCD15-DFB38D-149AA44-1B3A0C8-1030-8113996}");
   del_key(HKEY_CURRENT_USER, "Software\\Adobe\\LocalData\\Descriptors", "{75BCD15-DFB38D-149AA44-1B3A0C8-1030-8113996}");
   del_key(HKEY_LOCAL_MACHINE, "Software\\Adobe\\LocalData\\Descriptors", "{75BCD15-DFB38D-149AA44-1B3A0C8-1030-8113996}");


return(0);
}
