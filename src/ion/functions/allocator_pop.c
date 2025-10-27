void* allocator_pop (
    struct allocator* allocator,
    unsigned int amount
)
{
  if (amount > allocator->position)
    allocator->position = 0;
  else
    allocator->position -= amount;

  return allocator->data + allocator->position;
}
