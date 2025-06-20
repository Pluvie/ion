bool map<K, V>_each (
    map<K, V>* map,
    struct iterator* iter
)
{
  iter->gate = ~0;

  for (; iter->position < map->keys.capacity; iter->position++)
    if (set_pos_is_occupied(&map->keys, iter->position))
      return true;

  return false;
}
