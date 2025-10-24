void* map<K, V>_reflection_adder (
    void* generic_map,
    void* generic_entry
)
{
  map<K, V>* map = (map<K, V>*) generic_map;
  struct { K* key; V* value; }* entry = generic_entry;
  unsigned int position = map<K, V>_set(map, *(entry->key), *(entry->value));
  return map->values + position;
}
