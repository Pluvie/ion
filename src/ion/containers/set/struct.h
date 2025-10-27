struct N {
  T* data;
  uint length;
  uint capacity;
  uint load_limit;
  uint* hashes;
  struct allocator* allocator;
};
