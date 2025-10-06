T* list<T>_at (
    list<T>* list,
    unsigned int position
)
{
  if (position < list->length)
    return list->data + position;

  fatal(f(position), ": overbound list position");
  return nullptr;
}
