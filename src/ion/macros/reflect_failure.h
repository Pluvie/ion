/**
 * Sets the error with the info coming from the given reflection but using the
 * file and line coming from the caller function. */
#define reflect_failure(reflection)                       \
  reflect_path_failure(reflection, __FILE__, __LINE__)
