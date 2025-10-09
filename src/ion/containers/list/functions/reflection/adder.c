void* list<T>_reflection_adder (
    void* generic_list,
    void* generic_element
)
{
  list<T>* list = (list<T>*) generic_list;
  unsigned int position = list<T>_push(list, *(T*) generic_element);
  return list->data + position;
}
