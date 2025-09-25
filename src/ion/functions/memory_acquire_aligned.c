void* memory_acquire_aligned (
    unsigned int amount,
    unsigned int alignment
)
{
  if (unlikely(amount == 0))
    fatal("memory_acquire_aligned: amount must not be zero");

  alignment = next_pow2(alignment);
  void* address = aligned_alloc(alignment, amount);

  if (unlikely(address == nullptr))
    fatal("memory_acquire_aligned: not enough memory");

  return address;
}
