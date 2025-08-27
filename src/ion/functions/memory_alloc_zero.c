void* memory_alloc_zero (
    memory* allocator,
    int amount
)
{
  void* address = memory_alloc(allocator, amount);
  zero_out(address, amount);
  return address;
}
