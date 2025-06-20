T* list<T>_pop (
    list<T>* list
)
{
  if (list->length > 0)
    goto pop;

  return NULL;

pop:
  T* element = list->data + list->length - 1;
  list->length--;
  return element;
}
