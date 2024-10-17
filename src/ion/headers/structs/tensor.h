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
};
check_sizeof(struct tensor_dimension, 16);




struct tensor_range;
struct tensor_range {
  u64 min;
  u64 max;
};
check_sizeof(struct tensor_range, 16);
