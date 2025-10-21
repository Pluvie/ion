/*
  Linux.
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

/* For the `sleep` and `clock_gettime` functions. */
#define _POSIX_C_SOURCE 200809L
#include <time.h>
