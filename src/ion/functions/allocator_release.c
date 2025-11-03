void allocator_release (
    struct allocator* allocator
)
{
  struct allocator_arena* arena = &(allocator->arena);
  struct allocator_line* line = &(allocator->line);

  uint region_index;
  for (region_index = 0; region_index < arena->regions.count; region_index++)
    memory_release(arena->regions.addresses[region_index]);

  if (arena->regions.addresses != nullptr)
    memory_release(arena->regions.addresses);

  if (arena->data != nullptr)
    memory_release(arena->data);

  if (line->data != nullptr)
    memory_release(line->data);

  memory_set(allocator, 0, sizeof(*allocator));
}
