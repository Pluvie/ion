/**
 * Used to define a struct field in a reflection. */
#define field(name_var, enum_type, struct_type, ...)                    \
  .name = &s(#name_var),                                                \
  .type = (enum_type),                                                  \
  .offset = offsetof(struct_type, __VA_OPT__(__VA_ARGS__.)name_var)     \
    __VA_OPT__(- offsetof(struct_type, __VA_ARGS__)),                   \
  .size = sizeof(((struct_type*)0)->__VA_OPT__(__VA_ARGS__.)name_var)
