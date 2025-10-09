void* map<K, V>_reflection_adder (
    void* generic_map,
    void* generic_key
)
{
  map<K, V>* map = (map<K, V>*) generic_map;
  unsigned int position = map<K, V>_set(map, *(K*) generic_key, (V) { 0 });
  return map->values + position;
}
