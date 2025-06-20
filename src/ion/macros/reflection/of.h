/**
 * Used to define a nested type in a protocol reflection.
 * Usually seen in presence of pointers, sequences, arrays or vectors. */
#define of(...) \
  .element = &(struct reflection) __VA_ARGS__
