/*
  Microsoft Windows - 32 bit architecture.
*/

typedef int             native_int_t;   /* 32 bit */
#define widest_int_t    int             /* 32 bit */

#define INT_BIT_WIDTH   32
#define INT_MAXCHARS    10    /* 2147483647 = (2^32 - 1) */
#define INT_FORMAT      "%i"
#define INT_UFORMAT     "%u"

#include "windows32/libraries.h"
