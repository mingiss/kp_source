// ----------------------------
// test_reg.cpp
// registracijos testas
//

// ------------------------------------
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <windows.h>

using namespace std;

#define BUF_LEN 1000

// ------------------------------------
int main(/* int argc, char** argv */)
{
fstream in_file;
fstream out_file("test_reg.log", ios::out | ios::app);
char in_ch;
long val;
static char str_buf[BUF_LEN + 1];
HKEY key = NULL;
static BYTE data_buf[BUF_LEN + 1];
DWORD buf_len;
DWORD val_type;

   if(out_file.fail()){ cout << "test_reg.log klaida" << endl; cin.getline(str_buf, BUF_LEN); }
   else
   { 
      out_file << "-------------------" << endl;

// ---------------
      out_file << "1: " << getenv("SystemRoot") << endl;
      out_file << "2: " << getenv("USERNAME") << endl;
      out_file << "3: " << getenv("Temp") << endl;
      out_file << "4: " << getenv("HOMEPATH") << endl;
   
// ---------------
      out_file << "5: ";
//    in_file.open("C:\\Program Files\\Common Files\\Adobe\\LocalData\\Descriptors\\{75BCD15-DFB38D-149AA44-1B3A0C8-64014}", ios::in | ios::binary);
//    in_file.open("C:\\Program Files\\Common Files\\Adobe\\LocalData\\Descriptors\\{75BCD15-DFB38D-149AA44-1B3A0C8-1163}", ios::in | ios::binary);
      in_file.open("C:\\Program Files\\Common Files\\Adobe\\LocalData\\Descriptors\\{75BCD15-DFB38D-149AA44-1B3A0C8-1071}", ios::in | ios::binary);
      if(in_file.fail()) out_file << "file not found" << endl;
      else
      {
#if FALSE
         while(TRUE)
         {
            in_file.read(&in_ch, 1);
            if(in_file.eof()) break;
            else if(in_file.fail()){ out_file << " >>> file error"; break; }
            else out_file << hex << (int)in_ch << " ";
         }
         out_file << endl;
#else
         in_file.read((char *)&val, sizeof(val));
         out_file << hex << val;
         out_file << " " << dec << ((val ^ 1071) / 10) << endl;
#endif

         in_file.close();
      }
      
// --------------
      out_file << "6: ";
//    if(RegCreateKeyEx(HKEY_CURRENT_USER, "Software\\Adobe\\LocalData\\Descriptors\\{75BCD15-DFB38D-149AA44-1B3A0C8-64014}", 
//    if(RegCreateKeyEx(HKEY_CURRENT_USER, "Software\\Adobe\\LocalData\\Descriptors\\{75BCD15-DFB38D-149AA44-1B3A0C8-1163}", 
      if(RegCreateKeyEx(HKEY_CURRENT_USER, "Software\\Adobe\\LocalData\\Descriptors\\{75BCD15-DFB38D-149AA44-1B3A0C8-1071}", 
         0, NULL, REG_OPTION_VOLATILE, KEY_QUERY_VALUE, NULL, &key, NULL) != ERROR_SUCCESS)
            out_file << "key not found" << endl; 
      else
      {
         buf_len = BUF_LEN;
         if(RegQueryValueEx(key, "EstDispl", NULL, &val_type, data_buf, &buf_len) != ERROR_SUCCESS)
            out_file << "val not found" << endl;
         else
         {
            out_file << data_buf;
char data_buf[200];            
            sscanf(data_buf, "%x", &val);
            out_file << " " << ((val ^ 1071) / 10) << endl;    
         }
         
         RegCloseKey(key);
      }
      
// --------------
      out_file << "7: ";
//    if(RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Adobe\\LocalData\\Descriptors\\{75BCD15-DFB38D-149AA44-1B3A0C8-64014}", 
//    if(RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Adobe\\LocalData\\Descriptors\\{75BCD15-DFB38D-149AA44-1B3A0C8-1163}", 
      if(RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Adobe\\LocalData\\Descriptors\\{75BCD15-DFB38D-149AA44-1B3A0C8-1071}", 
         0, NULL, REG_OPTION_VOLATILE, KEY_QUERY_VALUE, NULL, &key, NULL) != ERROR_SUCCESS)
            out_file << "key not found" << endl; 
      else
      {
         buf_len = BUF_LEN;
         if(RegQueryValueEx(key, "EstDispl", NULL, &val_type, data_buf, &buf_len) != ERROR_SUCCESS)
            out_file << "val not found" << endl;
         else
         {
            out_file << data_buf;
char data_buf[200];            
            sscanf(data_buf, "%x", &val);
            out_file << " " << ((val ^ 1071) / 10) << endl;    
         }
         
         RegCloseKey(key);
      }
      
// --------------
      out_file << "8: ";
//    if(RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\Á pagalbà abiturientui. Matematika 1999-2010_is1", 
//    if(RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\Matematyka dla Ciebie. Klasa 9. Cz. 1_is1", 
      if(RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\Ðiuolaikiðkas þvilgsnis á kompiuterinæ leidybà_is1", 
         0, NULL, REG_OPTION_VOLATILE, KEY_QUERY_VALUE, NULL, &key, NULL) != ERROR_SUCCESS)
            out_file << "key not found" << endl; 
      else
      {
         buf_len = BUF_LEN;
         if(RegQueryValueEx(key, "Inno Setup: App Path", NULL, &val_type, data_buf, &buf_len) != ERROR_SUCCESS)
            out_file << "val not found" << endl;
         else
         {
//          out_file << data_buf << endl;

            strcat((char *)data_buf, "\\data.dat");
            in_file.open((const char *)data_buf, ios::in);
            if(in_file.fail()) out_file << "file not found" << endl;
            else
            {
               out_file << endl;
               while(TRUE)
               {
                  in_file.read(&in_ch, 1);
                  if(in_file.eof()) break;
                  else if(in_file.fail()){ out_file << " >>> file error"; break; }
                  else out_file << in_ch;
               }
               out_file << endl;

               in_file.close();
            }
         }
         
         RegCloseKey(key);
      }
      
// --------------
      out_file.close(); 
   }

return(0);
}

