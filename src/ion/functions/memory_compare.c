int memory_compare (
    const void* v,
    const void* u,
    uint length
)
{
  if (v == nullptr && u == nullptr)
    return 0;

  if (v != nullptr && u == nullptr)
    return 1;

  if (v == nullptr && u != nullptr)
    return -1;

  return memcmp(v, u, length);
}
