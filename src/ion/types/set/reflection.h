int set<T>_reflection_adder (
    void* set,
    void* element
)
{
  return set<T>_add(set, *(T*) element);
}

void* set<T>_reflection_creator (
    int capacity,
    memory* allocator
)
{
  return set<T>_alloc(capacity, allocator);
}
