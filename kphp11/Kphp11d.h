/*----------------------------------------------------------------------------*/
/* FILENAME:         Kphp11d.h                                                */
/* DESCRIPTION:      Kphp11:  Irenginiai                                      */
/* LANGUAGE:         C++                                                      */
/* DESTINATION:      *                                                        */
/* SYSTEM_INTERFACE: *                                                        */
/* USER_INTERFACE:   *                                                        */
/* ARCHIVE_VERSION:  LATEST                                                   */
/* ARCHIVE_COMMENT:                                                           */
/*----------------------------------------------------------------------------*/


#ifndef Kphp11d
#define Kphp11d


#define D_SectSiz 01000  /* RT-11 sector size */

#define MaxDev 16    /* Max. irenginiu skaicius */

typedef enum
{
  TERM_NO,
  TERM_VT52,
  TERM_VT100,
  TERM_VT220,
  TERM_BK0010,
  TERM_TETRONIX
} TermTypes;


typedef unsigned char KbChar;

/* bendra terminalo tipo klases dalis */
class EmuD_TT_comt
{
public:
  TermTypes termtyp;

  KbChar /* unsigned int */ tkbuf[KPW_KB_BUF_SIZE+1];  /* klaviaturos ivedimo buferis */
  int tkbin;                    /* ivedimo rodykle */
  int tkbout;                   /* nuskaitymo rodykle */

  short tokbbuf(KbChar /* unsigned int chr */); /* simboli i klav. eile, False - nera vietos */
  short tkbhit(void);              /* ar yra simbolis klav. buferyje? */
  KbChar /* unsigned int */ tfromkbbuf(void);   /* simboli is klaviaturos buferio, Nul - buferis tuscias */

  EmuD_TT_comt(); /* konstruktorius */

  virtual KbChar /* unsigned int */ tputchar(KbChar /* unsigned int */ chr, KpConsole *wnd) = 0;
  virtual short ttokbbuf(KbChar /* unsigned int */ chr) = 0; /* simboli i klav. eile, False - nera vietos */
};


typedef enum
{
  DEV_NO,
  DEV_TT,
  DEV_MX,
  DEV_MY,
  DEV_MZ,
  DEV_LP,
  DEV_RC,
  DEV_RY
} DevTypes;


/* Bendra irenginio apraso dalis */              
class EmuD_comt
{
public:
   DevTypes devtyp;          /* irenginio tipas */
   AdrTyp   portadr;         /* pirmo (TT_in_CSR) registro adresas */
   int      portnum;         /* registru skaicius; vieno reg. ilgis 2 baitai (16 bitu) */
   AdrTyp   intvect;         /* trukiu vektoriu pradzios adresas */
   unsigned char devnam[3];  /* irenginio vardas */
   int      devno;           /* kisenes numeris */
   unsigned char filnam[Fnsiz+1]; /* susieto failo vardas, ne diskui - "" */
   KpConsole *wndw;          /* terminalo isvedimo langas, ne terminalui - NULL */
   EmuD_TT_comt *ttadr;      /* terminalo tipo klases adresas, ne terminalui - NULL */

   EmuD_comt();              /* konstruktorius */

   virtual void reset(void) = 0;      /* inicializavimas (trukiu uzdraudimas) */

// kphp11 site port i/o
   virtual short getw(AdrTyp adress, Word16Typ *valp) = 0;
   virtual short getb(AdrTyp adress, ByteTyp *valp) = 0;
   virtual short putw(AdrTyp adress, Word16Typ val) = 0;
   virtual short putb(AdrTyp adress, ByteTyp val) = 0;

// Win32 site port i/o
   virtual short dputw(int portn, Word16Typ val) = 0;

// trukio generavimas
// portn - CSR porto numeris 0..portnum
   virtual short dintrpt(int portn) = 0;
};


// visi irenginiai
class EmuDt
{
  EmuD_comt *devcl[MaxDev]; /* irenginio klases adresas */

public:
  short testports(void);  /* portu adresu sinchronizavimas ir patikrinimas, True - gerai */
  short plugdev(DevTypes devtp, AdrTyp porta, AdrTyp intv, int devn, unsigned char *filn, KpConsole *wnd,  TermTypes termtyp);
                          /* naujo irenginio prijungimas, porta - CSR adresas,
                             intv - trukio vekt. adr., devn - kisenes nr.,
                             filn - susieto failo vardas; wnd - terminalo isvedimo langas,
                             tta - terminalo tipo klases adr., True - gerai */
  short reset(void);      /* irenginiu inicializavimas (trukiu uzdraudimas), True - gerai */

                                 /* skaitymas/rasymas; True - gerai */
  short getw(AdrTyp adress, Word16Typ *valp);
  short getb(AdrTyp adress, ByteTyp *valp);
  short putw(AdrTyp adress, Word16Typ val);
  short putb(AdrTyp adress, ByteTyp val);

  short getdevn(AdrTyp adress, int *devnr);
                          /* irenginio suradimas pagal reg. adr.,
                             grazina devnr - ireng. masyvo indexa,
                             True - surado */
  short getndevn(unsigned char *devnm, int devn, int *devnr); 
                          /* irenginio suradimas pagal varda,
                             devnm - vardas (MZ, MX, ...),
                             devn - kisenes nr.,
                             grazina devnr - ireng. masyvo indexa,
                             True - surado */
  short getndevn(DevTypes devtp, int devn, int *devnr); 
                          /* irenginio suradimas pagal tipa,
                             devtp - irenginio tipas
                             devn - kisenes nr.,
                             grazina devnr - ireng. masyvo indexa,
                             True - surado */

  unsigned char *getfnam(int devnr); /* irenginio failo vardas, NULL - nerado */ 

  short tokb(KbChar /* unsigned int */ ch); /* i klaviaturos eile, False - nerado terminalo */
  short dkbhit(void); // ar yra simboliu klaviaturoje

  short ddputw(DevTypes devtp, int devn, int portn, Word16Typ val);
            // rasymas i porta
            // devtp - irenginio tipas
            // devn - kisenes nr
            // portn - porto numeris 0..XX_MaxPort

  short ddintrpt(DevTypes devtp, int devn, int portn);
            // trukio generavimas
            // devtp - irenginio tipas
            // devn - kisenes nr
            // portn - CSR porto numeris 0..XX_MaxPort

  EmuDt();                /* konstruktorius */
  ~EmuDt();               /* destruktorius */
};

extern EmuDt EmuDv;

#endif
