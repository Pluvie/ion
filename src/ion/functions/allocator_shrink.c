uint allocator_shrink (
    struct allocator* allocator,
    uint amount
)
{
  if (amount > allocator->line.position)
    allocator->line.position = 0;
  else
    allocator->line.position -= amount;

  return allocator_position_get(allocator);
}
