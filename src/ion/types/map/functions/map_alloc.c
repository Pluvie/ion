map<K, V>* map<K, V>_alloc (
    int initial_capacity,
    memory* allocator,
    void* address
)
{
  map<K, V>* map;
  if (address == NULL) {
    map = memory_alloc_zero(allocator, sizeof(map<K, V>));
  } else {
    zero_out(address, sizeof(map<K, V>));
    map = address;
  }

  set<K>_alloc(initial_capacity, allocator, &(map->keys));
  map->values = memory_alloc_zero(allocator, map->keys.capacity * sizeof(V));
  map->length = 0;
  return map;
}
