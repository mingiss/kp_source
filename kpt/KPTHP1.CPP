/*---------------------*/
/* hyphenation         */
/* kpthp1.cpp          */
/*---------------------*/

/*---------------------*/
#include "envir.h"

#include <string.h>
#include <string>
#include <stdio.h>
#include <fstream>
#include <windows.h>
#include <time.h>
#include <richedit.h>
#include <Richole.h>

#if (Compiler != Watcom) || (__WATCOMC__ > 1201)
using namespace std;
#endif

/* #include "..\kpx\kpx.h" */
/* #include "kpx0.h" */
#include "kpstdlib.h"
#include "kptt.h"
#include "kperrno.h"
#include "kptree.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpcolors.h"
#include "kpstdio.h"
#include "res_com.h"
#include "kpwindow.h"
#include "kperr.h"
#include "kpthp.h"

/*---------------------*/
unsigned char wordbuf[FileLinLen + 1]; // 256
unsigned char *wordpnt = NULL;
int hypfl = Hyp1; // Hyp0;

unsigned char hpbalsar[] = {"aàeæëiáyouøû"}; // 43: "aÝeñóiõyouùû ¥¨®ãëíîï", 71: "aàeæëiáyouøû ¥¨®ã íîï"
/* char hpputstr[]={"<->"}; */
unsigned char *hnxarr[] =
{ 
(unsigned char *)"ch",
(unsigned char *)"dz",
(unsigned char *)"dþ"
};
unsigned char wordsav[FileLinLen + 1]; // 256
unsigned char fwbuf[FileLinLen + 1]; // 256     /* zodzio pradzia is zodynu */
long skarr[Dicnum][0x100];  /* pozicijos failuose */
File dflar[Dicnum];
char dicname[Dicnum][MAXFILE + MAXEXT + 1] = {"kpttdf.dic", "kpttdp.dic"};


/*---------------------*/
int hnstrcmp(unsigned char *str1, unsigned char *str2)  /* ar str1 ieina i str2? */
{
unsigned char *pnt1, *pnt2;
bool efl;
int retv;

   retv=0;
   pnt1=str1; pnt2=str2;

   do
   {
      efl = ((*pnt1 == Nul) || (*pnt2 == Nul));
      if((*pnt2 == Nul) && (*pnt1 != Nul)) retv=1;
      if(!efl)
      {
         if(*pnt1<*pnt2) retv=(-1);
         if(*pnt1>*pnt2) retv=1;
      }
      efl|=retv;
      pnt1++; pnt2++;
   } while(!efl);

return(retv);
}


/*---------------------*/
bool hdicttest(int dcn)
{
bool retf;
bool efl;
bool fndfl;
unsigned char wbuf[FileLinLen + 1]; // 256
unsigned char dbuf[FileLinLen + 1]; // 256
unsigned char tbuf[FileLinLen + 1]; // 256
const unsigned char *pnts;
unsigned char *pntd;
unsigned char *pntw;

   retf=False;

   if(
      (dflar[dcn].fp != NULL)&&
      (skarr[dcn][ctolower(wordbuf[0])&0xFF] >= 0l)
     )
   {
/*  do{ */
      
      fndfl = False;
      msbcpy(wbuf, wordbuf); 
      cstrlwr(wbuf); 
      strcat(wbuf,".");
      
      if(dflar[dcn].cfseek(skarr[dcn][wbuf[0]&0xFF]))
      {
         cferr(8, __FILE__, __LINE__);
         dflar[dcn].cvfpurge();
      }
      
      efl = (dflar[dcn].fp == NULL);
      
      while(!efl)
      {
         dflar[dcn].cfgetss(dbuf,255);
         efl = (efl || feof(dflar[dcn].fp));
         if(ferror(dflar[dcn].fp))
         {
            efl=True;
            cferr(8, __FILE__, __LINE__);
            dflar[dcn].cvfpurge();
         }
        
         if(!efl) efl|=(dbuf[0]!=wbuf[0]);
         if(!efl)
         {
            pnts=dbuf; pntd=tbuf;
            while(*pnts)
            {
               if((*pnts!='-')&&(*pnts!='/')) *pntd++=*pnts;
               pnts++;
            }
            *pntd = Nul;
            fndfl |= (hnstrcmp(tbuf,wbuf) == 0);
            retf |= fndfl;
            efl |= fndfl;
         }
      }
      
      if(fndfl)
      {
         pntw = wordbuf;
         pnts = dbuf;
         pntd = fwbuf; 
         while(*pntd) pntd++;
         while((*pnts) && (*pnts != '/'))
         {
            if(*pnts == '-')
            {
               if((pntd > fwbuf + 1) || (hypfl == Hyp2)) *pntd ++= Hyp;
               pnts++;
            }
            else
            {
               if(*pnts != '.') *pntd++ = *pntw++;
               pnts++;
            }
         }
         *pntd = Nul;
         strcpy(wordbuf, pntw);
      }
/*    } while(fndfl); */
   }

return(retf);
}


int dicttest(void)
{
bool retf, fndfl;

   retf = False;
   fwbuf[0] = Nul;
   fndfl = hdicttest(1); retf |= fndfl;
   if(!fndfl) do
   {
      fndfl = hdicttest(0); retf |= fndfl;
      if(fndfl) fndfl = !hdicttest(1);
   } while(fndfl);

return(retf);
}


/*---------------------*/
int isbals(int ch)
{
return((ch!=Nul) && (strchr(hpbalsar, ctolower(ch)) != NULL));
}


/*---------------------
char *hputhyp(char *pnt){

  strcpy(pnt,hpputstr);
  return(pnt+strlen(hpputstr));

  *pnt=Hyp;
  return(pnt+1);
  }
*/


/*---------------------*/
int balsfnd(unsigned char *pnt)
{
unsigned char *pntc;

   pntc = pnt;
   while(*pntc && (!isbals(*pntc))) pntc++;

return(*pntc != Nul);
}


/*---------------------*/
unsigned char *hnext(unsigned char *pnt)
{
unsigned char buf[hnxmax+1];
unsigned char *pntc;
int efl,ii;

   msncpy(buf, pnt, hnxmax);
   cstrlwr(buf);
   efl = False;
   for(ii=0; (ii<sizeof(hnxarr)/sizeof(char *)) && (!efl); ii++)
      efl=(hnstrcmp(hnxarr[ii], buf) == 0);
   pntc=pnt + (efl?strlen(hnxarr[ii-1]):1);

return(pntc);
}


/*---------------------*/
int pdgetc(int dcn, bool *efl, long *ll)
{
int ii;

   *efl |= (dflar[dcn].fp == NULL);
   if(!(*efl))
   {
      ii = dflar[dcn].cfgetc();
      *efl = (*efl || feof(dflar[dcn].fp));
      if(ferror(dflar[dcn].fp))
      {
         *efl = True;
         cferr(8, __FILE__, __LINE__);
         dflar[dcn].cvfpurge();
      }
      (*ll)++;
   }
   else ii = EOF;

return(ii);
}


bool dcinit(int dcn)
{
unsigned char runpath[MAXPATH + 1];
unsigned char buf[MAXPATH + 1]; // 256
bool err;
bool efl;
int ii;
long ll;

   err = False;
/* retc = */ GetAppPath(runpath, True);
   strcpy(buf, runpath); strcat(buf, dicname[dcn]);
   err = (dflar[dcn].cvfopen(buf, (const unsigned char *)"rb", NULL) == NULL);
   for(ii=0; ii < 0x100; ii++) skarr[dcn][ii] = (-1l);
   efl = False;
   ll = (-1l);
   while(!efl)
   {
      do ii = pdgetc(dcn, &efl, &ll); while((!cisalpha(ii)) && (!efl));
      if(!efl) if(skarr[dcn][ii]<0) skarr[dcn][ii]=ll;
      do ii=pdgetc(dcn,&efl,&ll); while((ii!=Lf)&&(!efl));
   }

return(err);
}


void hypinit(void)
{
int err;

   wordpnt = NULL;
   
   if(hypfl)
   {
      err = dcinit(Pdict);
      err |= dcinit(Fdict);
//    if(err) cferr(7, __FILE__, __LINE__);
   }
}


/*---------------------*/
void hypfinit(void)
{
   wordpnt = NULL;
   if(hypfl)
   {
      dflar[Fdict].cvfpurge();
      dflar[Pdict].cvfpurge();
   }
}


/*---------------------*/
void hyprun(void)
{
unsigned char *wpb, *wps, *pntc;
int lev, ii;

   dicttest();
   strcpy(wordsav, wordbuf);
   wpb = wordbuf; wps = wordsav;
   if(isbals(*wps)) lev = Bals;
   else lev = Prb1;
   while(*wps)
   {
      switch(lev)
      {
      case Prb1:
         *wpb++ = *wps++;
         if(isbals(*wps)) lev = Bals;
         break;
      case Bals:
         *wpb++=*wps++;
         if((!isbals(*wps)) && (*wps))
         {
            lev = Prb2;
            ii = *hnext(wps);
            if(isbals(ii))
            {
               if((wps > wordsav + 1) || (hypfl == Hyp2) || (fwbuf[0]))
               {
               /* wpb=hputhyp(wpb); */
                  *wpb++ = Hyp;
               }
               lev=Prb1;
            }
         }
         break;
      case Prb2:
         lev = Prb3;
         pntc = hnext(wps);
         while(wps<pntc) *wpb++=*wps++;
         break;
      case Prb3:
         pntc = hnext(wps);
         ii = *pntc;
         if(isbals(ii) || ((hypfl == Hyp2) && balsfnd(wps)))
         {
         /* wpb=hputhyp(wpb); */
            *wpb++ = Hyp;
         }
         if(isbals(ii)) lev = Prb1;
         else while(wps < pntc) *wpb++ = *wps++;
      }
   }
   
   *wpb = Nul;
   strcat(fwbuf, wordbuf);
   strcpy(wordbuf, fwbuf);
   pntc = wordbuf;
   while(*pntc) pntc++;
   if(pntc > wordbuf)
   {
      pntc--;
     if(*pntc == Hyp) *pntc = Nul;
      else pntc++;
      if(hypfl == Hyp1) if(pntc > wordbuf + 1)
      {
         pntc--;
         if(*(pntc - 1) == Hyp)
         {
            *(pntc - 1) = (*pntc);
            *pntc = Nul;
         }
      }
   }
}
