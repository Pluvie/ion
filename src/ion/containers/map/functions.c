struct N container_function(N, alloc) (
    uint initial_capacity,
    struct allocator* allocator
)
{
  struct N map = { 0 };
  map.keys = container_function(S, alloc)(initial_capacity, allocator);
  map.values = allocator_push(allocator, map.keys.capacity * sizeof(V));
  memory_set(map.values, 0, map.keys.capacity * sizeof(K));
  return map;
}

V* container_function(N, del) (
    struct N* map,
    K key
)
{
  uint position = container_function(S, del)(&map->keys, key);

  if (position == set_pos_invalid)
    return nullptr;

  map->length = map->keys.length;
  return map->values + position;
}

/*
bool container_function(N, each) (
    struct N* map,
    struct iterator* iter
)
{
  iter->gate = ~0;

  for (; iter->position < map->keys.capacity; iter->position++)
    if (set_pos_is_occupied(&map->keys, iter->position))
      return true;

  return false;
}
*/

V* container_function(N, get) (
    struct N* map,
    K key
)
{
  uint position = container_function(S, pos)(&map->keys, key);

  if (position == set_pos_invalid)
    return nullptr;

  if (set_pos_is_free(&map->keys, position))
    return nullptr;

  return map->values + position;
}

bool container_function(N, has) (
    struct N* map,
    K key
)
{
  return container_function(S, has)(&map->keys, key);
}

/*
struct N container_function(N, init) (
    uint capacity,
    K* keys,
    V* values,
    uint* hashes
)
{
  return (struct N) {
    .keys = container_function(S, init)(capacity, keys, hashes),
    .values = values,
  };
}

struct N container_function(N, literal) (
    uint capacity,
    K* keys,
    V* values,
    uint* hashes,
    void* pairs
)
{
  struct { K key; V value; }* key_value_pairs = pairs;

  for (uint i = 0; i < capacity; i++) {
    K key = key_value_pairs[i].key;
    V value = key_value_pairs[i].value;
    keys[i] = key;
    values[i] = value;
  }

  struct N map = {
    .keys = container_function(S, literal)(capacity, keys, hashes),
    .values = values,
    .length = capacity,
  };

  return map;
}
*/

uint container_function(N, set) (
    struct N* map,
    K key,
    V value
)
{
  uint capacity = map->keys.capacity;
  uint position = container_function(S, add)(&map->keys, key);
  if (position == set_pos_invalid) {
    fatal("set: stack allocated map is full");
    return set_pos_invalid;
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
