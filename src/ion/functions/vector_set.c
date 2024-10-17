#ifdef ION_INCLUDED
static inline
#endif

void* vector_set (
    struct vector* vec,
    u64 position,
    void* element
)
{
position_check:
  if (likely(position < vec->length))
    goto set;

abort:
  fprintf(stderr,
    "fatal: position %li out of bounds [%p]\n",
    position, vec);

  abort();

set:
  void* address = vec->data + (position * vec->typesize);
  memcpy(address, element, vec->typesize);
  return address;
}
