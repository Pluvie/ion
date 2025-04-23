t* set_add(t) (
    set(t)* set,
    t* element
)
{
  u64 element_hash = set_hasher(t)(element);
  u64 probe_index = element_hash & (set->capacity - 1);
  u64 probe_index_limit = set->capacity + SET_CAPACITY_PADDING - 1;

linear_probing:
  t* probed_element = set_element_at(set, probe_index);
  if (set_entry_is_empty(set, probe_index))
    goto set_element_new;

  if (set_comparer(t)(element, probed_element))
    goto set_element_existing;

  probe_index++;
  if (probe_index >= probe_index_limit)
    probe_index = 0;

  goto linear_probing;

set_element_new:
  *probed_element = *element;
  set_entry_occupy(set, probe_index, element_hash);
  set->length++;

set_element_existing:
  /* Nothing to do. */

  if (set->length >= set->load_limit)
    set_rehash(t)(set);

  return element;
}
