#include "functions/map_each.c"
#include "functions/map_init.c"
#include "functions/map_literal.c"
#include "functions/map_set.c"

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
