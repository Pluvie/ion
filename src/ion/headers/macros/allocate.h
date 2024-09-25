/**
 * Initializes a variable with program-bound lifetime.
 *
 * The variable is allocated on the `heap`, which is a memory region used to contain
 * all program-bound lifetimes. The heap is cleared upon program return.
 *
 * The variable is always initialized with zero, but it can be given another value
 * using the variadic arguments.
 *
 * Example:
 *
 * ```c
 * allocate(example_1, u64);      // This variable has value 0.
 * initialize(example_2, u64, 7);   // This variable has value 7.
 * ```
 *
 * The initialization follows the same principles also for struct types.
 *
 * The allocation is done by the `global_allocator`. */
#define allocate(pointer, type, ...)                                  \
  type* pointer = memory_alloc_zero(global_allocator, sizeof(type));  \
  __VA_OPT__(*pointer = (type) __VA_ARGS__)
