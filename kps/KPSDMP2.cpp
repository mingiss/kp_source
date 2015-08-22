/*---------------------------------------------*/
/* FILENAME:         kpsdmp2.c                 */
/* DESCRIPTION:      File dump                 */
/* DESTINATION:      *                         */
/* SYSTEM_INTERFACE: Stdc                      */
/* USER_INTERFACE:   In-line                   */
/*---------------------------------------------*/


/*---------------------------------------------*/
#include "envir.h"

#include <string>
#include <stdio.h>
#include <fstream>
#include <windows.h>
#include <richedit.h>
#include <Richole.h>

#include "kpstdlib.h"
#include "kperrno.h"
#include "kptree.h"
#include "kptt.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kptt.h"
#include "kpctype.h"
#include "kpcolors.h"
#include "kpstdio.h"
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
#include "xmlp.h"
#include "kpstap.h"


// ================================================== KpErrorProc_tag local functions
const unsigned char lpszProdName[] = "kpsdmp2"; 
int iProdVerGlob = 0;
KpErrorProcClass KpErrorProc(TRUE, 71);
bool bServiceFl = False;   
int iUpdNumGlob = -1;

int KpHp11NumOfExtFun=0;
KpHp11ExtFun KpHp11ExtFunTab[1]=
// HRESULT (*KpHp11ExtFunTab)(void *pPars)[]=
{
   NULL
};


/*---------------------------------------------*/
#define YNSize 1
#define RadSize 2


/*---------------------------------------------*/
unsigned char fname[Fnsiz + 1] = ""; /* File to dump */
/* unsigned char outfnam[Fnsiz + 1]; */   /* Output file name *.dmp */

int dmprct = 2;                      /* Radix 0 - 8, 1 - 10, 2 - 16 */
unsigned char dmprctt[RadSize + 1] = "";

int dmptxf = True;                   /* Text column flag */
unsigned char dmptxft[YNSize + 1] = "";

int dmpbtf = False;                  /* Bytes flag */
unsigned char dmpbtft[YNSize + 1] = "";

int dmpctf = 0; // False;            /* C source style flag */
unsigned char dmpctft[YNSize + 1] = "";

char *dmpprf[] =     {"0",       "",       "0x"};
char *dmppar[] =     {"%03o",    "%03d",   "%02x"};
char *dmpfar[2][3] = {"   ",     "   ",    "  ",
                      "    ",    "   ",    "    "};
char *dmppaw[] =     {"%06o",    "%05u",   "%04x"};
char *dmpfaw[2][3] = {"      ",  "     ",  "    ",
                      "       ", "     ",  "      "};
char *dmplar[] =     {"%08lo/",  "%06ld/", "%06lx/"};

long start_byte;
unsigned char start_byte_txt[MAX_LONG_DIGITS + 1] = "";

long num_of_bytes;
unsigned char num_of_bytes_txt[MAX_LONG_DIGITS + 1] = "";


/*---------------------------------------------*/
#define ofl stdout


// -----------------------------------------
HRESULT TestCompilerSettingsLocal(void)
{
#include "kpstcs.cpp" 
}
          

/*---------------------------------------------*/
HRESULT dmpinit(int argc, char **argv)
{
int ii;

  KpInit();
   
  fname[0] = Nul;
  dmprctt[0] = Nul;
  dmptxft[0] = Nul;
  dmpbtft[0] = Nul;

  strcpy(start_byte_txt, "0");
  strcpy(num_of_bytes_txt, "0");

  if(argc > 1) strncpy((char *)fname, argv[1], Fnsiz);
  if(argc > 2) strncpy((char *)dmprctt, argv[2], RadSize);
  if(argc > 3) strncpy((char *)dmptxft, argv[3], YNSize);
  if(argc > 4) strncpy((char *)dmpbtft, argv[4], YNSize);
  if(argc > 5) strncpy((char *)dmpctft, argv[5], YNSize);
  if(argc > 6) strncpy((char *)start_byte_txt, argv[6], MAX_LONG_DIGITS);
  if(argc > 7) strncpy((char *)num_of_bytes_txt, argv[7], MAX_LONG_DIGITS);

  fname[Fnsiz] = Nul;
  dmprctt[RadSize] = Nul;
  dmptxft[YNSize] = Nul;
  dmpbtft[YNSize] = Nul;
  dmpctft[YNSize] = Nul;
  start_byte_txt[MAX_LONG_DIGITS] = Nul;
  num_of_bytes_txt[MAX_LONG_DIGITS] = Nul;

// msbcpy(fname, fname);
   CutInitTrailSpcs(fname);

  msbcpy(dmprctt, dmprctt);
  msbcpy(dmptxft, dmptxft);
  msbcpy(dmpbtft, dmpbtft);
  msbcpy(dmpctft, dmpctft);
  msbcpy(start_byte_txt, start_byte_txt);
  msbcpy(num_of_bytes_txt, num_of_bytes_txt);

  if(strlen((char *)fname)==0)
  {
     printf("File name:");
     gets((char *)fname);
  }
  if(strlen((char *)dmprctt)==0)
  {
     printf("Radix (8/10/16):");
     gets((char *)dmprctt);
  }
  if(strlen((char *)dmptxft)==0)
  {
     printf("Text column (Y/N):");
     gets((char *)dmptxft);
  }
  if(strlen((char *)dmpbtft)==0)
  {
     printf("Bytes/Words (B/W):");
     gets((char *)dmpbtft);
  }
  if(strlen((char *)dmpctft)==0)
  {
     printf("Traditional/C source style/Embedded (T/C/E):");
     gets((char *)dmpctft);
  }

// msbcpy(fname, fname);
   CutInitTrailSpcs(fname);

  msbcpy(dmprctt, dmprctt);
  msbcpy(dmptxft, dmptxft);
  msbcpy(dmpbtft, dmpbtft);
  msbcpy(dmpctft, dmpctft);

  sscanf((char *)dmprctt, "%d", &ii);
  switch(ii)
  {
    case 8:  dmprct = 0; break;
    case 10: dmprct = 1; break;
    case 16:
    default: dmprct = 2; break;
  }
  strlwr(dmptxft); dmptxf = ('y' == dmptxft[0]);
  strlwr(dmpbtft); dmpbtf = ('b' == dmpbtft[0]);
// strlwr(dmpctft); if('y' == dmpctft[0]) dmpctf = 1; // True;
  strlwr(dmpctft); if('c' == dmpctft[0]) dmpctf = 1; // True;

  sscanf((const char *)start_byte_txt, "%ld", &start_byte);
  sscanf((const char *)num_of_bytes_txt, "%ld", &num_of_bytes);

  KpFinit();

return(S_OK);
}


/*---------------------------------------------*/
HRESULT dmpexe(void)
{
bool brk;
int filbuf[16];
FILE *ifl /*, *ofl */;
int kk, ll, mm;
unsigned int ii;
long cnt;
int fefl;      /* Input file end flag */
HRESULT retc=S_OK;
int cnt_line = 0;

  fefl=False; brk=False;

/*
  msbcpy(outfnam, fname);
  pntd = (unsigned char *)strchr((char *)outfnam,'.');
  if(NULL == (void *)pntd) pntd = outfnam + strlen((char *)outfnam);
  strcpy((char *)pntd, ".dmp");

  strcpy(buf, (char *)fname); strcat(buf," --> "); strcat(buf, (char *)outfnam); strcat(buf,"\n");
  printf(buf);

  ofl = fopen((char *)outfnam, "wt");
  if(NULL == ofl)
     retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, NULL, TRUE, __FILE__, __LINE__, 0L);
  brk |= FAILED(retc);
*/

  if(!brk)
  {
    ifl = fopen((char *)fname,"rb");
    if(NULL == ifl) 
      retc = KpErrorProc.OutputErrorMessage(KP_E_FILE_NOT_FOUND, null /* fname */, TRUE, __FILE__, __LINE__, 0L);
    brk |= FAILED(retc);
  }

  if(!brk) if(start_byte) fseek(ifl, start_byte, SEEK_SET);  

  cnt = 0;

  while(!brk)
  {
    for(kk = 0; (kk < 16) && (!brk); kk++)
    {
      if(dmpctf) fprintf(ofl, "/* ");
      fprintf(ofl, dmplar[dmprct], cnt);
      if(dmpctf) fprintf(ofl, " */");
      if(ferror(ofl) || feof(ofl)) 
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, TRUE, __FILE__, __LINE__, 0L);
      brk |= FAILED(retc);

      cnt_line = 0;
      
      for(ll = 0; (ll <
          16 - ((dmpbtf || (dmprct == 0)) && (dmprct != 2)) * 8
          ) && (!brk); ll++)
      {
        if(num_of_bytes) if(cnt >= num_of_bytes) brk = True;
        if(!brk)
        {
          cnt_line++;
          
          filbuf[ll] = fgetc(ifl); cnt++;
          fefl = feof(ifl);
          if(ferror(ifl)) 
            retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, TRUE, __FILE__, __LINE__, 0L);
          brk |= (fefl || FAILED(retc));
        }
      }
      if(fefl) ll--;

      brk = False;
      for(mm = 0; (mm <
          8 - ((!dmpbtf) && (dmprct == 0)) * 4 + (dmpbtf && (dmprct == 2)) * 8
          ) && (mm < cnt_line) && (!brk); mm++)
      {
         fprintf(ofl, " ");
         if(dmpbtf)
         {
            if(mm < ll)
            {
               if(dmpctf) fprintf(ofl, dmpprf[dmprct]);
               fprintf(ofl, dmppar[dmprct], filbuf[mm]);
               if(dmpctf) fprintf(ofl, ",");
            }
            else fprintf(ofl, dmpfar[dmpctf][dmprct]);
         }
         else
         {
            if(mm * 2 < ll)
            {
               if(dmpctf) fprintf(ofl, dmpprf[dmprct]);

               ii = filbuf[mm * 2];
               if(mm * 2 + 1 < ll) ii |= filbuf[mm * 2 + 1] << 8;
               fprintf(ofl, dmppaw[dmprct], ii);

               if(dmpctf) fprintf(ofl, ",");
            }
            else fprintf(ofl, dmpfaw[dmpctf][dmprct]);
         }

         if(ferror(ofl))
            retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, TRUE, __FILE__, __LINE__, 0L);
         if(feof(ofl)) 
            retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, null, TRUE, __FILE__, __LINE__, 0L);
         brk |= FAILED(retc);
      }
      brk |= (fefl || FAILED(retc));
      if(num_of_bytes) if(cnt >= num_of_bytes) brk = True;

      if(dmptxf && (!brk))
      {
        fprintf(ofl, "   ");
        if(ferror(ofl))
            retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, TRUE, __FILE__, __LINE__, 0L);
        if(feof(ofl)) 
            retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, null, TRUE, __FILE__, __LINE__, 0L);
        brk |= FAILED(retc);

        for(mm = 0; (mm < ll) && (!brk); mm++)
        {
          if(filbuf[mm] < Spc) fputc('.', ofl);
          else                 fputc(filbuf[mm], ofl);
          if(ferror(ofl)) 
            retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, TRUE, __FILE__, __LINE__, 0L);
          if(feof(ofl))
            retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, null, TRUE, __FILE__, __LINE__, 0L);
          brk |= FAILED(retc);
        }
      }

      fprintf(ofl, "\n");
      if(ferror(ofl)) 
            retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, TRUE, __FILE__, __LINE__, 0L);
      if(feof(ofl)) 
            retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, null, TRUE, __FILE__, __LINE__, 0L);
      brk |= FAILED(retc);
    }

    fprintf(ofl, "\n");
    if(ferror(ofl)) 
            retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, TRUE, __FILE__, __LINE__, 0L);
    if(feof(ofl)) 
            retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, null, TRUE, __FILE__, __LINE__, 0L);
    brk |= FAILED(retc);
  }

  fclose(ifl);
  if(fclose(ofl) && SUCCEEDED(retc)) 
            retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, TRUE, __FILE__, __LINE__, 0L);
  brk |= FAILED(retc);

return(retc);
}


/*---------------------------------------------*/
HRESULT dmpemb(void)
{
bool brk;
int fefl;      /* Input file end flag */
HRESULT retc=S_OK;
FILE *ifl;
int in_ch;

  fefl=False; brk=False;

/*
  msbcpy(outfnam, fname);
  pntd = (unsigned char *)strchr((char *)outfnam,'.');
  if(NULL == (void *)pntd) pntd = outfnam + strlen((char *)outfnam);
  strcpy((char *)pntd, ".dmp");

  strcpy(buf, (char *)fname); strcat(buf," --> "); strcat(buf, (char *)outfnam); strcat(buf,"\n");
  printf(buf);

  ofl = fopen((char *)outfnam, "wt");
  if(NULL == ofl)
     retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, NULL, TRUE, __FILE__, __LINE__, 0L);
  brk |= FAILED(retc);
*/

   if(!brk)
   {
      ifl = fopen((char *)fname,"rb");
      if(NULL == ifl) 
         retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_NOT_FOUND, null, TRUE, __FILE__, __LINE__, 0L);
      brk |= FAILED(retc);
   }

   do
   {
      if(dmpbtf)
      {
// bytes
         in_ch = fgetc(ifl);
         fefl = feof(ifl);
         if(ferror(ifl)) 
            retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, TRUE, __FILE__, __LINE__, 0L);
         brk |= (fefl || FAILED(retc));

         if(!brk) fprintf(ofl, "%c", in_ch & 0xFF);

         if((!brk) && ((in_ch<Spc) || (in_ch>=0x7F)) && (in_ch!=Cr) && (in_ch!=Lf)) switch(dmprct)
         {
         case 0:
            fprintf(ofl, "<%03o>", in_ch & 0xFF);   // octal
            break;
         case 1:
            fprintf(ofl, "<%d>", in_ch & 0xFF);   // decimal
            break;
         case 2:
         default:
            fprintf(ofl, "<%02x>", in_ch & 0xFF); // hex
            break;
         }

         if(ferror(ofl))
            retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, TRUE, __FILE__, __LINE__, 0L);
         if(feof(ofl)) 
            retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, null, TRUE, __FILE__, __LINE__, 0L);
         brk |= FAILED(retc);
      }
      else
      {
// words
         in_ch = fgetc(ifl);
         in_ch = (in_ch & 0xFF) | ((fgetc(ifl)<<8) & 0xFF00);
         fefl = feof(ifl);
         if(ferror(ifl)) 
            retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, TRUE, __FILE__, __LINE__, 0L);
         brk |= (fefl || FAILED(retc));

         if(!brk) fprintf(ofl, "%c", in_ch & 0xFF);

         if((!brk) && ((in_ch<Spc) || (in_ch>=0x7F)) && (in_ch!=Cr) && (in_ch!=Lf)) switch(dmprct)
         {
         case 0:
            fprintf(ofl, "<%05o>", in_ch & 0xFFFF);   // octal
            break;
         case 1:
            fprintf(ofl, "<%d>", in_ch & 0xFFFF);   // decimal
            break;
         case 2:
         default:
            fprintf(ofl, "<%04x>", in_ch & 0xFFFF);   // hex
            break;
         }

         if(ferror(ofl))
            retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, TRUE, __FILE__, __LINE__, 0L);
         if(feof(ofl)) 
            retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, null, TRUE, __FILE__, __LINE__, 0L);
         brk |= FAILED(retc);
      }

   } while(!brk);

   fclose(ifl);
   if(fclose(ofl) && SUCCEEDED(retc)) 
      retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, TRUE, __FILE__, __LINE__, 0L);
   brk |= FAILED(retc);

return(retc);
}


/*---------------------------------------------*/
int main(int argc, char **argv)
{
HRESULT retc;

  retc=dmpinit(argc,argv);

  fprintf(stderr,"\n");
  if(dmpctft[0]=='c') fprintf(stderr, "// ");
  fprintf(stderr,"    Dumping file %s\n\n",argv[1]);
  
  if(SUCCEEDED(retc))
  {
     switch(dmpctft[0])
     {
     case 't':
     case 'c':
        retc=dmpexe();
        break;
     case 'e':
        retc=dmpemb();
        break;
     }
  }

return(RET_CODE_WIN(retc));
}

