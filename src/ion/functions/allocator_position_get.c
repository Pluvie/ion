uint allocator_position_get (
    struct allocator* allocator
)
{
  return allocator->line.position;
}
