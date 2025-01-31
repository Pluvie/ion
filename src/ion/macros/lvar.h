/**
 * Generates a unique variable name using the line number. */
#define lvar(name) \
  compile_concat(name, __LINE__)
