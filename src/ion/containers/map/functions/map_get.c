V* map<K, V>_get (
    map<K, V>* map,
    K key
)
{
  unsigned int position = set<K>_pos(&map->keys, key);

  if (position == (unsigned int) -1)
    return nullptr;

  if (set_pos_is_free(&map->keys, position))
    return nullptr;

  return map->values + position;
}
