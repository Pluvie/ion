#ifdef ION_INCLUDED
static inline
#endif

void buffer_release (
    struct buffer* allocator
)
{
  if (allocator->data != NULL)
    free(allocator->data);

  memzero(allocator, sizeof(struct buffer));
}
