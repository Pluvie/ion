void* memory_move (
    void* target,
    const void* source,
    uint amount
)
{
  return memmove(target, source, amount);
}
