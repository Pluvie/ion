void* memory_resize (
    void* address,
    unsigned int amount
)
{
  void* new_address;

  new_address = realloc(address, amount);
  if (unlikely(address == nullptr))
    fatal("memory_resize: not enough memory");

  return new_address;
}
