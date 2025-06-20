list<T>* list<T>_alloc (
    int initial_capacity,
    memory* allocator
)
{
  int capacity = initial_capacity;
  if (initial_capacity < 16)
    capacity = 16;
  else
    capacity = next_pow2(initial_capacity);

  list<T>* list = memory_alloc_zero(allocator, sizeof(list<T>));
  list->capacity = capacity;
  list->allocator = allocator;
  list->data = memory_alloc_zero(allocator, capacity * sizeof(T));
  return list;
}
