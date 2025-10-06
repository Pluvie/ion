unsigned int list<T>_reflection_adder (
    void* list,
    void* element
)
{
  return list<T>_push(list, *(T*) element);
}
