void* buffer_pointer (
    struct buffer* allocator
)
{
  return ((byte*) allocator->data) + allocator->position;
}
