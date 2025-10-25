/* Linux platform. */

#if   architecture(X64)
typedef long int            widest_int_t;     /* 64 bit */
typedef unsigned long int   widest_uint_t;    /* 64 bit */
#define INT_FORMAT          "li"

#elif architecture(X86)
typedef int                 widest_int_t;     /* 32 bit */
typedef unsigned int        widest_uint_t;    /* 32 bit */
#define INT_FORMAT          "i"

#else
#error "ION: Unsupported architecture for Linux platform."
#endif
