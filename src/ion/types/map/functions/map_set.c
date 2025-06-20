int map<K, V>_set (
    map<K, V>* map,
    K key,
    V value
)
{
  if (map->keys.length < map->keys.load_limit)
    goto set;
  else
    goto rehash;

rehash:
  if (map->keys.allocator != NULL)
    set<K>_rehash(&map->keys);
  else
    return -1;

set:
  int position = set<K>_add(&map->keys, key);
  map->values[position] = value;
  map->length = map->keys.length;

  return position;
}
