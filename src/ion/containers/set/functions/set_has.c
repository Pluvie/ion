bool set<T>_has (
    set<T>* set,
    T element
)
{
  unsigned int position = set<T>_pos(set, element);
  if (position == (unsigned int) -1)
    return false;

  return set_pos_is_occupied(set, position);
}
