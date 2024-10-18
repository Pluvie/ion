#ifdef ION_INCLUDED
static inline
#endif

void* memory_alloc_zero (
    struct memory* allocator,
    u64 amount
)
{
  void* address = memory_alloc(allocator, amount);
  memzero(address, amount);
  return address;
}
