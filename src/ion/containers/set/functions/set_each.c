bool set<T>_each (
    set<T>* set,
    struct iterator* iter
)
{
  iter->gate = ~0;

  for (; iter->position < set->capacity; iter->position++)
    if (set_pos_is_occupied(set, iter->position))
      return true;

  return false;
}
