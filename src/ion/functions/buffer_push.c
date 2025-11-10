void* buffer_push (
    struct buffer* buffer,
    uint amount
)
{
  byte* address;
  uint new_capacity;

  if (buffer->data == nullptr)
    goto allocate_buffer;
  else if (buffer->position + amount <= buffer->capacity)
    goto extend_buffer;
  else
    goto reallocate_buffer;

allocate_buffer:
  if (amount > buffer->capacity)
    buffer->capacity = amount;

  buffer->position = 0;
  buffer->data = memory_acquire(buffer->capacity);
  goto extend_buffer;

reallocate_buffer:
  new_capacity = 2*buffer->capacity;
  if (amount + buffer->position > new_capacity)
    new_capacity = amount + buffer->position;

  buffer->data = memory_resize(buffer->data, new_capacity);
  buffer->capacity = new_capacity;

extend_buffer:
  address = buffer_address(buffer);
  buffer->position += amount;
  buffer->allocations.size += amount;
  buffer->allocations.count++;
  return address;
}
