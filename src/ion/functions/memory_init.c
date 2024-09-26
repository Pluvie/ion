#ifdef ION_INCLUDED
static inline
#endif

struct memory memory_init (
    u64 initial_capacity
)
{
capacity_check:
  u64 capacity = next_pow2(initial_capacity);
  if (capacity < MEMORY_DEFAULT_CAP)
    capacity = MEMORY_DEFAULT_CAP;

initialize:
  struct memory allocator = {
    .capacity = capacity,
    .position = 0,
    .allocations = 0,
    .regions_capacity = 8,
    .regions_count = 0,
    .regions = NULL,
    .data = NULL
  };

  return allocator;
}
