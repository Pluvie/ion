void* buffer_address_at (
    struct buffer* buffer,
    uint position
)
{
  return ((byte*) buffer->data) + position;
}
