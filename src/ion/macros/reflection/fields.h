/**
 * Used to define a struct fields in a protocol reflection. */
#define fields(...)  \
  .fields = &list(struct reflection, __VA_ARGS__)
