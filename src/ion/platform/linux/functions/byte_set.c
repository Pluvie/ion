static inline void* byte_set (
    void* target,
    int value,
    int length
)
{
  return memset(target, value, length);
}
