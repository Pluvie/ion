/**
 * Used to define a struct fields in a protocol reflection. */
#define fields(...)  \
  .child = &vector_of(struct reflect, __VA_ARGS__)
