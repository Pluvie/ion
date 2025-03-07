#ifdef ION_INCLUDED
static inline
#endif

void* array_pop (
    struct array* ary
)
{
  if (unlikely(ary->length == 0)) {
    fail("array at 0 length.");
    return NULL;
  }

  ary->length--;
  void* address = ary->data + (ary->length * ary->typesize);
  return address;
}
