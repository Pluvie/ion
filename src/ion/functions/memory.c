void* memory_acquire (
    uint amount
)
{
  void* address;

  if (unlikely(amount == 0))
    fatal("memory_acquire: amount must not be zero");

  address = malloc(amount);

  if (unlikely(address == nullptr))
    fatal("memory_acquire: not enough memory");

  return address;
}

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
  address = _aligned_alloc(alignment, amount);
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

int memory_compare (
    void* m1,
    void* m2,
    uint size
)
{
  return memcmp(m1, m2, size);
}

void* memory_copy (
    void* target,
    void* source,
    uint amount
)
{
  return memcpy(target, source, amount);
}

bool memory_equal (
    void* m1,
    void* m2,
    uint size
)
{
  return memcmp(m1, m2, size) == 0;
}

void memory_release (
    void* address
)
{
  free(address);
}

void memory_release_aligned (
    void* aligned_address
)
{
#if standard(>= C11)
#if platform(WINDOWS)
  _aligned_free(aligned_address);
#else
  free(aligned_address);
#endif

#else
  /* C89/C99 compliant implementation of `aligned_free`.

    Frees the address stored just before the `aligned_address`. This was the original
    address returned by malloc. See `memory_acquire_aligned` for more details. */
  free(((byte*) aligned_address) - sizeof(void*));

#endif
}

void* memory_resize (
    void* address,
    uint amount
)
{
  void* new_address;

  if (unlikely(amount == 0))
    fatal("memory_resize: amount must not be zero");

  new_address = realloc(address, amount);

  if (unlikely(new_address == nullptr))
    fatal("memory_resize: not enough memory");

  return new_address;
}

void* memory_set (
    void* target,
    byte value,
    uint amount
)
{
  return memset(target, value, amount);
}
