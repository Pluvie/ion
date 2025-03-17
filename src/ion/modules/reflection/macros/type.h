/**
 * Used to define a type of a reflection. */
#define type(enum_type, ...)                \
  .type = (enum_type),                      \
  .size = (u64) enum_type ## __SIZE         \
  __VA_OPT__(, .size = sizeof(__VA_ARGS__), \
  .struct_name = &s(#__VA_ARGS__))
