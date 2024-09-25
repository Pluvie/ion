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
  call(fprintf,
    stderr,
    "fatal: position %li out of bounds [%p]\n",
    position, ary);

  abort();

set:
  initialize(address, void*,
    pointer_offset(ary->data, position * ary->typesize));

  call(memcpy,
    address, element, ary->typesize);

  return address;
}
