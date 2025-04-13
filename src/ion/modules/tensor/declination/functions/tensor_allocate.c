tensor(t)* tensor_allocate(t) (
    array(u64)* dimensions,
    memory* allocator
)
{
  tensor(t)* tns = memory_alloc_zero(allocator, sizeof(tensor(t)));
  *tns = tensor_init(t)(dimensions, allocator);

  if (error.occurred)
    return NULL;
  else
    return tns;
}
