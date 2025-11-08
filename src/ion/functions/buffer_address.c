void* buffer_address (
    struct buffer* buffer
)
{
  return ((byte*) buffer->data) + buffer->position;
}
