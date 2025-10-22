/*
  Microsoft Windows.
*/

#if   architecture(X64)
  typedef int             native_int_t;   /* 32 bit */
  #define widest_int_t    long long int   /* 64 bit */

#elif architecture(X86)
  typedef int             native_int_t;   /* 32 bit */
  #define widest_int_t    int             /* 32 bit */

#else
  #error "⚡️ION⚡️: Unsupported architecture for Windows platform."
#endif

#if standard(>= C11)
/*
  Aligned allocation is supported in Windows through the <malloc.h> system header.
  Contrary to other platforms, like Linux, on Windows it is not possible to call the
  standard function `free` on memory allocated by the C11 function `aligned_alloc`.
  Therefore, we add the `aligned_free` macro as a compatibility layer between platforms.
*/
#include <malloc.h>
#define aligned_alloc _aligned_alloc
#define aligned_free  _aligned_free
#endif

/* For the `Sleep` function. */
#include <windows.h>

/* Undefines INT, BOOL, CHAR types to avoid conflict with reflection enums. */
#undef INT
#undef BOOL
#undef CHAR
