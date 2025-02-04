#ifdef ION_INCLUDED
static inline
#endif

void buffer_release (
    struct buffer* allocator
)
{
  free(allocator->data);

  memzero(allocator, sizeof(struct buffer));
}
