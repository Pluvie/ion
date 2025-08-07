/**
 * Used to define the container related functions in a reflection. */
#define container(...) \
  .container_adder = __VA_ARGS__ ## reflection_adder, \
  .container_creator = __VA_ARGS__ ## reflection_creator
