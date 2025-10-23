struct str_builder str_builder (
    unsigned int capacity
)
{
  struct str_builder builder = { 0 };
  if (capacity > 0) {
    builder.capacity = capacity;
    builder.memory = memory_acquire(capacity);
  }
  return builder;
}
