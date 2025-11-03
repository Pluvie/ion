struct allocator allocator_init (
    uint capacity
)
{
  struct allocator result = { 0 };
  result.arena.capacity = next_pow2(capacity);
  result.line.capacity = next_pow2(capacity);
  return result;
}
