struct tensor;
struct tensor {
  u64 length;
  u64 typesize;
  void* data;
  struct vector* dimensions;
};
check_sizeof(struct tensor, 32);
