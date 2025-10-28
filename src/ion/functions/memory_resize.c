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
