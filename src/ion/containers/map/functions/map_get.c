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
