typedef struct {
  u64 capacity;
  u64 length;
  u64* hashes;
  t* elements;
  u64 load_limit;
  memory* allocator;
  padding(16);
} set(t);
check_sizeof(set(t), 64);

typedef struct {
  t* element;
  u64 index;
} set_iterator(t);
check_sizeof(set_iterator(t), 16);
