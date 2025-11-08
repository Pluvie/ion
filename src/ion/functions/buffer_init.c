struct buffer buffer_init (
    uint capacity
)
{
  struct buffer result = { 0 };
  result.capacity = capacity;
  return result;
}
