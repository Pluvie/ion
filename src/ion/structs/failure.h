struct failure;
/**
 * Explain the login for normalizing all errors. */
struct failure {
  bool occurred;
  u32 length;
  char* file;
  u64 line;
  char message[488];
};
check_sizeof(struct failure, 512);
