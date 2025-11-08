void* buffer_pop (
    struct buffer* buffer,
    uint amount
)
{
  if (amount > buffer->position)
    buffer->position = 0;
  else
    buffer->position -= amount;

  return buffer_address(buffer);
}
