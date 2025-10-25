/* Tells the compiler that the "true" branch of this condition is likely to happen,
 so the code prefetching in the CPU pipeline shall be loaded with the "true" branch,
 in order to gain speed.

 This macro works on both GCC and clang compilers, since they support the builtin and
 define the __GNUC__ constant. A fallback is provided for compilers who do not support
 this feature. */
#if compiler(GCC) || compiler(CLANG)
#define likely(x) __builtin_expect(!!(x), 1) 
#else
#define likely(x) x
#endif
