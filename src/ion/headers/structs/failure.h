struct failure;
/**
 * Explain the login for normalizing all errors. */
struct failure {
  bool occurred;
  u64 length;
  char message[240];
};
check_sizeof(struct failure, 256);
