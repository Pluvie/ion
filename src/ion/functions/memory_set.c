void* memory_set (
    void* target,
    unsigned char byte_value,
    unsigned int amount
)
{
  return memset(target, byte_value, amount);
}
