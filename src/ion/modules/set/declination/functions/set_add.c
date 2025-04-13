t* set_add(t) (
    set(t)* s,
    t* element
)
{
  u64 element_hash = set_hasher(t)(element);
  u64 probe_index = element_hash & (s->capacity - 1);
  u64 probe_index_limit = s->capacity + MAP_CAPACITY_PADDING - 1;

linear_probing:
  t* probed_element = set_element_at(s, probe_index);
  if (set_entry_is_empty(s, probe_index))
    goto set_element_new;

  if (set_comparer(t)(element, probed_element))
    goto set_element_existing;

  probe_index++;
  if (probe_index >= probe_index_limit)
    probe_index = 0;

  goto linear_probing;

set_element_new:
  *probed_element = *element;
  set_entry_occupy(s, probe_index, element_hash);
  s->length++;

set_element_existing:
  /* Nothing to do. */

  if (s->length >= s->load_limit)
    set_rehash(t)(s);

  return element;
}
