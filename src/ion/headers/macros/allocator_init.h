/**
 * Initializes an allocator with capacity equal to `MEMORY_DEFAULT_CAP`. */
#define allocator_init()                    \
  (struct memory) {                         \
    .capacity = MEMORY_DEFAULT_CAP,         \
    .position = 0,                          \
    .allocations = 0,                       \
    .regions_capacity = MEMORY_MIN_REGIONS, \
    .regions_count = 0,                     \
    .regions = NULL,                        \
    .data = NULL                            \
  };
