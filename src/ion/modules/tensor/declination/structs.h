typedef struct {
  u64 length;
  t* data;
  array(u64)* offsets;
  memory* allocator;
} tensor(t);
check_sizeof(tensor(t), 32);

typedef struct {
  t* value;
  u64 dimension;
  u64 index;
  padding(8);
} tensor_iterator(t);
check_sizeof(tensor_iterator(t), 32);
