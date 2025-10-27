void* allocator_pop (
    struct allocator* allocator,
    uint amount
)
{
  if (amount > allocator->position)
    allocator->position = 0;
  else
    allocator->position -= amount;

  return allocator->data + allocator->position;
}
