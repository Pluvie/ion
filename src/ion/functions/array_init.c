struct array array_init (
    u64 typesize,
    u64 initial_capacity,
    struct memory* allocator
)
{
capacity_check:
  initialize(capacity, u64,
    call(next_pow2, initial_capacity));

  if (capacity < ARRAY_DEFAULT_CAP)
    capacity = ARRAY_DEFAULT_CAP;

initialization:
  initialize(array, struct array, {
    .capacity = capacity,
    .length = 0,
    .typesize = typesize,
    .data = call(memory_alloc_zero, allocator, typesize * capacity),
    .allocator = allocator
  });

  return array;
}
