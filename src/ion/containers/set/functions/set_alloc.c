set<T>* set<T>_alloc (
    unsigned int initial_capacity,
    struct allocator* allocator
)
{
  unsigned int capacity = initial_capacity;
  if (initial_capacity < 16)
    capacity = 16;
  else
    capacity = next_pow2(initial_capacity);

  set<T>* set = allocator_push(allocator, sizeof(set<T>));
  memory_set(set, 0, sizeof(set<T>));

  set->capacity = capacity;
  set->allocator = allocator;
  set->data = allocator_push(allocator, capacity * sizeof(T));
  set->hashes = allocator_push(allocator, capacity * sizeof(unsigned int));
  set->load_limit = set_load_limit(set);

  memory_set(set->data, 0, capacity * sizeof(T));
  memory_set(set->hashes, 0, capacity * sizeof(unsigned int));

  return set;
}
