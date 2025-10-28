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
