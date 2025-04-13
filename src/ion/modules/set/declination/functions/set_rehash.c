void set_rehash(t) (
    set(t)* s
)
{
  u64 new_capacity = s->capacity * 2;
  set(t) rehashed_set = set_init(t)(new_capacity, s->allocator);

  for (u64 i = 0; i < s->capacity + MAP_CAPACITY_PADDING; i++) {
    if (set_entry_is_empty(s, i))
      continue;

    t* element = set_element_at(s, i);
    set_add(t)(&rehashed_set, element);
  }

  s->capacity = new_capacity;
  s->hashes = rehashed_set.hashes;
  s->elements = rehashed_set.elements;
  s->load_limit = set_load_limit(new_capacity);
}
