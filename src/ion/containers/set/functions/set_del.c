unsigned int set<T>_del (
    set<T>* set,
    T element
)
{
  unsigned int position = set<T>_pos(set, element);
  if (position == (unsigned int) -1)
    return (unsigned int) -1;

  if (set_pos_is_free(set, position))
    return (unsigned int) -1;

  set_pos_free(set, position);
  set->length--;
  return position;
}
