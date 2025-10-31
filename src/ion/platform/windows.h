/* Windows platform. */

#if   architecture(X64)
/* For int64_t type because `long long` is not supported in C89. */
#include <stdint.h>
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

/* For _aligned_malloc and other Windows internals. */
#define BOOL  BOOL_TYPE_WIN32
#define INT   INT_TYPE_WIN32
#include <windows.h>
#undef  BOOL
#undef  INT

/* For _BitScanReverse builtin. */
#include <intrin.h>
