t* set_del(t) (
    set(t)* set,
    t* element
)
{
  u64 element_hash = set_hasher(t)(element);
  u64 probe_index = element_hash & (set->capacity - 1);
  u64 probe_index_limit = set->capacity + SET_CAPACITY_PADDING - 1;

linear_probing:
  if (set_comparer(t)(element, set_element_at(set, probe_index))) {
    set_entry_free(set, probe_index);
    set->length--;
    return set_element_at(set, probe_index);
  }

  if (set_entry_is_empty(set, probe_index))
    return NULL;

  probe_index++;
  if (probe_index >= probe_index_limit)
    probe_index = 0;

  goto linear_probing;
}
