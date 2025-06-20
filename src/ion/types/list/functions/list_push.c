bool list<T>_push (
    list<T>* list,
    T element
)
{
  if (list->length < list->capacity)
    goto push;
  else
    goto grow;

grow:
  if (list->allocator == NULL)
    return false;

  list->capacity *= 2;
  T* new_data = memory_alloc_zero(list->allocator, list->capacity * sizeof(T));
  memcpy(new_data, list->data, list->length * sizeof(T));
  list->data = new_data;

push:
  list->data[list->length] = element;
  list->length++;
  return true;
}
