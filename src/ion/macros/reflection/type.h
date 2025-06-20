/**
 * Used to define a type of a reflection. */
#define type(enum_type, ...)                        \
  .type = (enum_type),                              \
  .size = (int) enum_type ## __SIZE                 \
  __VA_OPT__(, .size = sizeof(__VA_ARGS__),         \
  .type_name = s(compile_stringize(__VA_ARGS__)))
