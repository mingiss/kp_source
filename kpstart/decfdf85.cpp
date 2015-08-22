// --------------------------------
// decfdf85.cpp data.dat failo su vartotojo informacija iskodavimas
//

// --------------------------------
#include "envir.h"
#include "iBshn.h"
#include "lzdshn.h"

#include <stdio.h>
#include <windows.h>

#if CompilerGr == Mingw
#include <iostream>
#endif

#include <fstream>
#include <string>
#include <richedit.h>
#include <time.h>

using namespace std;

#if CompilerGr == Mingw
#include "IInputStream.hh"
#include "IString.hh"
#include "XApplication.hh"
#include "XGecko.hh"
#include "XGeckoDOMEvent.hh"
#include "XGeckoInit.hh"
#endif

#include "kpstdlib.h"
#include "kperrno.h"
#include "kptt.h"
#include "kptree.h"
#include "kpcolors.h"
#include "kpfonts.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpstdio.h"
#include "kperr.h"
#include "kpttucf.h"
#include "kpsock.h"
#include "res_com.h"
#include "kpwindow.h"
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
#include "KpGecko.h"
#include "xmln.h"
#include "kpstap.h"

#define MAX_COMP_DATA_POS 20

// using namespace std;
// #define cout stdout

// --------------------------------
const unsigned char lpszProdName[] = "decfdf85";
KpErrorProcClass KpErrorProc(True, 71);
// int SortMode=KP_LNG_LIT;
int iProdVerGlob=0;
int iUpdNumGlob = -1;
// KpStApp theApp;
#define theApp (*theKpStAppPtr)
bool bServiceFl=False;
int KpHp11NumOfExtFun=KP_RC_CBIX_NumOfCommonIxs;
KpHp11ExtFun KpHp11ExtFunTab[KP_RC_CBIX_NumOfCommonIxs_8 + 1] =
// HRESULT (*KpHp11ExtFunTab)(void *pPars)[]=
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
   ResetRestDays_RC,

   RegSert_RC,
   UnRegSert_RC,

   NULL
};


// -----------------------------------------
HRESULT TestCompilerSettingsLocal(void)
{
#include "kpstcs.cpp"
}


// --------------------------------
int main(
#ifdef Debug
void
#else
int argc, char **argv
#endif
)
{
HRESULT retc=S_OK;
HRESULT retc0=S_OK;
KpString dat_str;
XmlTagPars *dat_rec = NULL;
XmlTagPars *dat_rec_ptr = NULL;
unsigned char par_nam[TV_TAG_LEN + 1];
static unsigned char par_val[MAX_XML_PAR_VAL_LEN + 1];
// unsigned char ini_fname[KP_MAX_FNAME_LEN + 1];
// String inp_mode_str;
FdfInputMode inp_mode = FdfInputFdf;
// String outp_mode_str;
FdfOutputMode outp_mode = FdfOutputRawAscii;
// String comp_data_pos_str;
int comp_data_pos;
#ifdef Debug
// istream in_file("data.dat", ios::in);
// fstream in_file("data.dat", ios::in);
// KpInStream in_file("data.dat", ios::in);
// KpInStream /* fstream */ in_file((const unsigned char *)"data.dat" /* "test_fl.log" */, ios::in);
filebuf fb;
const unsigned char *fname = null;
KpInStream *in_file_ptr = NULL;
#define in_file (*in_file_ptr)
#else
#if CompilerGr == Mingw
// #define in_file cin
KpInStream in_file(cin.rdbuf());
#else
KpInStream in_file(cin);
#endif
#endif
static unsigned char add_comp_data[KPSTAP_NUM_OF_ADD_COMP_DATA][KP_MAX_FILE_LIN_LEN+1];
int ii, jj;
const /* unsigned */ char *pnts;
const unsigned char *pntsu;
unsigned char *pntd;
int len;
const unsigned char *start_pos;
int start_len;
int win_ver;

// theKpStAppPtr = &theApp;
   KP_NEW(theKpStAppPtr, KpStApp());

   if(SUCCEEDED(retc))
   {
#ifdef Debug
      inp_mode = FdfInputRawA85; // FdfInputFdf; // FdfInputRawAscii; //
      outp_mode = FdfOutputAscii; // FdfOutputRawAscii;
      comp_data_pos = 2; // 0; //

      if(SUCCEEDED(retc))
      {
         fname = (const unsigned char *)"data.dat";
         if(!fb.open((const char *)fname, ios::in))
            retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_NOT_FOUND, fname, True, __FILE__, __LINE__, 0L, NULL);
      }

      KP_NEW(in_file_ptr, KpInStream(&fb));
#else
      if(argc==4)
      {
         if(SUCCEEDED(retc))
         {
//          inp_mode_str = argv[1];
//          inp_mode_str >> inp_mode;
            sscanf(argv[1], "%d", &inp_mode);
            if(((inp_mode < 0) || (inp_mode >= FdfInputMax)) && SUCCEEDED(retc))
            {
               inp_mode = FdfInputFdf;
               retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);
            }
         }

         if(SUCCEEDED(retc))
         {
//          outp_mode_str = argv[2];
//          outp_mode_str >> outp_mode;
            sscanf(argv[2], "%d", &outp_mode);
            if(((outp_mode < 0) || (outp_mode >= FdfOutputMax)) && SUCCEEDED(retc))
            {
               outp_mode = FdfOutputRawAscii;
               retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);
            }
         }

         if(SUCCEEDED(retc))
         {
//          comp_data_pos_str = argv[2];
//          comp_data_pos_str >> comp_data_pos;
            sscanf(argv[3], "%d", &comp_data_pos);
            if(((comp_data_pos < 0) || (comp_data_pos > MAX_COMP_DATA_POS)) && SUCCEEDED(retc))
            {
               comp_data_pos = 0;
               retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);
            }
         }

#endif // #else // #ifdef Debug

//       if(SUCCEEDED(retc)) retc=GetIniFname(ini_fname);

         if(SUCCEEDED(retc)) retc=KpInit();
//       if(SUCCEEDED(retc)) retc=theApp.InitStApp(0 /* hInstance */, ini_fname, "" /* lpCmdLine */, KpStEditMode);


         if(SUCCEEDED(retc))
         {
            if(outp_mode == FdfOutputHead)
            {
               dat_str =
                  "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tServFl\tRezFileName\tClipBrdFl\tGlobJsFl\tNumOfRecs\tCompId\tCompName\tUserName\tWinVer\tWinSP\tOsPlatformID\tOsMajorVers\tOsMinorVers\tOsVers\tOsBuildNo\tFieldCnt\t"
                  +(MAX_COMP_DATA_POS - comp_data_pos); // +(20 - comp_data_pos);
               if(SUCCEEDED(retc))
               {
                  pnts = dat_str.ExtractValueA();
                  cout << pnts << endl;
               }
            }
            else
            {
               do
               {
//                if(SUCCEEDED(retc)) retc = theApp.GetKpstFdfData(&dat_str, &in_file, inp_mode);
                  dat_rec = NULL;
                  if(SUCCEEDED(retc)) retc = theApp.GetKpstFdfDataRec(&dat_rec, &in_file, inp_mode, True);

                  if(outp_mode == FdfOutputFdf)
                     retc = theApp.SaveKpstFdfDataRec(dat_rec, &cout, outp_mode, True);
                  else // if(outp_mode == FdfOutputFdf)
                  {
                     dat_rec_ptr = dat_rec;
                     while(dat_rec_ptr && SUCCEEDED(retc))
                     {
                        retc = dat_rec_ptr->GetCurTextPar(par_nam, par_val);

                        if(SUCCEEDED(retc)) cout << par_nam << ':' << endl;

                        if(SUCCEEDED(retc)) dat_str = par_val;

                        if((outp_mode == FdfOutputAscii) && SUCCEEDED(retc))
                        {
                           for(jj=0; jj<KPSTAP_NUM_OF_ADD_COMP_DATA; jj++) add_comp_data[jj][0] = Nul;

                           len = dat_str.length();

                           pnts = dat_str.ExtractValueA();
// ieskom add comp data pradzios
                           start_pos = (const unsigned char *)pnts;
                           for(ii = 0; ii<comp_data_pos; ii++)
                           {
                              pntd = strchr(start_pos, '\t');
                              if(pntd) start_pos = pntd + 1;
                              else start_pos = (const unsigned char *)pnts + len;
                           }
                           start_len = start_pos - (const unsigned char *)pnts;
                           pntsu = start_pos;

// perkeliam add comp data i add_comp_data[][]
                           jj = 0;
                           pntd = add_comp_data[jj];
                           for(ii = 0; (ii < len - start_len) && SUCCEEDED(retc); ii++)
                           {
                              if(*pntsu == '\t')
                              {
                                 jj++;
                                 pntd = add_comp_data[jj];
                              }
                              else
                              {
                                 if((pntd - add_comp_data[jj])<KP_MAX_FILE_LIN_LEN)
                                 {
                                    *pntd++ = (*pntsu);
                                    *pntd = Nul;
                                 }
                                 else
                                    retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L, NULL);
                              }
                              pntsu++;
                           }

                           for(jj = 0; (jj < KPSTAP_NUM_OF_ADD_COMP_DATA) && SUCCEEDED(retc); jj++) switch(jj)
                           {
                           case 0: break;                                        // ServFl // ar duom. i serveri?
                           case 1: retc=EncodeText(add_comp_data[jj]); break;    // RezFileName // duom. failo vardas
                           case 2: break;                                        // ClipBrdFl // ar buvo duomenu clipboard'e?
                           case 3: break;                                        // GlobJsFl // ar buvo duomenu pdf parametruose?
                           case 4: break;                                        // NumOfRecs // duom. eiluciu skaicius
                           case 5: break;                                        // CompId // kompo ID
                           case 6: retc=EncodeText(add_comp_data[jj]); break;    // CompName // kompo vardas
                           case 7: retc=EncodeText(add_comp_data[jj]); break;    // UserName // user name
                           case 8:                                               // WinVer // windows version
                              win_ver = 0;
                              if(sscanf((const char *)add_comp_data[jj], "%d", &win_ver)<1) win_ver = 0;
                              if(((win_ver<0) || (win_ver>=NumOfWinVersions0)) && SUCCEEDED(retc))
                                 retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, win_ver, NULL);
                              if(SUCCEEDED(retc))
                              {
                                 strncpy(add_comp_data[jj], lpszaWindowsVerNames[win_ver], KP_MAX_FILE_LIN_LEN);
                                 add_comp_data[jj][KP_MAX_FILE_LIN_LEN] = Nul;
                              }
                              break;
                           case 9: break;                                        // WinSP // service pack
                           case 10: break;                                       // OsPlatformID // os platform OSVERSIONINFOEX
                           case 11: break;                                       // OsMajorVers // os major version OSVERSIONINFOEX
                           case 12: break;                                       // OsMinorVers // os minor version OSVERSIONINFOEX
                           case 13: retc=EncodeText(add_comp_data[jj]); break;   // OsVers // os version OSVERSIONINFOEX
                           case 14: break;                                       // OsBuildNo // os build no OSVERSIONINFOEX
                           case 15: break;                                       // FieldCnt // duom. lauku skaicius (atsirado nuo 2005.04.14) - nafig reikia?
                           }

                           if(SUCCEEDED(retc))
                           {
                              dat_str = dat_str.substr(0, start_len);
                              for(jj = 0; (jj < KPSTAP_NUM_OF_ADD_COMP_DATA) && SUCCEEDED(retc); jj++)
                              {
                                 if(jj > 0) dat_str += "\t";
                                 dat_str += (const char *)add_comp_data[jj];
                              }
                           }

                        } // if((outp_mode == FdfOutputAscii) && SUCCEEDED(retc))

                        pntsu = dat_str.ExtractUnsignedValueA();
                        if(SUCCEEDED(retc)) cout << pntsu /* dat_str */ << endl;

                        if(SUCCEEDED(retc)) retc = dat_rec_ptr->GetNextBrother((KpTreeEntry **)&dat_rec_ptr);

                     } // while(dat_rec_ptr && SUCCEEDED(retc))

                  } // else // if(outp_mode == FdfOutputFdf)

               } while((!in_file.eof()) && (inp_mode != FdfInputFdf) && SUCCEEDED(retc));

            } // else // if(outp_mode == FdfOutputHead)

         } // if(SUCCEEDED(retc))


      /* if(SUCCEEDED(retc)) retc = */ KpFinit();
//    /* if(SUCCEEDED(retc)) */ retc0=theApp.CloseStApp(retc, KP_My_Documents);  if(SUCCEEDED(retc)) retc=retc0;

#ifndef Debug
      }
      else // if(argc==4)
      {
         cout << endl;
         cout << "DecFdf85.exe - failo su vartotojo informacija iÕkodavimas" << endl;
         cout << endl;
         cout << "decfdf85.exe 0 1 2 < infile.fdf > outfile.txt" << endl;
         cout << "             ^ ^ ^" << endl;
         cout << "             | | +---- lauko, nuo kurio prasideda papildomi vartotojo duomenys," << endl;
         cout << "             | |       numeris, t.y., pagrindiniÖ duomenÖ laukÖ skaiÑius" << endl;
         cout << "             | |       (data.dat - 2, bebras2008 - 12)" << endl;
         cout << "             | +------ iÕvedimo formatas:" << endl;
         cout << "             |            " << FdfOutputRawAscii << " - teksto eilutÓ, laukai atskirti tabuliacijomis," << endl;
         cout << "             |                kodavimas neatliekamas" << endl;
         cout << "             |            " << FdfOutputAscii << " - tabuliacijomis atskirtÖ laukÖ teksto eilutÓ," << endl;
         cout << "             |                koduoti laukai perkoduojami" << endl;
         cout << "             |            " << FdfOutputHead << " - tabuliacijomis atskirtÖ laukÖ pavadinimÖ kepurÓ" << endl;
         cout << "             |            " << FdfOutputFdf << " - .fdf keliÖ ÔraÕÖ Ascii85 uØkoduotas failas" << endl;
         cout << "             +-------- Ôvedimo formatas:" << endl;
         cout << "                          " << FdfInputFdf << " - .fdf failas, gali b×ti keli duomenÖ ÔraÕai arba" << endl;
         cout << "                              Java scriptas, paprastai koduota Ascii85" << endl;
         cout << "                          " << FdfInputRawA85 << " - viena tekstinÓ eilutÓ, uØkoduota Ascii85" << endl;
         cout << "                          " << FdfInputRawAscii << " - tabuliacijomis atskirtÖ laukÖ teksto eilutÓ" << endl;
         cout << endl;
      }
#endif

   } // if(SUCCEEDED(retc))


#ifdef Debug
system("pause");
#endif

return(RET_CODE_MAIN(retc));
}

