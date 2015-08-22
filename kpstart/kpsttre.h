// ---------------
// kpsttre.h
// tux pdf i�kodavimas ir greitas licencijos registravimo pasitikrinimas
//

#ifndef kpsttre_included
#define kpsttre_included


// ---------------
// Tux u�koduoto failo i�kodavimas emuliatorium.
// Jei registracija (registracijos tikrinimas) KpsTestReg() nepavyko, tur�t� nekoduoti.
// Jei KpsTestReg() dar nebuvo i�kviestas - meta klaid�, nes dar nepaleistas emuliatoriaus thread'as.
// lpszFileBuf - failo turinys buferyje, buferio ilgis turi b�ti kartotinis 4 (arba didesnis 4 baitais, negu lFileLen) - koduojama
//    4 bait� blokeliais. I�lyginimo DWORD adresui nereikia.
//
#define KpstTuxDecodeBuf KpstTDB
extern
#ifdef KPSTTRG_DLL
"C" // __declspec(dllexport)
#endif
#ifdef KPSTTRG_DLL_IMP
"C" __declspec(dllimport)
#endif
HRESULT KpstTuxDecodeBuf(char *lpszFileBuf, long lFileLen);


// ------------------
// Hash funkcija, veikia, tik jei registracija buvo s�kminga
#define KpstTuxHash KpstTH
extern
#ifdef KPSTTRG_DLL
"C" // __declspec(dllexport)
#endif
#ifdef KPSTTRG_DLL_IMP
"C" __declspec(dllimport)
#endif
unsigned long KpstTuxHash(unsigned long ulVal);

// ------------------
// Greitas pasitikrinimas, ar licencija buvo s�kmingai u�registruota, hash funkcija, skai�iuojama emuliatorium.
// Jei KpsTestReg() dar nebuvo i�kviestas - meta klaid�, nes dar nepaleistas emuliatoriaus thread'as.
// Naudojimo b�dai:
//
// 1.
//    if(TUX_HASH_OK_STAT) { ... }
//
// 2.
// time_t cur_clock;
//
//    time(&cur_clock);
//    if(TUX_HASH_OK(cur_clock)) { ... }
// ...
//    time(&cur_clock);
//    if(TUX_HASH_OK(cur_clock)) { ... }
//
// 3.
// time_t cur_clock;
// unsigned long rand_value;
//    time(&cur_clock);
//    srand(cur_clock);
//
//    rand_value = (unsigned long)rand()*rand();
//    if(TUX_HASH_OK(rand_value)) { ... }
// ...
//    rand_value = (unsigned long)rand()*rand();
//    if(TUX_HASH_OK(rand_value)) { ... }
//
// negalima naudoti if(TUX_HASH_OK((unsigned long)rand()*rand())) :)
//
#define TUX_HASH(val) \
( \
   ( \
      ( \
         ( \
            ((((((unsigned long)val) & 0xFFFFL) + 17909L) * 25169L) & 0xFFFFL) + \
            (((((((unsigned long)val) >> 16) & 0xFFFFL) + 17909L) * 25169L) & 0xFFFFL) \
         ) << \
         16 \
      ) & 0xFFFF0000L \
   ) | \
   ( \
      ( \
         ((((((unsigned long)val) & 0xFFFFL) + 17909L) * 25169L) & 0xFFFFL) - \
         (((((((unsigned long)val) >> 16) & 0xFFFFL) + 17909L) * 25169L) & 0xFFFFL) \
      ) & 0xFFFFL \
   ) \
)
#define TUX_HASH_OK_STAT (KpstTuxHash(1) == 0x3b5b6251L)
#define TUX_HASH_OK(val) (KpstTuxHash(val) == TUX_HASH(val)) // negalima naudoti val, turin�io �alutin� poveik�

#endif // #ifndef kpsttre_included
