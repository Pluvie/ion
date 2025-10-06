list<T> list<T>_alloc (
    unsigned int initial_capacity,
    struct allocator* allocator
)
{
  unsigned int capacity = initial_capacity;
  if (initial_capacity < 16)
    capacity = 16;
  else
    capacity = next_pow2(initial_capacity);

  list<T> list = { 0 };

  list.capacity = capacity;
  list.allocator = allocator;
  list.data = allocator_push(allocator, capacity * sizeof(T));
  memory_set(list.data, 0, capacity * sizeof(T));

  return list;
}
