#ifdef string
#undef string
#endif

typedef struct string {
  char* pointer;
  int length;
} string;
