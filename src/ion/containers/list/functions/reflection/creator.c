void list<T>_reflection_creator (
    void* address,
    unsigned int initial_capacity,
    struct allocator* allocator
)
{
  list<T> list = list<T>_alloc(initial_capacity, allocator);
  memory_copy(address, &list, sizeof(list));
}
