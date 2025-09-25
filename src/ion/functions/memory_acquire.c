void* memory_acquire (
    unsigned int amount
)
{
  if (unlikely(amount == 0))
    fatal("memory_acquire: amount must not be zero");

  void* address = malloc(amount);

  if (unlikely(address == nullptr))
    fatal("memory_acquire: not enough memory");

  return address;
}
