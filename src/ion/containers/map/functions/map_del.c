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
