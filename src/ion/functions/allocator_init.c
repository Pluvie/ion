struct allocator allocator_init (
    unsigned int capacity
)
{
  capacity = next_pow2(capacity);
  return (struct allocator) {
    .capacity = capacity
  };
}
