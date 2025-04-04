#ifdef ION_INCLUDED
static inline
#endif

struct map map_init (
    u32 key_typesize,
    u32 value_typesize,
    u32 initial_capacity,
    struct memory* allocator
)
{
capacity_check:
  u32 capacity = next_pow2(initial_capacity);
  if (capacity < MAP_DEFAULT_CAP)
    capacity = MAP_DEFAULT_CAP;

initialize:
  u32 entry_typesize = key_typesize + value_typesize;
  u32 padded_capacity = capacity + MAP_PADDED_CAP;

  struct map map = {
    .capacity = capacity,
    .length = 0,
    .load_limit = map_load_limit(capacity),
    .key_typesize = key_typesize,
    .value_typesize = value_typesize,
    .entry_typesize = entry_typesize,
    .hashes = memory_alloc_zero(allocator, sizeof(u32) * padded_capacity),
    .entries = memory_alloc_zero(allocator, entry_typesize * padded_capacity),
    .allocator = allocator
  };

  return map;
}
