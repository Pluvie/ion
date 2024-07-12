void* array_set (
    struct array* ary,
    u64 position,
    void* element
)
{
position_check:
  if (likely(position < ary->length))
    goto set;

abort:
  fprintf(stderr, "fatal: position %li out of bounds [%p]\n", position, ary);
  abort();

set:
  void* address = ary->data + (position * ary->typesize);
  memcpy(address, element, ary->typesize);
  return address;
}
