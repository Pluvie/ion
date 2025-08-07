int map<K, V>_reflection_adder (
    void* map,
    void* key
)
{
  return map<K, V>_set(map, *(K*) key, (V) { 0 });
}

void* map<K, V>_reflection_creator (
    int capacity,
    memory* allocator,
    void* address
)
{
  return map<K, V>_alloc(capacity, allocator, address);
}
