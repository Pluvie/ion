bool memory_equal (
    const void* v,
    const void* u,
    uint length
)
{
  return memory_compare(v, u, length) == 0;
}
