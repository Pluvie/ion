struct allocator {
  void* data;
  unsigned int capacity;
  unsigned int position;
  struct {
    void** addresses;
    unsigned int capacity;
    unsigned int count;
  } regions;
  struct {
    unsigned int count;
    unsigned int size;
  } allocations;
};
check_sizeof(64, struct allocator);
