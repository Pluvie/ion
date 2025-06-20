map<K, V>* map<K, V>_alloc (
    int initial_capacity,
    memory* allocator
)
{
  map<K, V>* map = memory_alloc_zero(allocator, sizeof(map<K, V>));
  map->keys = *set<K>_alloc(initial_capacity, allocator);
  map->values = memory_alloc_zero(allocator, map->keys.capacity * sizeof(V));
  map->length = 0;
  return map;
}
