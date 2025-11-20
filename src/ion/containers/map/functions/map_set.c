uint container_function(N, set) (
    struct N* map,
    K key,
    V value
)
{
  uint capacity = map->keys.capacity;
  uint position = container_function(S, add)(&map->keys, key);
  if (position == set_pos_invalid) {
    fatal("map_set: stack allocated map is full");
    return set_pos_invalid;
  }

  if (map->keys.capacity > capacity) {
    V* new_values = arena_push(map->keys.allocator, map->keys.capacity * sizeof(V));
    memory_set(new_values, 0, map->keys.capacity * sizeof(V));
    memory_copy(new_values, map->values, capacity);
    map->values = new_values;
  }

  map->values[position] = value;
  map->length = map->keys.length;

  return position;
}
