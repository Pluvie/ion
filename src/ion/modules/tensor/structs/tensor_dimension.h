struct tensor_dimension;
struct tensor_dimension {
  u64 length;
  u64 offset;
  u64 cursor;
  padding(8);
};
check_sizeof(struct tensor_dimension, 32);
