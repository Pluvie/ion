/**
 * Computes the logarithm in base `2` of a *number*.
 *
 * The computation is done using compiler builtins, specifically [__builtin_clzl](
 * https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html) which are fast and efficient
 * operation on CPU registers. */
#define log2(number) \
  (number > 1 ? 64 - __builtin_clzll((u64) number - 1) : 0)
