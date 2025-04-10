void* memory_alloc_zero (
    memory* allocator,
    u64 amount
)
{
  void* address = memory_alloc(allocator, amount);
  memzero(address, amount);
  return address;
}
