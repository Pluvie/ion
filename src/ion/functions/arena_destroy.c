void arena_destroy (
    struct arena* allocator
)
{
  uint region_index;
  for (region_index = 0; region_index < allocator->regions.count; region_index++)
    memory_release(allocator->regions.addresses[region_index]);

  if (allocator->regions.addresses != nullptr)
    memory_release(allocator->regions.addresses);

  if (allocator->data != nullptr)
    memory_release(allocator->data);

  memory_set(allocator, 0, sizeof(*allocator));
}
