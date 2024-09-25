/**
 * Initializes a variable with function-bound lifetime.
 *
 * The variable is allocated on the `stack`, which is a memory region used to contain
 * all function-bound lifetimes. The stack is cleared upon function return.
 *
 * The variable is always initialized with zero, but it can be given another value
 * using the variadic arguments.
 *
 * Example:
 *
 * ```c
 * initialize(example_1, u64);      // This variable has value 0.
 * initialize(example_2, u64, 7);   // This variable has value 7.
 * ```
 *
 * The initialization follows the same principles also for struct types. */
#define initialize(variable, type, ...) \
  type variable = (type) { 0 };         \
  __VA_OPT__(variable = __VA_ARGS__)
