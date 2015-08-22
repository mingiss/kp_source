// ------------------------------
// kphp11ry.h
// kphp11 remote memory access device
// allowes internal kphp11 process to access external Win32 process memory
//


#ifndef Kphp11ry
#define Kphp11ry

// RY_CSR flags
// lower byte only
#define RY_read       020  // request to read data from Win32 memory
                           // writable from kphp11 side
#define RY_write      040  // request to write data to Win32 memory
                           // writable from kphp11 side
#define RY_ien       0100  // interrupt enable
#define RY_ready     0200  // requested data ready, if RY_ien, generates interrupt
                           // resets RY_request
                           // writable only from Win32 side
#define RY_CSR       0 
#define RY_ADDR1     1     // lower word of memory address, not necessary alligned on word boundary
#define RY_ADDR2     2     // higher word of memory address
#define RY_DATA1     3     // lower 2 bytes of read data
#define RY_DATA2     4     // higher 2 bytes of read data
#define RY_MaxPort   5

#define RY_DEF_CSR 0177310
#define RY_DEF_INT 310

// device class
class EmuD_RYt : public EmuD_comt
{            
  Word16Typ   ports[RY_MaxPort]; /* registrai */

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

  EmuD_RYt(AdrTyp porta, AdrTyp intv, int devn, unsigned char *filn, KpConsole *wnd, EmuD_TT_comt *tta);
                          /* konstruktorius, porta - CSR adresas,
                             intv - trukio vekt. adr., devn - kisenes nr.,
                             filn - susieto failo vardas (NULL); wnd - terminalo isvedimo langas,
                             tta - terminalo tipo klases adr. */
};

#endif
