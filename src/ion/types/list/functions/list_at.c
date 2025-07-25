T* list<T>_at (
    list<T>* list,
    int position
)
{
  if (position >= 0 && position < list->length)
    return list->data + position;

  fail("%li: overbound list position", position);
  return NULL;
}
