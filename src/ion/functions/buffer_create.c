struct buffer buffer_create (
    uint capacity
)
{
  struct buffer allocator = { 0 };
  allocator.capacity = capacity;
  return allocator;
}
