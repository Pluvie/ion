typedef struct list<T> {
  T* data;
  int length;
  int capacity;
  memory* allocator;
} list<T>;
check_sizeof(32, list<T>);
