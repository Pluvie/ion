/* Windows platform. */

#include <stdint.h>
#define BOOL  BOOL_WIN
#define INT   INT_WIN
#include <windows.h>
#undef  BOOL
#undef  INT

#if   architecture(X64)
typedef int64_t             widest_int_t;     /* 64 bit */
typedef uint64_t            widest_uint_t;    /* 64 bit */
#define INT_FORMAT          "lli"
#define UINT_FORMAT         "llu"

#elif architecture(X86)
typedef int                 widest_int_t;     /* 32 bit */
typedef unsigned int        widest_uint_t;    /* 32 bit */
#define INT_FORMAT          "i"
#define UINT_FORMAT         "u"

#else
#error "ION: Unsupported architecture for Windows platform."
#endif
