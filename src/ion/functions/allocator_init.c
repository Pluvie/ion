struct allocator allocator_init (
    uint capacity
)
{
  struct allocator result = { 0 };
  result.capacity = next_pow2(capacity);
  return result;
}
