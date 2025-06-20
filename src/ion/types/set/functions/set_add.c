int set<T>_add (
    set<T>* set,
    T element
)
{
  if (set->length < set->load_limit)
    goto add;
  else
    goto rehash;

rehash:
  if (set->allocator != NULL)
    set<T>_rehash(set);
  else
    return -1;

add:
  int position = set<T>_pos(set, element);
  if (position == -1)
    return -1;

  if (set_pos_is_free(set, position))
    goto occupy_pos;

  return position;

occupy_pos:
  set->data[position] = element;
  set_pos_occupy(set, position, hash(element));
  set->length++;

  return position;
}
