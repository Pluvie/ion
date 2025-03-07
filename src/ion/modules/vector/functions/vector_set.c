#ifdef ION_INCLUDED
static inline
#endif

void* vector_set (
    struct vector* vec,
    u64 position,
    void* element
)
{
  if (unlikely(position >= vec->length)) {
    fail("position %li out of bounds.", position);
    return NULL;
  }

  void* address = vec->data + (position * vec->typesize);
  memcpy(address, element, vec->typesize);
  return address;
}
