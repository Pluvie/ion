/**
 * Used to define a nested type in a protocol schema.
 * Usually seen in presence of pointers, sequences, arrays or vectors. */
#define of(...) \
  .child = &vector_of(struct reflect, { __VA_ARGS__ })
