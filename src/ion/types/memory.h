#ifdef NULL
#undef NULL
#endif

#define NULL ((void*)0)

#ifdef memory
#undef memory
#endif

typedef struct memory {
  void* data;
  int capacity;
  int position;
  struct {
    void** addresses;
    int capacity;
    int count;
  } regions;
  struct {
    int count;
    int size;
  } allocations;
} memory;
check_sizeof(64, memory);
