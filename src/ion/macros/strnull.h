/**
 * Helper to check if a string is null. */
#define strnull(s)            \
  _Generic((s),               \
    string : strnull<string>, \
    char* : strnull<char*>    \
  )(s)
