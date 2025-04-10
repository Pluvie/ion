void* buffer_data (
    buffer* allocator,
    u64 position
)
{
  return allocator->data + position;
}
