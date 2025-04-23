set(t) set_init(t) (
    u64 initial_capacity,
    memory* allocator
)
{
  u64 capacity = next_pow2(initial_capacity);
  if (capacity < SET_CAPACITY_DEFAULT)
    capacity = SET_CAPACITY_DEFAULT;

  u64 padded_capacity = capacity + SET_CAPACITY_PADDING;

  set(t) set = {
    .capacity = capacity,
    .length = 0,
    .hashes = memory_alloc_zero(allocator, padded_capacity * sizeof(u64)),
    .elements = memory_alloc_zero(allocator, padded_capacity * sizeof(t)),
    .load_limit = set_load_limit(capacity),
    .allocator = allocator,
  };
  return set;
}
