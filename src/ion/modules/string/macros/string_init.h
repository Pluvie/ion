/**
 * Helper to initialize a string with an allocator. */
#define string_init(length_var, allocator_var)                        \
  (struct string) {                                                   \
    .content = memory_alloc_zero(allocator_var, length_var + 1),      \
    .length = length_var,                                             \
  }
