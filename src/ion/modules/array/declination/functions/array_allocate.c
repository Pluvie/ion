array(t)* array_(allocate, t) (
    u64 initial_capacity,
    memory* allocator
)
{
  array(t)* array = memory_alloc_zero(allocator, sizeof(array(t)));
  *array = array_(init, t)(initial_capacity, allocator);
  return array;
}
