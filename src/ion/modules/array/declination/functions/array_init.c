array(t) array_(init, t) (
    u64 initial_capacity,
    memory* allocator
)
{
capacity_check:
  u64 capacity = next_pow2(initial_capacity);

  if (capacity < ARRAY_CAPACITY_DEFAULT)
    capacity = ARRAY_CAPACITY_DEFAULT;

initialization:
  array(t) array = {
    .capacity = capacity,
    .length = 0,
    .data = memory_alloc_zero(allocator, sizeof(t) * capacity),
    .allocator = allocator
  };

  return array;
}
