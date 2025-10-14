/*
  Linux - 64 bit architecture.
*/

#define INT_BIT_WIDTH   64
#define INT_MAXNUM      "9223372036854775807"   /* 2^63 - 1 */
#define INT_FORMAT      "%l"

typedef int             native_int_t;           /* 32 bit */
#define widest_int_t    long int                /* 64 bit */

/*
  Platform specific code.
*/

#if standard(>= C11)
/*
  Linux natively supports the `free` function to be called on memory allocated by the
  C11 function `aligned_malloc`. Since other platforms, like Windows, do not support
  this, we define an `aligned_free` symbol to have a compatibility layer between
  platforms. In case of Linux, as said above, it is just an alias for `free`.
*/
#define aligned_free  free
#endif
