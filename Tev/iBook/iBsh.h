// -----------------------------------------
// iBsh.h
// el. knygø perþiûros programa
// bendros nuostatos
//

#ifndef iBsh_included
#define iBsh_included


#ifndef iBshn_included
#error iBshn.h not included
#endif

// -----------------------------
#if FALSE // #ifdef IBSHT_ENCODED
#define IBSH_RC_NumOfRcIxs 2
#else
#define IBSH_RC_NumOfRcIxs 0
#endif
#define IBSH_RC_NumOfRcIxs_1 IBSH_RC_NumOfRcIxs

#define IBSH_RC_WriteRtfFromImg KP_RC_CBIX_NumOfCommonIxs
#define IBSH_RC_GetHwFromImg (KP_RC_CBIX_NumOfCommonIxs+1)

// -----------------------------

class iBshApp:
   public KpStApp
{
};

extern iBshApp theiBshApp; // use *theKpStAppPtr instead // former theApp

#endif

