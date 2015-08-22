// --------------------------------
// setatf.cpp atmintuko kodo ‘ra’ymas ‘ pamok÷ valdant‘ .fdf fail–
//

// --------------------------------
#include "envir.h"

#include <stdio.h>
#include <windows.h>
// #include <iostream> 
#include <fstream> 
#include <string>
#include <richedit.h>
#include <time.h>

#include "kpstdlib.h"
#include "kperrno.h"
#include "kptree.h"
#include "kpcolors.h"
#include "kptt.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpstdio.h"
#include "kperr.h"
#include "kpsock.h"
#include "kpwindow.h"
#include "kphp11y.h"
#include "kphp11d.h"
#include "kphp11rc.h"
#include "kphp11i.h"
#include "kpcapp.h"
#include "tvmain.h"
#include "xmlp.h"
#include "kpstap.h"

#define MAX_COMP_DATA_POS 20

// using namespace std;

// --------------------------------
const unsigned char lpszProdName[] = "setatf"; 
KpErrorProc_tag KpErrorProc(True, 43);
int iProdVerGlob=0;
KpStApp theApp;
bool bServiceFl=False;
int KpHp11NumOfExtFun=KP_RC_CBIX_NumOfCommonIxs;
KpHp11ExtFun KpHp11ExtFunTab[KP_RC_CBIX_NumOfCommonIxs_3+1]=
// HRESULT (*KpHp11ExtFunTab)(void *pPars)[]=
{
   GetCommonCompID_RC,
   TestFlashID_RC,
   TestIniChSum_RC,
   SetIniChSum_RC,
   
   CheckResRequest_RC,
   CheckRelRequest_RC,
   
   NULL
};


// -----------------------------------------
HRESULT TestCompilerSettingsLocal(void)
{
#include "kpstcs.cpp"
}


// --------------------------------
int main(int argc, char **argv)
{
HRESULT retc=S_OK;
KpString file_name;
KpString file_name_only;
KpString atm_kod_str;
filebuf fb;
KpInStream *in_file_ptr = NULL;
KpOutStream *out_file_ptr = NULL;
XmlTagPars *dat_rec = NULL;
static unsigned char par_val[MAX_XML_PAR_VAL_LEN + 1];
static unsigned char file_buf[MAX_XML_PAR_VAL_LEN + 1];
int par_num;
static unsigned char f_disk[KP_MAX_FNAME_LEN+1];
static unsigned char f_path[KP_MAX_FNAME_LEN+1];
static unsigned char f_name[KP_MAX_FNAME_LEN+1];
static unsigned char f_type[KP_MAX_FTYPE_LEN+1];
int ll;
const unsigned char *pnts;
unsigned char *pntd;

   theKpStAppPtr = &theApp;

   if(SUCCEEDED(retc)) retc = KpInit();

   if(SUCCEEDED(retc))
   {
      if(argc != 3)
      {
#ifdef Debug
         file_name = "x7_1_n.fdf";
         atm_kod_str = "5M6-584394"; // "IB6-604342";
#else
         cout << endl;
         cout << "SetAtF.exe - .fdf failo papildymas atmintuko kodu" << endl;
         cout << endl;
         cout << "setatf.exe x7_1_n.fdf IB6-604342" << endl;
         cout << "                        ^" << endl;
         cout << "                        +---- atmintuko kodas" << endl;
         cout << endl;
#endif
      }
      else // if(argc != 3)
      {
         file_name = argv[1]; 
         atm_kod_str = argv[2];

      } // else // if(argc != 2)

   } // if(SUCCEEDED(retc))
   
// -------------------------------- skaitom .fdf
   if(SUCCEEDED(retc))
      if(!fb.open(file_name, ios::in))
         retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_NOT_FOUND, null, True, __FILE__, __LINE__, 0L, NULL);
   KP_NEW(in_file_ptr, KpInStream(&fb));
   
   if(SUCCEEDED(retc))
   {
      dat_rec = NULL;
      retc = theApp.GetKpstFdfDataRec(&dat_rec, in_file_ptr, FdfInputFdf);
   }
   if((dat_rec == NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L, NULL);

   fb.close();
   
   KP_DELETE(in_file_ptr);

// ----------------------------- i’sitraukiam JavaScript–
   if(SUCCEEDED(retc))
   {
      retc = dat_rec->SeekTextPar("JavaScript", par_val, &par_num);
      if(retc == KP_E_KWD_NOT_FOUND)
         retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L, NULL);
   }

// ----------------------------- tikrinam, ar atm. kodo dar n”ra
   if(SUCCEEDED(retc))
   {
      strcpy(file_buf, par_val);
      retc = RemoveSpacesCode(file_buf);
   }
   if(SUCCEEDED(retc))
   {
      if(strstr(file_buf, "varAN=") == NULL) // dar ne
      {

// ----------------------------- i’traukiam tiksl÷ failo vard– be kelio
         retc = TvFnameSplit(f_disk, f_path, f_name, f_type, file_name.ExtractUnsignedValueA());
         if(SUCCEEDED(retc))
         {
            file_name_only = f_name;
            file_name_only += ".";
            file_name_only += (const char *)f_type;
         }

// ----------------------------- uÿkoduojam atmintuko kod–
         if(SUCCEEDED(retc))
            retc = theApp.EncAtmKod(&atm_kod_str, file_name_only);
         
// ----------------------------- pridedam prie JavaScripto
         if(SUCCEEDED(retc))
         {
            ll = strlen(par_val);
            if(ll >= KP_MAX_FILE_LIN_LEN - atm_kod_str.length() - 20) 
               retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L, NULL);
         }
         
         if(SUCCEEDED(retc)) if(ll > 0)
            if(par_val[ll - 1] != '\n') strcat(par_val, "\n");
            
         if(SUCCEEDED(retc))
         {
            strcat(par_val, "var AN=\"");

            pnts = atm_kod_str.ExtractUnsignedValueA();
            pntd = par_val + strlen(par_val);
            while(*pnts)
            {
               if(*pnts == '\"') *pntd++ = '\\';
               *pntd++ = *pnts++;
            }
            *pntd = Nul;
                        
            strcat(par_val, "\";\n");            
         }                           

// ----------------------------- ‘statom atgal parametro reik’m“
         if(SUCCEEDED(retc))
            retc = dat_rec->SetTextPar(par_num, par_val);

// ----------------------------- ‘ra’om fail– atgal
         if(SUCCEEDED(retc))
            if(!fb.open(file_name, ios::out))
               retc = KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
         KP_NEW(out_file_ptr, KpOutStream(&fb));

         if(SUCCEEDED(retc))
            retc = theApp.SaveKpstFdfDataRec(dat_rec, out_file_ptr, FdfOutputFdf);

         if(!fb.close()) if(SUCCEEDED(retc))
            retc = KpErrorProc.OutputErrorMessage(KP_E_FERROR, file_name.ExtractUnsignedValueA(), True, __FILE__, __LINE__, 0L, NULL);

         KP_DELETE(out_file_ptr);

      } // if(strstr(file_buf, "varAN=") != 0)
      
   } // if(SUCCEEDED(retc))
   
// ----------------------------
#ifdef Debug
system("pause");
#endif   
   
return(RET_CODE_MAIN(retc));
}

