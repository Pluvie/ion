void* memory_set (
    void* target,
    byte value,
    uint amount
)
{
  return memset(target, value, amount);
}
