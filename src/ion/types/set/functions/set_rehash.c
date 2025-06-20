void set<T>_rehash (
    set<T>* set
)
{
  int new_capacity = set->capacity * 2;
  set<T>* rehashed_set = set_alloc(T, new_capacity, set->allocator);

  for (int i = 0; i < set->capacity; i++) {
    if (set_pos_is_free(set, i))
      continue;

    T* element = set->data + i;
    set<T>_add(rehashed_set, *element);
  }

  set->capacity = new_capacity;
  set->data = rehashed_set->data;
  set->hashes = rehashed_set->hashes;
  set->load_limit = set_load_limit(rehashed_set);
}
