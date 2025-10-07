unsigned int map<K, V>_set (
    map<K, V>* map,
    K key,
    V value
)
{
  unsigned int capacity = map->keys.capacity;
  unsigned int position = set<K>_add(&map->keys, key);
  if (position == (unsigned int) -1) {
    fatal("set: stack allocated map is full");
    return (unsigned int) -1;
  }

  if (map->keys.capacity > capacity) {
    V* new_values = allocator_push(map->keys.allocator, map->keys.capacity * sizeof(V));
    memory_set(new_values, 0, map->keys.capacity * sizeof(V));
    memory_copy(new_values, map->values, capacity);
    map->values = new_values;
  }

  map->values[position] = value;
  map->length = map->keys.length;

  return position;
}
