
  void* address;

  if (unlikely(amount <= 0))
    fatal("memory_require: must have a positive amount");

  if (alignment > 0)
    goto require_aligned;
  else
    goto require_unaligned;

require_unaligned:
  address = malloc(amount);
  if (unlikely(address == nullptr))
    fatal("memory_require: not enough memory");

  return address;

require_aligned:
  alignment = next_pow2(alignment);
  int result = posix_memalign(&address, alignment, amount);

  if (unlikely(result != 0))
    fatal("memory_require: alignment failure");

  return address;
