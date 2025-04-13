t* set_del(t) (
    set(t)* s,
    t* element
)
{
  u64 element_hash = set_hasher(t)(element);
  u64 probe_index = element_hash & (s->capacity - 1);
  u64 probe_index_limit = s->capacity + MAP_CAPACITY_PADDING - 1;

linear_probing:
  if (set_comparer(t)(element, set_element_at(s, probe_index))) {
    set_entry_free(s, probe_index);
    s->length--;
    return set_element_at(s, probe_index);
  }

  if (set_entry_is_empty(s, probe_index))
    return NULL;

  probe_index++;
  if (probe_index >= probe_index_limit)
    probe_index = 0;

  goto linear_probing;
}
