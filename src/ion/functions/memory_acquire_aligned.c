void* memory_acquire_aligned (
    unsigned int amount,
    unsigned int alignment
)
{
  if (unlikely(amount == 0))
    fatal("memory_acquire_aligned: amount must not be zero");

  alignment = next_pow2(alignment);

#if standard(>= C11)
  void* address = aligned_alloc(alignment, amount);

  if (unlikely(address == nullptr))
    fatal("memory_acquire_aligned: not enough memory");

#else
  /*
    C99 compliant implementation of `aligned_alloc`.

    First, an `alloc_address` is acquired using malloc. The space requested is enough
    to hold the `amount` -- obviously -- plus the `aligment` and the size of `void*`.

    The `aligment` is added because malloc might not return an aligned address to the
    given boundary, so we must have to offset it. The highest amount of offset is equal
    to `aligment`. Suppose `aligment` is 32 and malloc returns 65. The next valid
    aligment after 65 is 96, so exactly 31 bytes more.

    The size of `void*` is because we will store here the address returned by malloc.
    This shall be passed to the `memory_release_aligned` function because that function
    must correctly free the original malloc returned address, and not what will be
    returned by this function.
  */
  void* alloc_address = malloc(sizeof(void*) + amount + alignment);

  if (unlikely(alloc_address == nullptr))
    fatal("memory_acquire_aligned: not enough memory");

  unsigned int top_address = (unsigned int) alloc_address + sizeof(void*) + alignment;
  unsigned int aligned_address = top_address - (top_address % alignment);
  void* address = (void*) aligned_address;
  memory_set(address - sizeof(void*), (unsigned int) alloc_address, sizeof(void*));

#endif

  return address;
}
