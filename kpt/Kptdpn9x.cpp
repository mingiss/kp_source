// Dump cp_XXXX.nls code page file of Win9x

#include "envdef.h"
#include "envir.h"
#include "envsupp.h"

#include <stdio.h>

#include "kpstdlib.h"
#include "kptt.h"
#include "kperr.h"

#include "tvxml.h"

// ================================================== KpErrorProc_tag local functions
KpErrorProc_tag KpErrorProc(TRUE, 71);

// --------------------------------------------------
HRESULT KpErrorProc_tag::FormatErrorMessage
(
	const HRESULT lhRetc,
	unsigned char *lpszMsg
)
{
return(FormatErrorMessageMain(lhRetc, lpszMsg));
}


short *uni2cp_table;


// --------------------------------------------------
int GetCpCode(int iUniCode)
{
int ii;

   ii=uni2cp_table[(iUniCode&0xFF00)>>8];
   ii=uni2cp_table[ii+((iUniCode&0xF0)>>4)];
   ii=uni2cp_table[ii+(iUniCode&0xF)];

return(ii);
}


// --------------------------------------------------
main()
{
FILE *in_file;
int in_word;

// field positions from beginning of the file (in 2-byte words)
int cp2uni_layout;
int cp2unidos_layout;
int cp2uniadd_layout;
int uni2cp_layout;
int toupper_layout;
int tolower_layout;
int noacc_layout;
int sort_layout;
int unkn_layout;
int char_type1_layout;
int char_type2_layout;
int char_type3_layout;
int except_layout;

// field sizes in bytes
int cp2uni_size;
int cp2unidos_size;
int cp2uniadd_size;
int uni2cp_size;
int toupper_size;
int tolower_size;
int noacc_size;
int sort_size;
int unkn_size;
int char_type1_size;
int char_type2_size;
int char_type3_size;
int except_size;

int ii;
int jj;
HRESULT retc=S_OK;
int cur_pos=0;
int cp_code;
int kpt_char;
const unsigned char *ch_name;

   in_file=fopen("cp_775.nls","rb");
   if(in_file!=NULL)
   {
      fread(&in_word, 4, 1, in_file);    // coding byte count
      cur_pos+=4;

      fread(&in_word, 4, 1, in_file);    // signature 0x0026
      cur_pos+=4;

      fread(&cp2uni_layout, 4, 1, in_file);    // codetable to unicode layout
      if(cp2uni_layout==0) cp2uni_size=0;
      else cp2uni_size=KPT_Ctbsiz*2;
      cur_pos+=4;

      fread(&cp2unidos_layout, 4, 1, in_file);    // codetable to unicode for DOS layout
      if(cp2unidos_layout==0) cp2unidos_size=0;
      else cp2unidos_size=KPT_Ctbsiz*2;
      cur_pos+=4;

      fread(&cp2uniadd_layout, 4, 1, in_file);    // additional codetable for 2-byte coding layout
      if(cp2uniadd_layout==0) cp2uniadd_size=0;
      else cp2uniadd_size=KPT_Ctbsiz*2;
      cur_pos+=4;

      fread(&uni2cp_layout, 4, 1, in_file); // unicode to codetable layout
      cur_pos+=4;

      fread(&toupper_layout, 4, 1, in_file);    // to upper table layout
      if(uni2cp_layout==0) uni2cp_size=0;
      else
      {
         if(toupper_layout==0) printf("Unable to calculate Uni2cp table size\n");
         else uni2cp_size=(toupper_layout-uni2cp_layout)*2;
      }
      if(toupper_layout==0) toupper_size=0;
      else toupper_size=KPT_Ctbsiz;
      cur_pos+=4;

      fread(&tolower_layout, 4, 1, in_file);    // to lower table layout
      if(tolower_layout==0) tolower_size=0;
      else tolower_size=KPT_Ctbsiz;
      cur_pos+=4;

      for(ii=0; ii<8; ii++) fread(&in_word, 2, 1, in_file); // skip 0 x 8
      cur_pos+=8*2;

      fread(&noacc_layout, 4, 1, in_file);    // no accents table layout
      if(noacc_layout==0) noacc_size=0;
      else noacc_size=KPT_Ctbsiz;
      cur_pos+=4;

      fread(&sort_layout, 4, 1, in_file);    // sort table layout
      if(sort_layout==0) sort_size=0;
      else sort_size=KPT_Ctbsiz*4;
      cur_pos+=4;

      fread(&unkn_layout, 4, 1, in_file);    // unknown table layout
      cur_pos+=4;

      fread(&char_type1_layout, 4, 1, in_file);    // char types 1 layout
      if(unkn_layout==0) unkn_size=0;
      else
      {
         if(char_type1_layout==0) printf("Unable to calculate Uni2cp table size\n");
         else unkn_size=(char_type1_layout-unkn_layout)*2;
      }
      if(char_type1_layout==0) char_type1_size=0;
      else char_type1_size=KPT_Ctbsiz*2;
      cur_pos+=4;

      fread(&char_type2_layout, 4, 1, in_file);    // char types 2 layout
      if(char_type2_layout==0) char_type2_size=0;
      else char_type2_size=KPT_Ctbsiz*2;
      cur_pos+=4;

      fread(&char_type3_layout, 4, 1, in_file);    // char types 3 layout
      if(char_type3_layout==0) char_type3_size=0;
      else char_type3_size=KPT_Ctbsiz*2;
      cur_pos+=4;

      fread(&except_layout, 4, 1, in_file);    // exceptions layout
      cur_pos+=4;

      fread(&in_word, 2, 1, in_file);    // coding byte count
      cur_pos+=2;

      for(ii=0; ii<4; ii++) fread(&in_word, 2, 1, in_file);  // substitution characters '?' x 4
      cur_pos+=4*2;

      for(ii=0; ii<6; ii++) fread(&in_word, 2, 1, in_file);  // substitution characters 0 x 6
      cur_pos+=6*2;

// codetable to unicode tables
      for(ii=0; ii<cp2uni_size; ii++)
      {
         fread(&in_word, 1, 1, in_file);
         cur_pos++;
      }

      for(ii=0; ii<cp2unidos_size; ii++)
      {
         fread(&in_word, 1, 1, in_file);
         cur_pos++;
      }

      for(ii=0; ii<cp2uniadd_size; ii++)
      {
         fread(&in_word, 1, 1, in_file);
         cur_pos++;
      }

      uni2cp_table=new short[uni2cp_size/2+1];
      if(uni2cp_table!=NULL) fread(uni2cp_table, uni2cp_size, 1, in_file);
      else printf("Out of memory\n");
      cur_pos+=uni2cp_size;

// to upper, to lower, no accents tables

      for(ii=0; ii<toupper_size; ii++)
      {
         fread(&in_word, 1, 1, in_file);
         cur_pos++;
      }

      for(ii=0; ii<tolower_size; ii++)
      {
         fread(&in_word, 1, 1, in_file);
         cur_pos++;
      }

      for(ii=0; ii<noacc_size; ii++)
      {
         fread(&in_word, 1, 1, in_file);
         cur_pos++;
      }

// sort table
      for(ii=0; ii<sort_size; ii++)
      {
         fread(&in_word, 1, 1, in_file);
         cur_pos++;
      }

// unknown table
      for(ii=0; ii<unkn_size; ii++)
      {
         fread(&in_word, 1, 1, in_file);
         cur_pos++;
      }

// char type tables
      for(ii=0; ii<char_type1_size; ii++)
      {
         fread(&in_word, 1, 1, in_file);
         cur_pos++;
      }

      for(ii=0; ii<char_type2_size; ii++)
      {
         fread(&in_word, 1, 1, in_file);
         cur_pos++;
      }

      for(ii=0; ii<char_type3_size; ii++)
      {
         fread(&in_word, 1, 1, in_file);
         cur_pos++;
      }

      if(feof(in_file)) printf("Netiketa failo pabaiga\n");

      while((!feof(in_file)) && (!ferror(in_file)))
      {
         fread(&in_word, 1, 1, in_file);
         cur_pos++;
      }

      except_size=cur_pos-except_layout*2-1;

      if(ferror(in_file)) printf("File I/O error\n");


      printf("      start word   start byte   byte count\n\n");

      printf("cp2uni      %4x       %4x         %d\n", cp2uni_layout, cp2uni_layout*2, cp2uni_size);
      printf("cp2unidos   %4x       %4x         %d\n", cp2unidos_layout, cp2unidos_layout*2, cp2unidos_size);
      printf("cp2uniadd   %4x       %4x         %d\n", cp2uniadd_layout, cp2uniadd_layout*2, cp2uniadd_size);
      printf("uni2cp      %4x       %4x         %d\n", uni2cp_layout, uni2cp_layout*2, uni2cp_size);
      printf("toupper     %4x       %4x         %d\n", toupper_layout, toupper_layout*2, toupper_size);
      printf("tolower     %4x       %4x         %d\n", tolower_layout, tolower_layout*2, tolower_size);
      printf("noacc       %4x       %4x         %d\n", noacc_layout, noacc_layout*2, noacc_size);
      printf("sort        %4x       %4x         %d\n", sort_layout, sort_layout*2, sort_size);
      printf("unkn        %4x       %4x         %d\n", unkn_layout, unkn_layout*2, unkn_size);
      printf("char_type1  %4x       %4x         %d\n", char_type1_layout, char_type1_layout*2, char_type1_size);
      printf("char_type2  %4x       %4x         %d\n", char_type2_layout, char_type2_layout*2, char_type2_size);
      printf("char_type3  %4x       %4x         %d\n", char_type3_layout, char_type3_layout*2, char_type3_size);
      printf("except      %4x       %4x         %d\n", except_layout, except_layout*2, except_size);
      printf("\n");


      for(ii=0; ii<KPT_Utbsiz; ii++)
      {
         cp_code=GetCpCode(ii);
         if(cp_code!=C_Quest)
         {
            kpt_char=C_Unkn;
            for(jj=0; jj<C_Charsize1; jj++)
            {
               if(iaUniChars[jj]==(unsigned int)ii)
               {
                  kpt_char=jj;
                  break;
               }
            }
            if(kpt_char<0) ch_name=(const unsigned char *)"Unknown";
            else
            {
               ch_name=plpszaXmlSpecCharTags[kpt_char];
               if(ch_name==NULL) ch_name=(const unsigned char *)"No XML";
            }
            printf(" 0x%04x:  0x%02x %3d  %s\n", ii, cp_code, cp_code, ch_name);
         }
      }

      KP_DELETE(uni2cp_table);

   }
   else 
      retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, NULL, TRUE, __FILE__, __LINE__, 0L);


return(RET_CODE(retc));
}
