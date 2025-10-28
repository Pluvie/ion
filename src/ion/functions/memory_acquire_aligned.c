void* memory_acquire_aligned (
    uint amount,
    uint alignment
)
{
  void* address;

  if (unlikely(amount == 0))
    fatal("memory_acquire_aligned: amount must not be zero");

  alignment = next_pow2(alignment);

#if standard(>= C11)
#if platform(WINDOWS)
  address = _aligned_malloc(alignment, amount);
#else
  address = aligned_alloc(alignment, amount);
#endif

  if (unlikely(address == nullptr))
    fatal("memory_acquire_aligned: not enough memory");

#else
  /* C89/C99 compliant implementation of `aligned_alloc`.

    First, an `address` is acquired using malloc. The space requested is enough
    to hold the `amount` -- obviously -- plus the `aligment` and the size of `void*`.

    The `aligment` is added because malloc might not return an aligned address to the
    given boundary, so we must have to offset it. The highest amount of offset is equal
    to `aligment`. Suppose `aligment` is 32 and malloc returns 65. The next valid
    aligment after 65 is 96, so exactly 31 bytes more.

    The size of `void*` is because we will store here the address returned by malloc.
    This shall be passed to the `memory_release_aligned` function because that function
    must correctly free the original malloc returned address, and not what will be
    returned by this function. */

  address = malloc(sizeof(void*) + amount + alignment);

  if (unlikely(address == nullptr))
    fatal("memory_acquire_aligned: not enough memory");

  {
    void* alloc_address = address;
    uint top_address = (uint) alloc_address + sizeof(void*) + alignment;
    uint aligned_address = top_address - (top_address % alignment);

    address = (void*) aligned_address;
    memory_set(((byte*) address) - sizeof(void*), (uint) alloc_address, sizeof(void*));
  }

#endif

  return address;
}
