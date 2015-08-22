// ------------------------------
// kphp11rc.h
// kphp11 remote controll device, allowes Win32 process access internal kphp11 procedures
//


#ifndef Kphp11rc
#define Kphp11rc

// flags of RC_CSR
// lower byte only
#define RC_exec    020  // execute callback Win32 procedure
                        // writable only from kphp11 side
                        // parameter block KpRcPars address must be 
                        //    left filled from recent RC call from
                        //    Win32 in registers
                        //    RC_DEF_CSR+RC_ADDR1*2 and RC_DEF_CSR+RC_ADDR2*2
                        //    remote function address in
                        //    KpHp11ExtFunTab[KpRcPars.enc.iCallBackIx]
                        //    parameter for remote function in
                        //    KpRcPars.enc.pCallBackPars
#define RC_busy    040  // procedure in progress, no other processing available
                        // procedure completion resets RC_busy to 0
                        // writable only from kphp11 side
#define RC_ien    0100  // enable interrupn on procedure request
                        // writable only from kphp11 side
#define RC_ready  0200  // procedure request pending, if RC_ien, generates interrupt
                        // writable only from Win32 side

#define RC_CSR       0 
#define RC_ADDR1     1  // lower word of parameter block address in Win32 process memory
#define RC_ADDR2     2  // higher word of parameter block address in Win32 process memory
#define RC_MaxPort   3

#define RC_DEF_CSR 0177300
#define RC_DEF_INT 0300

// bendri susitarimai del parametru bloko


// device class
class EmuD_RCt : public EmuD_comt
{            
  Word16Typ   ports[RC_MaxPort]; /* registrai */

public:

  void reset(void);      /* inicializavimas (trukiu uzdraudimas) */

                          /* skaitymas/rasymas; True - gerai */
  short getw(AdrTyp adress, Word16Typ *valp);
  short getb(AdrTyp adress, ByteTyp *valp);
  short putw(AdrTyp adress, Word16Typ val);
  short putb(AdrTyp adress, ByteTyp val);

                          /* Win32 puses skaitymas/rasymas; True - gerai */
  short dputw(int portn, Word16Typ val);

  short dintrpt(int portn); // portn - CSR porto numeris 0..portnum

  EmuD_RCt(AdrTyp porta, AdrTyp intv, int devn, unsigned char *filn, KpConsole *wnd, EmuD_TT_comt *tta);
                          /* konstruktorius, porta - CSR adresas,
                             intv - trukio vekt. adr., devn - kisenes nr.,
                             filn - susieto failo vardas (NULL); wnd - terminalo isvedimo langas,
                             tta - terminalo tipo klases adr. */
};
#endif
