/**
 * The `failure` type is used to trace a program failure. */
typedef struct failure {
  bool occurred;
  u32 length;
  u32 trace_count;
  struct {
    char* file;
    u64 line;
  } trace[ERROR_TRACE_CAP];
  char message[496];
} failure;
check_sizeof(failure, 1024);
