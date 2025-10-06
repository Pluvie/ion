void set<T>_rehash (
    set<T>* set
)
{
  unsigned int new_capacity = set->capacity * 2;

  set<T> rehashed_set = { 0 };
  rehashed_set.capacity = new_capacity;
  rehashed_set.data = allocator_push(set->allocator, new_capacity * sizeof(T));
  rehashed_set.hashes = allocator_push(set->allocator, new_capacity * sizeof(unsigned int));
  rehashed_set.load_limit = set_load_limit(&rehashed_set);

  memory_set(rehashed_set.data, 0, new_capacity * sizeof(T));
  memory_set(rehashed_set.hashes, 0, new_capacity * sizeof(unsigned int));

  for (unsigned int i = 0; i < set->capacity; i++) {
    if (set_pos_is_free(set, i))
      continue;

    T* element = set->data + i;
    set<T>_add(&rehashed_set, *element);
  }

  set->capacity = new_capacity;
  set->data = rehashed_set.data;
  set->hashes = rehashed_set.hashes;
  set->load_limit = set_load_limit(&rehashed_set);
}
