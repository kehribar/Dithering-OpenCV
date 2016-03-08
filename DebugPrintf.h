/*-----------------------------------------------------------------------------
/
/
/----------------------------------------------------------------------------*/
#include <stdio.h>

#define DEBUG_ENABLED 1

#if DEBUG_ENABLED
    #define dbg(...) printf(__VA_ARGS__)
#else
    #define dbg(...)
#endif