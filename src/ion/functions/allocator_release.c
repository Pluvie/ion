void allocator_release (
    struct allocator* allocator
)
{
  if (allocator->data != nullptr)
    memory_release(allocator->data);

  for (int i = 0; i < allocator->regions.count; i++)
    memory_release(allocator->regions.addresses[i]);

  if (allocator->regions.addresses != nullptr)
    memory_release(allocator->regions.addresses);

  memory_set(allocator, 0, sizeof(*allocator));
}
