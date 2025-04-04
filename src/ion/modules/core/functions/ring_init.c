#ifdef ION_INCLUDED
static inline
#endif

struct ring ring_init (
    u64 initial_capacity
)
{
capacity_check:
  u64 capacity = next_pow2(initial_capacity);
  if (capacity < MEMORY_DEFAULT_CAP)
    capacity = MEMORY_DEFAULT_CAP;

initialize:
  struct ring allocator = {
    .capacity = capacity,
    .allocated_space = 0,
    .free_space = capacity,
    .begin = 0,
    .end = 0,
    .data = NULL,
    .junction = NULL,
  };

  return allocator;
}
