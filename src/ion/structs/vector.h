struct vector;
struct vector {
  u64 length;
  u64 typesize;
  void* data;
  padding(8);
};
check_sizeof(struct vector, 32);
