struct failure;
/**
 * Explain the login for normalizing all errors. */
struct failure {
  bool occurred;
  u32 length;
  char message[248];
};
check_sizeof(struct failure, 256);
