unsigned int set<T>_pos (
    set<T>* set,
    T element
)
{
  int element_hash = hash(element);
  int probe_index = element_hash & (set->capacity - 1);
  int probe_index_limit = set->capacity - 1;
  int initial_probe_index = probe_index;

linear_probing:
  T* probed_element = set->data + probe_index;

  if (set_pos_is_free(set, probe_index))
    return probe_index;

  if (eq(element, *probed_element))
    return probe_index;

  probe_index++;
  if (probe_index > probe_index_limit)
    probe_index = 0;

  if (probe_index != initial_probe_index)
    goto linear_probing;

  return -1;
}
