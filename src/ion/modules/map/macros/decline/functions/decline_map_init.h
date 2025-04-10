#define decline_map_init(kt, vt)                                                    _L_ \
                                                                                    _L_ \
map(kt, vt) map_init(kt, vt) (                                                      _L_ \
    u64 initial_capacity,                                                           _L_ \
    memory* allocator                                                               _L_ \
)                                                                                   _L_ \
{                                                                                   _L_ \
  u64 capacity = next_pow2(initial_capacity);                                       _L_ \
  if (capacity < MAP_CAPACITY_DEFAULT)                                              _L_ \
    capacity = MAP_CAPACITY_DEFAULT;                                                _L_ \
                                                                                    _L_ \
  u64 padded_capacity = capacity + MAP_CAPACITY_PADDING;                            _L_ \
                                                                                    _L_ \
  map(kt, vt) m = {                                                                 _L_ \
    .capacity = capacity,                                                           _L_ \
    .length = 0,                                                                    _L_ \
    .hashes = memory_alloc_zero(allocator, padded_capacity * sizeof(u64)),          _L_ \
    .keys = memory_alloc_zero(allocator, padded_capacity * sizeof(kt)),             _L_ \
    .values = memory_alloc_zero(allocator, padded_capacity * sizeof(vt)),           _L_ \
    .load_limit = map_load_limit(capacity),                                         _L_ \
    .allocator = allocator,                                                         _L_ \
  };                                                                                _L_ \
  return m;                                                                         _L_ \
}
