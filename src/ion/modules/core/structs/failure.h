struct failure;
/**
 * Explain the logic for normalizing all errors. */
struct failure {
  bool occurred;
  u32 length;
  u32 trace_count;
  struct {
    char* file;
    u64 line;
  } trace[ERROR_TRACE_CAP];
  char message[496];
};
check_sizeof(struct failure, 1024);
