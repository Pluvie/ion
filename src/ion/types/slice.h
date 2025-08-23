#ifdef slice
#undef slice
#endif

typedef struct slice {
  void* pointer;
  int length;
} slice;
