#ifdef string
#undef string
#endif

typedef struct string {
  char* content;
  int length;
} string;
