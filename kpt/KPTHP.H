/*---------------------*/
/* hyphenation         */
/* kpthp.h             */
/*---------------------*/

/*---------------------*/
/* #include <dir.h> */

/*---------------------*/
#define hnxmax 2

/*---------------------*/
enum
{
   Hyp0,
   Hyp1,
   Hyp2,
   
   Hypsiz
};

enum
{
   Prb1,     /* priebalsiai pradzioje skiemens */
   Bals,     /* balsiai */
   Prb2,     /* pirmas priebalsis gale skiemens */
   Prb3,     /* priebalsiai gale skiemens */

   Prbbsiz
};

enum
{
   Fdict,
   Pdict,
   
   Dicnum
};


/*---------------------*/
extern unsigned char wordbuf[FileLinLen + 1];
extern unsigned char *wordpnt;
extern int hypfl;

/*---------------------*/
extern void hypinit(void);
extern void hypfinit(void);
extern void hyprun(void);
