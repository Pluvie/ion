void* list<T>_reflection_creator (
    unsigned int capacity,
    struct allocator* allocator
)
{
  return list<T>_alloc(capacity, allocator);
}
