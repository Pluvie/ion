/**
 * Initializes an allocator with capacity equal to `MEMORY_DEFAULT_CAP`. */
#define allocator_init(capacity)      \
  (struct memory) {                   \
    .capacity = MEMORY_DEFAULT_CAP,   \
    .position = 0,                    \
    .allocations = 0,                 \
    .regions_capacity = 8,            \
    .regions_count = 0,               \
    .regions = NULL,                  \
    .data = NULL                      \
  };
