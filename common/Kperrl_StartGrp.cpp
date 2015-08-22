// ==================================================
// kperrl.cpp
// KpProcessError() papildomø prie DiagMsg prijungiamø failø sàraðas
// prikompiliuojamas prie XFS projekto (prie kpsttrg.lib), skirtingiems projektams gali bûti skirtingi
//

// ======================================= definitions
#include <windows.h>

#include "kperrno.h"

// --------------------------------------------
const unsigned char *KpDiagMsgAddFiles[] =
{
   (const unsigned char *)"{progpath}\\DAT0\\StartGrp.cfg",
// (const unsigned char *)"{progpath}\\StartGrp.xml",
   (const unsigned char *)"{progpath}\\DAT0\\StartGrp.htm",
   (const unsigned char *)"{progpath}\\startgrp.ini",
   NULL
};
