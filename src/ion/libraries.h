/*
  These are ⚡️ION⚡️ real dependencies -- as much as the C standard library can be a
  classified as a dependency. Any platform or standard which do not natively provide
  these headers must implement the dependent functions.

  It may be considered in future release of ⚡️ION⚡️ to progressively remove these
  dependencies to bring self provided code.
*/


/* For variadic argument support, used in `print_*` functions. */
#include <stdarg.h>

#if standard(>= C23)
/* For bitwise operations, used in `bit_*` functions. */
#include <stdbit.h>
#endif

#if standard(< C23)
/* To introduce the `bool` type. */
#include <stdbool.h>
#endif

/* For the `offsetof` macro. */
#include <stddef.h>


/* For IO support, used in `print_*` functions. */
#include <stdio.h>

/* For memory allocation, used in `memory_*` functions. */
#include <stdlib.h>

/* For the `strcmp`, `memcmp` and `memcpy` functions. */
#include <string.h>

#if standard(>= C11)
/* For the `thread_local` macro on the global failure variable, and all threading API. */
#include <threads.h>
#endif
