V* map<K, V>_del (
    map<K, V>* map,
    K key
)
{
  int position = set<K>_del(&map->keys, key);

  if (position < 0)
    return NULL;

  map->length = map->keys.length;
  return map->values + position;
}
