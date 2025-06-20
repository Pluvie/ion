/**
 * Tells the compiler that the "false" branch of this condition is likely to happen,
 * so the code prefetching in the CPU pipeline shall be loaded with the "false" branch,
 * in order to gain speed. */
#define unlikely(x) \
  __builtin_expect(!!(x), 0)
