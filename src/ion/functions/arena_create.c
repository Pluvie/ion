struct arena arena_create (
    uint capacity
)
{
  struct arena allocator = { 0 };
  allocator.capacity = capacity;
  return allocator;
}
