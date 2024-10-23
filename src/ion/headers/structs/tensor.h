struct tensor;
struct tensor {
  u64 length;
  u64 typesize;
  void* data;
  struct vector* dimensions;
};
check_sizeof(struct tensor, 32);




struct tensor_dimension;
struct tensor_dimension {
  u64 length;
  u64 offset;
  u64 cursor;
  padding(8);
};
check_sizeof(struct tensor_dimension, 32);
