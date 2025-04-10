u64 buffer_alloc_zero (
    buffer* allocator,
    u64 amount
)
{
  u64 position = buffer_alloc(allocator, amount);
  memzero(buffer_data(allocator, position), amount);
  return position;
}
