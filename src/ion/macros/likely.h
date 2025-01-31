/**
 * Tells the compiler that the "true" branch of this condition is likely to happen,
 * so the code prefetching in the CPU pipeline shall be loaded with the "true" branch,
 * in order to gain speed. */
#define likely(x) \
  __builtin_expect(!!(x), 1) 
