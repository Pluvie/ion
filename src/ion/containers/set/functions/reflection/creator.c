void set<T>_reflection_creator (
    void* address,
    unsigned int initial_capacity,
    struct allocator* allocator
)
{
  set<T> set = set<T>_alloc(initial_capacity, allocator);
  memory_copy(address, &set, sizeof(set));
}
