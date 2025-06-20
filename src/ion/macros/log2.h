/**
 * Computes the logarithm in base 2 of a *number*.
 *
 * If the number is `0` or `1`, the macro returns `0`.
 * Otherwise returns the calculated logarithm in base 2 of *number*.
 *
 * The computation is done using compiler builtins, specifically [__builtin_clzll](
 * https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html) which are fast and efficient
 * operation on CPU registers. */
#define log2(number) \
  (number > 1 ? 64 - __builtin_clzll((int) number - 1) : 0)
