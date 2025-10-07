unsigned int set<T>_reflection_adder (
    void* set,
    void* element
)
{
  return set<T>_add(set, *(T*) element);
}
