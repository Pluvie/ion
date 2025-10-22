typedef struct list<T> {
  T* data;
  unsigned int length;
  unsigned int capacity;
  struct allocator* allocator;
} list<T>;
