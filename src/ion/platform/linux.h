/*
  Linux.
*/

#if   architecture(X64)
  typedef int             native_int_t;   /* 32 bit */
  #define widest_int_t    long int        /* 64 bit */
  #define INT_FORMAT      "%l"

#elif architecture(X86)
  typedef int             native_int_t;   /* 32 bit */
  #define widest_int_t    int             /* 32 bit */
  #define INT_FORMAT      "%"

#else
  #error "⚡️ION⚡️: Unsupported architecture for Linux platform."
#endif

#if standard(>= C11)
/*
  Linux natively supports the `free` function to be called on memory allocated by the
  C11 function `aligned_malloc`. Since other platforms, like Windows, do not support
  this, we define an `aligned_free` symbol to have a compatibility layer between
  platforms. In case of Linux, as said above, it is just an alias for `free`.
*/
#define aligned_free  free
#endif

/* For the `sleep` and `clock_gettime` functions. */
#define _POSIX_C_SOURCE 200809L
#include <time.h>
