unsigned int list<T>_push (
    list<T>* list,
    T element
)
{
  if (list->length < list->capacity)
    goto push;
  else
    goto grow;

grow:
  if (list->allocator == nullptr)
    fatal("push: stack allocated list is full");

  list->capacity *= 2;
  T* new_data = allocator_push(list->allocator, list->capacity * sizeof(T));
  memory_set(new_data, 0, list->capacity * sizeof(T));
  memory_copy(new_data, list->data, list->length * sizeof(T));
  list->data = new_data;

push:
  unsigned int position = list->length;
  list->data[list->length] = element;
  list->length++;
  return position;
}
