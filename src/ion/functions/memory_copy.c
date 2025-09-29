void* memory_copy (
    void* target,
    void* source,
    unsigned int amount
)
{
  return memcpy(target, source, amount);
}
