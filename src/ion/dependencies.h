/* Included below are the real ⚡️ION⚡️ dependencies, as much as the C89 (ANSI) headers
  can be considered as such.

  Any implementation which does not provide these headers is not ANSI C compatible and
  therefore is not supported by ⚡️ION⚡️.

  If you can however provide the required funcionalities by implementing them
  yourself on the platform, then ⚡️ION⚡️ should work just fine. */

/* For the `errno` and related functions. */
#include <errno.h>

/* For variadic argument support, used in `fail` and `fatal` functions. */
#include <stdarg.h>

/* For the `stdc_*` bit manipulation functions. */
#if standard(>= C23)
#include <stdbit.h>
#endif

/* For the `offsetof` macro. */
#include <stddef.h>

/* For the `printf` family functions. */
#include <stdio.h>

/* For memory allocation with `malloc`, `realloc` and `free`. */
#include <stdlib.h>

/* For the `memcpy`, `memmove`, `strcmp` and `strerror` functions. */
#include <string.h>
