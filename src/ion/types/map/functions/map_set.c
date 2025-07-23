int map<K, V>_set (
    map<K, V>* map,
    K key,
    V value
)
{
  int position = set<K>_add(&map->keys, key);
  if (position == -1) {
    fail("set: stack allocated map is full");
    return -1;
  }

  map->values[position] = value;
  map->length = map->keys.length;

  return position;
}
