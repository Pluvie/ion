set<T>* set<T>_alloc (
    int initial_capacity,
    memory* allocator
)
{
  int capacity = initial_capacity;
  if (initial_capacity < 16)
    capacity = 16;
  else
    capacity = next_pow2(initial_capacity);

  set<T>* set = memory_alloc_zero(allocator, sizeof(set<T>));
  set->capacity = capacity;
  set->allocator = allocator;
  set->data = memory_alloc_zero(allocator, capacity * sizeof(T));
  set->hashes = memory_alloc_zero(allocator, capacity * sizeof(int));
  set->load_limit = set_load_limit(set);
  return set;
}
