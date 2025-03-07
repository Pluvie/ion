#ifdef ION_INCLUDED
static inline
#endif

void* array_last (
    struct array* ary
)
{
  if (unlikely(ary->length == 0)) {
    fail("array at 0 length.");
    return NULL;
  }

  return ary->data + ((ary->length - 1) * ary->typesize);
}
