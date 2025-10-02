/*
  Microsoft Windows - 32 bit architecture.
*/

#define INT_BIT_WIDTH   32
#define INT_MAXCHARS    10    /* 2147483647 = (2^32 - 1) */
#define INT_FORMAT      "%"

#define widest_int_t    int             /* 32 bit */

#ifdef ION_EXEC         /* Defines the `native_int_t` only in compilation phase. */

typedef int             native_int_t;   /* 32 bit */

#include "windows_32/libraries.h"

#endif
