unsigned int list<T>_del (
    list<T>* list,
    T element
)
{
  T previous = { 0 };

  for(int i = list->length - 1; i >= 0; i--) {
  #ifdef list_eq_function
    if (list_eq_function(element, list->data[i])) {
  #else
    if (memory_equal((&element), list->data + i, sizeof(T))) {
  #endif
      memory_copy(list->data + i, &previous, sizeof(T));
      list->length--;
      return (unsigned int) i;
    }

    T temp = { 0 };
    memory_copy(&temp, list->data + i, sizeof(T));
    memory_copy(list->data + i, &previous, sizeof(T));
    memory_copy(&previous, &temp, sizeof(T));
  }

  return (unsigned int) -1;
}
