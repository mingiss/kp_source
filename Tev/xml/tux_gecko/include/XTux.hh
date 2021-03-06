#ifndef XTUX_HH
#define XTUX_HH

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <windows.h>
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define XTUX_VER                "0.0.1"
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define X
#define S                       static
#define V                       virtual
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#undef interface
#define interface               struct
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef char                    i8_t;
typedef unsigned char           u8_t;
typedef short                   i16_t;
typedef unsigned short          u16_t;
typedef int                     i32_t;
typedef unsigned int            u32_t;
typedef long long               i64_t;
typedef unsigned long long      u64_t;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef char                    *str_t;
typedef const char              *cstr_t;
typedef wchar_t                 *wstr_t;
typedef const wchar_t           *cwstr_t;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/************************************************************* TX *************************************************************/
/*                                                            XTux                                                            */
/******************************************************************************************************************************/

struct XTux
{
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "XDebug.hh"
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif /* XTUX_HH */
