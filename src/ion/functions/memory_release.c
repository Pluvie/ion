void memory_release (
    memory* allocator
)
{
  if (allocator->data != NULL)
    free(allocator->data);

  for (int i = 0; i < allocator->regions.count; i++)
    free(allocator->regions.addresses[i]);

  if (allocator->regions.addresses != NULL)
    free(allocator->regions.addresses);

  memzero(allocator, sizeof(memory));
}
