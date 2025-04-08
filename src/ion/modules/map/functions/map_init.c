#ifdef ION_INCLUDED
static inline
#endif

struct map map_init (
    u32 key_typesize,
    u32 value_typesize,
    u64 initial_capacity,
    struct memory* allocator
)
{
capacity_check:
  u64 capacity = next_pow2(initial_capacity);
  if (capacity < MAP_DEFAULT_CAP)
    capacity = MAP_DEFAULT_CAP;

initialize:
  if (key_typesize < sizeof(u64))
    key_typesize = sizeof(u64);

  //u32 entry_typesize = sizeof(u64) + key_typesize + value_typesize;
  u64 padded_capacity = capacity + MAP_PADDED_CAP;

  struct map map = {
    .capacity = capacity,
    .length = 0,
    .load_limit = map_load_limit(capacity),
    .key_typesize = key_typesize,
    .value_typesize = value_typesize,
    //.entry_typesize = entry_typesize,
    //.hash_typesize = sizeof(u64),
    //.entries = memory_alloc_zero(allocator, entry_typesize * padded_capacity),
    .hashes = memory_alloc_zero(allocator, sizeof(u64) * padded_capacity),
    .keys = memory_alloc_zero(allocator, key_typesize * padded_capacity),
    .values = memory_alloc_zero(allocator, value_typesize * padded_capacity),
    .allocator = allocator
  };

  return map;
}
