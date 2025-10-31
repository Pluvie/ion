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
