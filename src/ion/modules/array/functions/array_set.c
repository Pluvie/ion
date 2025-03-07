#ifdef ION_INCLUDED
static inline
#endif

void* array_set (
    struct array* ary,
    u64 position,
    void* element
)
{
  if (unlikely(position >= ary->length)) {
    fail("position %li out of bounds.", position);
    return NULL;
  }

  void* address = ary->data + (position * ary->typesize);
  memcpy(address, element, ary->typesize);
  return address;
}
