void* memory_alloc_zero (
    struct memory* allocator,
    u64 amount
)
{
  void* address = memory_alloc(allocator, amount);
  bzero(address, amount);
  return address;
}
