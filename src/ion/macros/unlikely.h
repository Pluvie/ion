/* Tells the compiler that the "false" branch of this condition is likely to happen,
 so the code prefetching in the CPU pipeline shall be loaded with the "false" branch,
 in order to gain speed.

 This macro works on both GCC and clang compilers, since they support the builtin and
 define the __GNUC__ constant. A fallback is provided for compilers who do not support
 this feature. */
#if compiler(GCC) || compiler(CLANG)
#define unlikely(x) __builtin_expect(!!(x), 0) 
#else
#define unlikely(x) x
#endif
