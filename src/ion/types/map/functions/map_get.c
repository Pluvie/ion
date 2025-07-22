V* map<K, V>_get (
    map<K, V>* map,
    K key
)
{
  int position = set<K>_pos(&map->keys, key);

  if (position < 0)
    return NULL;

  if (set_pos_is_free(&map->keys, position))
    return NULL;

  return map->values + position;
}
