set(t)* set_allocate(t) (
    u64 initial_capacity,
    memory* allocator
)
{
  set(t)* s = memory_alloc(allocator, sizeof(set(t)));
  *s = set_init(t)(initial_capacity, allocator);
  return s;
}
