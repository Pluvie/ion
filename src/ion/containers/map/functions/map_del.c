V* map<K, V>_del (
    map<K, V>* map,
    K key
)
{
  unsigned int position = set<K>_del(&map->keys, key);

  if (position == (unsigned int) -1)
    return nullptr;

  map->length = map->keys.length;
  return map->values + position;
}

