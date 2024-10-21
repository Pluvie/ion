#ifdef ION_INCLUDED
static inline
#endif

void* array_get (
    struct array* ary,
    u64 position
)
{
  if (unlikely(position >= ary->length)) {
    fail("position %li out of bounds.", position);
    return NULL;
  }

  return ary->data + (position * ary->typesize);
}
