bool list<T>_each (
    list<T>* list,
    struct iterator* iter
)
{
  iter->gate = ~0;

  if (iter->position < list->length)
    return true;

  return false;
}
