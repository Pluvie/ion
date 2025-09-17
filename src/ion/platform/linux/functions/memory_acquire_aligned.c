void* platform_memory_acquire_aligned (
    unsigned int amount,
    unsigned int alignment
)
{
  void* address;
  alignment = next_pow2(alignment);

  int result = posix_memalign(&address, alignment, amount);

  if (likely(result == 0))
    return address;
  else
    return nullptr;
}
