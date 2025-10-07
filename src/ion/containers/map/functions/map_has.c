bool map<K, V>_has (
    map<K, V>* map,
    K key
)
{
  return set<K>_has(&map->keys, key);
}
