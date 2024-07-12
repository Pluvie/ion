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
  u64 probed_capacity = capacity + log2(capacity);

  struct map map = {
    .capacity = capacity,
    .length = 0,
    .key_typesize = key_typesize,
    .value_typesize = value_typesize,
    .keys = memory_alloc(allocator, key_typesize * probed_capacity),
    .values = memory_alloc(allocator, value_typesize * probed_capacity),
    .hashes = memory_alloc(allocator, sizeof(u64) * probed_capacity),
    .allocator = allocator
  };

  memset(map.hashes, 0xff, sizeof(u64) * probed_capacity);

  return map;
}
