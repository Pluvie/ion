#ifdef ION_INCLUDED
static inline
#endif

void* vector_get (
    struct vector* vec,
    u64 position
)
{
position_check:
  if (likely(position < vec->length))
    goto get;

abort:
  fprintf(stderr,
    "fatal: position %li out of bounds [%p]\n",
    position, vec);

  abort();

get:
  return vec->data + (position * vec->typesize);
}
