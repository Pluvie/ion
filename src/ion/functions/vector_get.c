#ifdef ION_INCLUDED
static inline
#endif

void* vector_get (
    struct vector* vec,
    u64 position
)
{
  if (unlikely(position >= vec->length)) {
    fail("position %li out of bounds.", position);
    return NULL;
  }

  return vec->data + (position * vec->typesize);
}
