void* buffer_pointer_at (
    struct buffer* allocator,
    uint position
)
{
  if (unlikely(position >= allocator->position))
    fatal("buffer overflow");

  return ((byte*) allocator->data) + position;
}
