int list<T>_reflection_adder (
    void* list,
    void* element
)
{
  return list<T>_push(list, *(T*) element);
}

void* list<T>_reflection_creator (
    int capacity,
    memory* allocator
)
{
  return list<T>_alloc(capacity, allocator);
}
