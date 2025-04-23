set(t)* set_allocate(t) (
    u64 initial_capacity,
    memory* allocator
)
{
  set(t)* set = memory_alloc(allocator, sizeof(set(t)));
  *set = set_init(t)(initial_capacity, allocator);
  return set;
}
