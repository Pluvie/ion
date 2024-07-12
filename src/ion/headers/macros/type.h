/**
 * Used to define a type of a protocol schema. */
#define type(type_name, ...)            \
  .type = type_name __VA_OPT__(, .bounds = __VA_ARGS__, .child = (struct reflect []))
