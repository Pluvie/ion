/*
  Linux - 64 bit architecture.
*/

#define INT_BIT_WIDTH   64
#define INT_MAXCHARS    19    /* 9223372036854775807 = (2^63 - 1) */
#define INT_FORMAT      "%l"

typedef int             native_int_t;   /* 32 bit */
#define widest_int_t    long int        /* 64 bit */

#include "linux/libraries.h"
