array(t)* array_allocate(t) (
    u64 initial_capacity,
    memory* allocator
)
{
  array(t)* ary = memory_alloc_zero(allocator, sizeof(array(t)));
  *ary = array_init(t)(initial_capacity, allocator);
  return ary;
}
