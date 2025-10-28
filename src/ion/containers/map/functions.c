#include "functions/map_set.c"
#include "functions/map_init.c"

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
