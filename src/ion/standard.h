/* ⚡️ION⚡️ C standards mapping.  */

#ifndef __STDC_VERSION__
#define __STDC_VERSION__ 0L
#endif

#define C89 0L
#define C99 199901L
#define C11 201112L
#define C17 201710L
#define C23 202000L

#define standard(check) \
  __STDC_VERSION__ check

/* Included below are C89 (ANSI) headers which provide ⚡️ION⚡️ required
  functionalities. If a platform does not provide these headers is not ANSI C
  compatible and therefore is not supported by ⚡️ION⚡️.

  If you can however provide the required funcionalities by implementing them
  yourself on the platform, then ⚡️ION⚡️ should work just fine. */

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

/* For the `strcmp`, `memcmp` and `memcpy` functions. */
#include <string.h>
