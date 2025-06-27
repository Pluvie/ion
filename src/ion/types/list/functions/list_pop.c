T* list<T>_pop (
    list<T>* list
)
{
  if (list->length > 0)
    goto pop;

  fail("pop: empty list");
  return NULL;

pop:
  T* element = list->data + list->length - 1;
  list->length--;
  return element;
}
