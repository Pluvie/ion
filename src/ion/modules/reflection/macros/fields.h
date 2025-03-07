/**
 * Used to define a struct fields in a protocol reflection. */
#define fields(...)  \
  .fields = &vector_of(struct reflection, __VA_ARGS__)
