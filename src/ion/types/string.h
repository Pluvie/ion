#ifdef string
#undef string
#endif

typedef struct string {
  void* pointer;
  int length;
} string;
