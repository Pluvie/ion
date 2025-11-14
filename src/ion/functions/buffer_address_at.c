void* buffer_address_at (
    struct buffer* buffer,
    uint position
)
{
  if (unlikely(position >= buffer->position))
    fatal("buffer overflow");

  return ((byte*) buffer->data) + position;
}
