void list<T>_sort (
    list<T>* list,
    int (*cmp_function)(T* v, T* u)
)
{
  qsort(list->data, list->length, sizeof(T),
    (int0 (*)(const void*, const void*)) cmp_function);
}
