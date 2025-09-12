
  void* new_address;

  if (unlikely(amount <= 0))
    fatal("memory_resize: must have a positive amount");

  new_address = realloc(address, amount);
  if (unlikely(address == nullptr))
    fatal("memory_resize: not enough memory");

  if (alignment <= 0)
    return new_address;

  alignment = next_pow2(alignment);
  if (((unsigned int) new_address & (alignment - 1)) == 0)
    return new_address;

  void* aligned_new_address;
  int result = posix_memalign(&aligned_new_address, alignment, amount);

  if (unlikely(result != 0))
    fatal("memory_resize: alignment failure");

  return aligned_new_address;
