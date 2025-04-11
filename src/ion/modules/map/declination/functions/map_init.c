map(kt, vt) map_(init, kt, vt) (
    u64 initial_capacity,
    memory* allocator
)
{
  u64 capacity = next_pow2(initial_capacity);
  if (capacity < MAP_CAPACITY_DEFAULT)
    capacity = MAP_CAPACITY_DEFAULT;

  u64 padded_capacity = capacity + MAP_CAPACITY_PADDING;

  map(kt, vt) m = {
    .capacity = capacity,
    .length = 0,
    .hashes = memory_alloc_zero(allocator, padded_capacity * sizeof(u64)),
    .keys = memory_alloc_zero(allocator, padded_capacity * sizeof(kt)),
    .values = memory_alloc_zero(allocator, padded_capacity * sizeof(vt)),
    .load_limit = map_load_limit(capacity),
    .allocator = allocator,
  };
  return m;
}
