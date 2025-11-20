void* buffer_push (
    struct buffer* allocator,
    uint amount
)
{
  byte* address;
  uint new_capacity;

  if (allocator->data == nullptr)
    goto allocate_buffer;
  else if (allocator->position + amount <= allocator->capacity)
    goto extend_buffer;
  else
    goto reallocate_buffer;

allocate_buffer:
  if (amount > allocator->capacity)
    allocator->capacity = amount;

  allocator->position = 0;
  allocator->data = memory_acquire(allocator->capacity);
  goto extend_buffer;

reallocate_buffer:
  new_capacity = 2*allocator->capacity;
  if (amount + allocator->position > new_capacity)
    new_capacity = amount + allocator->position;

  allocator->data = memory_resize(allocator->data, new_capacity);
  allocator->capacity = new_capacity;

extend_buffer:
  address = buffer_pointer(allocator);
  allocator->position += amount;
  return address;
}
