struct tensor;
struct tensor {
  u64 length;
  u64 typesize;
  void* data;
  struct vector* dimensions;
  struct vector* offsets;
  struct memory* allocator;
  padding(16);
};
check_sizeof(struct tensor, 64);
