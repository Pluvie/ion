memory memory_init (
    int initial_capacity
)
{
  memory allocator = { 0 };

  if (initial_capacity <= 0)
    return allocator;

  allocator.capacity = next_pow2(initial_capacity);
  return allocator;
}
