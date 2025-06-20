bool set<T>_has (
    set<T>* set,
    T element
)
{
  int position = set<T>_pos(set, element);
  if (position < 0)
    return false;

  return set_pos_is_occupied(set, position);
}
