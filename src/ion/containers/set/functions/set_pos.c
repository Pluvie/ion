unsigned int set<T>_pos (
    set<T>* set,
    T element
)
{
#ifdef set_hash_function
  unsigned int element_hash = set_hash_function(element); 
#else
  unsigned int element_hash = hash_djb2(&element, sizeof(T)); 
#endif

  unsigned int probe_index = element_hash & (set->capacity - 1);
  unsigned int probe_index_limit = set->capacity - 1;
  unsigned int initial_probe_index = probe_index;

linear_probing:
  T* probed_element = set->data + probe_index;

  if (set_pos_is_free(set, probe_index))
    return probe_index;

#ifdef set_cmp_function
  if (set_cmp_function(element, (*probed_element)))
#else
  if (memory_equal((&element), probed_element, sizeof(T)))
#endif
    return probe_index;

  probe_index++;
  if (probe_index > probe_index_limit)
    probe_index = 0;

  if (probe_index != initial_probe_index)
    goto linear_probing;

  return (unsigned int) -1;
}
