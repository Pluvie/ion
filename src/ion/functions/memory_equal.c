bool memory_equal (
    void* m1,
    void* m2,
    unsigned int size
)
{
  return memcmp(m1, m2, size) == 0;
}
