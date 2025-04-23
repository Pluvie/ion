void set_rehash(t) (
    set(t)* set
)
{
  u64 new_capacity = set->capacity * 2;
  set(t) rehashed_set = set_init(t)(new_capacity, set->allocator);

  for (u64 i = 0; i < set->capacity + SET_CAPACITY_PADDING; i++) {
    if (set_entry_is_empty(set, i))
      continue;

    t* element = set_element_at(set, i);
    set_add(t)(&rehashed_set, element);
  }

  set->capacity = new_capacity;
  set->hashes = rehashed_set.hashes;
  set->elements = rehashed_set.elements;
  set->load_limit = set_load_limit(new_capacity);
}
