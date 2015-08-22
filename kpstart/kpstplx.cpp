// ---------------------------
// kpstplx.cpp
// ðablonas programos paleidimui su registracija
// tux failø iðkodavimo pavyzdys
//

#include <time.h>
#include <windows.h>
#include <string>
#include <fstream>
#include <sstream>

#include "kperrno.h"
#include "kperr.h"
#include "kpsttrg.h"
#include "kpsttre.h"

using namespace std;


// --------------------------------------------------------------------------------------
// lokalus buferio iðkodavimas, palyginimui su KpstTuxDecodeBuf()
HRESULT KpstplTuxDecodeBufLocal(char *lpszFileBuf, long lFileLen)
{
char *pnts = lpszFileBuf;
long cnt = 0L;

   while(cnt < lFileLen) *pnts++ ^= cnt++;

return(S_OK);
}


// --------------------------------------------------------------------------------------
// tux uþkoduoto failo iðkodavimas
//
HRESULT KpstplTuxDecodeFile(const char *lpszInFileName, const char *lpszOutFileName)
{
HRESULT retc = S_OK;
fstream in_file(lpszInFileName, ios::in | ios::binary);
fstream out_file(lpszOutFileName, ios::out | ios::binary);
char *file_buf = NULL;
long file_len;

   if(in_file.fail()) retc = KP_ERROR(KP_E_FILE_NOT_FOUND);
   else
   {
      if(out_file.fail()) retc = KP_ERROR(KP_E_DIR_ERROR);
      else
      {
// failo ilgis
         in_file.seekg(0, ios::end);
         file_len = in_file.tellg();
         in_file.seekg(0, ios::beg);
         if(in_file.fail() || (file_len < 0)) retc = KP_ERROR(KP_E_FERROR);

         KP_NEWA(file_buf, char, file_len + 4 + 1); // kad bûtø galima iðlyginti iki kartotinio 4 baitø blokeliams

         if(SUCCEEDED(retc))
         {
            in_file.read(file_buf, file_len);
            if(in_file.fail()) retc = KP_ERROR(KP_E_FERROR);
         }

//       if(SUCCEEDED(retc)) retc = KpstplTuxDecodeBufLocal(file_buf, file_len);
         if(SUCCEEDED(retc)) retc = KpstTuxDecodeBuf(file_buf, file_len);

         if(SUCCEEDED(retc))
         {
            out_file.write(file_buf, file_len);
            if(out_file.fail()) retc = KP_ERROR(KP_E_FERROR);
         }

         out_file.close();

// besàlygiðkai trint negalima, gali bûti uþsilikæs KpstTuxDecodeBuf()
         if(SUCCEEDED(retc)) KP_DELETEA(file_buf);

      } // else // if(out_file.fail())

      in_file.close();

   } // else // if(InFile.fail())

return(retc);
}


// -----------------------------------------
int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
HRESULT retc = S_OK;

// -------------------------------------
// tikrinam registracijà
   retc = KpsTestReg();
   if(SUCCEEDED(retc))
   {
// pavyko
KpMsgOut("Vysks gerai", IDI_ASTERISK, KP_MB_TESTI);


// ....


   }


// -------------------------------------
// iðkoduojam failà - jei registracijos patikrinimas pavyko, turëtø atkoduoti, jei ne - ne
   /* retc = */ KpstplTuxDecodeFile("data/txe.titulinis.pdf", "titulinis.pdf");


// -------------------------------------
   if(TUX_HASH_OK_STAT) KpMsgOut("Statiðkas hash pavyko", IDI_ASTERISK, KP_MB_TESTI);
   else KpMsgOut("Statiðkas hash nepavyko", IDI_ASTERISK, KP_MB_TESTI);

// -------------
time_t cur_clock;

   time(&cur_clock);
   if(TUX_HASH_OK(cur_clock)) KpMsgOut("Time hash pavyko", IDI_ASTERISK, KP_MB_TESTI);
   else KpMsgOut("Time hash nepavyko", IDI_ASTERISK, KP_MB_TESTI);

// -------------
unsigned long rand_value;
int ii;
stringstream str_stream;
string str_str;

   if(SUCCEEDED(retc))
   {
      srand(cur_clock);
      for(ii = 0; ii < 10000; ii++)
      {
         rand_value = (unsigned long)rand()*rand();
         if(!TUX_HASH_OK(rand_value))
         {
            str_stream << "Rand hash nepavyko: " << hex << rand_value;
            KpMsgOutStr(str_stream.str(), IDI_ASTERISK, KP_MB_TESTI);
         }
      }
   }

// -------------
unsigned long ll;

   if(SUCCEEDED(retc))
   {
      for(ll = 0; ll < 0x20000L; ll++) if(!TUX_HASH_OK(ll)) KpMsgOut("Loop hash nepavyko", IDI_ASTERISK, KP_MB_TESTI);
      for(ll = 0xFFFFF000L; ll < 0xFFFFFFFFL; ll++) if(!TUX_HASH_OK(ll)) KpMsgOut("Loop hash nepavyko", IDI_ASTERISK, KP_MB_TESTI);
      if(!TUX_HASH_OK(0xFFFFFFFFL)) KpMsgOut("Loop hash nepavyko", IDI_ASTERISK, KP_MB_TESTI);
   }

// -------------------------------------
   KpMsgOut("Kpstplx pabaiga", IDI_ASTERISK, KP_MB_TESTI);

return(retc);
}
