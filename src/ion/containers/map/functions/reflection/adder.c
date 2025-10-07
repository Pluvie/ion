unsigned int map<K, V>_reflection_adder (
    void* map,
    void* key
)
{
  return map<K, V>_set(map, *(K*) key, (V) { 0 });
}
