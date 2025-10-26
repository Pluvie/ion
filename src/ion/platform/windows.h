/* Windows platform. */

#if   architecture(X64)
typedef long long int             widest_int_t;     /* 64 bit */
typedef unsigned long long int    widest_uint_t;    /* 64 bit */
#define INT_FORMAT                "lli"
#define UINT_FORMAT               "llu"

#elif architecture(X86)
typedef int                       widest_int_t;     /* 32 bit */
typedef unsigned int              widest_uint_t;    /* 32 bit */
#define INT_FORMAT                "i"
#define UINT_FORMAT               "u"

#else
#error "ION: Unsupported architecture for Windows platform."
#endif
