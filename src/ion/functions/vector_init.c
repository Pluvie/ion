#ifdef ION_INCLUDED
static inline
#endif

struct vector vector_init (
    u64 typesize,
    u64 length,
    struct memory* allocator
)
{
  struct vector vector = {
    .typesize = typesize,
    .length = length,
    .data = memory_alloc_zero(allocator, typesize * length),
  };

  return vector;
}
