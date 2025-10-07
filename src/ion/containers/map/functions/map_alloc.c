map<K, V> map<K, V>_alloc (
    unsigned int initial_capacity,
    struct allocator* allocator
)
{
  map<K, V> map = { 0 };
  map.keys = set<K>_alloc(initial_capacity, allocator);
  map.values = allocator_push(allocator, map.keys.capacity * sizeof(V));
  memory_set(map.values, 0, map.keys.capacity * sizeof(K));
  return map;
}
