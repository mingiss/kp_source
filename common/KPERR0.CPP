// ==================================================
// kperr0.cpp
// error processing object for plain C projects
//


// ======================================= definitions
#include "envdef.h"
#include "envir.h"
#include "envsupp.h"

#include "kpstdlib.h"
#include "kptt.h"
#include "kperr.h"


// =======================================
KpErrorProc_tag KpErrorProc
(
#if ((Envir==No) || (Envir==MSDosCon) || (Envir==MSWinCon) || (Envir==Nd) || (Envir==Unix) || (Envir==Linux) || (Envir==MSWin32Con) || (Envir==MSWin32ConMfc))
   True,
#else
   False,
#endif
  43
);


// =======================================
HRESULT KpErrorProc_tag::FormatErrorMessage
(
	const HRESULT lhRetc,
	unsigned char *lpszMsg
)
{
return(FormatErrorMessageMain(lhRetc, lpszMsg));
}

