/*
  This macro tests the equality of two pointers of the same type.
*/
#define eq(v1, v2, ...) \
  (_Generic(v1,         \
    char*   : strcmp,   \
    default : memcmp    \
  )(v1, v2 __VA_OPT__(, __VA_ARGS__)) == 0)
