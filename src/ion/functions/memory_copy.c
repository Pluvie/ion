void* memory_copy (
    void* target,
    const void* source,
    uint amount
)
{
  return memcpy(target, source, amount);
}
