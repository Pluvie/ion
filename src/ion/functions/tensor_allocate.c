#ifdef ION_INCLUDED
static inline
#endif

struct tensor* tensor_allocate (
    u64 typesize,
    struct vector* input_dimensions,
    struct memory* allocator
)
{
  struct tensor* tensor = memory_alloc_zero(allocator, sizeof(struct tensor));
  *tensor = tensor_init(typesize, input_dimensions, allocator);
  return tensor;
}
