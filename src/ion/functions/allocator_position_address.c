void* allocator_position_address (
    struct allocator* allocator,
    uint position
)
{
  return ((byte*) allocator->line.data) + position;
}
