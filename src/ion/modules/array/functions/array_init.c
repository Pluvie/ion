#ifdef ION_INCLUDED
static inline
#endif

struct array array_init (
    u64 typesize,
    u64 initial_capacity,
    struct memory* allocator
)
{
capacity_check:
  u64 capacity = next_pow2(initial_capacity);

  if (capacity < ARRAY_DEFAULT_CAP)
    capacity = ARRAY_DEFAULT_CAP;

initialization:
  struct array array = {
    .capacity = capacity,
    .length = 0,
    .typesize = typesize,
    .data = memory_alloc_zero(allocator, typesize * capacity),
    .allocator = allocator
  };

  return array;
}
