/**
 * Initializes a variable with function-bound lifetime.
 *
 * The variable is allocated on the `stack`, which is a memory region used to contain
 * all function-bound lifetimes. The stack is cleared upon function return.
 *
 * The variable is initialized with an undefined value, but it can be given a specific
 * value using the variadic arguments.
 *
 * Example:
 *
 * ```c
 * initialize(example_1, u64);          // This variable has undefined value.
 * initialize(example_2, u64, { 7 });   // This variable has value 7.
 * ```
 *
 * The initialization follows the same principles also for struct types. */
#define initialize(variable, type, ...)             \
  type variable __VA_OPT__(= __VA_ARGS__)
