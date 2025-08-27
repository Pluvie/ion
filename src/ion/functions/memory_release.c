void memory_release (
    memory* allocator
)
{
  if (allocator->data != NULL)
    alloc_release(allocator->data);

  for (int i = 0; i < allocator->regions.count; i++)
    alloc_release(allocator->regions.addresses[i]);

  if (allocator->regions.addresses != NULL)
    alloc_release(allocator->regions.addresses);

  zero_out(allocator, sizeof(memory));
}
