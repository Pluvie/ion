/**
 * Used to define a type of a reflection. */
#define type(enum_type, ...)                \
  .type = (enum_type),                      \
  .size = type_sizes[enum_type]             \
  __VA_OPT__(, .size = sizeof(__VA_ARGS__))
