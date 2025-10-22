typedef struct set<T> {
  T* data;
  unsigned int length;
  unsigned int capacity;
  unsigned int load_limit;
  unsigned int* hashes;
  struct allocator* allocator;
} set<T>;
