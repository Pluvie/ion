void* set<T>_reflection_adder (
    void* generic_set,
    void* generic_element
)
{
  set<T>* set = (set<T>*) generic_set;
  unsigned int position = set<T>_add(set, *(T*) generic_element);
  return set->data + position;
}
