buffer buffer_init (
    u64 initial_capacity
)
{
capacity_check:
  u64 capacity = next_pow2(initial_capacity);
  if (capacity < MEMORY_DEFAULT_CAPACITY)
    capacity = MEMORY_DEFAULT_CAPACITY;

initialize:
  buffer allocator = {
    .capacity = capacity,
    .position = 0,
    .data = NULL
  };

  return allocator;
}
