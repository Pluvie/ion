#ifdef ION_INCLUDED
static inline
#endif

void* buffer_data (
    struct buffer* allocator,
    u64 position
)
{
  return allocator->data + position;
}
