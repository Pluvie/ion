#ifdef ION_INCLUDED
static inline
#endif

struct vector* vector_allocate (
    u64 typesize,
    u64 length,
    struct memory* allocator
)
{
  struct vector* vector = memory_alloc_zero(allocator, sizeof(struct vector));
  *vector = vector_init(typesize, length, allocator);
  return vector;
}
