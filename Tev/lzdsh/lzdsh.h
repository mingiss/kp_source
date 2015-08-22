// -----------------------------------------
// lzdsh.h
// zodyno perziuros programa ir XMLT redaktorius
// bendros nuostatos
//

#ifndef lzdsh_included
#define lzdsh_included

#ifndef lzdshn_included
#error lzdshn.h not included
#endif


// -----------------------------
#ifdef LZDSHT_ENCODED
#define LZDSH_RC_NumOfRcIxs 2
#else
#define LZDSH_RC_NumOfRcIxs 0
#endif
#define LZDSH_RC_NumOfRcIxs_1 LZDSH_RC_NumOfRcIxs

#define LZDSH_RC_WriteRtfFromImg KP_RC_CBIX_NumOfCommonIxs
#define LZDSH_RC_GetHwFromImg (KP_RC_CBIX_NumOfCommonIxs+1)

#ifndef LZDSH_DELT
#define LZDSH_HELP_FILE ((const unsigned char *)"WinLED_instrukcija.htm")
#else
#define LZDSH_HELP_FILE ((const unsigned char *)"DeLt_instrukcija.htm")
#endif

// -----------------------------

class LzdShApp:
#ifdef KP_USE_WXWIDGETS
   public wxApp,
#endif
   public KpStApp
{
#ifdef KP_USE_WXWIDGETS
public:
// LzdShApp() : wxApp() : KpStApp() {};
// ~LzdShApp() { ~wxApp(); ~KpStApp(); };

/* virtual */ bool OnInit();
#endif
};

#ifndef KP_USE_WXWIDGETS
extern LzdShApp theLzdShApp; // use *theKpStAppPtr instead // former theApp
#endif

#endif

