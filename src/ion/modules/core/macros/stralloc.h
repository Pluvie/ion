/**
 * Helper to allocate an empty string with an allocator. */
#define stralloc(length_var, allocator_var)                   \
  (string) {                                                  \
    .content = memory_alloc_zero(allocator_var, length_var),  \
    .length = length_var,                                     \
  }
