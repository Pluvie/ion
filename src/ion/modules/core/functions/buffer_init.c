#ifdef ION_INCLUDED
static inline
#endif

struct buffer buffer_init (
    u64 initial_capacity
)
{
capacity_check:
  u64 capacity = next_pow2(initial_capacity);
  if (capacity < MEMORY_DEFAULT_CAP)
    capacity = MEMORY_DEFAULT_CAP;

initialize:
  struct buffer allocator = {
    .capacity = capacity,
    .position = 0,
    .data = NULL
  };

  return allocator;
}
