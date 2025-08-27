static inline int byte_compare (
    void* v1,
    void* v2,
    int len
)
{
  return memcmp(v1, v2, len);
}
