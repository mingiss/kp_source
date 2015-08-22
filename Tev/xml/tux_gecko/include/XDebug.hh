#ifndef XDEBUG_HH
#define XDEBUG_HH

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <XTux.hh>
#include <stdio.h>
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define XASSERT(x)          if (!(x)) debug.debug(5, __FILE__, __LINE__, __FUNCTION__, L"- " #x)
#define XASSERT_S(x, msg)   if (!(x)) debug.debug(5, __FILE__, __LINE__, __FUNCTION__, msg)
#define XASSERT_F(x, ...)   if (!(x)) debug.debugf(5, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)
#define XDEBUG_S(msg)       debug.debug(0, __FILE__, __LINE__, __FUNCTION__, msg)
#define XDEBUG_F(...)       debug.debugf(0, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)
#define XENSURE(x, r)                                 \
  if (!(x))                                           \
  {                                                   \
    XDEBUG_S(L"- ENSURANCE FAILED: " #x);             \
    return r;                                         \
  }
#define XTEST(x)            if (!(x)) XDEBUG_S(L"- TEST FAILED: " #x);

/************************************************************* TX *************************************************************/
/*                                                           XDebug                                                           */
/******************************************************************************************************************************/

struct XDebug
{
  public:
    X       XDebug();
    X       ~XDebug();
    X void  debug(int level, cstr_t file, int line, cstr_t func, cwstr_t msg);
    X void  debugf(int level, cstr_t file, int line, cstr_t func, cwstr_t fmt, ...);
    X void  printf(cwstr_t fmt, ...);
  private:
    X FILE  *m_log;
} extern debug;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif /* XDEBUG_HH */
