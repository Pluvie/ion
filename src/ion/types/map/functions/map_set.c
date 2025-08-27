int map<K, V>_set (
    map<K, V>* map,
    K key,
    V value
)
{
  int capacity = map->keys.capacity;
  int position = set<K>_add(&map->keys, key);
  if (position == -1) {
    fail("set: stack allocated map is full");
    return -1;
  }

  if (map->keys.capacity > capacity) {
    V* new_values = memory_alloc_zero(
      map->keys.allocator, map->keys.capacity * sizeof(V));
    byte_copy(new_values, map->values, capacity);
    map->values = new_values;
  }

  map->values[position] = value;
  map->length = map->keys.length;

  return position;
}
