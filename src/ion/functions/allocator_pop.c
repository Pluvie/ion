void* allocator_pop (
    struct allocator* allocator,
    uint amount
)
{
  struct allocator_arena* arena = &(allocator->arena);

  if (amount > arena->position)
    arena->position = 0;
  else
    arena->position -= amount;

  return arena->data + arena->position;
}
