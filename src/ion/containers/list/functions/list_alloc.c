list<T>* list<T>_alloc (
    unsigned int initial_capacity,
    struct allocator* allocator,
    void* address
)
{
  int capacity = initial_capacity;
  if (initial_capacity < 16)
    capacity = 16;
  else
    capacity = next_pow2(initial_capacity);

  list<T>* list;

  if (address == nullptr) {
    list = allocator_push(allocator, sizeof(list<T>));
    memory_set(list, 0, sizeof(list<T>));
  } else {
    memory_set(address, 0, sizeof(list<T>));
    list = address;
  }

  list->capacity = capacity;
  list->allocator = allocator;
  list->data = allocator_push(allocator, capacity * sizeof(T));
  memory_set(list->data, 0, capacity * sizeof(T));
  return list;
}
