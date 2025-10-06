typedef struct list<T> {
  T* data;
  unsigned int length;
  unsigned int capacity;
  struct allocator* allocator;
} list<T>;
check_sizeof(32, list<T>);
