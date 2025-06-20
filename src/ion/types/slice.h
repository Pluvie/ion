#ifdef slice
#undef slice
#endif

typedef struct slice {
  void* data;
  int length;
} slice;
