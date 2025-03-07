#ifdef ION_INCLUDED
static inline
#endif

struct array* array_allocate (
    u64 typesize,
    u64 initial_capacity,
    struct memory* allocator
)
{
  struct array* array = memory_alloc_zero(allocator, sizeof(struct array));
  *array = array_init(typesize, initial_capacity, allocator);
  return array;
}
