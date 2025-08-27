void* byte_copy (
    void* target,
    void* source,
    int length
)
{
  return memcpy(target, source, length);
}
