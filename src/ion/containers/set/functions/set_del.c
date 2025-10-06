unsigned int set<T>_del (
    set<T>* set,
    T element
)
{
  int position = set<T>_pos(set, element);
  if (position < 0)
    return -1;

  if (set_pos_is_free(set, position))
    return -1;

  set_pos_free(set, position);
  set->length--;
  return position;
}
