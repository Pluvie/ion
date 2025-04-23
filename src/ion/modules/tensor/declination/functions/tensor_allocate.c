tensor(t)* tensor_allocate(t) (
    array(u64)* dimensions,
    memory* allocator
)
{
  tensor(t)* tensor = memory_alloc_zero(allocator, sizeof(tensor(t)));
  *tensor = tensor_init(t)(dimensions, allocator);

  if (error.occurred)
    return NULL;
  else
    return tensor;
}
