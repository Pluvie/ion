void buffer_destroy (
    struct buffer* buffer
)
{
  if (buffer->data != nullptr)
    memory_release(buffer->data);

  memory_set(buffer, 0, sizeof(*buffer));
}
