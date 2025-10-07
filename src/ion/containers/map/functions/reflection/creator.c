void map<K, V>_reflection_creator (
    void* address,
    unsigned int initial_capacity,
    struct allocator* allocator
)
{
  map<K, V> map = map<K, V>_alloc(initial_capacity, allocator);
  memory_copy(address, &map, sizeof(map));
}
