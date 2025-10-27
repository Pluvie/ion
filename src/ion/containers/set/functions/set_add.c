uint container_function(N, add) (
    struct N* set,
    T element
)
{
  uint position;

  if (set->length < set->load_limit)
    goto add;

  if (set->allocator != nullptr)
    goto rehash;

  /* If the set is stack-allocated (set->allocator == nullptr) and fully-loaded
   (set->length >= set->load_limit), and the element to be added is already present
   in the set, we want the `set_add` function to allow this operation without failing.
   Of course, adding an already present element to a set means, in reality, doing
   exactly nothing. */
  position = container_function(N, pos)(set, element);
  if (position != set_pos_invalid)
    return position;

  fatal("add: stack allocated set is full");
  return set_pos_invalid;


rehash:
  container_function(N, rehash)(set);

add:
  position = container_function(N, pos)(set, element);
  if (unlikely(position == set_pos_invalid)) {
    /* NOTE(Pluvie): this is dead code, a program should never reach this point due
     to how the load limit behaves. Nevertheless, a failing guard is placed just
     in case someone breaks this implementation. */
    fatal("add: load limit behavior not respected");
    return set_pos_invalid;
  }

  if (set_pos_is_free(set, position))
    goto occupy_pos;

  return position;

occupy_pos:
  set->data[position] = element;
  set_pos_occupy(set, position, container_hasher(element));
  set->length++;

  return position;
}
