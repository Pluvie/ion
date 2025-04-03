#ifdef ION_INCLUDED
static inline
#endif

struct map map_init (
    u64 key_typesize,
    u64 value_typesize,
    u64 initial_capacity,
    struct memory* allocator
)
{
capacity_check:
  u64 capacity = next_pow2(initial_capacity);
  if (capacity < MAP_DEFAULT_CAP)
    capacity = MAP_DEFAULT_CAP;

initialize:
  u64 entry_typesize = key_typesize + value_typesize + sizeof(u64);

  struct map map = {
    .capacity = capacity,
    .length = 0,
    .load_limit = (capacity * 70) / 100,
    .key_typesize = key_typesize,
    .value_typesize = value_typesize,
    .entry_typesize = entry_typesize,
    .entries = memory_alloc_zero(allocator, entry_typesize * capacity),
    .allocator = allocator
  };

  return map;
}
