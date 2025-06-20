typedef struct set<T> {
  T* data;
  int length;
  int capacity;
  int load_limit;
  int* hashes;
  memory* allocator;
} set<T>;
check_sizeof(48, set<T>);
