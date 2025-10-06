unsigned int set<T>_add (
    set<T>* set,
    T element
)
{
  if (set->length < set->load_limit)
    goto add;

  if (set->allocator != NULL)
    goto rehash;

  /* If the set is stack-allocated (set->allocator == nullptr) and fully-loaded
   * (set->length >= set->load_limit), and the element to be added is already present
   * in the set, we want the `set_add` function to allow this operation without failing.
   * Of course, adding an already present element to a set means, in reality, doing
   * exactly nothing. */
  unsigned int position = set<T>_pos(set, element);
  if (position != (unsigned int) -1)
    return position;

  fatal("add: stack allocated set is full");
  return (unsigned int) -1;


rehash:
  set<T>_rehash(set);

add:
  position = set<T>_pos(set, element);
  if (unlikely(position == (unsigned int) -1)) {
    /* NOTE(Pluvie): this is dead code, a program should never reach this point due
     * to how the load limit behaves. Nevertheless, a failing guard is placed just
     * in case someone breaks this implementation. */
    fatal("add: load limit behavior not respected");
    return (unsigned int) -1;
  }

  if (set_pos_is_free(set, position))
    goto occupy_pos;

  return position;

occupy_pos:
  set->data[position] = element;
  set_pos_occupy(set, position, hash(element));
  set->length++;

  return position;
}
