/* Windows platform. */

#if   architecture(X64)
typedef long long int           int_t;    /* 64 bit */
typedef unsigned long long int  uint_t;   /* 64 bit */
#define INT_T__FORMAT           "lli"

#elif architecture(X86)
typedef int                     int_t;    /* 32 bit */
typedef unsigned int            uint_t;   /* 32 bit */
#define INT_T__FORMAT           "i"

#else
#error "ION: Unsupported architecture for Windows platform."
#endif
